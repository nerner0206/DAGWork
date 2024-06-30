//--------------------------------------------------------------------------------------
// File: SystemUI.h
//
// �ݒ�UI�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SYSTEM_UI_DEFINED
#define SYSTEM_UI_DEFINED

#include "MyLib/AudioResources.h"
#include "MyLib/UserInterface.h"
#include "Game/DataPath.h"

class SystemWindow;
class IScene;

/// <summary>
/// �X�y�[�XUI�N���X
/// </summary>
class SystemUI
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SystemUI(const wchar_t* fileName, const DirectX::SimpleMath::Vector2& pos)
	{
		//	�����\�[�X�N���X�̎擾
		m_ar = AudioResources::GetInstance();

		//	�摜�̐���
		m_image = std::make_unique<UserInterface>();
		m_image->Create(
			fileName,
			pos,
			DirectX::SimpleMath::Vector2::One,
			ANCHOR::MIDDLE_CENTER);
	}

	/// <summary>
	/// �����\�[�X�N���X�̎擾
	/// </summary>
	/// <returns>�����\�[�X�N���X�̃|�C���^</returns>
	AudioResources* GetAudioResources() { return m_ar; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const DirectX::SimpleMath::Vector2 GetPos() { return m_image->GetPosition(); }

	/// <summary>
	/// UI�̎擾
	/// </summary>
	/// <returns>UI�̃|�C���^</returns>
	UserInterface* GetImage() { return m_image.get(); }

public:
	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~SystemUI() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
	/// <param name="window">�ݒ��ʃN���X�̃|�C���^</param>
	virtual void Update(IScene* scene, SystemWindow* window) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Render() = 0;

private:
	//	�����\�[�X�N���X�̃|�C���^
	AudioResources* m_ar;
	//	UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_image;
};
#endif // !System_UI_DEFINED