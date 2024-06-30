//--------------------------------------------------------------------------------------
// File: SpringPart.h
//
// プレイヤーばねの部品クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#ifndef SPRING_PART_DEFINED
#define SPRING_PART_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// プレイヤーばねの部品クラス
/// </summary>
class SpringPart : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpringPart();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpringPart();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="fileName">モデルのファイルパス</param>
	void Initialize(const wchar_t* fileName);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void Render(
		const DirectX::SimpleMath::Matrix& world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 影描画
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	void ShadowRender(
		const DirectX::SimpleMath::Matrix& world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

private:
	//	モデルのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;

	//	ベクトル
	DirectX::SimpleMath::Vector3 m_vel;

	//	ワールド行列
	DirectX::SimpleMath::Matrix m_world;
};
#endif // !SPRING_PART_DEFINED
