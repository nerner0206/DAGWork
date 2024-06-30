//--------------------------------------------------------------------------------------
// File: Collider.h
//
// �����蔻��N���X�̃w�b�_�[�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#ifndef COLLIDER_DEFINED
#define COLLIDER_DEFINED

class CollisionObject;

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Collider();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Collider();

	/// <summary>
	/// �����m�̓����蔻��
	/// </summary>
	/// <param name="sph1">���̓����蔻��N���X�̃|�C���^1</param>
	/// <param name="sph2">���̓����蔻��N���X�̃|�C���^2</param>
	/// <returns>�Փ˔���</returns>
	bool SphereToSphereCheck(CollisionObject* sph1, CollisionObject* sph2);

	/// <summary>
	/// ���Ɣ��̓����蔻��
	/// </summary>
	/// <param name="sph">���̓����蔻��N���X�̃|�C���^</param>
	/// <param name="box">���̓����蔻��N���X�̃|�C���^</param>
	/// <returns>�Փ˔���</returns>
	bool SphereToBoxCheck(CollisionObject* sph, CollisionObject* box);

	/// <summary>
	/// �����m�̓����蔻��
	/// </summary>
	/// <param name="box1">���̓����蔻��N���X�̃|�C���^1</param>
	/// <param name="box2">���̓����蔻��N���X�̃|�C���^2</param>
	/// <returns>�Փ˔���</returns>
	bool BoxToBoxCheck(CollisionObject* box1, CollisionObject* box2);

	/// <summary>
	/// �Փ˖ʂ̎Z�o�@
	/// </summary>
	/// <param name="sph">���̓����蔻��N���X�̃|�C���^</param>
	/// <param name="box">���̓����蔻��N���X�̃|�C���^</param>
	/// <returns>�Փ˖ʂ̔ԍ�</returns>
	int HitSurfaceNumber1(CollisionObject* sph, CollisionObject* box);
	/// <summary>
	/// �Փ˖ʂ̎Z�o�A
	/// </summary>
	/// <param name="sph">���̓����蔻��N���X�̃|�C���^</param>
	/// <param name="box">���̓����蔻��N���X�̃|�C���^</param>
	/// <returns>�Փ˖ʂ̔ԍ�</returns>
	int HitSurfaceNumber2(CollisionObject* sph, CollisionObject* box);

	/// <summary>
	/// �߂荞�ݗʂ̎擾
	/// </summary>
	/// <returns>�߂荞�ݗ�</returns>
	const float GetDistance() { return m_distance; }

private:
	//	�߂荞�ݗ�
	float m_distance;

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegOnSeparateAxis(
		const DirectX::SimpleMath::Vector3& sep,
		const DirectX::SimpleMath::Vector3& e1,
		const DirectX::SimpleMath::Vector3& e2,
		const DirectX::SimpleMath::Vector3& e3 = DirectX::SimpleMath::Vector3::Zero)
	{
		float r1 = fabsf(sep.Dot(e1));
		float r2 = fabsf(sep.Dot(e2));
		float r3 = 0.0f;
		if (e3 != DirectX::SimpleMath::Vector3::Zero) r3 = fabsf(sep.Dot(e3));

		return r1 + r2 + r3;
	}
};
#endif // !COLLIDER_DEFINED