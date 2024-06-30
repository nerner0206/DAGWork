//--------------------------------------------------------------------------------------
// File: CounterUI.h
//
// カウンターUIクラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "CounterUI.h"

#include "Game/DataPath.h"

using namespace DirectX;

//	二桁目の座標のオフセット
const SimpleMath::Vector2 CounterUI::FIRST_OFFSET = SimpleMath::Vector2(80, 0);
//	二桁目の座標のオフセット
const SimpleMath::Vector2 CounterUI::SECOND_OFFSET = SimpleMath::Vector2(40, 0);
//	三桁目の座標のオフセット
const SimpleMath::Vector2 CounterUI::THIRD_OFFSET = SimpleMath::Vector2(-40, 0);
//	四桁目の座標のオフセット
const SimpleMath::Vector2 CounterUI::FOURTH_OFFSET = SimpleMath::Vector2(-80, 0);

/// <summary>
/// コンストラクタ
/// </summary>
CounterUI::CounterUI()
{

}

/// <summary>
/// デストラクタ
/// </summary>
CounterUI::~CounterUI()
{

}

/// <summary>
/// 初期化
/// </summary>
void CounterUI::Initialize(const DirectX::SimpleMath::Vector2& pos)
{
    //  中心座標
    m_centerPos = pos;

    //  中心座標から各桁の座標の計算
    m_firstPos = m_centerPos + FIRST_OFFSET;
    m_secondPos = m_centerPos + SECOND_OFFSET;
    m_thirdPos = m_centerPos + THIRD_OFFSET;
    m_fourthPos = m_centerPos + FOURTH_OFFSET;

    //  中心UIの生成
    m_centerUI = std::make_unique<UserInterface>();
    m_centerUI->Create(
        DataPath::TIMER_CENTER_IMAGE_PATH,
        m_centerPos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);

    //  各数字UIの生成
    for (int i = 0; i < DataPath::NUMBER_IMAGE_NUMBER; i++)
    {
        //  生成する
        std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>();
        ui->Create(
            DataPath::NUMBER_IMAGE_PATHs[i],
            SimpleMath::Vector2::Zero,
            SimpleMath::Vector2::One,
            ANCHOR::MIDDLE_CENTER);

        //  配列へ格納
        m_numbersUI.push_back(std::move(ui));
    }
}

/// <summary>
/// 描画
/// </summary>
void CounterUI::Render(const int& num)
{
    if (num > 3600) return;

    //  中心UIの描画
    m_centerUI->Render();

    //  分
    int minute = num / 60;
    //  秒
    int second = num % 60;

    //  一桁目
    int n = second % DataPath::NUMBER_IMAGE_NUMBER;
    //  座標の設定
    m_numbersUI[n]->SetPosition(m_firstPos);
    //  描画
    m_numbersUI[n]->Render();

    //  二桁目
    n = second / DataPath::NUMBER_IMAGE_NUMBER;
    //  座標の設定
    m_numbersUI[n]->SetPosition(m_secondPos);
    //  描画
    m_numbersUI[n]->Render();

    //  三桁目
    n = minute % DataPath::NUMBER_IMAGE_NUMBER;
    //  座標の設定
    m_numbersUI[n]->SetPosition(m_thirdPos);
    //  描画
    m_numbersUI[n]->Render();

    //  四桁目
    n = minute / DataPath::NUMBER_IMAGE_NUMBER;
    //  座標の設定
    m_numbersUI[n]->SetPosition(m_fourthPos);
    //  描画
    m_numbersUI[n]->Render();
}