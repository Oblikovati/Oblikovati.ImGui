project "Oblikovati"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir )
    objdir ("bin-obj/" .. outputdir )

    pchheader ("pch.h")
    pchsource ("pch.cpp")

    files
    {
        "*.h",
        "*.cpp",
    }

    includedirs
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}"
    }

    sysincludedirs
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "ImGui",
        "GLFW"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        system "windows"
        staticruntime "On"
        systemversion "latest"
        defines 
        {
            "OBKT_PLATFORM_WINDOWS"
        }
        files
        {
            "platform/windows/**.h",
            "platform/windows/**.cpp",
            "Dependencies/imgui/backends/imgui_impl_vulkan.h",
            "Dependencies/imgui/backends/imgui_impl_vulkan.cpp",
            "Dependencies/imgui/backends/imgui_impl_glfw.h",
            "Dependencies/imgui/backends/imgui_impl_glfw.cpp"
        }

    filter "system:macosx"
        system "macosx"
        defines "OBKT_PLATFORM_MAC"
        files
        {
            "platform/mac/**.h",
            "platform/mac/**.cpp",
            "platform/mac/**.mm",
            "platform/mac/Info.plist",
            --"platform/mac/app.entitlements",
            "Dependencies/imgui/backends/imgui_impl_metal.h",
            "Dependencies/imgui/backends/imgui_impl_metal.mm",
            "Dependencies/imgui/backends/imgui_impl_glfw.h",
            "Dependencies/imgui/backends/imgui_impl_glfw.cpp"
        }
        links
        {
            "CoreFoundation.framework",
            "Cocoa.framework",
            "Metal.framework",
            "MetalKit.framework",
            "IOKit.framework",
            "CoreVideo.framework",
            "QuartzCore.framework"
        }
        xcodebuildsettings {
            ["MACOSX_DEPLOYMENT_TARGET"] = "11.0",
            ["PRODUCT_BUNDLE_IDENTIFIER"] = 'com.oblikovati',
            ["CODE_SIGN_STYLE"] = "Automatic",
            ["INFOPLIST_FILE"] = "../platform/mac/Info.plist",                     -- path is relative to the generated project file
            ["ENABLE_HARDENED_RUNTIME"] = "YES",                                    -- hardened runtime is required for notarization
            ["CODE_SIGN_IDENTITY"] = "Apple Development",                           -- sets 'Signing Certificate' to 'Development'. Defaults to 'Sign to Run Locally'. not doing this will crash your app if you upgrade the project when prompted by Xcode
            ["LD_RUNPATH_SEARCH_PATHS"] = "$(inherited) @executable_path/../Frameworks", -- tell the executable where to find the frameworks. Path is relative to executable location inside .app bundle
        }

    filter "system:linux"
        system "linux"
        defines 
        {
            "OBKT_PLATFORM_LINUX"
        }
        files
        {
            "platform/linux/**.h",
            "platform/linux/**.cpp"
        }

    filter "configurations:Debug-x64"
        defines "OBKT_DEBUG"
        architecture "x86_64"
        symbols "On"

    filter "Configurations:Release-x64"
        optimize "On"
        architecture "x86_64"

    filter "configurations:Debug-ARM"
        defines "OBKT_DEBUG"
        architecture "ARM"
        symbols "On"

    filter "Configurations:Release-ARM"
        optimize "On"
        architecture "ARM"