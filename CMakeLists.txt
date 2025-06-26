# cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
# project name
PROJECT(libini)

# set c++ version
SET(CMAKE_CXX_STANDARD 11)

# set source file
INCLUDE_DIRECTORIES(include)
AUX_SOURCE_DIRECTORY(src LIBINI_SRC)

# set compile_command.json
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# build static lib
ADD_LIBRARY(ini_static STATIC ${LIBINI_SRC})
# rename static lib
SET_TARGET_PROPERTIES(ini_static PROPERTIES  OUTPUT_name "ini")
# do not clean output
SET_TARGET_PROPERTIES(ini_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# build shared lib
ADD_LIBRARY(ini SHARED ${LIBINI_SRC})

# set header files which is required to install
SET(HEADER_FILES
	${LIBINI_INC}/libini.hpp
)
# install header files
INSTALL(FILES include/libini/libini.hpp DESTINATION include/libini)
# install lib
INSTALL(TARGETS ini ini_static 
		LIBRARY DESTINATION lib 
		ARCHIVE DESTINATION lib
)


