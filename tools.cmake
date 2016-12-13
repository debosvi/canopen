
#set(CMAKE_PREFIX_PATH /usr/share/lib/cmake)
#
#find_package(Skarnet REQUIRED)
#message(STATUS "Skarnet found: " ${SKARNET_VERSION_STRING})
#include_directories(${SKARNET_INCLUDE_DIRS})
#link_directories(${SKARNET_LIBRARY_DIRS})

message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_HOST_WIN32: ${CMAKE_HOST_WIN32}")
message(STATUS "MINGW: ${MINGW}")
message(STATUS "MSYS: ${MSYS}")
message(STATUS "CYGWIN: ${CYGWIN}")
message(STATUS "WIN32: ${WIN32}")
message(STATUS "UNIX: ${UNIX}")
if(${MINGW})
    add_definitions(-DWIN32)
endif()
    
# include_directories($ENV{HOME}/usr/include)
# link_directories($ENV{HOME}/usr/lib)
# link_directories($ENV{HOME}/usr/lib/skalibs)

# include_directories(${PROJECT_SOURCE_DIR}/cots/include)
# link_directories(${PROJECT_SOURCE_DIR}/cots/lib)
