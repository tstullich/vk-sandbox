#pragma once

#include <array>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_vulkan.h"

#include "shaderloader.h"

class Application {
public:
    Application();

    ~Application();

    void run();

private:
    struct QueueFamilyIndices {
        uint32_t graphicsFamilyIndex;
        uint32_t computeFamilyIndex;
        uint32_t presentFamilyIndex;
    };

    struct SwapchainConfiguration {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData) {

        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                              const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }

    static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    VkCommandBuffer beginSingleTimeCommands(VkCommandPool cmdPool);

    bool checkDeviceExtensions(VkPhysicalDevice device);

    bool checkValidationLayerSupport();

    void cleanupSwapchain();

    void cleanupUIResources();

    void createCommandBuffers();

    void createCommandPool();

    void createDescriptorPool();

    void createFramebuffers();

    void createGraphicsPipeline();

    void createImageViews();

    void createInstance();

    void createLogicalDevice();

    void createRenderPass();

    void createUICommandBuffers();

    void createUICommandPool(VkCommandPool *commandPool, VkCommandPoolCreateFlags flags);

    void createUIDescriptorPool();

    void createUIFramebuffers();

    void createUIRenderPass();

    VkShaderModule createShaderModule(const std::vector<char> &shaderCode);

    void createSurface();

    void createSwapchain();

    void createSyncObjects();

    void drawFrame();

    static void drawUI();

    void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool cmdPool);

    void getDeviceQueueIndices();

    std::vector<const char*> getRequiredExtensions() const;

    void initUI();

    void initVulkan();

    void initWindow();

    bool isDeviceSuitable(VkPhysicalDevice device);

    VkPhysicalDevice pickPhysicalDevice();

    VkExtent2D pickSwapchainExtent(const VkSurfaceCapabilitiesKHR &surfaceCapabilities);

    static VkPresentModeKHR pickSwapchainPresentMode(const std::vector<VkPresentModeKHR> &presentModes);

    static VkSurfaceFormatKHR pickSwapchainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &formats);

    SwapchainConfiguration querySwapchainSupport(const VkPhysicalDevice &physicalDevice);

    void recordUICommands(uint32_t bufferIdx);

    void recreateSwapchain();

    void setupDebugMessenger();

    const uint32_t WINDOW_WIDTH = 1200;
    const uint32_t WINDOW_HEIGHT = 900;

    GLFWwindow *window;

    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSurfaceKHR surface;

    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    VkExtent2D swapchainExtent;
    VkFormat swapchainImageFormat;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    std::vector<VkFramebuffer> uiFramebuffers;

    VkRenderPass renderPass;
    VkRenderPass uiRenderPass;

    VkPipeline graphicsPipeline;
    VkPipelineLayout graphicsPipelineLayout;

    VkCommandPool commandPool;
    VkCommandPool uiCommandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkCommandBuffer> uiCommandBuffers;

    uint32_t imageCount = 0;
    uint32_t currentFrame = 0;
    const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    VkDescriptorPool descriptorPool;
    VkDescriptorPool uiDescriptorPool;

    bool framebufferResized = false;

    std::vector<const char*> requiredExtensions;

    const std::array<const char*, 1> validationLayers = {
        "VK_LAYER_KHRONOS_validation",
    };

    const std::array<const char*, 1> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    QueueFamilyIndices queueIndices;

    // Debug utilities
    VkDebugUtilsMessengerEXT debugMessenger;
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
};