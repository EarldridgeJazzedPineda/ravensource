--- rapid/plugin/x/mysqlx_configure.cmake.orig	2019-12-18 12:59:40 UTC
+++ rapid/plugin/x/mysqlx_configure.cmake
@@ -42,6 +42,7 @@ CONFIGURE_FILE(${MYSQLX_PROJECT_DIR}/src
 CONFIGURE_FILE(${MYSQLX_PROJECT_DIR}/src/mysqlx_version.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/generated/mysqlx_version.h )
 
+IF(FALSE)
 INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/mysqlx_error.h
         DESTINATION ${INSTALL_INCLUDEDIR}
         COMPONENT Developement)
@@ -53,3 +54,4 @@ INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR
 INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/mysqlx_version.h
         DESTINATION ${INSTALL_INCLUDEDIR}
         COMPONENT Developement)
+ENDIF()
