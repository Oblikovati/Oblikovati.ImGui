VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/Oblikovati/Dependencies/imgui"
IncludeDir["GLFW"] = "%{wks.location}/Oblikovati/Dependencies/glfw/include"
IncludeDir["SPDLOG"] = "%{wks.location}/Oblikovati/Dependencies/spdlog/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"