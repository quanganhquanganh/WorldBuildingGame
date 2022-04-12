workspace "WorldBuildingGame"
  architecture "x64"
  startproject "WorldBuildingGame"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

project "WorldBuildingGame"
  location "WorldBuildingGame"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"

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

  flags
  {
    "FatalWarnings",
  }