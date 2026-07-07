# Tuff

Tuff is a small C++20 OpenGL framework.

## Libraries
```
Tuff.Backend
Tuff.Core
Tuff.OpenGL
Tuff.ImGui
```
`Tuff.Sandbox` is the test enviornment and contains the main entry point.

## Current Features
* GLFW
* OpenGL backend
* ImGui
* Camera
* Editor Grid
* OpenGL object abstractions

## Build
No cmake yet, open the project in visual studio or rider and add the Tuff libaries as reference for sandbox and should be enough.

Targets:
```text
C++20
x64
OpenGL 4.6
```

## Camera Controls
```
`(~)          Toggle mouse capture
W A S D       Move camera
Q / E         Move down / up
Shift         Faster movement
Ctrl          Slower movement
Mouse         Look around
```
