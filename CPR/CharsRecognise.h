#pragma once
//////////////////////////////////////////////////////////////////////////
// Name:	    chars_recognise Header
// Version:		1.1
// Date:	    2014-09-28
// MDate:		2015-01-30
// Author:	    liuruoze
// MAuthod:		WayneWu
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CCharsRecognise
//////////////////////////////////////////////////////////////////////////
#ifndef __CHARS_RECOGNISE_H__
#define __CHARS_RECOGNISE_H__

#include "CharsSegment.h"
#include "CharsIdentify.h"


class CCharsRecognise 
{
public:
	CCharsRecognise();

	//! �ַ��ָ���ʶ��
	int charsRecognise(Mat, String&);
	int charsRecognise2(Mat, String&);

	//! װ��ANNģ��
	void LoadANN(string s);

	//! ��ó�����ɫ
	inline string getPlateType(Mat input) const
	{
		string color = "δ֪";
		int result = m_charsSegment->getPlateType(input);
		if (1 == result)
		{
			color = "����";
		}
		if (2 == result)
		{
			color = "����";
		}
		return color;
	}

	//! ���ñ���
	inline void setLiuDingSize(int param){ m_charsSegment->setLiuDingSize(param);}
	inline void setColorThreshold(int param){ m_charsSegment->setColorThreshold(param);}
	inline void setBluePercent(float param){ m_charsSegment->setBluePercent(param);}
	inline float getBluePercent() const { return m_charsSegment->getBluePercent();}
	inline void setWhitePercent(float param){ m_charsSegment->setWhitePercent(param);}
	inline float getWhitePercent() const { return m_charsSegment->getWhitePercent();}

private:
	//���ַ��ָ�
	CCharsSegment* m_charsSegment;

	//! �ַ�ʶ��
	CCharsIdentify* m_charsIdentify;
};


#endif /* endif __CHARS_RECOGNISE_H__ */