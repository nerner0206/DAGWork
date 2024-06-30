//--------------------------------------------------------------------------------------
// File: SpringPart.h
//
// �v���C���[�΂˂̕��i�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#ifndef SPRING_PART_DEFINED
#define SPRING_PART_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// �v���C���[�΂˂̕��i�N���X
/// </summary>
class SpringPart : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SpringPart();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SpringPart();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="fileName">���f���̃t�@�C���p�X</param>
	void Initialize(const wchar_t* fileName);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="elapsedTime">�t���[���Ԃ̌o�ߎ��ԁi�b�j</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]</param>
	void Update(
		const float& elapsedTime,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate);
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(
		const DirectX::SimpleMath::Matrix& world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �e�`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void ShadowRender(
		const DirectX::SimpleMath::Matrix& world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

private:
	//	���f���̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;

	//	�x�N�g��
	DirectX::SimpleMath::Vector3 m_vel;

	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
};
#endif // !SPRING_PART_DEFINED
