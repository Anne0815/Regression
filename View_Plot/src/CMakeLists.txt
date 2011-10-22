
cmake_minimum_required (VERSION 2.6)
project (Regression)

# variablen

set( EXTERN_DIR "${CMAKE_SOURCE_DIR}/../extern" )

find_package( Qt4 4.6 COMPONENTS QtCore QtGui QtNetwork REQUIRED )

include(${QT_USE_FILE})

IF( ( WIN32 OR WIN64 ) AND NOT UNIX)

IF( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )
set( VS vs2010 )
ELSE( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )
set( VS vs2008 )
ENDIF( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )

ENDIF( ( WIN32 OR WIN64 ) AND NOT UNIX )

#SET( CHARD_DIR ${CMAKE_SOURCE_DIR}/../extern/ChartDirector/include/ )
SET( CHARD_DIR ${EXTERN_DIR}/ChartDirector/include/ )
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CHARD_DIR})

link_directories( "${EXTERN_DIR}/ChartDirector/lib" )

SET( MOC_HDRS QViewChart.h )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HDRS} )

SET( VIEW_HDRS ChartDirector.h ${MOC_HDRS} )
SET( VIEW_SRCS ChartDirector.cpp main.cpp QViewChart.cpp ${MOC_SRCS})

SET( REGR_HDRS Dll.h DataImporter.h LinearRegression.h UnitTesting.h )
SET( REGR_SRCS DataImporter.cpp LinearRegression.cpp UnitTesting.cpp )


LINK_LIBRARIES( ${QT_QTMAIN_LIBRARY} )

add_library(LinearRegression SHARED ${REGR_HDRS} ${REGR_SRCS})
target_link_libraries(LinearRegression ${QT_LIBRARIES} )

add_executable (View_Plot ${VIEW_HDRS} ${VIEW_SRCS}  )
target_link_libraries(View_Plot LinearRegression ${QT_LIBRARIES} chartdir50.dll)


INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_EXECUTABLES "View_Plot" "View_Plot")
INCLUDE(CPack)

IF( ( WIN32 OR WIN64 ) AND NOT UNIX)
	INSTALL(FILES ../build/Release/View_Plot.exe DESTINATION bin)
	INSTALL(FILES ../src/qt.conf DESTINATION bin)
	INSTALL(FILES  ../extern/ChartDirector/lib/chartdir50.dll DESTINATION bin)
	INSTALL(FILES "${QT_LIBRARY_DIR}/../bin/QtGui4.dll" DESTINATION bin)
	INSTALL(FILES "${QT_LIBRARY_DIR}/../bin/QtCore4.dll" DESTINATION bin)
	INSTALL(FILES "${QT_LIBRARY_DIR}/../plugins/imageformats/qjpeg4.dll" DESTINATION bin/plugins/imageformats)
	
	IF( WIN32 )
		INSTALL(FILES "c:/Windows/System32/msvcp100.dll" DESTINATION bin)
		INSTALL(FILES "c:/Windows/System32/msvcr100.dll" DESTINATION bin)
	ELSEIF( WIN64 )
		INSTALL(FILES "c:/Windows/SysWOW64/msvcp100.dll" DESTINATION bin)
		INSTALL(FILES "c:/Windows/SysWOW64/msvcr100.dll" DESTINATION bin)
	ENDIF( WIN32 )
ELSE( UNIX AND NOT ( WIN32 OR WIN64 ) )
	SET( CMAKE_CXX_FLAGS "-std=c++0x" )
	INSTALL(FILES ../build/View_Plot DESTINATION bin)
	INSTALL(FILES ../src/qt.conf DESTINATION bin)
	INSTALL(FILES "${QT_QTGUI_LIBRARY}.4" DESTINATION bin)
	INSTALL(FILES "${QT_QTGUI_LIBRARY}.4.6.2" DESTINATION bin)
	INSTALL(FILES "${QT_QTCORE_LIBRARY}.4" DESTINATION bin)
	INSTALL(FILES "${QT_QTCORE_LIBRARY}.4.6.2" DESTINATION bin)
	INSTALL(FILES "${QT_PLUGINS_DIR}/imageformats/libqjpeg.so" DESTINATION bin/plugins/imageformats)
ENDIF( ( WIN32 OR WIN64 ) AND NOT UNIX )

