//--------------------------------------------------------------------------------------
// File: BigCloud.h
//
// 大きい雲クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BIG_CLOUD_DEFINED
#define BIG_CLOUD_DEFINED

#include "GameObjects/Object.h"

class IScene;

/// <summary>
/// 大きい雲クラス
/// </summary>
class BigCloud : public Object
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scene">シーンクラスのポインタ</param>
	BigCloud(IScene* scene);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BigCloud();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector3& pos, const float& sca);
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
	//	定数バッファの構造体
	struct ConstantBuffer
	{
		DirectX::SimpleMath::Matrix LightViewProj;		//	ライトのビュー行列
		DirectX::SimpleMath::Vector4 LightPos;			//	ライトの座標
		DirectX::SimpleMath::Vector4 LightDir;			//	ライトの方向ベクトル
	};

private:
	//	現在のシーンクラスのポインタ
	IScene* m_nowScene;

	//	モデルクラスのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;

	//	定数バッファのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//	頂点シェーダーのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダのコムポインタ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

private:
	/// <summary>
	/// シェーダの作成
	/// </summary>
	void CreateShader();
};
#endif // !BIG_CLOUD_DEFINED
