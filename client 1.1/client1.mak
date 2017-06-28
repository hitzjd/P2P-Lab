# Microsoft Developer Studio Generated NMAKE File, Based on client1.dsp
!IF "$(CFG)" == ""
CFG=client1 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to client1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "client1 - Win32 Release" && "$(CFG)" != "client1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "client1.mak" CFG="client1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "client1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "client1 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "client1 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\client1.exe"


CLEAN :
	-@erase "$(INTDIR)\cdownload.obj"
	-@erase "$(INTDIR)\client1.obj"
	-@erase "$(INTDIR)\client1.pch"
	-@erase "$(INTDIR)\client1.res"
	-@erase "$(INTDIR)\client1Doc.obj"
	-@erase "$(INTDIR)\client1View.obj"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\downonline.obj"
	-@erase "$(INTDIR)\IpBar1.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Online.obj"
	-@erase "$(INTDIR)\OnlineList.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\client1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\client1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\client1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\client1.pdb" /machine:I386 /out:"$(OUTDIR)\client1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\cdownload.obj" \
	"$(INTDIR)\client1.obj" \
	"$(INTDIR)\client1Doc.obj" \
	"$(INTDIR)\client1View.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\downonline.obj" \
	"$(INTDIR)\IpBar1.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Online.obj" \
	"$(INTDIR)\OnlineList.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\client1.res"

"$(OUTDIR)\client1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\client1.exe" "$(OUTDIR)\client1.bsc"


CLEAN :
	-@erase "$(INTDIR)\cdownload.obj"
	-@erase "$(INTDIR)\cdownload.sbr"
	-@erase "$(INTDIR)\client1.obj"
	-@erase "$(INTDIR)\client1.pch"
	-@erase "$(INTDIR)\client1.res"
	-@erase "$(INTDIR)\client1.sbr"
	-@erase "$(INTDIR)\client1Doc.obj"
	-@erase "$(INTDIR)\client1Doc.sbr"
	-@erase "$(INTDIR)\client1View.obj"
	-@erase "$(INTDIR)\client1View.sbr"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\CntrItem.sbr"
	-@erase "$(INTDIR)\downonline.obj"
	-@erase "$(INTDIR)\downonline.sbr"
	-@erase "$(INTDIR)\IpBar1.obj"
	-@erase "$(INTDIR)\IpBar1.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Online.obj"
	-@erase "$(INTDIR)\Online.sbr"
	-@erase "$(INTDIR)\OnlineList.obj"
	-@erase "$(INTDIR)\OnlineList.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\client1.bsc"
	-@erase "$(OUTDIR)\client1.exe"
	-@erase "$(OUTDIR)\client1.ilk"
	-@erase "$(OUTDIR)\client1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\client1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\client1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\client1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cdownload.sbr" \
	"$(INTDIR)\client1.sbr" \
	"$(INTDIR)\client1Doc.sbr" \
	"$(INTDIR)\client1View.sbr" \
	"$(INTDIR)\CntrItem.sbr" \
	"$(INTDIR)\downonline.sbr" \
	"$(INTDIR)\IpBar1.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Online.sbr" \
	"$(INTDIR)\OnlineList.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\client1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\client1.pdb" /debug /machine:I386 /out:"$(OUTDIR)\client1.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cdownload.obj" \
	"$(INTDIR)\client1.obj" \
	"$(INTDIR)\client1Doc.obj" \
	"$(INTDIR)\client1View.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\downonline.obj" \
	"$(INTDIR)\IpBar1.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Online.obj" \
	"$(INTDIR)\OnlineList.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\client1.res"

"$(OUTDIR)\client1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("client1.dep")
!INCLUDE "client1.dep"
!ELSE 
!MESSAGE Warning: cannot find "client1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "client1 - Win32 Release" || "$(CFG)" == "client1 - Win32 Debug"
SOURCE=.\cdownload.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\cdownload.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\cdownload.obj"	"$(INTDIR)\cdownload.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\client1.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\client1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\client1.obj"	"$(INTDIR)\client1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\client1.rc

"$(INTDIR)\client1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\client1Doc.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\client1Doc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\client1Doc.obj"	"$(INTDIR)\client1Doc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\client1View.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\client1View.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\client1View.obj"	"$(INTDIR)\client1View.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\CntrItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\CntrItem.obj"	"$(INTDIR)\CntrItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\downonline.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\downonline.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\downonline.obj"	"$(INTDIR)\downonline.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\IpBar1.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\IpBar1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\IpBar1.obj"	"$(INTDIR)\IpBar1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\Online.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\Online.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\Online.obj"	"$(INTDIR)\Online.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\OnlineList.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"


"$(INTDIR)\OnlineList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"


"$(INTDIR)\OnlineList.obj"	"$(INTDIR)\OnlineList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\client1.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "client1 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\client1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\client1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "client1 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\client1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\client1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

