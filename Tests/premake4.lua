project "Tests"
  kind "WindowedApp"
  links "xEngine"

  objdir "../Buildscrap/Obj/Tests" 
  targetdir "../Buildscrap/Bin"

  language "C++"
    includedirs { "../xEngine/Include" }
    files { "**.h", "**.cpp" }
    
  if os.is("windows") then    
    flags { "WinMain" }
  end
 
  configuration "Debug"
    targetsuffix "_d"
    defines { "DEBUG" }
    flags { "Symbols" }
 
  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" } 
