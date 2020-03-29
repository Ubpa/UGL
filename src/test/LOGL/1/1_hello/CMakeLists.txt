Ubpa_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")
Ubpa_GetTargetName(glad "${PROJECT_SOURCE_DIR}/src/_deps/glad")
Ubpa_AddTarget(MODE "EXE" TEST ON LIBS "Ubpa::${core};${glad};glfw")
