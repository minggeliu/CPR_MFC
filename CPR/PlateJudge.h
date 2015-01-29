#pragma once
//////////////////////////////////////////////////////////////////////////
// Name:	    plate_judge Header
// Version:		1.1
// Date:	    2014-09-22
// MData:		2015-01-29
// Author:	    liuruoze
// MAuthor:		WayneWu
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:  
// Defines CPlateLocate
//////////////////////////////////////////////////////////////////////////
#ifndef __PLATE_JUDGE_H__
#define __PLATE_JUDGE_H__

#include <highgui.h>

using namespace cv;

class CPlateJudge 
{
public:
	CPlateJudge();

	//! �����ж�
	int plateJudge(const vector<Mat>&, vector<Mat>&);
	int plateJudge(Mat src);

	//! ֱ��ͼ����
	Mat histeq(Mat, int = 0);

	//! װ��SVMģ��
	void LoadModel();

	//! װ��SVMģ��
	void LoadModel(string s);

	//! �������ȡģ��·��
	inline void setModelPath(string path){	m_path = path;	}
	inline string getModelPath() const{	 return m_path;	}

	inline void setDebug(int param){ m_debug = param;}

	//! �Ƿ�������ģʽ������Ĭ��0����ر�
	static const int DEFAULT_DEBUG = 0;

private:
	//��ʹ�õ�SVMģ��
	CvSVM svm;

	//! ģ�ʹ洢·��
	string m_path;

protected:
	//! �Ƿ�������ģʽ��0�رգ���0����
	int m_debug;
};

#endif /* endif __PLATE_JUDGE_H__ */