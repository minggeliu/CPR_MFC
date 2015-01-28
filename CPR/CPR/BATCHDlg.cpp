// BATCHDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CPR.h"
#include "BATCHDlg.h"
#include "afxdialogex.h"

#include <vector>

using std::vector;


// CBATCHDlg �Ի���

IMPLEMENT_DYNAMIC(CBATCHDlg, CDialogEx)

CBATCHDlg::CBATCHDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBATCHDlg::IDD, pParent)
{
	m_path = _T("");
	m_res = _T("");
}

CBATCHDlg::~CBATCHDlg()
{
}

void CBATCHDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_path);
	DDX_Text(pDX, IDC_EDIT_RES, m_res);
	DDX_Control(pDX, IDC_EDIT_PATH, m_ctr_path);
}


BEGIN_MESSAGE_MAP(CBATCHDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELETEPATH, &CBATCHDlg::OnBnClickedButtonSeletepath)
END_MESSAGE_MAP()


// CBATCHDlg ��Ϣ�������


void CBATCHDlg::OnBnClickedButtonSeletepath()
{
	TCHAR			szFolderPath[MAX_PATH] = {0};
	CString			strFolderPath = TEXT("");
		
	BROWSEINFO		sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot   = 0;
	sInfo.lpszTitle   = _T("��ѡ��һ���ļ��У�");
	sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn     = NULL;

	// ��ʾ�ļ���ѡ��Ի���
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
		{
			strFolderPath = szFolderPath;
			m_path = strFolderPath;
			
			CString str_file = strFolderPath;
			
			CString res_str;
			vector<CString>  str_vector;

			CString suffixs[] = {"\\*.jpg","\\*.jpeg","\\*.bmp","\\*.png"};
			for(int i = 0; i < 4; ++i)
			{
				CFileFind finder;
				CString filepathname;
				BOOL YesNo=finder.FindFile(str_file + suffixs[i]);
				while (YesNo)
				{
					YesNo=finder.FindNextFile();
					filepathname=finder.GetFilePath();
					str_vector.push_back(filepathname);
				}
			}

			for(vector<CString>::size_type v_i = 0; v_i != str_vector.size(); ++v_i)
			{
				res_str += str_vector[v_i];
				res_str += "\r\n";
			}

			m_res = res_str;

			UpdateData(FALSE);
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}




}
