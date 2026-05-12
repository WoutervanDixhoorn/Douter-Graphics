cmake_minimum_required(VERSION 3.26)
project("douter-graphics")

set(CMAKE_CXX_STANDARD 23)

if (EMSCRIPTEN)
	add_library(glfw INTERFACE)
    target_link_options(glfw INTERFACE -sUSE_GLFW=3)
else()
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

	add_subdirectory(vendor/glfw)
endif()

add_subdirectory(vendor/glad)

#Recurse the src dir and save the .cpp files inside the MY_SROUCES variable
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_library(${CMAKE_PROJECT_NAME} ${MY_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PRIVATE glfw 
    PRIVATE glad
)

target_include_directories(${CMAKE_PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
)

install(TARGETS ${CMAKE_PROJECT_NAME}
		ARCHIVE DESTINATION LIB)
		
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
		DESTINATION include
		FILES_MATCHING PATTERN "*h")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm"
		DESTINATION include)