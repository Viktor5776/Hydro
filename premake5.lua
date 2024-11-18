vcpkgPath = "./vendor/vcpkg"
vcpkgTriplet = os.istarget("windows") and "x64-windows" or "x64-linux"

workspace "Hydro"
    architecture  "x64"

    configurations
    {
        "Debug",
        "Release"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
    location "Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/include"
    }

    libdirs
    {
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/lib"
    }

    links
    {
        -- Add the libraries you need here SDL2 glm etc
        "SDL2"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
          "_WIN32"
            --preprocessor definitions
        }

        postbuildcommands
        {
            --copying the .dll file to the Sandbox project
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
        }
        
    filter "system:linux"
      cppdialect "C++20"
      staticruntime "On"
      toolset "clang"

      defines
      {
          --preprocessor definitions for Linux
      }

      links
      {
          "pthread", -- Add threading library if needed
          "dl" -- Dynamic linking library
      }

      postbuildcommands
      {
          -- Copy the .so file to the Sandbox project (shared library for Linux)
          ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),

          --copy library so to bin folder (propbly wrong but test in case)
          ("{COPYFILE} %{prj.location}/vendor/vcpkg/installed/%{vcpkgTriplet}/bin/SDL2.so %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/SDL2.so")
      }

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Realse"
        defines "HYDRO_RELEASE"
        optimize "On"

    filter "kind:SharedLib"
        defines { "ENGINE_EXPORT" }
    

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Engine/src",
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/include"
    }

    libdirs
    {
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/lib"
    }

    links
    {
        "Engine"
        --Add vcpkg libraries here if needed in sandbox
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
          "_WIN32"
            --preprocessor definitions
        }

	postbuildcommands
        {
   	    --copy library dll to bin folder
            "{COPYFILE} vendor/vcpkg/installed/%{vcpkgTriplet}/bin/SDL2.dll bin/" .. outputdir .. "/Sandbox/SDL2.dll"        
        }
        
    filter "system:linux"
        cppdialect "C++20"
        staticruntime "On"
        toolset "clang"

        defines
        {
            --preprocessor definitions for Linux
        }

        links
        {
            "pthread", -- Add threading library if needed
            "dl" -- Dynamic linking library
        }

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Realse"
        defines "HYDRO_RELEASE"
        optimize "On"
