![Header](https://i.imgur.com/m6hEuEI.png)
### Game

### Introduction

A lightweight `Ruby` interpreter based on `mruby` and its low-memory footprint bytecode virtual-machine. It's built
on top of `SDL3`, and `PhysFS` for built-in hardware and filesystem abstraction. This makes it good for:

+ Game Engines
+ Home Labbing
+ Embedded Systems
+ Robotics
+ Desktop and Mobile Applications

### How to Build

Ruby is required to run the rake tasks used to `build`, `test`, `install`, `uninstall`, and `clean`. Just run this command: `rake` or `rake -s` for a silent build.

The Game Platform depends on these packages:

+ [`game-mruby`](https://github.com/stalbordboat/game-mruby)
+ [`SDL3`](https://github.com/libsdl-org/SDL/tree/release-3.4.x)
+ [`PhysFS`](https://github.com/icculus/physfs/tree/stable-3.2)
+ [`sdl3-mixer`](https://github.com/libsdl-org/SDL_mixer/tree/release-3.2.x)

**Build:**
```ruby
rake -s
```

**Install:** The default install path is to `$HOME/.local`. This can be changed by using the `PREFIX` environment variable.
```ruby
rake -s install
```

### Getting Started

To get started just create a file called `Start.rb` and paste in this code:

```ruby
Log.info 'Hello, world!'
```

Then run by sending this command to the terminal:

```sh
game
```

Afterwards check out this article for a longer [introduction](https://github.com/stalbordboat/Game/wiki/Introduction).

### Documentation

+ [The Game Wiki](https://github.com/stalbordboat/Game/wiki)
