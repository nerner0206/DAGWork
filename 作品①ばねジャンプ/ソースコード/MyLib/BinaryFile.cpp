//--------------------------------------------------------------------------------------
// File: BinaryFile.cpp
//
// バイナリファイル読み込みクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BinaryFile.h"

#include <fstream>
#include <assert.h>

/// <summary>
/// コンストラクタ
/// </summary>
BinaryFile::BinaryFile() :
	m_size(0)
{
	
}

/// <summary>
/// ファイルの読み込み
/// </summary>
/// <param name="fileName">ファイル名</param>
/// <returns>バイナリファイルクラス</returns>
BinaryFile BinaryFile::LoadFile(const wchar_t * fileName)
{
	//	返す変数
	BinaryFile bin;

	//	ファイルを開く
	std::ifstream ifs;
	ifs.open(fileName, std::ios::in | std::ios::binary);

	// 読み込み失敗時、強制終了
	assert(ifs);

	// ファイルサイズを取得
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	bin.m_size = (unsigned int)(eofPos - begPos);

	// 読み込むためのメモリを確保
	bin.m_data.reset(new char[bin.m_size]);

	// ファイル先頭からバッファへコピー 
	ifs.read(bin.m_data.get(), bin.m_size);

	// ファイルを閉じる
	ifs.close();

	//	バイナリファイルを返す
	return bin;
}