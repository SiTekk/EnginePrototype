project "EnginePrototype"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    warnings "Extra"
    targetdir ("../out/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../out/obj/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    filter "system:windows"
        includedirs {
            "../vendor/glfw/include",
            "../vendor/glad/include",
            "../vendor/glm",
            "../vendor/stb"
        }

        links {
        "GLFW",
        "GLAD",
        "opengl32.lib"
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
    
        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"


    filter "system:linux"
        links {
            "glfw",
            "dl",
            "pthread",
            "X11",
            "Xxf86vm",
            "Xrandr",
            "Xi"
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"