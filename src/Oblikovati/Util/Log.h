#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> //Log custom types
#include <memory>

namespace Oblikovati
{
    class Log
    {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define OB_TRACE(...) Oblikovati::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OB_INFO(...)  Oblikovati::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OB_WARN(...)  Oblikovati::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OB_ERROR(...) Oblikovati::Log::GetCoreLogger()->error(__VA_ARGS__)
