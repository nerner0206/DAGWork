//--------------------------------------------------------------------------------------
// File: TitleTextModels.h
//
// �^�C�g���̕������f���Ǘ��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TitleTextModels.h"

using namespace DirectX;

//	�������W
const SimpleMath::Vector3 TitleTextModels::INIT_DEF_POSITION = SimpleMath::Vector3(-3.0f, 1.3f, 0.0f);
//	���W�̊Ԋu
const float TitleTextModels::INIT_SPACE = 0.75f;

//	�k�ޑ��x
const float TitleTextModels::SHRINK_SPEED = 0.95f;
//	�L�т鑬�x
const float TitleTextModels::EXTEND_SPEED = 1.3f;

//	�g�嗦�̉���
const float TitleTextModels::MIN_SCALE = 0.2f;
//	�g�嗦�̃f�t�H���g
const float TitleTextModels::DEF_SCALE = 1.0f;

//	�W�����v��
const float TitleTextModels::JUMP_POWER = 3.2f;
//	�d�͉����x
const float TitleTextModels::GRAVITY_SCALE = -0.08;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleTextModels::TitleTextModels()
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleTextModels::~TitleTextModels()
{

}

/// <summary>
/// ������
/// </summary>
void TitleTextModels::Initialize()
{
	//	�����z��̐���
	for (int i = 0; i < DataPath::TITLE_TEXT_MODEL_NUMBER; i++)
	{
		//	�������f���̐���
		std::unique_ptr<TextModel> text = std::make_unique<TextModel>();
		//	������
		text->Initialize(DataPath::TITLE_TEXT_MODEL_PATHs[i]);
		//	���W�̐ݒ�
		SimpleMath::Vector3 pos = INIT_DEF_POSITION;
		pos.x += (i * INIT_SPACE);
		text->SetPos(pos);
		//	�z��Ɋi�[
		m_textModels.push_back(std::move(text));

		//	�W�����v�t���O�̒ǉ�
		m_isJumps.push_back(false);
		//	���x�̒ǉ�
		m_velocities.push_back(SimpleMath::Vector3::Zero);
	}
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
void TitleTextModels::Update(const float& elapsedTime)
{
	//	�����z��̐���
	for (int i = 0; i < DataPath::TITLE_TEXT_MODEL_NUMBER; i++)
	{
		//	���W���擾
		SimpleMath::Vector3 pos = m_textModels[i]->GetPos();
		//	�g�嗦���擾
		SimpleMath::Vector3 sca = m_textModels[i]->GetSca();

		if (m_isJumps[i])
		{
			//	���X�ɏk��
			sca.y *= SHRINK_SPEED;

			//	���ȏ�k�񂾂�߂�
			if (sca.y <= MIN_SCALE)
			{
				//	�����l�ɏC��
				sca.y = MIN_SCALE;

				//	��W�����v��Ԃ�
				m_isJumps[i] = false;

				//	���˕Ԃ�(�΂˂̑��x�ɉ����ĕύX����)
				m_velocities[i] = SimpleMath::Vector3::Up * JUMP_POWER;
			}
		}
		else
		{
			//	���X�ɐL�΂�
			if (sca.y < DEF_SCALE)
			{
				sca.y *= EXTEND_SPEED;
				if (sca.y > DEF_SCALE) sca.y = DEF_SCALE;
			}

			//	�d�͉����x�̉��Z
			m_velocities[i].y += GRAVITY_SCALE;
			//	���x�̉��Z
			pos += (m_velocities[i] * elapsedTime);

			if (pos.y < 0.0f)
			{
				//	������Ȃ��ʒu�Ɉړ�
				pos.y = 0.0f;
				//	�ړ��ʂ�����
				m_velocities[i] = SimpleMath::Vector3::Zero;
				//	�W�����v��Ԃ�
				m_isJumps[i] = true;
			}
		}

		//	���W�̐ݒ�
		m_textModels[i]->SetPos(pos);
		//	�g�嗦�̐ݒ�
		m_textModels[i]->SetSca(sca);
	}
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void TitleTextModels::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& textModel : m_textModels)
	{
		textModel->Render(view, proj);
	}
}

/// <summary>
/// �e�`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void TitleTextModels::ShadowRender(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (auto& textModel : m_textModels)
	{
		textModel->ShadowRender(view, proj);
	}
}

/// <summary>
/// �I��
/// </summary>
void TitleTextModels::Finalize()
{
	for (auto& textModel : m_textModels)
	{
		textModel->Finalize();
	}
}