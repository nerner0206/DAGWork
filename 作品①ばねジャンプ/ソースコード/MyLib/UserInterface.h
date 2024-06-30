//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// UI基底クラスのヘッダーファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#pragma once
#ifndef USER_INTERFACE_DEFINED
#define USER_INTERFACE_DEFINED

#include "MyLib/UserResources.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

//	UIのアンカーポイントの列挙数
enum ANCHOR
{
	TOP_LEFT = 0,
	TOP_CENTER,
	TOP_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
};

/// <summary>
/// UI基底クラス
/// </summary>
class UserInterface
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UserInterface();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UserInterface();

	/// <summary>
	/// テクスチャリソースの読み込み
	/// </summary>
	/// <param name="path">ファイル名</param>
	void LoadTexture(const wchar_t* path);

	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="path">ファイル名</param>
	/// <param name="position">座標</param>
	/// <param name="scale">拡大率</param>
	/// <param name="anchor">アンカーポイント</param>
	void Create(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		ANCHOR anchor);

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	/// <summary>
	/// 画像サイズの取得
	/// </summary>
	/// <returns>画像サイズ</returns>
	const DirectX::SimpleMath::Vector2 GetTextureSize() { return m_textureSize; }

	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const DirectX::SimpleMath::Vector2& scale) { m_scale = scale; }
	/// <summary>
	/// 拡大率の取得
	/// </summary>
	/// <returns>拡大率</returns>
	const DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns></returns>
	const DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

	/// <summary>
	/// アンカーポイントの設定
	/// </summary>
	/// <param name="anchor">アンカーポイント</param>
	void SetAnchor(const ANCHOR& anchor) { m_anchor = anchor; };
	/// <summary>
	/// アンカーポイントの取得
	/// </summary>
	/// <returns>アンカーポイント</returns>
	const ANCHOR GetAnchor() { return m_anchor; }

	/// <summary>
	/// 縦横比の設定
	/// </summary>
	/// <param name="ratio">比率</param>
	void SetRenderRatio(const float& ratio) { m_renderRatio = ratio; }
	/// <summary>
	/// 縦横比の取得
	/// </summary>
	/// <returns>比率</returns>
	float GetRenderRatio() const { return m_renderRatio; }

	/// <summary>
	/// 透明度の設定
	/// </summary>
	/// <param name="alpha">透明度</param>
	void SetAlpha(const float& alpha) { m_alpha = alpha; }
	/// <summary>
	/// 透明度の取得
	/// </summary>
	/// <returns>透明度</returns>
	float GetAlpha() const { return m_alpha; }

public:
	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
	};

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//	画像の縦横サイズ
	DirectX::SimpleMath::Vector2 m_textureSize;

	//	拡大率
	DirectX::SimpleMath::Vector2 m_scale;
	//	座標
	DirectX::SimpleMath::Vector2 m_position;

	//	アンカーポイント
	ANCHOR m_anchor;

	//	縦横比
	float m_renderRatio;

	//	透明度
	float m_alpha;

private:
	/// <summary>
	/// シェーダーの作成
	/// </summary>
	void CreateShader();
};
#endif // !USER_INTERFACE_DEFINED