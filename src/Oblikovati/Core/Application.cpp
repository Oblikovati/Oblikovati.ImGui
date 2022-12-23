#include "Core.h"

#include "Application.h"
#include "ImGuiLayer.h"
#include "KeyEvent.h"

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
        KeyPressedEvent e(1,2);
        OB_TRACE(e);
        m_imGuiLayer->Run();
    }
}
