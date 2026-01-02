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

A small exploratory project focused on understanding the basics of the OpenGL pipeline.

- Uses **VAO** and **VBO** to upload geometry
- Loads and compiles minimal vertex and fragment shaders

Responsibilities are intentionally separated:

- **Renderer**: OpenGL logic
- **GLWindow**: SDL window creation and OpenGL context
- **Application**: SDL initialization and application lifecycle

This project is intentionally small and focused on learning how data flows from the
CPU to the GPU.

---

## Disclaimer

This repository is for **learning purposes only**.

It is not intended to be production-ready and may evolve as understanding improves.
