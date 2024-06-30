//--------------------------------------------------------------------------------------
// File: TitleTextModel.h
//
// �^�C�g���̕������f���Ǘ��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef TITLE_TEXT_MODEL_DEFINED
#define TITLE_TEXT_MODEL_DEFINED

#include "GameObjects/Common/TextModel.h"

#include <vector>

/// <summary>
/// �^�C�g���̕������f���Ǘ��N���X
/// </summary>
class TitleTextModels
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleTextModels();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleTextModels();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	void Update(const float& elapsedTime);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

private:
	//	�������W
	static const DirectX::SimpleMath::Vector3 INIT_DEF_POSITION;
	//	���W�̊Ԋu
	static const float INIT_SPACE;

	//	�k�ޑ��x
	static const float SHRINK_SPEED;
	//	�L�т鑬�x
	static const float EXTEND_SPEED;

	//	�g�嗦�̉���
	static const float MIN_SCALE;
	//	�g�嗦�̃f�t�H���g
	static const float DEF_SCALE;

	//	�W�����v��
	static const float JUMP_POWER;
	//	�d�͉����x
	static const float GRAVITY_SCALE;

private:
	//	���f���N���X�̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<TextModel>> m_textModels;

	//	�W�����v�t���O�z��
	std::vector<bool> m_isJumps;
	//	���x�z��
	std::vector<DirectX::SimpleMath::Vector3> m_velocities;	
};
#endif // !TITLE_TEXT_MODEL_DEFINED