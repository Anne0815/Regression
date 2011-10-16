# Microsoft Developer Studio Project File - Name="zoomscrolldemo2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=zoomscrolldemo2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "zoomscrolldemo2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zoomscrolldemo2.mak" CFG="zoomscrolldemo2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zoomscrolldemo2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "zoomscrolldemo2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "zoomscrolldemo2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_CRT_SECURE_NO_DEPRECATE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\lib\chartdir50.lib /nologo /subsystem:windows /machine:I386
# Begin Special Build Tool
OutDir=.\..\bin\Release
SOURCE="$(InputPath)"
PostBuild_Desc=Copying ChartDirector DLL to output directory (if necessary)
PostBuild_Cmds=xcopy /D /Y /C ..\..\lib\chartdir50.dll $(OutDir)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "zoomscrolldemo2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_CRT_SECURE_NO_DEPRECATE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\lib\chartdir50.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
OutDir=.\..\bin\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=Copying ChartDirector DLL to output directory (if necessary)
PostBuild_Cmds=xcopy /D /Y /C ..\..\lib\chartdir50.dll $(OutDir)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "zoomscrolldemo2 - Win32 Release"
# Name "zoomscrolldemo2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChartViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\DragRect.cpp
# End Source File
# Begin Source File

SOURCE=.\HotSpotDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RepeatButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\zoomscrolldemo2.cpp
# End Source File
# Begin Source File

SOURCE=.\zoomscrolldemo2.rc
# End Source File
# Begin Source File

SOURCE=.\zoomscrolldemo2Dlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChartViewer.h
# End Source File
# Begin Source File

SOURCE=.\DragRect.h
# End Source File
# Begin Source File

SOURCE=.\HotSpotDlg.h
# End Source File
# Begin Source File

SOURCE=.\RepeatButton.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\zoomscrolldemo2.h
# End Source File
# Begin Source File

SOURCE=.\zoomscrolldemo2Dlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\dot.ico
# End Source File
# Begin Source File

SOURCE=.\res\downarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\downleftarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\downrightarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\leftarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\pointerPB.ico
# End Source File
# Begin Source File

SOURCE=.\res\rightarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\uparrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\upleftarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\uprightarrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\zoomInPB.ico
# End Source File
# Begin Source File

SOURCE=.\res\zoomOutPB.ico
# End Source File
# Begin Source File

SOURCE=.\res\zoomscrolldemo2.ico
# End Source File
# Begin Source File

SOURCE=.\res\zoomscrolldemo2.rc2
# End Source File
# End Group
# End Target
# End Project
