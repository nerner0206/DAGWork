//--------------------------------------------------------------------------------------
// File: PlayCamera.h
//
// �v���C�J�����N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef PLAY_CAMERA_DEFINED
#define PLAY_CAMERA_DEFINED

#include "GameObjects/Common/Camera.h"
#include "MyLib/JsonManager.h"

class Player;

/// <summary>
/// �v���C�J�����N���X
/// </summary>
class PlayCamera : public Camera
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="startPos">�J�n���W</param>
	/// <param name="endPos">�I�����W</param>
	PlayCamera(
		const DirectX::SimpleMath::Vector3& startPos,
		const DirectX::SimpleMath::Vector3& endPos);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayCamera();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="player">�v���C���[�N���X�̃|�C���^</param>
	void Update(const float& elapsedTime, Player* player);

	/// <summary>
	/// �J�n�O�X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="startPos">�J�n���W</param>
	/// <param name="endPos">�I�����W</param>
	/// <param name="duration">�Ԋu</param>
	/// <returns>�X�V�I���t���O</returns>
	bool BeforeUpdate(
		const float& elapsedTime, 
		const DirectX::SimpleMath::Vector3& startPos, 
		const DirectX::SimpleMath::Vector3& endPos,
		const float& duration);

	/// <summary>
	/// �f�o�b�O�p�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void DebugRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// �f�[�^�̕ۑ�
	/// </summary>
	void SaveData();

private:
	//	�f�[�^�̐�
	static const int DATA_NUMBER = 5;
	//	�f�[�^�A�N�Z�X������z��
	static const std::string DATA_STRING[DATA_NUMBER];

private:
	//	json�t�@�C��
	nlohmann::json m_cameraData;

	//	���W�̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_offset;

	//	X���W�̃I�t�Z�b�g�ő�l
	float m_maxOffset_x;

	//	Z���W�̃I�t�Z�b�g�ő�l
	float m_maxOffset_z;
	//	Z���W�̃I�t�Z�b�g�ŏ��l
	float m_minOffset_z;

	//	�����_�̕ύX����
	float m_targetDistance;

	//	�ύX�t���O
	bool m_swich;

	//	��ԗ�
	float m_t;
	//	�^�C�}�[
	float m_timer;

private:
	/// <summary>
	/// ���W�̍X�V
	/// </summary>
	/// <param name="pos">����W</param>
	/// <param name="t">����</param>
	/// <returns>���W</returns>
	DirectX::SimpleMath::Vector3 EyeUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const float& t);

	/// <summary>
	/// �ڕW���W�̍X�V
	/// </summary>
	/// <param name="pos">����W</param>
	/// <param name="forward">���ʍ��W</param>
	/// <param name="t">����</param>
	/// <returns>�ڕW���W</returns>
	DirectX::SimpleMath::Vector3 TargetUpdate(
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& forward,
		const float& t);

	/// <summary>
	/// �I�t�Z�b�g�̕ύX
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void ChangeOffset(const float& elapsedTime);
};
#endif // !PLAY_CAMERA_DEFINED