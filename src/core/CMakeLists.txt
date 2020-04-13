Ubpa_GlobGroupSrcs(RST sources PATHS
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include/UGL"
)

Ubpa_GetTargetName(glad "${PROJECT_SOURCE_DIR}/src/_deps/glad")

Ubpa_AddTarget_GDR(
	MODE "LIB"
	SOURCES ${sources}
	INTERFACE_INC ON
	PUBLIC_GLIBS
		"Ubpa::UGM_core"
		"Ubpa::UDP_core"
		"${glad}"
)
