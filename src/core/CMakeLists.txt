Ubpa_GetTargetName(glad "${PROJECT_SOURCE_DIR}/src/_deps/glad")

Ubpa_AddTarget(
  MODE STATIC
  SOURCES
    "${PROJECT_SOURCE_DIR}/include/UGL"
  LIB
    "Ubpa::UGM_core"
    "Ubpa::UDP_core"
    ${glad}
  INC
    include
)
