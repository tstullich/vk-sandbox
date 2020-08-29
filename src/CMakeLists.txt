SET(SRCS main.cpp
        application.cpp shaderloader.h)

add_executable(renderer ${SRCS})

add_subdirectory(imgui)

target_include_directories(renderer PUBLIC imgui)

target_link_libraries(renderer glfw Vulkan::Vulkan)