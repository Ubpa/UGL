Ubpa_GlobGroupSrcs(RST sources PATHS
	${CMAKE_CURRENT_SOURCE_DIR}
	"${PROJECT_SOURCE_DIR}/include/UGL"
)

if(${UBPA_UGL_GLAD})
	add_definitions(-DUBPA_UGL_GLAD)
endif()

Ubpa_ToPackageName(ugm_package_name UGM ${UGM_VERSION})
Ubpa_ToPackageName(udp_package_name UDP ${UDP_VERSION})
Ubpa_AddTarget(
	MODE "LIB"
	SOURCES ${sources}
	INTERFACE_INC ON
	LIBS
		"Ubpa::${ugm_package_name}_core"
		"Ubpa::${udp_package_name}_core"
)
