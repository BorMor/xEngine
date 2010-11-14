project "xEngine"
  kind "SharedLib"

  objdir "../Buildscrap/Obj/xEngine" 
 
  targetdir "../Buildscrap/Bin"

  language "C++"
    includedirs { "Include" }
    files { "**.h", "**.cpp", "**.inl" }
  if os.is("windows") then
    includedirs { "Dependencies/pcre/Include" }
	libdirs { "Dependencies/pcre/Lib" }
  end


  if os.is("linux") then
	excludes { "**/Win32/**" }
    links "GL"
  elseif os.is("windows") then
	excludes { "**/Linux/**" }
	defines { "xENGINE_EXPORTS" }	
    links { "OpenGL32" } 
    links { "Gdi32" } 
  end
 
  configuration "Debug"
    targetsuffix "_d"
    implibsuffix "_d"
    defines { "DEBUG" }
    flags { "Symbols" }
	
	links { "pcre_d" } 
 
  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" } 

	links { "pcre" } 