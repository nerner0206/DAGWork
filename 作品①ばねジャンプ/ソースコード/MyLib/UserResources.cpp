//--------------------------------------------------------------------------------------
// File: UserResources.cpp
//
// �l�X�ȏꏊ�Ŏg�p���郆�[�U�[���\�[�X�N���X�̃\�[�X�t�@�C���i�V���O���g�����j
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "UserResources.h"

std::unique_ptr<UserResources> UserResources::s_userResources = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
UserResources::UserResources():
	m_timer(nullptr),
	m_deviceResources(nullptr),
	m_keyboardTracker(nullptr),
	m_mouseTracker(nullptr),
	m_states(nullptr),
	m_shadowMap(nullptr)
{

}

/// <summary>
///	�f�X�g���N�^
/// </summary>
UserResources::~UserResources()
{

}