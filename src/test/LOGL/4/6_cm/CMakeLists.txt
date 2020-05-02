Ubpa_GetTargetName(core "${PROJECT_SOURCE_DIR}/src/core")
Ubpa_GetTargetName(camera "${PROJECT_SOURCE_DIR}/src/test/LOGL/camera")
Ubpa_AddTarget(
  TEST
  MODE EXE
  LIB ${core} glfw ${camera}
)
