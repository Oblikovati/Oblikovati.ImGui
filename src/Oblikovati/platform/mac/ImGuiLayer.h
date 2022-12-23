#pragma once
#include "pch.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"
#include <stdio.h>


#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

namespace Oblikovati
{
    class ImGuiLayer
    {
    private:
        ImGuiIO* io;
        GLFWwindow* window;
        ImGuiStyle* style;
        id <MTLCommandQueue> commandQueue;
        CAMetalLayer* layer;
        MTLRenderPassDescriptor* renderPassDescriptor;
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        void Run();
    };
}
