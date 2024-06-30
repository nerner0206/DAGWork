//--------------------------------------------------------------------------------------
// File: JsonManager.h
//
// json�Ǘ��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef JSON_MANAGER_DEFINED
#define JSON_MANAGER_DEFINED

#include "ThirdLib/nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <Windows.h>

/// <summary>
/// json�Ǘ��N���X
/// </summary>
class JsonManager
{
public:
	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C���p�X</param>
	static nlohmann::json LoadFile(const char* fileName)
	{
		nlohmann::json j;

		//	�t�@�C����ǂݍ��ݗp�ŊJ��
		std::ifstream ifs;
		ifs.open(fileName, std::ios::in, std::ios::binary);
		if (!ifs)
		{
			MessageBoxA(0, "�t�@�C�����J���܂���ł����B", NULL, MB_OK);
			return j;
		}
		//	json�t�@�C���ɏ�������
		ifs >> j;
		//	����
		ifs.close();

		//	�Ԃ�
		return j;
	}

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="j"></param>
	static  void SaveFile(const char* fileName, const nlohmann::json& j)
	{
		//	�t�@�C�����������ݗp�ŊJ��
		std::ofstream ofs;
		ofs.open(fileName, std::ios::out, std::ios::binary);
		if (!ofs)
		{
			MessageBoxA(0, "�t�@�C�����J���܂���ł����B", NULL, MB_OK);
			return;
		}
		//	������ɕϊ�
		std::string input = j.dump();
		std::string output;
		for (char ch : input)
		{
			if(ch == '}' || ch == ']')output.push_back('\n');
			output.push_back(ch);
			if (ch == '{' || ch == ',' || ch == '[') output.push_back('\n');
		}
		//	��������
		ofs << output;
		//	����
		ofs.close();
	}
};
#endif // !JSON_MANAGER_DEFINED

