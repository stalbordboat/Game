# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

namespaces = %w(
Graphics
Scene
Point
Rect
Color
Image
Sprite
Camera
Mixer
AudioRecorder
Sound
Location
Event
Input
Gamepad
FileUtils
Env
Time
Power
File
Timer
Process
)

namespaces.constants_defined? :within => Object
