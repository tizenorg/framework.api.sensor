CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(fw_name "capi-system-sensor")

PROJECT(${fw_name})

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(PC_NAME ${fw_name})
SET(PC_REQUIRED "capi-base-common")
SET(VERSION ${FULLVER})

CONFIGURE_FILE(
    ../${fw_name}.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)

INSTALL(DIRECTORY include/ DESTINATION include/sensor FILES_MATCHING PATTERN "*.h")
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION lib/pkgconfig)
