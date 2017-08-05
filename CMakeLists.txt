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
	daemon-communication
	SHARED
	${SOURCES}
)

TARGET_LINK_LIBRARIES(
	daemon-communication
)

######## Install targets ########
INSTALL(TARGETS daemon-communication
	 DESTINATION usr/bin
)
