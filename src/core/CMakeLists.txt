Ubpa_GlobGroupSrcs(RST sources PATHS
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include/UGL"
)

if(${UBPA_UGL_GLAD})
	add_definitions(-DUBPA_UGL_GLAD)
endif()

Ubpa_AddTarget_GDR(
	MODE "LIB"
	SOURCES ${sources}
	INTERFACE_INC ON
	PUBLIC_GLIBS
		"Ubpa::UGM_core"
		"Ubpa::UDP_core"
)
