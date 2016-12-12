cmake_minimum_required (VERSION 3.0)
project (canopen)

include(project_ver.cmake)
include(ext-build/cmake/boz-build.cmake)
include(CTest)

include(tools.cmake)

# set (CMAKE_VERBOSE_MAKEFILE ON)

BOZ_COMPS_FIND_ALL(${CMAKE_CURRENT_SOURCE_DIR}/comps)

