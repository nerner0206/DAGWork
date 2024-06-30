//--------------------------------------------------------------------------------------
// File: SystemWindow.h
//
// �ݒ��ʃN���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#ifndef SYSTEM_WINDOW_DEFINED
#define SYSTEM_WINDOW_DEFINED

#include <vector>

class UserInterface;
class SystemUI;
class IScene;

/// <summary>
/// �ݒ��ʃN���X
/// </summary>
class SystemWindow
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SystemWindow();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SystemWindow();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	void Initialize(const int& mouseNumber);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="scene">�V�[�����N���X�̃|�C���^</param>
	void Update(IScene* scene);
	/// <summary>
	/// �`��
	/// </summary>
	void Render();
	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �ݒ��ʂ̊J�n
	/// </summary>
	/// <param name="scene">�V�[���N���X�̃|�C���^</param>
	void OnWindow(IScene* scene);
	/// <summary>
	/// �ݒ��ʂ̏I��
	/// </summary>
	/// <param name="scene">�V�[���N���X�̃|�C���^</param>
	void OffWindow(IScene* scene);

	/// <summary>
	/// �ݒ��ʒ�����̎擾
	/// </summary>
	/// <returns>�ݒ��ʒ�����</returns>
	const bool GetIsSystemOpen() { return m_isSystemOpen; }

private:
	//	�e�I�����̋���
	static const int ITEM_DISTANCE = 130;

private:
	//	�ݒ��ʒ�����
	bool m_isSystemOpen;

	//	�I��ԍ�
	int m_selectNum;
	//	�I���ő�ԍ�
	int m_selectMaxNum;

	//	�e�I�����̃��j�[�N�|�C���^�z��
	std::vector<std::unique_ptr<SystemUI>> m_items;

	//	�I���t���[���摜�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_itemFrame;
	//	�w�i�摜�̃��j�[�N�|�C���^
	std::unique_ptr<UserInterface> m_back;

private:
	/// <summary>
	/// �I���t���[���𓮂���
	/// </summary>
	void MoveFrame();

	/// <summary>
	/// �eUI�̐���
	/// </summary>
	/// <param name="mouseNumber">�}�E�X���x�ԍ�</param>
	void CreateUI(const int& mouseNumber);
};
#endif // !SYSTEM_WINDOW_DEFINED
