# Douter Graphics (DG)

![Status](https://img.shields.io/badge/status-active--development-orange) ![Language](https://img.shields.io/badge/language-C%2B%2B23-blue) ![Graphics](https://img.shields.io/badge/API-OpenGL-green)

**Douter Graphics** is a lightweight 2D graphics abstraction framework built on top of OpenGL. 
It was born out of the need to minimize boilerplate code—such as shader loading, buffer management, 
and window creation—allowing the focus to remain entirely on application logic.

## Goals
1. **Abstraction**: Provide a clean C++ wrapper around OpenGL objects (VAO, VBO, EBO, Shaders).
2. **Modern C++**: Utilize C++23 features like `std::print` and `std::optional` for better error handling and performance.
3. **Resource Management**: Implement a mature structure for sharing meshes and shaders between objects without unnecessary copying.
4. **Simplicity**: An API powerful enough for simulations, yet simple enough to get a window on the screen within minutes.

## Architecture
The library is divided into logical modules:
* `Window`: Handling GLFW context and DeltaTime calculations.
* `Renderer`: Abstraction of the render pipeline and clear calls.
* `Camera`: Support for 2D orthographic projection and world-space transformations.
* `Mesh/Shader`: Management of geometry and GLSL programs.

## References
* **GLFW/Glad**: For window management and OpenGL function loading.
* **GLM**: For all mathematical calculations (vectors and matrices).
