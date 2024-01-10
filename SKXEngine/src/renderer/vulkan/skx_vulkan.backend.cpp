#include "skx_vulkan_backend.h"
#include "skx_vulkan_platform.h"
#include "skx_vulkan_types.inl"

#include <core/skx_logger.h>
#include <core/skx_string.h>

#include <containers/skx_darray.h>

#include <platform/skx_platform.h>

// static Vulkan context
static SKXVulkanContext context;

VKAPI_ATTR VkBool32 VKAPI_CALL skx_vulkan_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data, void *user_data);

b8 skx_vulkan_renderer_backend_initialize(struct SKXRendererBackend *backend,
                                          const char *application_name,
                                          struct SKXPlatformState *plat_state) {

  // TODO: custom allocator
  context.allocator = 0;

  // Setup Vulkan instance.
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.apiVersion = VK_API_VERSION_1_2;
  app_info.pApplicationName = application_name;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "SplashKitX Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

  VkInstanceCreateInfo create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  // Obtain a list of required extensions
  const char **required_extensions =
      (const char **)skx_darray_create(const char *);
  {
    auto temp = &VK_KHR_SURFACE_EXTENSION_NAME;
    required_extensions =
        (const char **)(_darray_push(required_extensions, &temp));
  };
  skx_platform_get_required_extension_names(&required_extensions);

#if defined(_DEBUG)
  {
    auto temp = &VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    required_extensions =
        (const char **)(_darray_push(required_extensions, &temp));
  };

  SKX_DEBUG("Required extensions:");
  u32 length = skx_darray_length(required_extensions);
  for (u32 i = 0; i < length; i++) {
    SKX_DEBUG(required_extensions[i]);
  }
#endif

  create_info.enabledExtensionCount = skx_darray_length(required_extensions);
  create_info.ppEnabledExtensionNames = required_extensions;

  // Validation layers
  const char **required_validation_layer_names = 0;
  u32 required_validation_layer_count = 0;

  // If validation should be done, get a list of the required validation layer
  // names and make sure they exist. Validation layers should only be enabled on
  // non-release builds
#if defined(_DEBUG)
  SKX_INFO("Validation layers enabled. Enumerating...");

  // The list of validation layers required
  required_validation_layer_names =
      (const char **)skx_darray_create(const char *);
  {
    auto temp = &"VK_LAYER_KHRONOS_validation";
    required_validation_layer_names = (const char **)_darray_push(required_validation_layer_names, &temp);
  };
  required_validation_layer_count =
      skx_darray_length(required_validation_layer_names);

  // Obtain a list of available validation layers
  u32 available_layer_count = 0;
  SKX_VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
  VkLayerProperties *available_layers = (VkLayerProperties *)skx_darray_reserve(
      VkLayerProperties, available_layer_count);
  SKX_VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count,
                                                  available_layers));

  // Verify all required validation layers are available
  for (u32 i = 0; i < required_validation_layer_count; ++i) {
    SKX_INFO("Searching for layer: %s...", required_validation_layer_names[i]);
    b8 found = FALSE;
    for (u32 j = 0; j < available_layer_count; ++j) {
      if (skx_strings_equal(required_validation_layer_names[i],
                            available_layers[j].layerName)) {
        found = TRUE;
        SKX_INFO("Found.");
        break;
      }
    }

    if (!found) {
      SKX_FATAL("Required validation layer is missing: %s", required_validation_layer_names[i]);
      return FALSE;
    }
  }
  SKX_INFO("All required validation layers are present.");
#endif

  create_info.enabledLayerCount = required_validation_layer_count;
  create_info.ppEnabledLayerNames = required_validation_layer_names;

  SKX_VK_CHECK(
      vkCreateInstance(&create_info, context.allocator, &context.instance));
  SKX_INFO("Vulkan Instance created successfully.");

// Debugger
#if defined(_DEBUG)
  SKX_DEBUG("Creating Vulkan Debugger...");
  u32 log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;

  VkDebugUtilsMessengerCreateInfoEXT debug_create_info = {
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
  debug_create_info.messageSeverity = log_severity;
  debug_create_info.messageType =
      VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_create_info.pfnUserCallback = skx_vulkan_debug_callback;

  PFN_vkCreateDebugUtilsMessengerEXT func =
      (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
          context.instance, "vkCreateDebugUtilsMessengerEXT");
  SKX_ASSERT_MSG(func, "Failed to create debug messenger!");
  SKX_VK_CHECK(func(context.instance, &debug_create_info, context.allocator,
                    &context.debug_messenger));
  SKX_DEBUG("Vulkan debugger created.");
#endif

  SKX_INFO("Vulkan renderer initialized successfully!");
  return TRUE;
}

void skx_vulkan_renderer_backend_shutdown(struct SKXRendererBackend *backend) {
#if defined(_DEBUG)
  SKX_DEBUG("Destroying Vulkan debugger...");
  if (context.debug_messenger) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = 
    (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
    func(context.instance, context.debug_messenger, context.allocator);
  }

  SKX_DEBUG("Destroying Vulkan instance");
  vkDestroyInstance(context.instance, context.allocator);
#endif
}

void skx_vulkan_renderer_backend_resized(struct SKXRendererBackend *backend,
                                         u16 width, u16 height) {}

b8 skx_vulkan_renderer_backend_begin_frame(struct SKXRendererBackend *backend,
                                           f32 delta_time) {
  return TRUE;
}
b8 skx_vulkan_renderer_backend_end_frame(struct SKXRendererBackend *backend,
                                         f32 delta_time) {
  return TRUE;
}

VKAPI_ATTR VkBool32 VKAPI_CALL skx_vulkan_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
    void *user_data) {
  switch (message_severity) {
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
    SKX_TRACE(callback_data->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    SKX_INFO(callback_data->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    SKX_WARN(callback_data->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    SKX_ERROR(callback_data->pMessage);
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
    break;
  }
  return VK_FALSE;
}
