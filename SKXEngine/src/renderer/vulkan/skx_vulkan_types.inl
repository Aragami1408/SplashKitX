#pragma once

#include <core/skx_asserts.h>
#include <skx_defines.h>

#include <vulkan/vulkan.h>

#define SKX_VK_CHECK(expr)                                                     \
  { SKX_ASSERT(expr == VK_SUCCESS); }

struct SKXVulkanContext {
  VkInstance instance;
  VkAllocationCallbacks *allocator;

#if defined(_DEBUG)
  VkDebugUtilsMessengerEXT debug_messenger;
#endif
};
