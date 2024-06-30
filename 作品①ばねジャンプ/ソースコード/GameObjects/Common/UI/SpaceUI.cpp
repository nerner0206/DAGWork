//--------------------------------------------------------------------------------------
// File: SpaceUI.h
//
// �X�y�[�XUI�N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SpaceUI.h"

#include "Game/DataPath.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SpaceUI::SpaceUI():
    count(0)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpaceUI::~SpaceUI()
{

}

/// <summary>
/// ������
/// </summary>
void SpaceUI::Initialize(const DirectX::SimpleMath::Vector2& pos)
{
    //  �X�y�[�X�摜1�̍쐬
    m_Space_01 = std::make_unique<UserInterface>();
    m_Space_01->Create(
        DataPath::SPACE01_IMAGE_PATH,
        pos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);

    //  �X�y�[�X�摜2�̍쐬
    m_Space_02 = std::make_unique<UserInterface>();
    m_Space_02->Create(
        DataPath::SPACE02_IMAGE_PATH,
        pos,
        SimpleMath::Vector2::One,
        ANCHOR::MIDDLE_CENTER);
}

/// <summary>
/// �`��
/// </summary>
void SpaceUI::Render()
{
    //  �X�y�[�X�摜1�̕`��
    m_Space_01->Render();
    //  �X�y�[�X�摜2�̕`��
    if (count % 90 > 45) m_Space_02->Render();
    count++;
}