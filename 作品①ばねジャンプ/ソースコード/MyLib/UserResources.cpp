//--------------------------------------------------------------------------------------
// File: UserResources.cpp
//
// 様々な場所で使用するユーザーリソースクラスのソースファイル（シングルトン化）
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "UserResources.h"

std::unique_ptr<UserResources> UserResources::s_userResources = nullptr;

/// <summary>
/// コンストラクタ
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
///	デストラクタ
/// </summary>
UserResources::~UserResources()
{

}