#include "pch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"
#include <stdio.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

namespace Oblikovati
{
    ImGuiLayer::ImGuiLayer()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
        io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;        // Enable Docking
        io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;      // Enable Multi-Viewport / Platform Windows

        // Setup style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        style = &ImGui::GetStyle();
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style->WindowRounding = 0.0f;
            style->Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        // Setup window
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return;

        // Create window with graphics context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+Metal example", NULL, NULL);
        if (window == NULL)
            return;

        id <MTLDevice> device = MTLCreateSystemDefaultDevice();
        commandQueue = [device newCommandQueue];

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOther(window, true);
        ImGui_ImplMetal_Init(device);

        NSWindow *nswin = glfwGetCocoaWindow(window);
        layer = [CAMetalLayer layer];
        layer.device = device;
        layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        nswin.contentView.layer = layer;
        nswin.contentView.wantsLayer = YES;

        renderPassDescriptor = [MTLRenderPassDescriptor new];


    }
    
    ImGuiLayer::~ImGuiLayer()
    {
        // Cleanup
        ImGui_ImplMetal_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void ImGuiLayer::Run()
    {
        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        float clear_color[4] = {0.45f, 0.55f, 0.60f, 1.00f};
        // Main loop
        while (!glfwWindowShouldClose(window))
        {
            @autoreleasepool
            {
                // Poll and handle events (inputs, window resize, etc.)
                // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
                // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
                // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
                // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
                glfwPollEvents();

                int width, height;
                glfwGetFramebufferSize(window, &width, &height);
                layer.drawableSize = CGSizeMake(width, height);
                id<CAMetalDrawable> drawable = [layer nextDrawable];

                id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
                renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
                renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
                renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
                renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
                id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
                [renderEncoder pushDebugGroup:@"ImGui demo"];

                // Start the Dear ImGui frame
                ImGui_ImplMetal_NewFrame(renderPassDescriptor);
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
                if (show_demo_window)
                    ImGui::ShowDemoWindow(&show_demo_window);

                // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
                {
                    static float f = 0.0f;
                    static int counter = 0;

                    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                    ImGui::Checkbox("Another Window", &show_another_window);

                    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                        counter++;
                    ImGui::SameLine();
                    ImGui::Text("counter = %d", counter);

                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::End();
                }

                // 3. Show another simple window.
                if (show_another_window)
                {
                    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                    ImGui::Text("Hello from another window!");
                    if (ImGui::Button("Close Me"))
                        show_another_window = false;
                    ImGui::End();
                }

                // Rendering
                ImGui::Render();
                ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, renderEncoder);

                // Update and Render additional Platform Windows
                if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                }

                [renderEncoder popDebugGroup];
                [renderEncoder endEncoding];

                [commandBuffer presentDrawable:drawable];
                [commandBuffer commit];
            }
        }
    }
}
