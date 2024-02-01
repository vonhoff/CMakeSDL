# CMakeSDL

This is a cross-platform CMake-based project that uses SDL2 to render a simple gradient animation. You can build it on
Windows, MacOS or Linux.

This project is based on [preshing/CMakeDemo](https://github.com/preshing/CMakeDemo), but with some modifications:

- OpenGL is not included and has been completely removed.
- To determine if the Windows system is 64 bit, we now check if the value of `CMAKE_SIZEOF_VOID_P` is 8.
- The logic within `setup-win32.py` has been moved to `CMakeLists.txt`. As a result, `setup-win32.py` has been removed.
- The SDL2 version is now configurable and required. It is no longer hardcoded to "2.0.5".
- The `extern` directory has been renamed to `vendor`.

![](http://preshing.com/images/cmakedemo-preview.png)

## Requirements

### Windows (Visual Studio)

CMakeDemo expects to find the SDL2 headers and libraries in a subdirectory named `vendor\SDL-2.0.5`. If they are not
present, CMake will automatically download and extract them
from [this link](https://www.libsdl.org/release/SDL2-devel-2.0.5-VC.zip). The version is configurable, so use a version
that suits your needs by simply updating the variables in the `CMakeLists.txt`.

### MacOS (Xcode)

Use the following command to install the SDL2 headers and libraries using MacPorts.

    `sudo port install libsdl2`

### Ubuntu

Use the following command to install the SDL2 headers and libraries:

    `sudo apt install libsdl2-dev`

## Build Instructions

For build instructions, see preshing's blog
post: [How to Build a CMake-Based Project](http://preshing.com/20170511/how-to-build-a-cmake-based-project).

## Contribution

If you want to contribute to this project, you are welcome to submit pull requests or report issues on GitHub.