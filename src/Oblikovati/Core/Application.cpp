#include "pch.h"
#include "Application.h"
#include "ImGuiLayer.h"

namespace Oblikovati
{
    Application::Application()
    {
        m_imGuiLayer = new ImGuiLayer();
    }

    Application::~Application()
    {
        m_imGuiLayer->~ImGuiLayer();
    }

    void Application::Run()
    {
        m_imGuiLayer->Run();
    }
}
