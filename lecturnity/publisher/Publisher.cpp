// Publisher.cpp : Legt das Klassenverhalten f�r die Anwendung fest.
//

#include "stdafx.h"
#include "Publisher.h"

#include "MainFrm.h"
#include "PublisherDoc.h"
#include "DocumentPropsView.h"

#include "FrontpageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPublisherApp

BEGIN_MESSAGE_MAP(CPublisherApp, CWinApp)
	//{{AFX_MSG_MAP(CPublisherApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublisherApp Konstruktion

CPublisherApp::CPublisherApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CPublisherApp-Objekt

CPublisherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPublisherApp Initialisierung

BOOL CPublisherApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Gr��e Ihrer fertigen 
	//  ausf�hrbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht ben�tigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	// �ndern des Registrierungsschl�ssels, unter dem unsere Einstellungen gespeichert sind.
	// ZU ERLEDIGEN: Sie sollten dieser Zeichenfolge einen geeigneten Inhalt geben
	// wie z.B. den Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("imc AG\\LECTURNITY"));

	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschlie�lich MRU)

   CFrontpageDlg frontPage;
   if (IDOK == frontPage.DoModal())
   {
	   // Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	   //  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	   CSingleDocTemplate* pDocTemplate;
	   pDocTemplate = new CSingleDocTemplate(
		   IDR_MAINFRAME,
		   RUNTIME_CLASS(CPublisherDoc),
		   RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		   RUNTIME_CLASS(CDocumentPropsView));
	   AddDocTemplate(pDocTemplate);

	   // DDE-Execute-Open aktivieren
	   EnableShellOpen();
	   RegisterShellFileTypes(TRUE);

	   // Befehlszeile parsen, um zu pr�fen auf Standard-Umgebungsbefehle DDE, Datei offen
	   CCommandLineInfo cmdInfo;
	   ParseCommandLine(cmdInfo);

	   // Verteilung der in der Befehlszeile angegebenen Befehle
	   if (!ProcessShellCommand(cmdInfo))
		   return FALSE;

	   // Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	   m_pMainWnd->ShowWindow(SW_SHOW);
	   m_pMainWnd->UpdateWindow();

	   // �ffnen mit Drag & Drop aktivieren
	   m_pMainWnd->DragAcceptFiles();
   }

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog f�r Info �ber Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// �berladungen f�r virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausf�hren des Dialogfelds
void CPublisherApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPublisherApp-Nachrichtenbehandlungsroutinen