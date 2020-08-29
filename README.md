# Vulkan Sandbox
Welcome to the Vulkan Sandbox! If you are looking to develop a Vulkan application
together with a highly customizable user interface (Dear Imgui) and do not want to write
thousands of lines of boilerplate code, this project might be for you. Or if you
just want to marvel at how many lines of code it takes to draw a triangle you
can just peruse the code.

This repository is designed to be cloned and ready for use on all Linux, Windows, and
Mac. The project makes minimal assumptions about code structure and places all the necessary
code into just four header and source files, so that it is easy to get started right away.
No abstraction layers have been written for the creation of Vulkan objects, but it
should definitely be possible to quickly refactor components.

If you want more in-depth details take a look at the [Resources](#resources) section below.

# Dependencies
* Compiler toolchain that supports C++14
* CMake 3.16
* Vulkan SDK 1.2
* GLFW 3.3

# Building
Building is straightforward and should work out of the box. If that is not the case please
file an issue with me and I will try to help you out. To build the project follow these
steps:

```
git clone https://github.com/tstullich/vk-sandbox
cd vk-sandbox
mkdir build
cd build
cmake .. && make
```

Once the build finishes make sure to compile the shaders into SPIR-V by using the
`compile.sh` script found in the `shaders` subdirectory.

```
cd shaders
./compile.sh
```

Afer this you should be able to run the project in an IDE or directly from the build directory
and you should be greeted with a window like the one below. Now you should be ready to write your application!

![Image Success](https://i.imgur.com/Nor3VDg.png)

# Resources
A lot of the work for this repository is based on the great [vulkan-tutorial](https://vulkan-tutorial.com)
so if you want to learn more about Vulkan you should definitely check that out.
[Dear Imgui](https://github.com/ocornut/imgui) also has some documentation, although I find it
to be scattered and good information is hard to find. But do read through it to get started on writing
your own
