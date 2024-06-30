//--------------------------------------------------------------------------------------
// File: SkyDome.h
//
// スカイドームクラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#ifndef SKY_DOME_DEFINED
#define SKY_DOME_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// スカイドームクラス
/// </summary>
class SkyDome : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SkyDome();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SkyDome();

	/// <summary>
	/// 自転
	/// </summary>
	/// <param name="speed">回転速度</param>
	void RotUpdate(const float& speed);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

private:
	//	モデルクラスのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;
};
#endif // !SKY_DOME_DEFINED
