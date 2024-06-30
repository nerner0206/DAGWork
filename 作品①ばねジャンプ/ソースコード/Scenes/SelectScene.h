//--------------------------------------------------------------------------------------
// File: SelectScene.h
//
// �Z���N�g�V�[���N���X�̃w�b�_�[�t�F�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef SELECT_SCENE_DEFINED
#define SELECT_SCENE_DEFINED

#include "MyLib/IScene.h"

#include <vector>

class TextModel;
class Cloud;

class SpaceUI;

/// <summary>
/// �Z���N�g�V�[���N���X
/// </summary>
class SelectScene : public IScene
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SelectScene();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SelectScene();

	/// <summary>
	/// ������
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
	//	�X�J�C�h�[���̉�]���x
	static const float SKYDOME_ROT_SPEED;

	//	�J�����̉�]�����萔
	static const float MODEL_DISTANCE;

	//	���f���̍��WY�EZ
	static const float MODEL_POS_Y;
	static const float MODEL_POS_Z;

	//	�e�L�X�g���f���̍��WY
	static const float TEXT_MODEL_POS_Y;

	//	���f���̏k���{��
	static const float MODEL_MIN_SCALE;

	//	�J�����̖ڕW���W�萔
	static const DirectX::SimpleMath::Vector3 CAMERA_TARGET_POSITION;

	//	���C�g�̉e���͈�
	static const float LIGHT_RANGE;

	//	�X�y�[�XUI�̍���
	static const int SPACE_UI_HEIGHT = 600;

	//	�^�C�g���摜�̊g�嗦
	static const float TITLE_IMAGE_SCALE;
	//	���摜�̊Ԋu
	static const int ARROW_IMAGE_DISTANCE = 300;

private:
	//	�������f���N���X�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<TextModel>> m_textModels;
	//	�_�N���X�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<Cloud>> m_clouds;

	//	�X�e�[�W�ԍ�
	int m_stageNum;
	//	�ȑO�̃X�e�[�W�ԍ�
	int m_stageBeforeNum;

	//	�J�����̌��݂̍��W
	DirectX::SimpleMath::Vector3 m_cameraNowPos;
	//	�J�����̎��̍��W
	DirectX::SimpleMath::Vector3 m_cameraNextPos;

	//	�X�e�[�W�ύX��
	bool isChange;

	//	�^�C�}�[
	float m_timer;

	//	�Z���N�g�^�C�g��UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_selectTitleUI;
	//	�E���UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_rightArrowUI;
	//	�����UI�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_leftArrowUI;
	//	�X�^�[�gUI�N���X�̃��j�[�N�|�C���^
	std::unique_ptr<SpaceUI> m_spaceUI;

private:
	/// <summary>
	/// �X�e�[�W�ύX
	/// </summary>
	void ChangeStage();
};
#endif		// SELECT_SCENE_DEFINED