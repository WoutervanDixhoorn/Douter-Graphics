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
file(GLOB_RECURSE DG_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_library(douter-graphics STATIC ${DG_SOURCES})

target_link_libraries(douter-graphics
    PRIVATE glfw 
    PRIVATE glad
)

target_include_directories(douter-graphics
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
)

install(TARGETS douter-graphics
		ARCHIVE DESTINATION LIB)
		
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
		DESTINATION include
		FILES_MATCHING PATTERN "*h")

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm"
		DESTINATION include)