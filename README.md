# Modern OpenGL Exploration

This project exists purely out of **personal interest**.

I wanted to better understand how C++ can take advantage of the GPU, beyond using
higher-level libraries such as SDL.

I am not a graphics expert, and this is **not intended to be a game engine or
production-ready graphics code**. The goal is to understand the fundamentals behind:

- How modern C++ applications interact with the GPU
- How OpenGL works at a low level
- How responsibilities can be cleanly structured in native code

C++ is widely used to build high-performance 2D and 3D applications, and I’ve always
been curious about what actually happens under the hood. This repository is a
hands-on exploration of those ideas.

---

## Code

### `0_gl_setup`

A minimal setup project used to verify that OpenGL is correctly initialized.

- Creates an SDL window with an OpenGL context
- Uses **glad** to load OpenGL functions
- Queries and prints GPU and OpenGL information directly

The goal of this project is purely **validation and environment setup**.

---

### `1_draw_triangle`

An exploratory project focused on understanding the modern OpenGL rendering pipeline
from CPU to GPU.

Features

- Uses VAO and VBO to upload geometry
- Loads, compiles, and links vertex and fragment shaders
- Demonstrates multiple vertex data layouts:
  - Single VBO (position only)
  - Interleaved VBO (position + color)
  - Multiple VBOs (separate position and color buffers)
- Renders:
  - A triangle (default)
  - A quad composed of two triangles

This project is intentionally small and focused on learning how data flows from the
CPU to the GPU.

### Runtime options

```bash
./prog        # draw a triangle (default)
./prog -q     # draw a quad (two triangles)
```
### Building
```bash
make vbo-single       # single VBO (positions only)
make vbo-interleaved  # interleaved position + color
make vbo-multiple     # multiple VBOs (separate buffers)

```
---

### Architecture Overview

Responsibilities are intentionally separated:

- Application
  - SDL initialization
  - Application lifecycle and event loop

- GLWindow
  - SDL window creation
  - OpenGL context management

- Renderer
  - OpenGL state setup
  - Draw calls

- GPUObject
  - Owns VAO, VBO(s), and shader program
  - Uploads geometry data to the GPU
  - Encapsulates OpenGL resource lifetime (RAII)

- GeometryData
  - CPU-side vertex definitions (triangle / quad)
  - Used to experiment with different VBO layouts

---

## Disclaimer

This repository is for **learning purposes only**.

It is not intended to be production-ready and may evolve as understanding improves.
