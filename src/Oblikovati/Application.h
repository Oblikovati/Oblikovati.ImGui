#include "pch.h"
#include "ImGuiLayer.h"

namespace Oblikovati
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
    private:
        ImGuiLayer* m_imGuiLayer;
    };
}
