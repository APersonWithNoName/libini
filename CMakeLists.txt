# cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
# project name
PROJECT(libini CXX)

# set c++ version
SET(CMAKE_CXX_STANDARD 11)

# set source file
SET(LIBINI_SRC libini.cpp)

# build static lib
ADD_LIBRARY(ini_static STATIC ${LIBINI_SRC})
# rename static lib
SET_TARGET_PROPERTIES(ini_static PROPERTIES  OUTPUT_NAME "ini")
# do not clean output
SET_TARGET_PROPERTIES(ini_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# build shared lib
ADD_LIBRARY(ini SHARED ${LIBINI_SRC})

# install header-file
INSTALL(FILES libini.hpp DESTINATION include/libini)
# install lib
INSTALL(TARGETS ini ini_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

