# cmake version
cmake_minimum_required(VERSION 3.10)
# project name
project(ini)

# set c++ version
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Og -Wall -g -ggdb")

# set source file
include_directories(include)
aux_source_directory(src LIBINI_SRC)
aux_source_directory(test LIBINI_TEST)

# set compile_command.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# build shared lib
add_library(${PROJECT_NAME} SHARED ${LIBINI_SRC})

# set original name of static lib
set(ORIGINAL_STATIC_LIB_NAME ${PROJECT_NAME}-static)
# build static lib
add_library(${ORIGINAL_STATIC_LIB_NAME} STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
# rename static lib
set_target_properties(${ORIGINAL_STATIC_LIB_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# build test

add_executable(ini_test ${LIBINI_TEST})
target_link_libraries(ini_test ${ORIGINAL_STATIC_LIB_NAME})
file(COPY test/test.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# install header files
install(FILES include/libini/libini.hpp
	          include/libini/Error.hpp
              include/libini/libini_wrapper.h
	    DESTINATION include/libini)
# install lib
install(TARGETS ${PROJECT_NAME} ${ORIGINAL_STATIC_LIB_NAME}
		LIBRARY DESTINATION lib 
		ARCHIVE DESTINATION lib
)

# build test
enable_testing()

add_test(
	NAME ini_test
	COMMAND $<TARGET_FILE:ini_test>#
)
