//--------------------------------------------------------------------------------------
// File: UserInterface.h
//
// UI���N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef USER_INTERFACE_DEFINED
#define USER_INTERFACE_DEFINED

#include "MyLib/UserResources.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>

//	UI�̃A���J�[�|�C���g�̗񋓐�
enum ANCHOR
{
	TOP_LEFT = 0,
	TOP_CENTER,
	TOP_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
};

/// <summary>
/// UI���N���X
/// </summary>
class UserInterface
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UserInterface();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UserInterface();

	/// <summary>
	/// �e�N�X�`�����\�[�X�̓ǂݍ���
	/// </summary>
	/// <param name="path">�t�@�C����</param>
	void LoadTexture(const wchar_t* path);

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="path">�t�@�C����</param>
	/// <param name="position">���W</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="anchor">�A���J�[�|�C���g</param>
	void Create(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		ANCHOR anchor);

	/// <summary>
	/// �`��
	/// </summary>
	void Render();

	/// <summary>
	/// �摜�T�C�Y�̎擾
	/// </summary>
	/// <returns>�摜�T�C�Y</returns>
	const DirectX::SimpleMath::Vector2 GetTextureSize() { return m_textureSize; }

	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const DirectX::SimpleMath::Vector2& scale) { m_scale = scale; }
	/// <summary>
	/// �g�嗦�̎擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns></returns>
	const DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

	/// <summary>
	/// �A���J�[�|�C���g�̐ݒ�
	/// </summary>
	/// <param name="anchor">�A���J�[�|�C���g</param>
	void SetAnchor(const ANCHOR& anchor) { m_anchor = anchor; };
	/// <summary>
	/// �A���J�[�|�C���g�̎擾
	/// </summary>
	/// <returns>�A���J�[�|�C���g</returns>
	const ANCHOR GetAnchor() { return m_anchor; }

	/// <summary>
	/// �c����̐ݒ�
	/// </summary>
	/// <param name="ratio">�䗦</param>
	void SetRenderRatio(const float& ratio) { m_renderRatio = ratio; }
	/// <summary>
	/// �c����̎擾
	/// </summary>
	/// <returns>�䗦</returns>
	float GetRenderRatio() const { return m_renderRatio; }

	/// <summary>
	/// �����x�̐ݒ�
	/// </summary>
	/// <param name="alpha">�����x</param>
	void SetAlpha(const float& alpha) { m_alpha = alpha; }
	/// <summary>
	/// �����x�̎擾
	/// </summary>
	/// <returns>�����x</returns>
	float GetAlpha() const { return m_alpha; }

public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
	};

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11Resource> m_res;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//	�摜�̏c���T�C�Y
	DirectX::SimpleMath::Vector2 m_textureSize;

	//	�g�嗦
	DirectX::SimpleMath::Vector2 m_scale;
	//	���W
	DirectX::SimpleMath::Vector2 m_position;

	//	�A���J�[�|�C���g
	ANCHOR m_anchor;

	//	�c����
	float m_renderRatio;

	//	�����x
	float m_alpha;

private:
	/// <summary>
	/// �V�F�[�_�[�̍쐬
	/// </summary>
	void CreateShader();
};
#endif // !USER_INTERFACE_DEFINED