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
    kind "StaticLib"
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
        "SDL2",
        "GLM",
        "backward"
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

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Realse"
        defines "HYDRO_RELEASE"
        optimize "On"     

project "Editor"
    location "Editor"
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
        "Engine",
        "Imgui"
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
            "{COPY} " .. "%{wks.location}vendor/vcpkg/installed/%{vcpkgTriplet}/bin/SDL2.dll" .. " %{wks.location}bin/" .. outputdir .. "/Editor/"        
        }

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Realse"
        defines "HYDRO_RELEASE"
        optimize "On"
 

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
            "{COPY} " .. "%{wks.location}vendor/vcpkg/installed/%{vcpkgTriplet}/bin/SDL2.dll" .. " %{wks.location}bin/" .. outputdir .. "/Sandbox/"        
        }

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Realse"
        defines "HYDRO_RELEASE"
        optimize "On"

project "UnitTest"
    location "UnitTest"
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
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/lib",
        "%{vcpkgPath}/installed/%{vcpkgTriplet}/lib/manual-link"
    }

    links
    {
        "Engine",
        "gtest",
        "gtest_main"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            --copy library dll to bin folder
            "{COPY} " .. "%{wks.location}vendor/vcpkg/installed/%{vcpkgTriplet}/bin/gtest.dll" .. " %{wks.location}bin/" .. outputdir .. "/UnitTest/",
            "{COPY} " .. "%{wks.location}vendor/vcpkg/installed/%{vcpkgTriplet}/bin/gtest_main.dll" .. " %{wks.location}bin/" .. outputdir .. "/UnitTest/"
        }

    filter "configurations:Debug"
        defines "HYDRO_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HYDRO_RELEASE"
        optimize "On"