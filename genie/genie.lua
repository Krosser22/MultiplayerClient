--
-- ////////////////////////////////////////////
-- /////Autor: Juan Daniel Laserna Condado/////
-- /////Email: S6106112@live.tees.ac.uk   /////
-- /////            2016-2017             /////
-- ////////////////////////////////////////////
--

-- Define the project. Put the release configuration first so it will be the
-- default when folks build using the makefile. That way they don't have to
-- worry about the /scripts argument and all that.
--

solution "multiplayerClient"
  configurations { "Release", "Debug" }
  location (_OPTIONS["to"])
  
  os.mkdir("../project/build/bin/windows")
    
  configuration "Debug"
    defines { "_DEBUG", "LUA_COMPAT_MODULE" }
    flags { "Symbols" }
    debugdir "../project/build/bin/windows"
    links {
      "openal32",
      "opengl32",
	  "openssl",
      "sfml-audio-d",
      "sfml-graphics-d",
      "sfml-network-d",
      "sfml-system-d",
      "sfml-window-d",
    }

  configuration "Release"
    defines { "NDEBUG", "LUA_COMPAT_MODULE" }
    flags { "Optimize" }
    debugdir "../project/build/bin/windows"
    links {
      "openal32",
      "opengl32",
	  "openssl",
      "sfml-graphics",
      "sfml-network",
      "sfml-system",
      "sfml-window",
    }

  configuration "vs*"
    defines { "_CRT_SECURE_NO_WARNINGS" }

  configuration "windows"
    targetdir "../project/build/bin/windows"

--
-- Use the --to=path option to control where the project files get generated. I use
-- this to create project files for each supported toolset, each in their own folder,
-- in preparation for deployment.
--
  newoption {
    trigger = "to",
    value   = "path",
    description = "Set the output location for the generated files"
  }
  
  os.copyfile("../lib/openal32.lib", "../project/build/bin/windows/openal32.lib")
  os.copyfile("../lib/opensl.lib", "../project/build/bin/windows/opensl.lib")
  os.copyfile("../lib/openal32.dll", "../project/build/bin/windows/openal32.dll")
  os.copyfile("../lib/sfml-audio-2.dll", "../project/build/bin/windows/sfml-audio-2.dll")
  os.copyfile("../lib/sfml-audio.lib", "../project/build/bin/windows/sfml-audio.lib")
  os.copyfile("../lib/sfml-audio-d-2.dll", "../project/build/bin/windows/sfml-audio-d-2.dll")
  os.copyfile("../lib/sfml-audio-d.lib", "../project/build/bin/windows/sfml-audio-d.lib")
  os.copyfile("../lib/sfml-graphics-2.dll", "../project/build/bin/windows/sfml-graphics-2.dll")
  os.copyfile("../lib/sfml-graphics.lib", "../project/build/bin/windows/sfml-graphics.lib")
  os.copyfile("../lib/sfml-graphics-d-2.dll", "../project/build/bin/windows/sfml-graphics-d-2.dll")
  os.copyfile("../lib/sfml-graphics-d.lib", "../project/build/bin/windows/sfml-graphics-d.lib")
  os.copyfile("../lib/sfml-network-2.dll", "../project/build/bin/windows/sfml-network-2.dll")
  os.copyfile("../lib/sfml-network.lib", "../project/build/bin/windows/sfml-network.lib")
  os.copyfile("../lib/sfml-network-d-2.dll", "../project/build/bin/windows/sfml-network-d-2.dll")
  os.copyfile("../lib/sfml-network-d.lib", "../project/build/bin/windows/sfml-network-d.lib")
  os.copyfile("../lib/sfml-system-2.dll", "../project/build/bin/windows/sfml-system-2.dll")
  os.copyfile("../lib/sfml-system.lib", "../project/build/bin/windows/sfml-system.lib")
  os.copyfile("../lib/sfml-system-d-2.dll", "../project/build/bin/windows/sfml-system-d-2.dll")
  os.copyfile("../lib/sfml-system-d.lib", "../project/build/bin/windows/sfml-system-d.lib")
  os.copyfile("../lib/sfml-window-2.dll", "../project/build/bin/windows/sfml-window-2.dll")
  os.copyfile("../lib/sfml-window.lib", "../project/build/bin/windows/sfml-window.lib")
  os.copyfile("../lib/sfml-window-d-2.dll", "../project/build/bin/windows/sfml-window-d-2.dll")
  os.copyfile("../lib/sfml-window-d.lib", "../project/build/bin/windows/sfml-window-d.lib")
  
--[[--------------------------------------------
------------- MULTIPLAYER CLIENT ---------------
--]]--------------------------------------------
project "multiplayerClient"
  targetname "multiplayerClient"
  language "C++"
  location "../project/build"
  libdirs "../lib"
  kind "ConsoleApp"
  
  includedirs {
    "../include",
    "../deps/SFML/include",
    "../deps/imgui",
    "../deps/openssl/include",
  }
  
  files {
    "../src/**.*",
    "../include/**.*",
    "../deps/SFML/include/**.*",
    "../deps/imgui/imgui.cpp",
    "../deps/imgui/imgui_draw.cpp",
    "../deps/imgui/imgui-SFML.cpp",
    "../deps/imgui/imgui_demo.cpp",
    "../deps/openssl/include/**.*",
  }

  defines {
    "_GLFW_WIN32",
    "_GLFW_WGL",
    "_GLFW_USE_OPENGL",
  }