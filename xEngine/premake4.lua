project "xEngine"
  kind "SharedLib"

  objdir "../Buildscrap/Obj/xEngine"

  targetdir "../Buildscrap/Bin"

  flags { "NoExceptions", "NoRTTI" }

  language "C++"
    includedirs { "Include" }
    files { "**.h", "**.cpp", "**.inl" }
  if os.is("windows") then
	excludes { "Dependencies/**" }
    includedirs { "Dependencies/pcre/Include" }
	libdirs { "Dependencies/pcre/Lib" }
  end


  if os.is("linux") then
	excludes { "**/Win32/**" }
  elseif os.is("windows") then
	excludes { "**/Linux/**" }
	defines { "xENGINE_EXPORTS" }
  end

  if _OPTIONS["gfxapi"] == "opengl" then
     excludes { "**/Direct3D/**" }
     
	 defines { "xRENDERSYSTEM_OPENGL" }
     if os.is("linux") then
	   links "GL"
	 elseif os.is("windows") then
       links { "OpenGL32" }
       links { "Gdi32" }
	 end
  elseif _OPTIONS["gfxapi"] == "d3d" then
    excludes { "**/OpenGL/**" }

    defines { "xRENDERSYSTEM_DIRECT3D" }
	includedirs { "%DXSDK_DIR%Include" }
	libdirs { "%DXSDK_DIR%Lib/x86" }
	
    links "d3d11"
    links "dxguid"
    links "d3dcompiler"
  end

  configuration "Debug"
    targetsuffix "_d"
    implibsuffix "_d"
    defines { "DEBUG" }
    flags { "Symbols" }
  if os.is("linux") then
	links { "pcre" }
  else
    links { "pcre_d" }
  end

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" }

	links { "pcre" }
