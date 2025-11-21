; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXenomapDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xenomap.h"

ClassCount=5
Class1=CXenomapApp
Class2=CXenomapDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_XENOMAP_DIALOG
Resource4=IDD_IMAGE
Resource5=IDR_MAINACCEL
Resource6=IDR_MAINMENU
Class4=CNumEdit
Resource7=IDD_XENOMAP_DIALOG (English (U.S.))
Class5=CImageDlg
Resource8=IDD_ABOUTBOX (English (U.S.))

[CLS:CXenomapApp]
Type=0
HeaderFile=xenomap.h
ImplementationFile=xenomap.cpp
Filter=N

[CLS:CXenomapDlg]
Type=0
HeaderFile=xenomapDlg.h
ImplementationFile=xenomapDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ACC_ESC

[CLS:CAboutDlg]
Type=0
HeaderFile=xenomapDlg.h
ImplementationFile=xenomapDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_XENOMAP_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CXenomapDlg

[DLG:IDD_XENOMAP_DIALOG (English (U.S.))]
Type=1
Class=CXenomapDlg
ControlCount=39
Control1=IDC_IMAGENUM,edit,1484857474
Control2=IDC_SPINIMAGE,msctls_updown32,1476395058
Control3=IDC_PIECENUM,edit,1484857474
Control4=IDC_SPINPIECE,msctls_updown32,1476395058
Control5=IDC_IMAGEX,edit,1484857474
Control6=IDC_IMAGEY,edit,1484857474
Control7=IDC_SIZEX,edit,1484857474
Control8=IDC_SIZEY,edit,1484857474
Control9=IDC_SCREENX,edit,1484849282
Control10=IDC_SCREENY,edit,1484849282
Control11=IDC_UNKNOWN,edit,1484849280
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308352
Control14=IDC_IMAGENUMMAX,edit,1484857474
Control15=IDC_PIECENUMMAX,edit,1484857474
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308354
Control18=IDC_STATIC,static,1342308354
Control19=IDC_STATIC,static,1342308354
Control20=IDC_STATIC,static,1342308354
Control21=IDC_STATIC,static,1342308354
Control22=IDC_STATIC,static,1342308354
Control23=IDC_STATIC,static,1342308354
Control24=IDC_STATIC,static,1342308354
Control25=IDC_STATIC,button,1342177287
Control26=IDC_ADD,button,1476460544
Control27=IDC_REMOVE,button,1476460544
Control28=IDC_XORIGINE,edit,1350639746
Control29=IDC_YORIGINE,edit,1350639746
Control30=IDC_RAWPATH,edit,1484849280
Control31=IDC_OPENRAW,button,1342242816
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,button,1342177287
Control36=IDC_RENDER,button,1476460544
Control37=IDC_HFLIP,button,1476460579
Control38=IDC_VFLIP,button,1476460579
Control39=IDC_VIEWALL,button,1476460579

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[ACL:IDR_MAINACCEL]
Type=1
Class=?
Command1=ACC_ESC
Command2=ACC_RETURN
CommandCount=2

[MNU:IDR_MAINMENU]
Type=1
Class=?
Command1=ID_FILE_APRI
Command2=ID_FILE_SALVA
Command3=ID_FILE_SALVACONNOME
Command4=ID_FILE_ESCI
CommandCount=4

[CLS:CNumEdit]
Type=0
HeaderFile=NumEdit.h
ImplementationFile=NumEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[DLG:IDD_IMAGE]
Type=1
Class=CImageDlg
ControlCount=0

[CLS:CImageDlg]
Type=0
HeaderFile=ImageDlg.h
ImplementationFile=ImageDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

