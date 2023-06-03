workspace "EnginePrototype"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "EnginePrototype"

outputdir = "%{cfg.buildcfg}"

include "EnginePrototype"
include "vendor/premake5_glfw.lua"
include "vendor/premake5_glad.lua"

-- if os.host() == "windows" then
--     include "vendor/premake5_glfw.lua"
--     os.execute("cd VulkanPrototype/shader/ && runShaderCompiler.bat")
-- end

-- if os.host() == "linux" then
--     os.execute("cd VulkanPrototype/shader/ && bash runShaderCompiler.sh")
-- end