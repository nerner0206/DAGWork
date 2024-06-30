//--------------------------------------------------------------------------------------
// File: SkyDome.h
//
// �X�J�C�h�[���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#ifndef SKY_DOME_DEFINED
#define SKY_DOME_DEFINED

#include "GameObjects/Object.h"

/// <summary>
/// �X�J�C�h�[���N���X
/// </summary>
class SkyDome : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SkyDome();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SkyDome();

	/// <summary>
	/// ���]
	/// </summary>
	/// <param name="speed">��]���x</param>
	void RotUpdate(const float& speed);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

private:
	//	���f���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;
};
#endif // !SKY_DOME_DEFINED
