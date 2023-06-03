project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("../out/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../out/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "glad/src/**.c",
        "glad/include/**.h"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"