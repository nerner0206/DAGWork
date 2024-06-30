//--------------------------------------------------------------------------------------
// File: BinaryFile.h
//
// バイナリファイル読み込みクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BINARY_FILE_DEFINED
#define BINARY_FILE_DEFINED

#include <memory>

/// <summary>
/// バイナリファイル読み込みクラス
/// </summary>
class BinaryFile
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BinaryFile();

	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>バイナリファイルクラス</returns>
	static BinaryFile LoadFile(const wchar_t* fileName);

	/// <summary>
	/// データの取得
	/// </summary>
	/// <returns>データのポインタ</returns>
	char* GetData() { return m_data.get(); }
	/// <summary>
	/// データサイズの取得
	/// </summary>
	/// <returns>データサイズ</returns>
	unsigned int GetSize() { return m_size; }

private:
	// データ
	std::unique_ptr<char[]> m_data;
	// サイズ
	unsigned int m_size;
};
#endif // !BINARY_FILE_DEFINED