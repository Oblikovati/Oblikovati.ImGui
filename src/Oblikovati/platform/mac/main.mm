#include "pch.h"
#include "Application.h"
#include "Log.h"

int main(int, char**)
{
    Oblikovati::Log::Init();
    OB_INFO("Oblikovati");
    auto app = Oblikovati::Application();
    app.Run();
    return 0;
}
