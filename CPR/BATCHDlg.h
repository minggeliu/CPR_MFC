#pragma once
#include "afxwin.h"


// CBATCHDlg �Ի���

class CBATCHDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBATCHDlg)

public:
	CBATCHDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBATCHDlg();

// �Ի�������
	enum { IDD = IDD_BATCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSeletepath();
	CString m_path;
	CString m_res;
	CEdit m_ctr_path;
};
