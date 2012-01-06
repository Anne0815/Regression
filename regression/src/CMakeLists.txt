
cmake_minimum_required (VERSION 2.6)
project (Regression)

# variablen

set( EXTERN_DIR "${CMAKE_SOURCE_DIR}/../libs" )
set( CHARD_DIR "${EXTERN_DIR}/ChartDirector/include/" )

IF( ( WIN32 OR WIN64 ) AND NOT UNIX)

IF( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )
set( VS vs2010 )
ELSE( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )
set( VS vs2008 )
ENDIF( ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" )

ENDIF( ( WIN32 OR WIN64 ) AND NOT UNIX )


# packages

find_package( Qt4 4.6 COMPONENTS QtCore QtGui QtNetwork REQUIRED )


# includes and link directories

include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CHARD_DIR})

LINK_LIBRARIES( ${QT_QTMAIN_LIBRARY} )    #??????????????????
link_directories( "${EXTERN_DIR}/ChartDirector/lib" )


# sources

QT4_WRAP_UI( ui_ControlView.h ControlView.ui )

set( MOC_HDRS QViewChart.h QControlView.h )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HDRS} )

set( VIEW_HDRS ChartDirector.h QControlView.h ui_ControlView.h ${MOC_HDRS} )
set( VIEW_SRCS ChartDirector.cpp main.cpp QControlView.cpp QViewChart.cpp ${MOC_SRCS})

set( REGR_HDRS bigfloat.h Controller.h CramerRule.h DataGenerator.h DataImporter.h Dll.h 
		GaussElimination.h global.h LinearRegression.h Regularization.h UnitTesting.h )
set( REGR_SRCS bigfloat.cpp bigfloatdec.cpp Controller.cpp CramerRule.cpp DataGenerator.cpp DataImporter.cpp 
		GaussElimination.cpp LinearRegression.cpp Regularization.cpp UnitTesting.cpp )


# executables and libraries

add_library(LinearRegression SHARED ${REGR_HDRS} ${REGR_SRCS})
target_link_libraries(LinearRegression ${QT_LIBRARIES} )

add_executable (View_Plot ${VIEW_HDRS} ${VIEW_SRCS}  )
target_link_libraries(View_Plot LinearRegression ${QT_LIBRARIES} chartdir50.dll)


# cpack: packaging

INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_EXECUTABLES "View_Plot" "View_Plot")
INCLUDE(CPack)

IF( ( WIN32 OR WIN64 ) AND NOT UNIX)
	INSTALL(FILES ../build/Release/View_Plot.exe DESTINATION bin)
	INSTALL(FILES ../src/qt.conf DESTINATION bin)
	INSTALL(FILES "${EXTERN_DIR}/ChartDirector/lib/chartdir50.dll" DESTINATION bin)
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

