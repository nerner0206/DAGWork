//--------------------------------------------------------------------------------------
// File: SystemWindow.h
//
// 設定画面クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#ifndef SYSTEM_WINDOW_DEFINED
#define SYSTEM_WINDOW_DEFINED

#include <vector>

class UserInterface;
class SystemUI;
class IScene;

/// <summary>
/// 設定画面クラス
/// </summary>
class SystemWindow
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SystemWindow();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SystemWindow();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	void Initialize(const int& mouseNumber);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="scene">シーン基底クラスのポインタ</param>
	void Update(IScene* scene);
	/// <summary>
	/// 描画
	/// </summary>
	void Render();
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// 設定画面の開始
	/// </summary>
	/// <param name="scene">シーンクラスのポインタ</param>
	void OnWindow(IScene* scene);
	/// <summary>
	/// 設定画面の終了
	/// </summary>
	/// <param name="scene">シーンクラスのポインタ</param>
	void OffWindow(IScene* scene);

	/// <summary>
	/// 設定画面中判定の取得
	/// </summary>
	/// <returns>設定画面中判定</returns>
	const bool GetIsSystemOpen() { return m_isSystemOpen; }

private:
	//	各選択肢の距離
	static const int ITEM_DISTANCE = 130;

private:
	//	設定画面中判定
	bool m_isSystemOpen;

	//	選択番号
	int m_selectNum;
	//	選択最大番号
	int m_selectMaxNum;

	//	各選択肢のユニークポインタ配列
	std::vector<std::unique_ptr<SystemUI>> m_items;

	//	選択フレーム画像のユニークポインタ
	std::unique_ptr<UserInterface> m_itemFrame;
	//	背景画像のユニークポインタ
	std::unique_ptr<UserInterface> m_back;

private:
	/// <summary>
	/// 選択フレームを動かす
	/// </summary>
	void MoveFrame();

	/// <summary>
	/// 各UIの生成
	/// </summary>
	/// <param name="mouseNumber">マウス感度番号</param>
	void CreateUI(const int& mouseNumber);
};
#endif // !SYSTEM_WINDOW_DEFINED
