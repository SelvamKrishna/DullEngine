workspace "dull_engine"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    location "build"

-- === Dull Engine Static Library ===
project "dull_engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir "%{wks.location}/%{cfg.buildcfg}"
    objdir "%{wks.location}/%{cfg.buildcfg}/obj/%{prj.name}"

    includedirs { "." }

    files { "engine/**.cpp", "engine/**.hpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        optimize "Off"
        buildoptions { "-Wall", "-Wextra", "-g", "-O0" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"
        buildoptions { "-Wall", "-Wextra", "-Werror", "-O3" }

    filter "system:windows"
        systemversion "latest"

-- === Application Executable ===
project "application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir "%{wks.location}/%{cfg.buildcfg}"
    objdir "%{wks.location}/%{cfg.buildcfg}/obj/%{prj.name}"

    includedirs { "." }

    files { "app/**.cpp", "app/**.hpp" }

    libdirs { "vendor", "C:\\raylib\\raylib\\src" }
    links { "dull_engine", "raylib", "winmm", "gdi32", "opengl32" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        optimize "Off"
        buildoptions { "-Wall", "-Wextra", "-g", "-O2" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"
        buildoptions { "-Wall", "-Wextra", "-Werror", "-O3" }

    filter "system:windows"
        systemversion "latest"
