# sdl3_mixer cmake project-config input for CMakeLists.txt script


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SDL3_mixerConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(FeatureSummary)
set_package_properties(SDL3_mixer PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_mixer/"
    DESCRIPTION "SDL_mixer is a sample multi-channel audio mixer library"
)

set(SDL3_mixer_FOUND                ON)

set(SDL3MIXER_VENDORED              ON)

set(SDL3MIXER_CMD                   FALSE)

set(SDL3MIXER_SNDFILE               FALSE)

set(SDL3MIXER_FLAC                  TRUE)
set(SDL3MIXER_FLAC_LIBFLAC          FALSE)
set(SDL3MIXER_FLAC_DRFLAC           TRUE)

set(SDL3MIXER_GME                   FALSE)

set(SDL3MIXER_MOD                   FALSE)
set(SDL3MIXER_MOD_MODPLUG           FALSE)
set(SDL3MIXER_MOD_XMP               FALSE)
set(SDL3MIXER_MOD_XMP_LITE          FALSE)

set(SDL3MIXER_MP3                   FALSE)
set(SDL3MIXER_MP3_DRMP3             FALSE)
set(SDL3MIXER_MP3_MPG123            FALSE)

set(SDL3MIXER_MIDI                  TRUE)
set(SDL3MIXER_MIDI_FLUIDSYNTH       FALSE)
set(SDL3MIXER_MIDI_NATIVE           FALSE;TRUE)
set(SDL3MIXER_MIDI_TIMIDITY         TRUE)

set(SDL3MIXER_OPUS                  FALSE)

set(SDL3MIXER_VORBIS                TRUE)
set(SDL3MIXER_VORBIS_STB            TRUE)
set(SDL3MIXER_VORBIS_TREMOR         FALSE)
set(SDL3MIXER_VORBIS_VORBISFILE     FALSE)

set(SDL3MIXER_WAVE                  FALSE)

set(SDL3MIXER_WAVPACK               FALSE)

set(SDL3MIXER_SDL3_REQUIRED_VERSION 3.0.0)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_mixer-shared-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_mixer-shared-targets.cmake")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL3_mixer-static-targets.cmake")

    if(SDL3MIXER_VENDORED)
        if(SDL3MIXER_GME)
            include(CheckLanguage)
            check_language(CXX)
            if(NOT CMAKE_CXX_COMPILER)
                message(WARNING "CXX language not enabled. Linking to SDL3_mixer::SDL3_mixer-static might fail.")
            endif()
        endif()
    else()
        include(CMakeFindDependencyMacro)
        include(PkgConfigHelper)

        set(_sdl_cmake_module_path "${CMAKE_MODULE_PATH}")
        list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

        if(NOT DEFINED CMAKE_FIND_PACKAGE_PREFER_CONFIG)
            set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
        endif()

        if(SDL3MIXER_SNDFILE AND NOT TARGET SndFile::sndfile)
            find_dependency(SndFile)
        endif()

        if(SDL3MIXER_FLAC_LIBFLAC AND NOT TARGET FLAC::FLAC)
            find_dependency(FLAC)
        endif()

        if(SDL3MIXER_MOD_MODPLUG AND NOT TARGET modplug::modplug)
            find_dependency(modplug)
        endif()

        if(SDL3MIXER_MOD_XMP AND NOT TARGET libxmp::libxmp)
            find_dependency(libxmp)
        endif()

        if(SDL3MIXER_MOD_XMP_LITE AND NOT TARGET libxmp-lite::libxmp-lite)
            find_dependency(libxmp-lite)
        endif()

        if(SDL3MIXER_MP3_MPG123 AND NOT TARGET MPG123::mpg123)
            find_dependency(mpg123)
        endif()

        if(SDL3MIXER_MIDI_FLUIDSYNTH AND NOT TARGET FluidSynth::libfluidsynth)
            find_dependency(FluidSynth)
        endif()

        if(SDL3MIXER_VORBIS_TREMOR AND NOT TARGET tremor::tremor)
            find_dependency(tremor)
        endif()

        if(SDL3MIXER_VORBIS_VORBISFILE AND NOT TARGET Vorbis::vorbisfile)
            find_dependency(Vorbis)
        endif()

        if(SDL3MIXER_OPUS AND NOT TARGET OpusFile::opusfile)
            find_dependency(OpusFile)
        endif()

        if(SDL3MIXER_WAVPACK AND NOT TARGET WavPack::WavPack)
            find_dependency(wavpack)
        endif()

        set(CMAKE_MODULE_PATH "${_sdl_cmake_module_path}")
        unset(_sdl_cmake_module_path)

        if(HAIKU AND SDL3MIXER_MIDI_NATIVE)
            include(CheckLanguage)
            check_language(CXX)
            if(NOT CMAKE_CXX_COMPILER)
                message(WARNING "CXX language not enabled. Linking to SDL3_mixer::SDL3_mixer-static might fail.")
            endif()
        endif()
    endif()

    include("${CMAKE_CURRENT_LIST_DIR}/SDL3_mixer-static-targets.cmake")
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

# Make sure SDL3_mixer::SDL3_mixer always exists
if(NOT TARGET SDL3_mixer::SDL3_mixer)
    if(TARGET SDL3_mixer::SDL3_mixer-shared)
        _sdl_create_target_alias_compat(SDL3_mixer::SDL3_mixer SDL3_mixer::SDL3_mixer-shared)
    else()
        _sdl_create_target_alias_compat(SDL3_mixer::SDL3_mixer SDL3_mixer::SDL3_mixer-static)
    endif()
endif()
