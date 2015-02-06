// BATCHDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CPR.h"
#include "BATCHDlg.h"
#include "afxdialogex.h"

#include "PlateLocate.h"
#include "PlateJudge.h"
#include "PlateDetect.h"
#include "CharsIdentify.h"
#include "CharsSegment.h"
#include "CharsRecognise.h"
#include "PlateRecognize.h"

#include <fstream>
#include <direct.h>

#include "prep.h"



// CBATCHDlg �Ի���

IMPLEMENT_DYNAMIC(CBATCHDlg, CDialogEx)

CBATCHDlg::CBATCHDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBATCHDlg::IDD, pParent)
{
	m_path = _T("");
	m_res = _T("");
	m_savepath = _T("");
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
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_savepath);
}


BEGIN_MESSAGE_MAP(CBATCHDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELETEPATH, &CBATCHDlg::OnBnClickedButtonSeletepath)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPATH, &CBATCHDlg::OnBnClickedButtonSavepath)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION, &CBATCHDlg::OnBnClickedButtonLocation)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL1, &CBATCHDlg::OnBnClickedButtonChannel1)
	ON_BN_CLICKED(IDC_BUTTON_JUDGE, &CBATCHDlg::OnBnClickedButtonJudge)
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CBATCHDlg::OnBnClickedButtonDetect)
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT, &CBATCHDlg::OnBnClickedButtonSegment)
	ON_BN_CLICKED(IDC_BUTTON_IDENTIFY, &CBATCHDlg::OnBnClickedButtonIdentify)
	ON_BN_CLICKED(IDC_BUTTON_RECOGNISE, &CBATCHDlg::OnBnClickedButtonRecognise)
	ON_BN_CLICKED(IDC_BUTTON_IDENTIFYOTHERS, &CBATCHDlg::OnBnClickedButtonRecogniseothers)
	ON_BN_CLICKED(IDC_BUTTON_PLATERECOGNIZE, &CBATCHDlg::OnBnClickedButtonPlaterecognize)
	ON_BN_CLICKED(IDC_BUTTON_BINARY, &CBATCHDlg::OnBnClickedButtonBinary)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION2, &CBATCHDlg::OnBnClickedButtonLocation2)
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT2, &CBATCHDlg::OnBnClickedButtonSegment2)
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
			m_images.clear();

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
					m_images.push_back(filepathname);
				}
			}

			for(vector<CString>::size_type v_i = 0; v_i != m_images.size(); ++v_i)
			{
				res_str += m_images[v_i];
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


void CBATCHDlg::OnBnClickedButtonSavepath()
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
			this->m_savepath = strFolderPath;
			
			UpdateData(FALSE);
			
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}


void CBATCHDlg::OnBnClickedButtonLocation()
{

	CPlateLocate plate;
	plate.setDebug(0);
	plate.setGaussianBlurSize(5);
	plate.setMorphSizeWidth(17);
	plate.setMorphSizeHeight(10);
	plate.setVerifyMin(8);
	plate.setVerifyMax(80);


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateLocate(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			for (int j = 0; j < num; j++)
			{
				Mat resultMat = resultVec[j];
				//IplImage pImg = resultMat;
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << v_i << "_location" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}

}


void CBATCHDlg::OnBnClickedButtonChannel1()
{
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);

		for (cv::Mat_<cv::Vec3b>::iterator it= src.begin<cv::Vec3b>() ; it!= src.end<cv::Vec3b>(); ++it) {  
			int tmp = (abs((*it)[0] - (*it)[1]) + abs((*it)[0] - (*it)[2]));
			if(tmp > 255) tmp = 255;
			/*if((*it)[2] > 100) tmp = 0;
			if(abs((*it)[2] - (*it)[1]) > 70) tmp = 0;*/
			(*it)[0] = (*it)[1] = (*it)[2] = tmp;
		}  

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << v_i << "_channel1" << ".jpg";
		imwrite(ss.str(), src);

	}

	MessageBox("Finish");
}


void CBATCHDlg::OnBnClickedButtonJudge()
{
	// TODO:
	CPlateJudge plate;
	plate.setDebug(0);


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateJudge(src);
		if (result == 1)
		{
			stringstream ss(stringstream::in | stringstream::out);
			ss << this->m_savepath << "\\" << v_i << "_judge" << ".jpg";
			imwrite(ss.str(), src);
		}
	}
}


void CBATCHDlg::OnBnClickedButtonDetect()
{
	// TODO: 
	CPlateDetect plate;


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateDetect(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			for (int j = 0; j < num; j++)
			{
				Mat resultMat = resultVec[j];
				//IplImage pImg = resultMat;
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << v_i << "_detect" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}


void CBATCHDlg::OnBnClickedButtonSegment()
{	
	_mkdir(m_savepath + "\\chinese");
	_mkdir(m_savepath + "\\others");

	CCharsSegment plate;

	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.charsSegment(src, resultVec);
		if (0 == result)
		{
			for (int j = 0; j < resultVec.size(); j++)
			{
				Mat resultMat = resultVec[j];
				stringstream ss(stringstream::in | stringstream::out);
				if(0 == j)	ss << m_savepath << "\\chinese\\" << v_i << "_segment" << j << ".jpg";
				else ss << m_savepath << "\\others\\" << v_i << "_segment" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}


void CBATCHDlg::OnBnClickedButtonIdentify()
{
	CCharsIdentify plate;
	string res_str = "";
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";

		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 0);
		string str_cr = plate.charsIdentify(src, true);
		if ("" != str_cr)
		{
			res_str += str_cr;
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\identify_chinese.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonRecognise()
{	
	CCharsRecognise plate;
	string res_str = "";
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";

		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		string str_cr;
		int result = plate.charsRecognise(src, str_cr);
		if (result == 0)
		{
			res_str += str_cr;
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\recognise.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonRecogniseothers()
{		
	CCharsIdentify plate;
	string res_str = "";
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";

		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 0);
		string str_cr = plate.charsIdentify(src, false);
		if ("" != str_cr)
		{
			res_str += str_cr;
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\identify_others.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();

}


void CBATCHDlg::OnBnClickedButtonPlaterecognize()
{	
	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	pr.setGaussianBlurSize(5);
	pr.setMorphSizeWidth(17);

	pr.setVerifyMin(3);
	pr.setVerifyMax(20);

	pr.setLiuDingSize(7);
	pr.setColorThreshold(150);

	string res_str = "";
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<string> plateVec;

		res_str += m_images[v_i];
		res_str += " Result: ";

		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		string str_cr;

		int result = pr.plateRecognize(src, plateVec);
		if (result == 0)
		{
			for(int i = 0; i < plateVec.size(); ++i) { res_str += " "; res_str += plateVec[i]; }
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	m_res = res_str.c_str();
	UpdateData(FALSE);

	CString filePath = this->m_savepath + "\\plate_recognize.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonBinary()
{
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 0);

		Mat img_threshold;
		//threshold(src, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
		threshold(src, img_threshold, 100, 255, CV_THRESH_BINARY);

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << v_i << "_binary" << ".jpg";
		imwrite(ss.str(), img_threshold);

	}

	MessageBox("Finish.");
}


void CBATCHDlg::OnBnClickedButtonLocation2()
{

	CPlateLocate plate;	plate.setDebug(1);
	plate.setVerifyMax(500);
	plate.setVerifyMin(75);
	
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{			
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		vector<Mat> resultVec;
		Mat src = imread(str, 1);
		int result = plate.plateLocate2(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			for (int j = 0; j < num; j++)
			{
				Mat resultMat = resultVec[j];
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << name << "_location" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}


void CBATCHDlg::OnBnClickedButtonSegment2()
{
	_mkdir(m_savepath + "\\chinese");
	_mkdir(m_savepath + "\\others");

	CCharsSegment plate;

	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.charsSegment2(src, resultVec);
		if (0 == result)
		{
			for (int j = 0; j < resultVec.size(); j++)
			{
				Mat resultMat = resultVec[j];
				stringstream ss(stringstream::in | stringstream::out);
				if(0 == j)	ss << m_savepath << "\\chinese\\" << v_i << "_segment" << j << ".jpg";
				else ss << m_savepath << "\\others\\" << v_i << "_segment" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}
