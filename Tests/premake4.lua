project "Tests"
kind "ConsoleApp"
  links "xEngine"

  objdir "../Buildscrap/Obj/Tests"
  targetdir "../Buildscrap/Bin"

  language "C++"
    includedirs { "../xEngine/Include" }
    files { "**.h", "**.cpp" }


  configuration "Debug"
    targetsuffix "_d"
    defines { "DEBUG" }
    flags { "Symbols" }

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" }
