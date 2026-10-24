### Contributing

This is an in-house project, that's being developed by me alone. I will be taking NO contributions in the form of PRs.
I will take any issues anyone has in the issues tab. However, this project is still open source so this document will
detail the things needed to contribute to the project, because it can help with the submission of issues and for the
general understanding of the project itself. This documents will cover the following thing(s):

+ Technical Stack
+ Project Structure
+ Code Style

You can read the entire thing from top to bottom, but you can also select one point of interest as well.

### Technical Stack

```
----------    ----------------------------------------------------
|Start.rb| <- |Other Scripts | Native Extension(Dynamic Library) | 
----------    ----------------------------------------------------
      | Binary Executable & Static Library
--------------
|Game | mruby|
--------------
      | Dynamic Library
--------------------     --------
|SDL3 | SDL3_mixer | <-> |Physfs|
--------------------     --------
```

At the very top of the stack are the scripts that `game` executes. These scripts are your game or program. By default `game`
uses a starter script called `Start.rb` as its entry point, but this can be changed with an environment variable like this:
`GAME_START_PATH=Init.rb game`. More scripts, and native extensions can be loaded-in from `Start.rb` using the methods:
`load_mrb` and `load_native` respectively. That may look something like this:

```ruby
# Entry Point
load_native 'CustomRenderer.so'
load_mrb    'SceneManager.rb'
```

In a typical `Ruby` interpreter you might expect to pass script(s) as an argument to the interpreter like this: `ruby foo.rb`
but command-line arguments are reserved for the scripts alone, not for `game`. This is because the code *is the interface*.
The `game` executable use environment variables that it recognizes as well as ones the SDL3 recognizes to influance how it
runs but that's it, in terms of user-interface. Here are a list of environment variables that `game` uses:

+ `GAME_PHYSFS_ARCHIVE`
+ `GAME_START_PATH`
+ `GAME_NO_GRAPHICS`
+ `GAME_NO_INPUT`
+ `GAME_NO_AUDIO`

To find `SDL3`'s environment variables go [*here*](https://wiki.libsdl.org/SDL3/CategoryHints), just remove the word "HINT" a
there you go, for example: `SDL_HINT_AUDIO_DRIVER` is `SDL_AUDIO_DRIVER`.

The last three environment variables prefixed with `GAME_NO_*` are used to turn off specific subsystems. The `game` executable
can run in a pretty dynamic way, let's say you're streaming music from a headless server, you can turn off the graphics, and
input subsystems and just play audio. What this does is, it won't even define the built-in classes and modules within those
subsystems. This can save some memory, but it also cuts off the chances of accidentally using code that just won't work in
certain environments.

The `GAME_PHYSFS_ARCHIVE` is useful for when you want to run your game or program from inside an archive of some kind.
When in this environment the `File` class and the `FileUtils::Stat` module, will use an abstract virtual filesystem,
provided by `Physfs`, instead of the usual virtual filesystem provided by `SDL3`. You can find a list of supported archives
[*here*](https://wiki.icculus.org/PhysicsFS3/CategoryPhysicsFS). `Physfs` also allows you to be able to create your own
abstract virtual filesystem designed for your own custom archive format if you're so inclined. Here's an example of how to
use `GAME_PHYSFS_ARCHIVE`: `GAME_PHYSFS_ARCHIVE=GameData.zip game`, `Start.rb` and all of the scripts and other assets must
all be in the same archive!

Embedded inside of the `game` executable is `mruby`; a lightweight, low-memory footprint, bytecode virtual-machine.
It's custom built to include most of `Ruby`'s core API, so all the standard stuff is there `Array`, `String`, `Hash`,
etc. The `mruby` static library is designed to be customized, so it can easily be re-built with more or less things,
if you wish and then statically re-linked into this project to be better for your needs. The mainline `mruby` project
uses a system called `mrbgems` for this, but my project is not an `mrbgem`. The `game` interpreter is built outside of
that ecosystem because it has its own built-in Game API that is core to the `game` interpreter itself and should not
be removed, so it wouldn't make sense for the Game API to be just another `mrbgem`, so it uses `mruby` outside of the
`mrbgem` ecosystem.

The Game API does more than just wrap the underlying `C` APIs in `Ruby` it abstracts them in a particular way to meet
the goals of the Game project in general. I could give you a laundry list of goals but, the goals can be summed up with
once statement, to *reduce cognitive load*. As a matter of fact, that desire has influanced the entire design of the
`game` interpreter period, but it's most pertinent to state that, goal explicitly when taking about the Game API.
Typically developers make direct wrappers over low-level libraries, in such a wrapper you may see something like this:
`SDL_Init()` in `C` may become `SDL.init` in `Ruby`. Another pattern that such wrappers follow, especially wrappers
intended for game development is to wrap manual management functions into `Ruby` by implementing a method for certain
objects and call it something like `dispose` or `destroy`.

Even though there may be good reasoning behind these patterns, I think they miss the point. The purpose of a high-level
programming environment is to reduce cognitive load, this is something that low-level programming environments can't
afford to do because they're operating a level where performance is crititcal. This is because low-level code is
ostensibly foundational, think operating system kernels, drivers, or virtual machines. They do the heavy lifting so that
applications and utilties can focus on their own specific domains, such as game development, or automation. High-level
developers should expect that the floor they walk on is solid, so that they can move from places to place without
having to wonder if the floor beneath them might cave in!

This is why I prefer automatic memory management in the form of Garbage Collection, and why the Game API uses it, instead
of implmenting a bunch of `dispose` methods everywhere. The Game API is takes full advantage of dynamic typing, Object-
Oriented Programming(at least on the API level), and as I mentioned before Garbage Collection. Now, the developer only has
to think about the things that are pertinent to their project. This is not a good solution for all situations though,
and when you must(e.g. you notice an perticular routine is going too slow) you can drop down to the level of `C` and
take advantage of a low-level environment. In life there is no such thing as a one size fits all solution to everything,
and I won't pretend like there is, use the best tool for the job!

The desired level of abstraction for the Game API as it relates to `SDL3` is to take advantage of all reasonable parts of
`SDL3`. I've left out some parts from `SDL3` because they either didn't align with the goals of the Game project or
because I determined them to be too low-level to be properly represented in `Ruby`. Below are some of those parts of `SDL3`
that I left out and why:

#### Doesn't Match Game's goals:
+ Application Entry Point
+ Surfaces
+ Multithreading
+ Storage Anstraction
+ ASync I/O
+ Locale Info
#### Too low-level:
+ Pixel Formats and Conversions
+ Vulkan, Metal and OpenXR
+ Sensors, HIDAPI
+ SDL3's Audio Playback - SDL_Mixer is used instead
+ SDL3's GPU Rendering and Compute
+ CPU Information
#### Too system specific:
+ File Dialogs
+ System Tray

##### Application Entry Point
The `game` executable is a platform onto its own self. It doesn't make sense to run this platform from another platform.

#### Surfaces
Surfaces have been outmoded by Textures, not only are Textures faster because they can be run on the GPU but they also
can be run on a software renderer too, making them more flexible! Surfaces are only useful when you need quick pixel
manipulation.

#### Multithreading
Ruby is not a multithreaded language, and I'm not going to force it to be.

#### Storage Anstraction
Adding this will only add more complxity and cognitive load. All you need for file management is a virtual filesystem.

#### ASync I/O
This is a specialized feature, and this is excluded to focus solely on the more commonly used and easier to understand
synchronous I/O.

#### Locale Info
This can be retrieved using the built-in `ENV` module to access the systems environment variables that hold this locale
info.

#### Pixel Formats and Conversions
These operartions are inharently low-level and require as much low-level control over bit as possible. These are also
highly specialized as well and won't at all be commonly used.

#### Vulkan, Metal and OpenXR
The Game API already has a generic renderer that performs fast texture rendering and EASILY! These offer low-level
fine-grained control, which is only good if you're implementing a renderer yourself. Plus these are HARD to use!

#### Sensors, HIDAPI
These offer low-level and fine-grained control and should only be used when implementing a device object.

#### SDL3's Audio Playback - SDL_Mixer is used instead
Outside of recording, SDL3_mixer provides better and much easier to use abstractions, ontop of useful mixing functions.

#### SDL3's GPU Rendering and Compute
See **Vulkan, Metal and OpenXR**!

#### CPU Information
These are often compiler intrinsics and are literally only useful if you're programming in `C`.

#### File Dialogs & System Tray
The `game` executable is a platform itself, and shouldn't have built-in features that are going to be features of
certain desktop or mobile operating system. The `game` executable can be targeted at embedded systems, using only
a kernel(e.g. Linux) which won't necessarliy have such a concept as a "System Tray".

Everything listed above can be implemented using the Natvie Extension API to build a Native Extension that gets loaded-in
at runtime using `load_native`. For instance an art creation program can shut off the Graphics Subsystem, and implement
their own surface based renderer as a Native Extension, and use surfaces for drawing and pixel manipulation!

Everything chosen for the technical stack is chosen because they are all cross-platform so the whole of the Game
platform can be targeted to run on different systems. This reduces cognitive load, because this effectively implements
"write once, run anyware." A high-level developer shouldn't need to think about the details of the underlying system
unless it's absolutely necessary. What you effectively get are game/programs written as scripts that can run not just
on the system they were written, but also systems that may not even exist yet! All this while preserving its reduction
of cognitive load!

Lastly, interpreters are ostensibly open platforms, but `game` doesn't have to be. If so desired, one can reap the benefits
of the fast development provided by the on-the-fly execution of programs, and ship a custom propritary archive using `Physfs`.
The `game` interpreter can also run compiled bytecode, so for some developers an ideal shippment may be byecode in an
encrypted archive format. I personally don't recommend this, because things like this are basically a cat and mouse game,
but I understand that for some it may not be a choice, higher ups may demand it, so I give a way to do it.

The `game` executable's execution model makes it very flexible and can be put into bundle formats like `flatpak`, `AppImage`,
or `MacOS` bundles, or whatever.

### Project Structure

```
+ Include
  + Native
+ Src
+ Mrblib
+ Tasks
+ Tests
```

+ Include - All header and source(usually bytecode arrays) files meant to be included.
+ Include/Native - The Native Extension API is all headers(no static or dynamic libraries). This gets installed.
+ Src - All source of the code that will be built into `game`.
+ Mrblib - Ruby scripts. These will usually be compiled into a bytecode array and that output, moved to Include.
+ Tasks - Ruby scripts for MRI that implement automation for building, testing, etc.
+ Tests - All tests for the `game`.

You're free to do whatever you want with this project, just as long as its within the bounrdires set by the MIT License!
Some things you may want to do are:

+ Use a different memory allocation library(`dlmalloc` is used by default.)
+ Perhaps add, additional embedded runtimes(e.g. `Lua`.)
+ Maybe you do actually want to use "Application Entry Points".
+ etc.

If Native Extensions aren't enough you can ship a modified `game` and call it whatever you want, like `plat` of whatever.

### Code Style

I believe strongly that good coding style isn't something that can be perfectly articulated with step-by-step intstructions.
A lot of things are about *"good taste"*, and *"good taste"* is intuitive, with that being said, I'll try my best to use this
section as a way to guide, rather than dictate!

`Ruby` is spiritually a `LISP` language, it's flexible. Instead of fighting this by enforcing rigid rules about how to use it,
I will flow with what makes this language what it is. Some things will feel more nautral to do, because of the style in-which
the Game API is written in, so indeed this API does have a style and a couple of paradigms in is written it. So go with the
flow!

The Game API is foundationally Object-Oriented, but the way the API is used in a more declarative style! Here's an example:

```ruby
image = Image.new 'Parallax.bmp'

image.dest.x += speed if horizontal?
image.dest.y += speed if vertical?

image.update
```

So keep this in mind when coding.

As far as the `C` code, I try to follow conventions set by SDL3. So function names may looks like this: `GetWindow()`.
SDL3 uses `bool` instead of `int` now for error status, so I do the same. Think of the internals as an abstraction of
`SDL3` more than anything. Internal `C` code should be decoupled from the `mruby` methods that bind them, because
some one may want to add more than one runtime, this way they don't have to douplicate the code for that other language.

The things mentioned above were more specific examples, but to wrap things up, follow these *clean code* principals and
let them be your guide to coding for and with `game`:

+ **Ruthless Simplicity** - Remove unnecessary concepts, mechanisms, dependencies, and abstractions so the system contains
only complexity that genuinely earns its place.

+ **KISS (Keep It Simple, Stupid)** - When multiple solutions work, prefer the one whose behavior and implementation require
the least mental effort to understand.

+ **Explicitness** - Make important behavior, dependencies, and decisions visible rather than hiding them behind implicit
mechanisms or clever abstractions.

+ **Locality** - Keep related behavior and knowledge close together so understanding one part of the system doesn't require
exploring distant parts of it.

+ **Minimize Coupling** - Keep components as independent as reasonably possible so changing or understanding one component
doesn't require understanding everything connected to it.

+ **Separation of Concerns** - Keep fundamentally different responsibilities distinct so each part of the system has a narrow
conceptual scope.

+ **Consistency** - Once you've established a good pattern, reuse it throughout the system so learning one part teaches you
how other parts work.

+ **YAGNI (You Aren't Gonna Need It)** - Don't build machinery for hypothetical requirements because every unnecessary feature
becomes something future programmers must understand and maintain.
