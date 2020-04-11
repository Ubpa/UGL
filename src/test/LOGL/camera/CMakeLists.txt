if(${UBPA_UGL_GLAD})
	add_definitions(-DUBPA_UGL_GLAD)
endif()

Ubpa_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")

Ubpa_AddTarget(MODE "LIB" TEST ON LIBS "Ubpa::${core};glfw")
