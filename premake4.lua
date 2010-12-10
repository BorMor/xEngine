solution "Project"
  configurations { "Debug", "Release" }

newoption
{
   trigger     = "gfxapi",
   value       = "API",
   description = "Choose a particular 3D API for rendering",
   allowed =
   {
      { "opengl",    "OpenGL 3.3" },
      { "d3d",  "Direct3D 10" },
   }
}

if not _OPTIONS["gfxapi"] then
   _OPTIONS["gfxapi"] = "opengl"
end

-- Direct3D supported only on windows
if not os.is("windows") then
  _OPTIONS["gfxapi"] = "opengl"
end

include "Game"
include "Tests"
include "xEngine"
