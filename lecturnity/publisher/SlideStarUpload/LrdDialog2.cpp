// LrdDialog2.cpp : implementation file
//

#include "stdafx.h"
#include "SlideStarUpload.h"
#include "LrdDialog2.h"
//#include "GeneralSettings.h"
#include "TransferSettings.h"
#include "Registry.h"
#include "SlideStarUploadDlg.h"
#include "MfcUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLrdDialog2 dialog


CLrdDialog2::CLrdDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CLrdDialog2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLrdDialog2)
	m_csZipFiles = _T("");
	//}}AFX_DATA_INIT
}


void CLrdDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLrdDialog2)
	DDX_Control(pDX, IDC_SLIDESTARUPLOADDOC, m_ZipFiles);
	DDX_Control(pDX, IDC_BARBOTTOM, m_stcBarBottom);
	DDX_CBString(pDX, IDC_SLIDESTARUPLOADDOC, m_csZipFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLrdDialog2, CDialog)
	//{{AFX_MSG_MAP(CLrdDialog2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDB_SLIDESTARUPLOAD, OnSlideStarUpload)
	ON_BN_CLICKED(IDB_SETINGS, OnSetings)
	ON_CBN_EDITCHANGE(IDC_SLIDESTARUPLOADDOC, OnEditchangeSlideStarUploaddoc)
	ON_CBN_SELCHANGE(IDC_SLIDESTARUPLOADDOC, OnSelchangeSlideStarUploaddoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLrdDialog2 message handlers
void CLrdDialog2::DrawLogo()
{
   RECT rct;
   this->GetClientRect(&rct);
   m_stcBarBottom.MoveWindow(0, rct.bottom  - 44, rct.right, 2, TRUE);
}

BOOL CLrdDialog2::OnInitDialog() 
{
	CDialog::OnInitDialog();
   SetIcon(AfxGetApp()->LoadIcon(IDI_SLIDESTARUPLOAD), TRUE);         // Set big icon
	
	// TODO: Add extra initialization here
	//RECT rt;
 //  dlg.Create(IDD_LRD_DIALOG, this);
 //  dlg.ShowWindow(SW_SHOW);
 //  GetClientRect(&rt);
 //  ::MoveWindow(dlg.m_hWnd, BORDER, BORDER + 26, rt.right - 2*BORDER,
 //     rt.bottom - 2*BORDER - 70, TRUE);

   DrawLogo();

   // from command line ?
   if(!csIniZipFile.IsEmpty())
   {
      // Does the file name contain special characters?
      CString csIniZipName(csIniZipFile);
      // Does the path / file name contain special characters?
///      int nLastSeparator = csIniZipFile.ReverseFind(_T('\\'));
///      if (nLastSeparator >= 0)
///         csIniZipName = csIniZipFile.Right(nLastSeparator+1);
      if (!CheckUrlFileName(csIniZipName))
      {
         CString csError;
         csError.LoadString(IDS_ERR_ZIPURL);
         AfxMessageBox(csError, MB_ICONSTOP);
      }
      else
      {
         m_ZipFiles.AddString(csIniZipFile);
         m_ZipFiles.SetCurSel(0);
      }
   }

   DWORD dwID[] = {
                  IDL_SLIDESTARUPLOADDOC,
                  IDB_BROWSE,
                  IDB_SLIDESTARUPLOAD,
                  IDB_SETINGS,
                  -1 };
   MfcUtils::Localize(this, dwID);

   BOOL bValid = m_ZipFiles.GetCount();
   ::EnableWindow(::GetDlgItem(m_hWnd, IDB_SLIDESTARUPLOAD), bValid);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//void CLrdDialog2::SearchForLrd(CString csMediaFile) 
//{
//   TCHAR strDirectory[MAX_PATH];
//   _tcscpy(strDirectory, csMediaFile);
//   // construct the path
//   for(int i = csMediaFile.GetLength() - 1;i >= 0; i--)
//   {
//      if(strDirectory[i] == _T('\\'))
//      {
//         strDirectory[i] = 0;
//         break;
//      }
//   }
//   // set as current directory   
//   ::SetCurrentDirectory(strDirectory);
//   // update 
//   dlg.UpdateData();
//   dlg.m_csLRDocument = dlg.FindFirstLrdFile();
//   dlg.ParseLrd();
//   dlg.UpdateData(FALSE);
//
//}
//
void CLrdDialog2::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CLrdDialog2::OnOK2() 
{
	// TODO: Add extra validation here	
	OnOK();
}

void CLrdDialog2::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLrdDialog2::OnCancel2() 
{
   OnCancel();
}

void CLrdDialog2::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CLrdDialog2::OnBrowse() 
{
	// TODO: Add your control notification handler code here
   CString csFilter = _T("SlideStarUpload Files (*.lzp)|*.lzp||");
   CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, csFilter, this);

   if(dlgOpen.DoModal() == IDOK)
   {
      UpdateData();
      // Does the path / file name contain special characters?
      if (!CheckUrlFileName(dlgOpen.GetPathName()))
      {
         CString csError;
         csError.LoadString(IDS_ERR_ZIPURL);
         AfxMessageBox(csError, MB_ICONSTOP);
      }
      else
      {
         // get the item
         m_csZipFiles = dlgOpen.GetPathName();
         //SearchForLrd(m_csZipFiles);
      
         //CString csItem;
         //BOOL bFound = FALSE;
         //for(int i=0;i < m_ZipFiles.GetCount();i++)
         //{
         //   m_ZipFiles.GetLBText(i, csItem);
         //   if(m_csZipFiles == csItem)
         //   {
         //      bFound = TRUE;
         //      break;
         //   }
         //}
      
         //if(!bFound)
         //{
         //   m_ZipFiles.AddString(dlgOpen.GetPathName());
         //}
      
         UpdateData(FALSE);
         BOOL bValid = !m_csZipFiles.IsEmpty();
         ::EnableWindow(::GetDlgItem(m_hWnd, IDB_SLIDESTARUPLOAD), bValid);
      }
   }
}

void CLrdDialog2::OnSlideStarUpload() 
{
	// TODO: Add your control notification handler code here
	CSlideStarUploadDlg dlgSlideStarUpload;

   UpdateData();
   //dlg.UpdateData();
   
   dlgSlideStarUpload.csMediaFile = m_csZipFiles;
   //dlgSlideStarUpload.csAuthor = dlg.m_csAuthor;
   //dlgSlideStarUpload.csTitle = dlg.m_csTitle;
   
   //dlg.UpdateData(FALSE);
   UpdateData(FALSE);

   // test if file exist
   FILE *fp = _tfopen(m_csZipFiles, _T("r"));
   if(fp != NULL)
   {
      fclose(fp);
      dlgSlideStarUpload.DoModal();
   }
   else
   {
      CString csMessage, csFormat;
      csFormat.LoadString(IDS_ERROPENFILE);
      csMessage.Format(csFormat, m_csZipFiles);
      AfxMessageBox( csMessage, MB_OK + MB_ICONSTOP);
      //EnableWindow(::GetDlgItem(m_hWnd, IDB_SLIDESTARUPLOAD), bResult);
   }

}

void CLrdDialog2::OnSetings() 
{
	// TODO: Add your control notification handler code here
   //CGeneralSettings dlgSettings;
   CTransferSettings dlgSettings;
   dlgSettings.DoModal();
}

void CLrdDialog2::OnEditchangeSlideStarUploaddoc() 
{
	// TODO: Add your control notification handler code here
   UpdateData();
   BOOL bValid = !m_csZipFiles.IsEmpty();
   ::EnableWindow(::GetDlgItem(m_hWnd, IDB_SLIDESTARUPLOAD), bValid);
	
}

void CLrdDialog2::OnSelchangeSlideStarUploaddoc() 
{
	// TODO: Add your control notification handler code here
   BOOL bValid = m_ZipFiles.GetCount();
   ::EnableWindow(::GetDlgItem(m_hWnd, IDB_SLIDESTARUPLOAD), bValid);
	
}

BOOL CLrdDialog2::CheckUrlFileName(CString csUrl)
{
   BOOL bAllOk = TRUE;

   _TCHAR tsz;

   for (int i = 0; i < csUrl.GetLength(); ++i)
   {
      tsz = csUrl.GetAt(i);
      bAllOk = bAllOk && ((tsz >= _T('a') && tsz <= _T('z')) || (tsz >= _T('A') && tsz <= _T('Z')) ||
                          (tsz >= _T('0') && tsz <= _T('9')) || 
                          (tsz == _T('-')) || (tsz == _T('.')) || (tsz == _T('_')) || (tsz == _T('~')) ||
						  (tsz == _T('&')) || (tsz == _T('(')) || (tsz == _T(')')) || (tsz == _T(' ')) ||
                          (tsz == _T(':')) || (tsz == _T('@')) || 
                          (tsz == _T('!')) || (tsz == _T('$')) || (tsz == _T('\'')) || 
                          (tsz == _T('*')) || (tsz == _T('+')) || 
                          (tsz == _T(',')) || (tsz == _T(';')) || (tsz == _T('=')) || 
                          (tsz == _T('%')) || (tsz == _T('/')) || (tsz == _T('\\')));
      // These 'allowed' characters seem not to work:
      // (tsz == _T('&')) || (tsz == _T('(')) || (tsz == _T(')')) || (tsz == _T(' ')) || 

      // "escape" sequence: "%" hex hex
      if (tsz == _T('%'))
      {
         if (i < (csUrl.GetLength()-2))
         {
            i++;
            _TCHAR h1 = csUrl.GetAt(i);
            i++;
            _TCHAR h2 = csUrl.GetAt(i);
            bAllOk = bAllOk && ((h1 >= _T('0') && h1 <= _T('9')) || 
                                (h1 >= _T('a') && h1 <= _T('f')) || (h1 >= _T('A') && h1 <= _T('F')));
            bAllOk = bAllOk && ((h2 >= _T('0') && h2 <= _T('9')) || 
                                (h2 >= _T('a') && h2 <= _T('f')) || (h2 >= _T('A') && h2 <= _T('F')));
         }
         else
            bAllOk = bAllOk && FALSE;
      }
   }

   return bAllOk;
}
