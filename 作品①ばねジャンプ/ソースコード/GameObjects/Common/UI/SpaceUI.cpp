//--------------------------------------------------------------------------------------
// File: SpaceUI.h
//
// スペースUIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpaceUI.h"

#include "Game/DataPath.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
SpaceUI::SpaceUI():
    count(0)
{

}

/// <summary>
/// デストラクタ
/// </summary>
SpaceUI::~SpaceUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void SpaceUI::Initialize(const DirectX::SimpleMath::Vector2& pos)
{
    //  スペース画像1の作成
    m_Space_01 = std::make_unique<UserInterface>();
    m_Space_01->Create(
        DataPath::SPACE01_IMAGE_PATH,
        pos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);

    //  スペース画像2の作成
    m_Space_02 = std::make_unique<UserInterface>();
    m_Space_02->Create(
        DataPath::SPACE02_IMAGE_PATH,
        pos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);
}

/// <summary>
/// 描画
/// </summary>
void SpaceUI::Render()
{
    //  スペース画像1の描画
    m_Space_01->Render();
    //  スペース画像2の描画
    if (count % 90 > 45) m_Space_02->Render();
    count++;
}