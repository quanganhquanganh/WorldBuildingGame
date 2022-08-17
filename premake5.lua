workspace "WorldBuilding"
  architecture "x64"
  startproject "WorldBuildingGame"

  configurations
  {
    "Debug",
    "Release",
  }

tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

project "WorldBuilding"
  location "WorldBuilding"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"

  targetdir(tdir)
  objdir(odir)

  sysincludedirs
  {
    "%{prj.name}/include",
  }

  files
  {
    "%{prj.name}/include/**.h",
    "%{prj.name}/include/**.hpp",
    "%{prj.name}/include/**.cpp",
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.hpp",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/**.natvis"
  }

project "WorldBuildingGame"
  location "WorldBuildingGame"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  links { "WorldBuilding" }

  files
  {
    "%{prj.name}/include/**.h",
    "%{prj.name}/include/**.hpp",
    "%{prj.name}/include/**.cpp",
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.hpp",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/**.natvis"
  }

  targetdir(tdir)
  objdir(odir)
  
  sysincludedirs
  {
    "WorldBuilding/include",
  }

  flags
  {
    "FatalWarnings",
  }