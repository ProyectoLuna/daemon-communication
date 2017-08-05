cmake_minimum_required (VERSION 2.8.1)

######## Project settings ########
PROJECT(daemon-communication)
SET(LICENSE "TBD")

######## Build and include settings ########
include_directories(
	inc
)

link_directories(
	${LINK_DIRECTORIES}
)


file(GLOB SOURCES
	"src/*.cpp"
)

add_library(
	daemon-comm
	SHARED
	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	daemon-comm
)

SET_TARGET_PROPERTIES(daemon-comm PROPERTIES VERSION 0.0.1 SOVERSION 1)

######## Install targets ########
INSTALL(TARGETS daemon-comm
	 DESTINATION usr/bin
)
