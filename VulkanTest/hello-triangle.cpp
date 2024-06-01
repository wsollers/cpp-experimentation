#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>

#define VK_CHECK_RESULT(f)                                                    \
  {                                                                           \
    VkResult res = (f);                                                       \
    if (res != VK_SUCCESS) {                                                  \
      std::cerr << "Fatal : VkResult is \"" << vkErrorString(res) << "\" in " \
                << __FILE__ << " at line " << __LINE__ << std::endl;          \
      assert(res == VK_SUCCESS);                                              \
    }                                                                         \
  }

#ifndef VERBOSE_LOGGING
#define VERBOSE_LOGGING 0
#endif

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

bool checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

#if VERBOSE_LOGGING
  std::cout << "Validation layers supported!" << std::endl;
#endif
  return true;
}

std::vector<const char*> getRequiredExtensions() {
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions,
                                      glfwExtensions + glfwExtensionCount);

  if (enableValidationLayers) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  return extensions;
}

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks* pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

class HelloTriangleApplication {
 public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

 private:
  GLFWwindow* window = nullptr;
  VkInstance instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

  bool isDeviceSuitable(VkPhysicalDevice device) {

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    std::cout << "Checking device suitability" << std::endl;
#if VERBOSE_LOGGING
    std::cout << "Device properties" << std::endl;
    std::cout << "Device name: " << deviceProperties.deviceName << std::endl;
    std::cout << '\t' << "Device type: " << deviceProperties.deviceType << std::endl;
    std::cout << '\t' << "API version: " << deviceProperties.apiVersion << std::endl;
    std::cout << '\t' << "Driver version: " << deviceProperties.driverVersion << std::endl;
    std::cout << '\t' << "Vendor ID: " << deviceProperties.vendorID << std::endl;
    std::cout << '\t' << "Device ID: " << deviceProperties.deviceID << std::endl;
#endif


    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
#if VERBOSE_LOGGING
    std::cout  << "\t\t" << "Device features:" << std::endl;
    std::cout  << "\t\t\t" << "Geometry shader support: " << deviceFeatures.geometryShader << std::endl;
    std::cout  << "\t\t\t" << "Tessellation shader support: " << deviceFeatures.tessellationShader << std::endl;
    std::cout  << "\t\t\t" << "Sampler anisotropy support: " << deviceFeatures.samplerAnisotropy << std::endl;
    std::cout  << "\t\t\t" << "Texture compression BC support: " << deviceFeatures.textureCompressionBC << std::endl;
    std::cout  << "\t\t\t" << "Texture compression ASTC_LDR support: " << deviceFeatures.textureCompressionASTC_LDR << std::endl;
    std::cout  << "\t\t\t" << "Texture compression ETC2 support: " << deviceFeatures.textureCompressionETC2 << std::endl;
    std::cout  << "\t\t\t" << "Shader storage image extended formats support: " << deviceFeatures.shaderStorageImageExtendedFormats << std::endl;
    std::cout  << "\t\t\t" << "Shader storage image read without format support: " << deviceFeatures.shaderStorageImageReadWithoutFormat << std::endl;
    std::cout  << "\t\t\t" << "Shader storage image write without format support: " << deviceFeatures.shaderStorageImageWriteWithoutFormat << std::endl;
    std::cout  << "\t\t\t" << "Shader uniform buffer array dynamic indexing support: " << deviceFeatures.shaderUniformBufferArrayDynamicIndexing << std::endl;
    std::cout  << "\t\t\t" << "Shader sampled image array dynamic indexing support: " << deviceFeatures.shaderSampledImageArrayDynamicIndexing << std::endl;
    std::cout  << "\t\t\t" << "Shader storage buffer array dynamic indexing support: " << deviceFeatures.shaderStorageBufferArrayDynamicIndexing << std::endl;
    std::cout  << "\t\t\t" << "Shader storage image array dynamic indexing support: " << deviceFeatures.shaderStorageImageArrayDynamicIndexing << std::endl;
    std::cout  << "\t\t\t" << "Shader clip distance support: " << deviceFeatures.shaderClipDistance << std::endl;
    std::cout  << "\t\t\t" << "Shader cull distance support: " << deviceFeatures.shaderCullDistance << std::endl;
    std::cout  << "\t\t\t" << "Shader float64 support: " << deviceFeatures.shaderFloat64 << std::endl;
    std::cout  << "\t\t\t" << "Shader int64 support: " << deviceFeatures.shaderInt64 << std::endl;
    std::cout  << "\t\t\t" << "Shader int16 support: " << deviceFeatures.shaderInt16 << std::endl;
    std::cout  << "\t\t\t" << "Shader resource residency support: " << deviceFeatures.shaderResourceResidency << std::endl;
#endif

    /*
     *
     * This is where we would check for device suitability
     * For example:
     *
     * return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
     *     deviceFeatures.geometryShader;
     *
     * We will just return true for now
     */
    return true;
  }

  void pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if ( deviceCount == 0) {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    std::cout << "Devices found: " << deviceCount << std::endl;
    for (const auto& device : devices) {
      if (isDeviceSuitable(device)) {
        physicalDevice = device;
        break;
      }
    }
    if (physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }

    
  }


  void initVulkan() {
    createInstance();
    setupDebugMessenger();
    pickPhysicalDevice();
  }

  void setupDebugMessenger() {
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};

    populateDebugMessengerCreateInfo(createInfo);

    auto result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr,
                                               &debugMessenger);
    if (result != VK_SUCCESS) {
      std::cerr << "failed to set up debug messenger!" << std::endl;
      std::cerr << "Error code: " << result << std::endl;
      throw std::runtime_error("failed to set up debug messenger!");
    }
  }

  void createInstance() {
    // check if validation layers are available
    if (enableValidationLayers && !checkValidationLayerSupport()) {
      std::cerr << "validation layers requested, but not available!"
                << std::endl;
      throw std::runtime_error(
          "validation layers requested, but not available!");
    }

#if VERBOSE_LOGGING
    // Lets get all the extensions that are available
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           extensions.data());
    std::cout << "Available extensions:\n";
    for (const auto& extension : extensions) {
      std::cout << '\t' << extension.extensionName << '\n';
    }
#endif

    // Create application info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto requiredExtensions = getRequiredExtensions();
    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
      createInfo.enabledLayerCount =
          static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
      populateDebugMessengerCreateInfo(debugCreateInfo);
      createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    } else {
      createInfo.enabledLayerCount = 0;
      createInfo.pNext = nullptr;
    }

    // Get required extensions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

#if VERBOSE_LOGGING
    // Print required extensions
    std::cout << "Required extensions:\n";
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
      std::cout << '\t' << "GLFW required extension: " << glfwExtensions[i]
                << std::endl;
    }
#endif

    // Pattern to create vulkan object is create struct, *allocator,  address to
    // store object in VkResult result = vkCreateInstance(&createInfo, nullptr,
    // &instance);
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
      std::cerr << "failed to create instance!" << std::endl;
      throw std::runtime_error("failed to create instance!");
    }
  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    // Destroy the debug messenger
    if (enableValidationLayers) {
      DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
  }

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData) {
    // Filter messages like so:
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      // Message is important enough to show
    }

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }

  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |  // Very noisy adjust
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
  }
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
