cmake_minimum_required (VERSION 2.6)
project (OXYGINE_ADMOB)

set(OXYGINE_ADMOB_INCLUDE_DIRS 
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OXYGINE_ADMOB_INCLUDE_DIRS})
add_library(oxygine-admob STATIC 
	src/admob.cpp 
	src/admob.h
	src/sim/AdmobSimulator.cpp 
	src/sim/AdmobSimulator.h
)

#target_link_libraries(oxyginemagicparticles)

set(OXYGINE_ADMOB_INCLUDE_DIRS ${OXYGINE_ADMOB_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINE_ADMOB_LIBS ${OXYGINE_ADMOB_LIBS} PARENT_SCOPE)