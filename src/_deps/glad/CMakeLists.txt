Ubpa_DownloadFile(
  https://cdn.jsdelivr.net/gh/Ubpa/UData@master/UGL/src/_deps/glad/glad.c
  ${CMAKE_CURRENT_SOURCE_DIR}/glad.c
  SHA256 D96F6E20CB9AFDE068B4414D121A7F7032614EA9890A1790A1B26C30BDDC6BD7
)

Ubpa_AddTarget(
  MODE STATIC
  SOURCE
    "${PROJECT_SOURCE_DIR}/include/_deps/glad"
	"${PROJECT_SOURCE_DIR}/include/_deps/KHR"
  INC
    "include/_deps/"
)
