//--------------------------------------------------------------------------------------
// File: TitleScene.h
//
// �^�C�g���V�[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef TITLE_SCENE_DEFINED
#define TITLE_SCENE_DEFINED

#include "MyLib/IScene.h"

class TitleTextModels;
class Cloud;
class BigCloud;

class SpaceUI;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene : public IScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleScene();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleScene();

	/// <summary>
	///	������
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	void Initialize(const int& mouseNumber) override;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime) override;
	/// <summary>
	/// �`��
	/// </summary>
	void Render() override;
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowRender() override;
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize() override;

private:
	//	���C�g�̍��W
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	//	���C�g�̉e���͈�
	static const float LIGHT_RANGE;

	//	�J�����̍��W
	static const DirectX::SimpleMath::Vector3 CAMERA_POSITION;

	//	�_�̍��W
	static const DirectX::SimpleMath::Vector3 CLOUD_POSITION;

	//	�傫���_�̍��W
	static const DirectX::SimpleMath::Vector3 BIG_CLOUD_POSITION;
	//	�傫���_�̊g�嗦
	static const float BIG_CLOUD_SCALE;

	//	�X�J�C�h�[���̉�]���x
	static const float ROT_SPEED;

	//	�X�y�[�XUI�̍��W
	static const DirectX::SimpleMath::Vector2 SPACE_UI_POSITION;

private:
	//	�e�L�X�g���f���Ǘ��N���X�̃��j�[�N�|�C���^
	std::unique_ptr<TitleTextModels> m_titleTextModel;
	//	�_�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<Cloud> m_cloud;
	//	�傫�ȉ_�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<BigCloud> m_bigCloud;

	//	�X�^�[�gUI�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<SpaceUI> m_spaceUI;
};
#endif		// TITLE_SCENE_DEFINED