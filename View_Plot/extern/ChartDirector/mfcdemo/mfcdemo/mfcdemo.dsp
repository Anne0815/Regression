# Microsoft Developer Studio Project File - Name="mfcdemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mfcdemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mfcdemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mfcdemo.mak" CFG="mfcdemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mfcdemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "mfcdemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mfcdemo - Win32 Release"

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
PostBuild_Cmds=xcopy /D /Y /C ..\..\lib\chartdir50.dll $(OutDir)	echo Copying resource files to output directory (if necessary)	xcopy /D /Y /C .\*.png $(OutDir)	xcopy /D /Y /C .\*.gif $(OutDir)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mfcdemo - Win32 Debug"

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
PostBuild_Cmds=xcopy /D /Y /C ..\..\lib\chartdir50.dll $(OutDir)	echo Copying resource files to output directory (if necessary)	xcopy /D /Y /C .\*.png $(OutDir)	xcopy /D /Y /C .\*.gif $(OutDir)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "mfcdemo - Win32 Release"
# Name "mfcdemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChartViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\HotSpotDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\mfccharts.cpp
# End Source File
# Begin Source File

SOURCE=.\mfcdemo.cpp
# End Source File
# Begin Source File

SOURCE=.\mfcdemo.rc
# End Source File
# Begin Source File

SOURCE=.\mfcdemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\mfcdemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChartViewer.h
# End Source File
# Begin Source File

SOURCE=.\HotSpotDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\mfccharts.h
# End Source File
# Begin Source File

SOURCE=.\mfcdemo.h
# End Source File
# Begin Source File

SOURCE=.\mfcdemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\mfcdemoView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\mfcdemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\mfcdemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\mfcdemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Images"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\angry.png
# End Source File
# Begin Source File

SOURCE=.\bg.png
# End Source File
# Begin Source File

SOURCE=.\clock.png
# End Source File
# Begin Source File

SOURCE=.\cloud.png
# End Source File
# Begin Source File

SOURCE=.\computer.png
# End Source File
# Begin Source File

SOURCE=.\doc.png
# End Source File
# Begin Source File

SOURCE=.\gas.gif
# End Source File
# Begin Source File

SOURCE=.\laugh.png
# End Source File
# Begin Source File

SOURCE=.\marble.png
# End Source File
# Begin Source File

SOURCE=.\marble2.png
# End Source File
# Begin Source File

SOURCE=.\marble3.png
# End Source File
# Begin Source File

SOURCE=.\molecule.png
# End Source File
# Begin Source File

SOURCE=.\nocomment.png
# End Source File
# Begin Source File

SOURCE=.\rain.png
# End Source File
# Begin Source File

SOURCE=.\robot1.png
# End Source File
# Begin Source File

SOURCE=.\robot2.png
# End Source File
# Begin Source File

SOURCE=.\robot3.png
# End Source File
# Begin Source File

SOURCE=.\robot4.png
# End Source File
# Begin Source File

SOURCE=.\robot5.png
# End Source File
# Begin Source File

SOURCE=.\rock.png
# End Source File
# Begin Source File

SOURCE=.\sad.png
# End Source File
# Begin Source File

SOURCE=.\service.png
# End Source File
# Begin Source File

SOURCE=.\small_computer.png
# End Source File
# Begin Source File

SOURCE=.\small_molecule.png
# End Source File
# Begin Source File

SOURCE=.\small_user.png
# End Source File
# Begin Source File

SOURCE=.\smile.png
# End Source File
# Begin Source File

SOURCE=.\snow.png
# End Source File
# Begin Source File

SOURCE=.\snowy.png
# End Source File
# Begin Source File

SOURCE=.\software.png
# End Source File
# Begin Source File

SOURCE=.\star.png
# End Source File
# Begin Source File

SOURCE=.\sun.png
# End Source File
# Begin Source File

SOURCE=.\tile.gif
# End Source File
# Begin Source File

SOURCE=.\wood.png
# End Source File
# End Group
# End Target
# End Project
