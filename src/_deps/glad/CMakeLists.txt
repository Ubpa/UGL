Ubpa_GlobGroupSrcs(RST sources PATHS
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include/_deps/glad"
	"${PROJECT_SOURCE_DIR}/include/_deps/KHR"
)

Ubpa_AddTarget(MODE "LIB"
	SOURCES ${sources}
	TEST ON
)
