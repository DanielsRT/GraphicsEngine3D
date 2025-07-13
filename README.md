# GraphicsEngine3D

A modern C++ application for loading, modeling, and rendering 3D graphics.  
This engine demonstrates how 3D coordinates are projected into 2D space using a customizable projection matrix.  
Developed in Visual Studio and powered by OpenGL, Glad, and GLFW.

<img width="996" height="949" alt="image" src="https://github.com/user-attachments/assets/33c9af6b-327e-4242-bbd6-a7b0dc1a9da3" />

---

## Features

- **3D Model Loading**: Import and display 3D models from various file formats.
- **Custom Projection**: 3D-to-2D conversion using a projection matrix for flexible camera control.
- **OpenGL Rendering**: Real-time rendering with programmable shaders.
- **Texture Support**: Apply and manage textures for realistic surfaces.
- **Lighting Shaders**: Flexible shader system for dynamic lighting effects.
- **Modular Architecture**: Components such as Camera, Mesh, Model, Texture, and Shader classes for easy extension.

---

## Getting Started

### Prerequisites

- **Visual Studio** (recommended)
- **C++17** or later
- **OpenGL** (hardware and drivers)
- **GLFW** and **Glad** (included, see `Libraries/`)
- **stb_image** (for texture loading, included)
- **json** (included)

### Cloning the Repository

```bash
git clone https://github.com/DanielsRT/GraphicsEngine3D.git
cd GraphicsEngine3D
```

### Building (Visual Studio)

1. Open `GraphicsEngine3D.sln` in Visual Studio.
2. Restore or confirm the presence of dependencies in the `Libraries/` folder.
3. Build the solution (`Build > Build Solution`).

### Running

- Make sure your working directory includes the required shader files (`default.vert`, `default.frag`, etc.) and sample models/textures.
- Run the executable from Visual Studio or directly from the `bin/` folder (if available).

---

## Repository Structure

- `main.cpp` – Application entry point.
- `Camera.*` – Camera and view matrix logic.
- `Mesh.*`, `Model.*` – 3D mesh/model structures and loaders.
- `Texture.*` – Texture management and loading.
- `shaderClass.*` – Shader program abstraction.
- `Libraries/` – Third-party dependencies (GLFW, Glad, stb_image, etc.).
- `models/` – Example 3D model files.
- `default.vert`, `default.frag`, `light.vert`, `light.frag` – Example GLSL shaders.
- `*.png` – Textures for demonstration.

---

## Dependencies

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [Glad](https://glad.dav1d.de/)
- [stb_image](https://github.com/nothings/stb)
- [json](https://github.com/nlohmann/json)
- [Visual Studio](https://visualstudio.microsoft.com/) or compatible C++ IDE

---

## Models & Textures

- Place your 3D models in the `models/` directory.
- Place textures in the root or a dedicated `textures/` folder.
- Update file paths in your code accordingly.
