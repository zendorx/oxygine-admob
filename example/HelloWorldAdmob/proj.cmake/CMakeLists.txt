cmake_minimum_required (VERSION 2.6)
project (HelloWorldFacebook)

add_subdirectory(../../../../oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_subdirectory(../../../../oxygine-facebook/ oxygine-facebook)
include_directories(${OXYGINE_FACEBOOK_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(HelloWorldFacebook ../src/main.cpp ../src/example.cpp  ../src/example.h ../src/test.h ../src/test.cpp)

if (WIN32) #disable console mode for VC++
	set_target_properties(HelloWorldFacebook PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(HelloWorldFacebook ${OXYGINE_CORE_LIBS} oxygine-facebook)