cmake_minimum_required(VERSION 3.28)

project(HomeWork)

# idea from https://github.com/gwaldron/osgearth/issues/608
# scan subdirectories, add directories with CMakeLists.txt to the current project
macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
	if(IS_DIRECTORY ${curdir}/${child} AND EXISTS ${curdir}/${child}/CMakeLists.txt)
          set(dirlist ${dirlist} ${child})
        endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

SUBDIRLIST(subdirs ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${subdirs})
    add_subdirectory(${subdir})
endforeach()
