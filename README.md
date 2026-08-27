# OpenGL_template
This is a simple boilerplate code for OpenGL projects that gives all the fundamental parts and structures them in a easy-to-use way.

# Build
For the build we use a minimal **Makefile** with a default target `app`.
By launching `make`, the executable will appear in `./bin/app`.

# Folder Structure
The current folder structure is the following
```
./
├── assets/
│   ├── 2d_shapes/
│   ├── 3d_shapes/
│   └── textures/
├── bin/
│   └── app
├── include/
├── shaders/
│   ├── basic/
│   └── tex/
├── src/
├── Makefile
└── main.cpp
```
`main.cpp` is the compiling target of **make** and therefore the entrypoint of the OpenGL application.

**NOTE** 
Being this a boilerplate and *not* a game engine neither a library, the code is run inside the class `Game` that **must** be extended and modified during the development, as it's the core part of the application!