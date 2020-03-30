if(${UBPA_UGL_GLAD})
	add_definitions(-DUBPA_UGL_GLAD)
endif()

Ubpa_GlobGroupSrcs(RST sources PATHS
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include/UGL"
)

Ubpa_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")
Ubpa_AddTarget(MODE "EXE" SOURCES ${sources} TEST ON LIBS "Ubpa::${core}")
