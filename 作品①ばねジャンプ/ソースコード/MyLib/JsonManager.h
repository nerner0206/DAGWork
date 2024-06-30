//--------------------------------------------------------------------------------------
// File: JsonManager.h
//
// json管理クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef JSON_MANAGER_DEFINED
#define JSON_MANAGER_DEFINED

#include "ThirdLib/nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <Windows.h>

/// <summary>
/// json管理クラス
/// </summary>
class JsonManager
{
public:
	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="fileName">ファイルパス</param>
	static nlohmann::json LoadFile(const char* fileName)
	{
		nlohmann::json j;

		//	ファイルを読み込み用で開く
		std::ifstream ifs;
		ifs.open(fileName, std::ios::in, std::ios::binary);
		if (!ifs)
		{
			MessageBoxA(0, "ファイルを開けませんでした。", NULL, MB_OK);
			return j;
		}
		//	jsonファイルに書き込む
		ifs >> j;
		//	閉じる
		ifs.close();

		//	返す
		return j;
	}

	/// <summary>
	/// 書き込み
	/// </summary>
	/// <param name="fileName"></param>
	/// <param name="j"></param>
	static  void SaveFile(const char* fileName, const nlohmann::json& j)
	{
		//	ファイルを書き込み用で開く
		std::ofstream ofs;
		ofs.open(fileName, std::ios::out, std::ios::binary);
		if (!ofs)
		{
			MessageBoxA(0, "ファイルを開けませんでした。", NULL, MB_OK);
			return;
		}
		//	文字列に変換
		std::string input = j.dump();
		std::string output;
		for (char ch : input)
		{
			if(ch == '}' || ch == ']')output.push_back('\n');
			output.push_back(ch);
			if (ch == '{' || ch == ',' || ch == '[') output.push_back('\n');
		}
		//	書き込む
		ofs << output;
		//	閉じる
		ofs.close();
	}
};
#endif // !JSON_MANAGER_DEFINED

