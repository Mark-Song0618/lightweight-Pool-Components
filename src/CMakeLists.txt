add_library(pool_util
	SHARED
	conPool.cpp
)

# mysql
set(MYSQL_ROOT "C:/Program Files/MySQL/MySQL Server 8.0")
target_include_directories(pool_util PUBLIC ${MYSQL_ROOT}/include)
target_link_directories(pool_util PUBLIC ${MYSQL_ROOT}/lib ${MYSQL_ROOT}/bin)
target_link_libraries(pool_util libmysql mysqlclient)

set_target_properties(
	pool_util
	PROPERTIES 
		POSITION_INDEPENDENT_CODE	1 
		CMAKE_VISIBILITY_PRESET		hidden
		VISIBILITY_INLINES_HIDDEN   1 
		OUTPUT_NAME					"pool_util"
		DEBUG_POSTFIX				"_d" 
		PUBLIC_HEADER				"conPool.h;threadPool.h;memPool.h;${INSTALL_INCLUDEDIR}/Export.h"
		MAXOSX_RPATH				ON
)

include(GenerateExportHeader)
generate_export_header(
	pool_util 
	BASE_NAME "poolUtil"
	EXPORT_MACRO_NAME "poolUtil_EXPORT"
	EXPORT_FILE_NAME "${INSTALL_INCLUDEDIR}/Export.h"
	DEPRECATED_MACRO_NAME "poolUtil_DEPRECATED"
    NO_EXPORT_MACRO_NAME "poolUtil_NO_EXPORT"
	STATIC_DEFINE "poolUtil_STATIC_DEFINE"
	NO_DEPRECATED_MACRO_NAME "poolUtil_NO_DEPRECATED"
    DEFINE_NO_DEPRECATED
)

target_include_directories(
	pool_util
	PUBLIC
	${INSTALL_INCLUDEDIR}
)

install(
TARGETS 
	pool_util
ARCHIVE 
	DESTINATION ${INSTALL_LIBDIR}
	COMPONENT   lib
RUNTIME
	DESTINATION ${INSTALL_BINDIR}
	COMPONENT   bin
LIBRARY
	DESTINATION ${INSTALL_LIBDIR}
	COMPONENT   lib
PUBLIC_HEADER
	DESTINATION ${INSTALL_INCLUDEDIR}
	COMPONENT   dev
)

