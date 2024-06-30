//--------------------------------------------------------------------------------------
// File: TitleTextModels.h
//
// タイトルの文字モデル管理クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TitleTextModels.h"

using namespace DirectX;

//	初期座標
const SimpleMath::Vector3 TitleTextModels::INIT_DEF_POSITION = SimpleMath::Vector3(-3.0f, 1.3f, 0.0f);
//	座標の間隔
const float TitleTextModels::INIT_SPACE = 0.75f;

//	縮む速度
const float TitleTextModels::SHRINK_SPEED = 0.95f;
//	伸びる速度
const float TitleTextModels::EXTEND_SPEED = 1.3f;

//	拡大率の下限
const float TitleTextModels::MIN_SCALE = 0.2f;
//	拡大率のデフォルト
const float TitleTextModels::DEF_SCALE = 1.0f;

//	ジャンプ力
const float TitleTextModels::JUMP_POWER = 3.2f;
//	重力加速度
const float TitleTextModels::GRAVITY_SCALE = -0.08;

/// <summary>
/// コンストラクタ
/// </summary>
TitleTextModels::TitleTextModels()
{

}

/// <summary>
/// デストラクタ
/// </summary>
TitleTextModels::~TitleTextModels()
{

}

/// <summary>
/// 初期化
/// </summary>
void TitleTextModels::Initialize()
{
	//	文字配列の生成
	for (int i = 0; i < DataPath::TITLE_TEXT_MODEL_NUMBER; i++)
	{
		//	文字モデルの生成
		std::unique_ptr<TextModel> text = std::make_unique<TextModel>();
		//	初期化
		text->Initialize(DataPath::TITLE_TEXT_MODEL_PATHs[i]);
		//	座標の設定
		SimpleMath::Vector3 pos = INIT_DEF_POSITION;
		pos.x += (i * INIT_SPACE);
		text->SetPos(pos);
		//	配列に格納
		m_textModels.push_back(std::move(text));

		//	ジャンプフラグの追加
		m_isJumps.push_back(false);
		//	速度の追加
		m_velocities.push_back(SimpleMath::Vector3::Zero);
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">フレーム間の経過時間（秒）</param>
void TitleTextModels::Update(const float& elapsedTime)
{
	//	文字配列の生成
	for (int i = 0; i < DataPath::TITLE_TEXT_MODEL_NUMBER; i++)
	{
		//	座標を取得
		SimpleMath::Vector3 pos = m_textModels[i]->GetPos();
		//	拡大率を取得
		SimpleMath::Vector3 sca = m_textModels[i]->GetSca();

		if (m_isJumps[i])
		{
			//	徐々に縮む
			sca.y *= SHRINK_SPEED;

			//	一定以上縮んだら戻す
			if (sca.y <= MIN_SCALE)
			{
				//	下限値に修正
				sca.y = MIN_SCALE;

				//	非ジャンプ状態へ
				m_isJumps[i] = false;

				//	跳ね返る(ばねの速度に応じて変更する)
				m_velocities[i] = SimpleMath::Vector3::Up * JUMP_POWER;
			}
		}
		else
		{
			//	徐々に伸ばす
			if (sca.y < DEF_SCALE)
			{
				sca.y *= EXTEND_SPEED;
				if (sca.y > DEF_SCALE) sca.y = DEF_SCALE;
			}

			//	重力加速度の加算
			m_velocities[i].y += GRAVITY_SCALE;
			//	速度の加算
			pos += (m_velocities[i] * elapsedTime);

			if (pos.y < 0.0f)
			{
				//	当たらない位置に移動
				pos.y = 0.0f;
				//	移動量を消す
				m_velocities[i] = SimpleMath::Vector3::Zero;
				//	ジャンプ状態へ
				m_isJumps[i] = true;
			}
		}

		//	座標の設定
		m_textModels[i]->SetPos(pos);
		//	拡大率の設定
		m_textModels[i]->SetSca(sca);
	}
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void TitleTextModels::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& textModel : m_textModels)
	{
		textModel->Render(view, proj);
	}
}

/// <summary>
/// 影描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void TitleTextModels::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& textModel : m_textModels)
	{
		textModel->ShadowRender(view, proj);
	}
}

/// <summary>
/// 終了
/// </summary>
void TitleTextModels::Finalize()
{
	for (auto& textModel : m_textModels)
	{
		textModel->Finalize();
	}
}