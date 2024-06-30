//--------------------------------------------------------------------------------------
// File: BigCloud.h
//
// �傫���_�N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#pragma once
#ifndef BIG_CLOUD_DEFINED
#define BIG_CLOUD_DEFINED

#include "GameObjects/Object.h"

class IScene;

/// <summary>
/// �傫���_�N���X
/// </summary>
class BigCloud : public Object
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene">�V�[���N���X�̃|�C���^</param>
	BigCloud(IScene* scene);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BigCloud();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector3& pos, const float& sca);
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
	//	�萔�o�b�t�@�̍\����
	struct ConstantBuffer
	{
		DirectX::SimpleMath::Matrix LightViewProj;		//	���C�g�̃r���[�s��
		DirectX::SimpleMath::Vector4 LightPos;			//	���C�g�̍��W
		DirectX::SimpleMath::Vector4 LightDir;			//	���C�g�̕����x�N�g��
	};

private:
	//	���݂̃V�[���N���X�̃|�C���^
	IScene* m_nowScene;

	//	���f���N���X�̃��j�[�N�|�C���^
	std::unique_ptr<DirectX::Model> m_model;

	//	�萔�o�b�t�@�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//	���_�V�F�[�_�[�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_�̃R���|�C���^
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

private:
	/// <summary>
	/// �V�F�[�_�̍쐬
	/// </summary>
	void CreateShader();
};
#endif // !BIG_CLOUD_DEFINED
