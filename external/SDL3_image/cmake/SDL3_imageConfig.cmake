# sdl3_image cmake project-config input for CMakeLists.txt script

include(FeatureSummary)
set_package_properties(SDL3_image PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_image/"
    DESCRIPTION "SDL_image is an image file loading library"
)

set(SDL3_image_FOUND ON)

set(SDL3IMAGE_AVIF          OFF)
set(SDL3IMAGE_AVIF_SHARED   OFF)
set(SDL3IMAGE_BMP           ON)
set(SDL3IMAGE_GIF           OFF)
set(SDL3IMAGE_JPG           ON)
set(SDL3IMAGE_JPG_SHARED    OFF)
set(SDL3IMAGE_JXL           OFF)
set(SDL3IMAGE_JXL_SHARED    OFF)
set(SDL3IMAGE_LBM           OFF)
set(SDL3IMAGE_PCX           OFF)
set(SDL3IMAGE_PNG           ON)
set(SDL3IMAGE_PNG_SHARED    OFF)
set(SDL3IMAGE_PNM           OFF)
set(SDL3IMAGE_QOI           OFF)
set(SDL3IMAGE_SVG           OFF)
set(SDL3IMAGE_TGA           OFF)
set(SDL3IMAGE_TIF           OFF)
set(SDL3IMAGE_TIF_SHARED    OFF)
set(SDL3IMAGE_XCF           OFF)
set(SDL3IMAGE_XPM           OFF)
set(SDL3IMAGE_XV            OFF)
set(SDL3IMAGE_WEBP_SHARED   OFF)

set(SDL3IMAGE_JPG_SAVE ON)
set(SDL3IMAGE_PNG_SAVE ON)

set(SDL3IMAGE_VENDORED  ON)

set(SDL3IMAGE_BACKEND_IMAGEIO   OFF)
set(SDL3IMAGE_BACKEND_STB       ON)
set(SDL3IMAGE_BACKEND_WIC       OFF)

set(SDL3IMAGE_SDL3_REQUIRED_VERSION  3.0.0)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_image-shared-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_image-shared-targets.cmake")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_image-static-targets.cmake")

    if(SDL3IMAGE_VENDORED)
        if(SDL3IMAGE_AVIF AND NOT SDL3IMAGE_AVIF_SHARED)
            find_package(Threads)
        endif()
        if(SDL3IMAGE_JXL AND NOT SDL3IMAGE_JXL_SHARED)
            include(CheckLanguage)
            check_language(CXX)
            if(NOT CMAKE_CXX_COMPILER AND NOT _sdl3image_nowarning)
                message(WARNING "CXX language not enabled. Linking to SDL3_image::SDL3_image-static might fail.")
            endif()
        endif()
        if(SDL3IMAGE_TIF AND NOT SDL3IMAGE_TIF_SHARED)
            if(NOT TARGET CMath::CMath)
                add_library(CMath::CMath INTERFACE IMPORTED)
                find_library(CMATH_LIBRARY NAMES m)
                if(CMATH_LIBRARY)
                    set_property(TARGET CMath::CMath PROPERTY INTERFACE_LINK_LIBRARIES "${CMAKE_LIBRARY}")
                endif()
            endif()
        endif()
        if(SDL3IMAGE_WEBP AND NOT SDL3IMAGE_WEBP_SHARED)
            find_package(Threads)
        endif()
    else()
        set(_sdl_cmake_module_path "${CMAKE_MODULE_PATH}")
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

        include(CMakeFindDependencyMacro)

        if(SDL3IMAGE_AVIF AND NOT TARGET avif AND NOT SDL3IMAGE_AVIF_SHARED)
            find_package(libavif 1.0 QUIET)
            if(NOT libavif_FOUND)
                find_package(libavif 0.9.3 QUIET)
            endif()
            if(NOT libavif_FOUND)
                set(SDL3_image_FOUND FALSE)
                return()
            endif()
        endif()

        if(SDL3IMAGE_JPG AND NOT TARGET JPEG::JPEG AND NOT SDL3IMAGE_JPG_SHARED)
            find_dependency(JPEG)
        endif()

        if(SDL3IMAGE_JXL AND NOT TARGET libjxl::libjxl)
            list(APPEND libjxl_ROOT "${CMAKE_CURRENT_LIST_DIR}")
            find_dependency(libjxl)
        endif()

        if(SDL3IMAGE_PNG AND NOT TARGET PNG::PNG AND NOT SDL3IMAGE_PNG_SHARED)
            find_dependency(PNG)
        endif()

        if(SDL3IMAGE_TIF AND NOT TARGET TIFF::TIFF)
            find_dependency(TIFF)
        endif()

        if(SDL3IMAGE_WEBP AND NOT TARGET WebP::webp AND NOT SDL3IMAGE_WEBP_SHARED)
            list(APPEND webp_ROOT "${CMAKE_CURRENT_LIST_DIR}")
            find_dependency(webp)
        endif()

        set(CMAKE_MODULE_PATH "${_sdl_cmake_module_path}")
        unset(_sdl_cmake_module_path)

    endif()

    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_image-static-targets.cmake")
endif()

function(_sdl_create_target_alias_compat NEW_TARGET TARGET)
    if(CMAKE_VERSION VERSION_LESS "3.18")
        # Aliasing local targets is not supported on CMake < 3.18, so make it global.
        add_library(${NEW_TARGET} INTERFACE IMPORTED)
        set_target_properties(${NEW_TARGET} PROPERTIES INTERFACE_LINK_LIBRARIES "${TARGET}")
    else()
        add_library(${NEW_TARGET} ALIAS ${TARGET})
    endif()
endfunction()

# Make sure SDL3_image::SDL3_image always exists
if(NOT TARGET SDL3_image::SDL3_image)
    if(TARGET SDL3_image::SDL3_image-shared)
        _sdl_create_target_alias_compat(SDL3_image::SDL3_image SDL3_image::SDL3_image-shared)
    else()
        _sdl_create_target_alias_compat(SDL3_image::SDL3_image SDL3_image::SDL3_image-static)
    endif()
endif()
