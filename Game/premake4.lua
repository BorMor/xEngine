project "Game"
  kind "WindowedApp"
  links "xEngine"

  objdir "../Buildscrap/Obj/Game" 
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
