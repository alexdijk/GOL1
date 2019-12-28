cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0048 NEW)

project(GOL VERSION 0.1.0 LANGUAGES CXX)
configure_file(GOLConfig.h.in GOLConfig.h)

add_executable(GOL 
	src/main.cpp 
	src/Interface.cpp 
	src/Board.cpp 
	src/StateField.cpp 
	src/StatusText.cpp
	)

target_compile_options(GOL PRIVATE -Wall -ggdb)
target_compile_features(GOL PRIVATE cxx_std_14)

target_include_directories(GOL
	PRIVATE
	/usr/include
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../sfml/install/include
	PUBLIC
	${PROJECT_BINARY_DIR}
	)

cmake_policy(SET CMP0072 OLD)
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	message(STATUS "OpenGL found")
	message(STATUS "OpenGL includes at ${OPENGL_INCLUDE_DIR}")
	message(STATUS "OpenGL libraries at ${OPENGL_LIBRARIES}")
endif()

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/home/alex/Documents/sfml/install/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(GOL sfml-system sfml-window sfml-graphics)

