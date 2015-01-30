#pragma once
//////////////////////////////////////////////////////////////////////////
// Name:	    chars_identify Header
// Version:		1.1
// Date:	    2014-09-25
// MData:		2015-01-30
// Author:	    liuruoze
// MAuthor:		WayneWu
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CCharsIdentify 
//////////////////////////////////////////////////////////////////////////
#ifndef __CHARS_IDENTIFY_H__
#define __CHARS_IDENTIFY_H__

#include <highgui.h>
#include <map>

using namespace cv;
	
class CCharsIdentify 
{
public:
	CCharsIdentify();

	//! �ַ��ָ�
	string charsIdentify(Mat, bool);

	//! �ַ�����
	int classify(Mat, bool);

	//create the accumulation histograms,img is a binary image, t is ˮƽ��ֱ
	Mat ProjectedHistogram(Mat img, int t);

	//! ����ַ�������ͼ
	Mat features(Mat in, int sizeData);

	//! װ��ANNģ��
	void LoadModel();

	//! װ��ANNģ��
	void LoadModel(string s);

	//! �������ȡģ��·��
	inline void setModelPath(string path){	m_path = path;	}
	inline string getModelPath() const{	 return m_path;	}

private:
	//��ʹ�õ�SVMģ��
	CvANN_MLP ann;

	//! ģ�ʹ洢·��
	string m_path;

	//! �����ߴ�
	int m_predictSize;

	//! ʡ�ݶ�Ӧmap
	std::map<string, string> m_map;
};

#endif /* endif __CHARS_IDENTIFY_H__ */