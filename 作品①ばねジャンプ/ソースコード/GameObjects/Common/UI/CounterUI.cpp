//--------------------------------------------------------------------------------------
// File: CounterUI.h
//
// �J�E���^�[UI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "CounterUI.h"

#include "Game/DataPath.h"

using namespace DirectX;

//	�񌅖ڂ̍��W�̃I�t�Z�b�g
const SimpleMath::Vector2 CounterUI::FIRST_OFFSET = SimpleMath::Vector2(80, 0);
//	�񌅖ڂ̍��W�̃I�t�Z�b�g
const SimpleMath::Vector2 CounterUI::SECOND_OFFSET = SimpleMath::Vector2(40, 0);
//	�O���ڂ̍��W�̃I�t�Z�b�g
const SimpleMath::Vector2 CounterUI::THIRD_OFFSET = SimpleMath::Vector2(-40, 0);
//	�l���ڂ̍��W�̃I�t�Z�b�g
const SimpleMath::Vector2 CounterUI::FOURTH_OFFSET = SimpleMath::Vector2(-80, 0);

/// <summary>
/// �R���X�g���N�^
/// </summary>
CounterUI::CounterUI()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CounterUI::~CounterUI()
{

}

/// <summary>
/// ������
/// </summary>
void CounterUI::Initialize(const DirectX::SimpleMath::Vector2& pos)
{
    //  ���S���W
    m_centerPos = pos;

    //  ���S���W����e���̍��W�̌v�Z
    m_firstPos = m_centerPos + FIRST_OFFSET;
    m_secondPos = m_centerPos + SECOND_OFFSET;
    m_thirdPos = m_centerPos + THIRD_OFFSET;
    m_fourthPos = m_centerPos + FOURTH_OFFSET;

    //  ���SUI�̐���
    m_centerUI = std::make_unique<UserInterface>();
    m_centerUI->Create(
        DataPath::TIMER_CENTER_IMAGE_PATH,
        m_centerPos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);

    //  �e����UI�̐���
    for (int i = 0; i < DataPath::NUMBER_IMAGE_NUMBER; i++)
    {
        //  ��������
        std::unique_ptr<UserInterface> ui = std::make_unique<UserInterface>();
        ui->Create(
            DataPath::NUMBER_IMAGE_PATHs[i],
            SimpleMath::Vector2::Zero,
            SimpleMath::Vector2::One,
            ANCHOR::MIDDLE_CENTER);

        //  �z��֊i�[
        m_numbersUI.push_back(std::move(ui));
    }
}

/// <summary>
/// �`��
/// </summary>
void CounterUI::Render(const int& num)
{
    if (num > 3600) return;

    //  ���SUI�̕`��
    m_centerUI->Render();

    //  ��
    int minute = num / 60;
    //  �b
    int second = num % 60;

    //  �ꌅ��
    int n = second % DataPath::NUMBER_IMAGE_NUMBER;
    //  ���W�̐ݒ�
    m_numbersUI[n]->SetPosition(m_firstPos);
    //  �`��
    m_numbersUI[n]->Render();

    //  �񌅖�
    n = second / DataPath::NUMBER_IMAGE_NUMBER;
    //  ���W�̐ݒ�
    m_numbersUI[n]->SetPosition(m_secondPos);
    //  �`��
    m_numbersUI[n]->Render();

    //  �O����
    n = minute % DataPath::NUMBER_IMAGE_NUMBER;
    //  ���W�̐ݒ�
    m_numbersUI[n]->SetPosition(m_thirdPos);
    //  �`��
    m_numbersUI[n]->Render();

    //  �l����
    n = minute / DataPath::NUMBER_IMAGE_NUMBER;
    //  ���W�̐ݒ�
    m_numbersUI[n]->SetPosition(m_fourthPos);
    //  �`��
    m_numbersUI[n]->Render();
}