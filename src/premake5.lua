include "dependencies.lua"

workspace "Oblikovati"
    configurations { "Debug-x64", "Release-x64", "Debug-ARM", "Release-ARM" }
    startproject "Oblikovati"

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"


group "Dependencies"
    include "Oblikovati/Dependencies/imgui"
    include "Oblikovati/Dependencies/glfw"

group ""

group "Core"
    include "Oblikovati"