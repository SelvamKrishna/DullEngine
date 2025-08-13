---@diagnostic disable: undefined-global

workspace "dull_engine"
    configurations { "debug", "release" }
    architecture "x86_64"
    location "build"

-- Engine as a static library
project "dull_engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "%{wks.location}/%{cfg.buildcfg}"
    objdir "%{wks.location}/%{cfg.buildcfg}/obj/%{prj.name}"

    -- Include directories for the engine
    includedirs {
        "include",
        "source",
        "vendor"
    }

    -- Engine sources
    files {
        "source/**.cpp",
        "source/**.hpp"
    }

    filter "configurations:debug"
        defines { "DEBUG", "DULL_MODE_DEBUG" }
        symbols "On"
        optimize "Off"
        buildoptions { "-Wall", "-Wextra", "-g", "-O2" }
        -- defines { "DULL_DBG_SCENES", "DULL_DBG_SIGNALS" } -- (OPTIONAL)

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "Full"
        buildoptions { "-Wall", "-Wextra", "-Werror", "-O3" }

    filter "system:windows"
        systemversion "latest"

-- Application executable
project "application"
    kind "ConsoleApp" -- Or "WindowedApp" if you want no console
    language "C++"
    cppdialect "C++20"
    targetdir "%{wks.location}/%{cfg.buildcfg}"
    objdir "%{wks.location}/%{cfg.buildcfg}/obj/%{prj.name}"

    includedirs {
        "include",
        "source",
        "vendor"
    }

    files {
        "app/**.cpp",
        "app/**.hpp"
    }

    libdirs { "vendor" }
    links {
        "dull_engine", -- Links against the static lib
        "raylib",
        "winmm",
        "gdi32",
        "opengl32"
    }

    filter "configurations:debug"
        defines { "DEBUG", "DULL_MODE_DEBUG" }
        symbols "On"
        optimize "Off"
        buildoptions { "-Wall", "-Wextra", "-g", "-O2" }

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "Full"
        buildoptions { "-Wall", "-Wextra", "-Werror", "-O3" }

    filter "system:windows"
        systemversion "latest"
