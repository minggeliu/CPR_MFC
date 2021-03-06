#pragma once
#include "afxwin.h"

#include <vector>


// CBATCHDlg 对话框

class CBATCHDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBATCHDlg)

public:
	CBATCHDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBATCHDlg();

// 对话框数据
	enum { IDD = IDD_BATCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSeletepath();
	CString m_path;
	CString m_res;
	CEdit m_ctr_path;
	CString m_savepath;
	afx_msg void OnBnClickedButtonSavepath();
	afx_msg void OnBnClickedButtonLocation();
	std::vector<CString>  m_images;
	afx_msg void OnBnClickedButtonChannel1();
	afx_msg void OnBnClickedButtonJudge();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonSegment();
	afx_msg void OnBnClickedButtonIdentify();
	afx_msg void OnBnClickedButtonRecognise();
	afx_msg void OnBnClickedButtonRecogniseothers();
	afx_msg void OnBnClickedButtonPlaterecognize();
	afx_msg void OnBnClickedButtonBinary();
	afx_msg void OnBnClickedButtonLocation2();
	afx_msg void OnBnClickedButtonSegment2();
	afx_msg void OnBnClickedButtonResize();
	afx_msg void OnBnClickedButtonPlaterecognize2();
};
