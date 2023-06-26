cmake_minimum_required(VERSION 3.26.4)
project(CMakeSFMLProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
	src/main.cpp
	src/map.h
	src/class.h
	src/view.h
	src/mission.h
)

set(IMAGES_FOLDER
	${CMAKE_SOURCE_DIR}/src/images/)
set(FONT ${CMAKE_SOURCE_DIR}/src/CyrilicOld.TTF)

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS CMakeSFMLProject)

add_custom_command(TARGET CMakeSFMLProject POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory ${IMAGES_FOLDER} ${CMAKE_BINARY_DIR}/images)
add_custom_command(TARGET CMakeSFMLProject POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy ${FONT} ${CMAKE_BINARY_DIR})