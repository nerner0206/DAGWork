//--------------------------------------------------------------------------------------
// File: Collider.cpp
//
// �����蔻��N���X�̃\�[�X�t�@�C��
//
// Author: ���c�@��
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Collider.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Collider::Collider() :
	m_distance(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Collider::~Collider()
{

}

/// <summary>
/// �����m�̓����蔻��
/// </summary>
/// <param name="sph1">���̓����蔻��N���X�̃|�C���^1</param>
/// <param name="sph2">���̓����蔻��N���X�̃|�C���^2</param>
/// <returns>�Փ˔���</returns>
bool Collider::SphereToSphereCheck(CollisionObject* sph1, CollisionObject* sph2)
{
	//	�����蔻��ΏۊO
	if (sph1 == nullptr || sph2 == nullptr) return false;
	if (sph1->GetCollisionType() != CollisionType::Sphere || sph2->GetCollisionType() != CollisionType::Sphere) return false;

	//	�L���X�g����
	SphereCollider* s1 = dynamic_cast<SphereCollider*>(sph1);
	SphereCollider* s2 = dynamic_cast<SphereCollider*>(sph2);

	//	���̔��a�̎擾
	float r1 = s1->GetRadius();
	float r2 = s2->GetRadius();

	//	���̍��W�̎擾
	SimpleMath::Vector3 pos1 = sph1->GetPos();
	SimpleMath::Vector3 pos2 = sph2->GetPos();

	//	�Q�̋��̋����̌v�Z�i���j
	float length = (pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) + (pos2.z - pos1.z) * (pos2.z - pos1.z);
	//	�Q�̋��̔��a�̘a�̌v�Z�i���j
	float L = (r1 + r2) * (r1 + r2);

	//	�����m�̋����������m�̔��a�̘a�ȉ��̏ꍇ�Փ˂��Ă���i��擯�m�̔���j
	if (length <= L)
	{
		//	�߂荞�ݗʂ̌v�Z
		m_distance = std::sqrtf(L) - std::sqrtf(length);

		//	�Փ˂��Ă���
		return true;
	}

	//	�Փ˂��Ă��Ȃ�
	return false;
}

/// <summary>
/// ���Ɣ��̓����蔻��
/// </summary>
/// <param name="sph">���̓����蔻��N���X�̃|�C���^</param>
/// <param name="box">���̓����蔻��N���X�̃|�C���^</param>
/// <returns>�Փ˔���</returns>
bool Collider::SphereToBoxCheck(CollisionObject* sph, CollisionObject* box)
{
	//	�����蔻��ΏۊO
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	�L���X�g����
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);

	//	���Ƌ��̓����蔻��i�����y���j
	if (!SphereToSphereCheck(sph, b->GetSphereCollider())) return false;

	//	�L���X�g����
	SphereCollider* s = dynamic_cast<SphereCollider*>(sph);

	//	���̔��a�̎擾
	float s_r = s->GetRadius();
	//	���̍��W�̎擾
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	���̊g�嗦�̎擾
	SimpleMath::Vector3 b_size = box->GetSca();
	//	���̍��W�̎擾
	SimpleMath::Vector3 b_pos = box->GetPos();

	//	���̊e���̒P�ʃx�N�g�����擾
	SimpleMath::Vector3 b_forward = box->GetForward();			//	�O��
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	����
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	����
	b_vertical.Normalize();

	//	���̒��S���甠�̒��S�܂ł̃x�N�g��
	SimpleMath::Vector3 s_b_vec = s_pos - b_pos;

	//	for���ŉ񂹂�悤�Ɋi�[����
	//	�e���̒P�ʃx�N�g��
	SimpleMath::Vector3 shafts[3] = { b_forward, b_horizontal, b_vertical };
	//	���̃T�C�Y�̔����i�d�S����e���ւ̒����j
	float L[3] = { b_size.z / 2.0f, b_size.x / 2.0f, b_size.y / 2.0f };

	//	���������߂邽�߂̃x�N�g��
	SimpleMath::Vector3 vec = SimpleMath::Vector3::Zero;

	//	�e���Ƃ̌v�Z
	for (int i = 0; i < 3; i++)
	{
		//	�������O�ȉ��Ȃ珈���s��
		if (L[i] <= 0.0f) continue;
		//	�������̂͂ݏo���Ċ��������߂遃-1�`s�`�P�̊ԂȂ�͂ݏo���Ă��Ȃ���
		float s = (s_b_vec.Dot(shafts[i])) / L[i];

		//	s�̐�Βl���擾
		s = fabsf(s);
		//	�͂ݏo��������������΂��̃x�N�g�������Z
		if (s > 1.0f) vec += (1 - s) * L[i] * shafts[i];
	}
	//	���������߂�
	float length = vec.Length();

	//	�Փ˔���
	if (length <= s_r)
	{
		//	�߂荞�ݗʂ̌v�Z
		m_distance = s_r - length;
		
		//	�Փ˂��Ă���
		return true;
	}

	return false;
}

//	�����������̒�����Փ˂����ʂ�����o��
int Collider::HitSurfaceNumber1(CollisionObject* sph, CollisionObject* box)
{
	//	�����蔻��ΏۊO
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	���̏d�S���W
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	���̏d�S���W
	SimpleMath::Vector3 b_pos = box->GetPos();
	//	�����狅�ւ̃x�N�g��
	SimpleMath::Vector3 b_s_vec = b_pos - s_pos;

	//	���̊e���̒P�ʃx�N�g�����擾
	SimpleMath::Vector3 b_forward = box->GetForward();			//	�O��
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	����
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	����
	b_vertical.Normalize();

	//	���̃T�C�Y���擾
	SimpleMath::Vector3 b_size = box->GetSca() / 2.0f;

	//	�e�ʂ̒��S�_�����߂�
	SimpleMath::Vector3 center_pos[6] =
	{
		(-b_forward * b_size.z) + b_pos,
		(-b_horizontal * b_size.x) + b_pos,
		(b_vertical * b_size.y) + b_pos,
		(-b_vertical * b_size.y) + b_pos,
		(b_horizontal * b_size.x) + b_pos,
		(b_forward * b_size.z) + b_pos,
	};
	//	�e�ʂ̖@���x�N�g��
	SimpleMath::Vector3 surface_nvec[6] =
	{
		-b_forward,
		-b_horizontal,
		b_vertical,
		-b_vertical,
		b_horizontal,
		b_forward,
	};

	//	���_�̍��W�����߂�
	SimpleMath::Vector3 vertex_pos[8] =
	{
		center_pos[0] + (b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[0] + (b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[0] + (-b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[0] + (-b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[5] + (b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[5] + (b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[5] + (-b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[5] + (-b_horizontal * b_size.x) + (b_vertical * b_size.y),
	};

	//	���ꂼ��̖ʂ̒��_�Ƃ��Ċi�[����
	SimpleMath::Vector3 surface_vertex[6][4] =
	{
		{ vertex_pos[0], vertex_pos[1], vertex_pos[2], vertex_pos[3] },
		{ vertex_pos[3], vertex_pos[2], vertex_pos[6], vertex_pos[7] },
		{ vertex_pos[4], vertex_pos[0], vertex_pos[3], vertex_pos[7] },
		{ vertex_pos[1], vertex_pos[5], vertex_pos[6], vertex_pos[2] },
		{ vertex_pos[4], vertex_pos[5], vertex_pos[1], vertex_pos[0] },
		{ vertex_pos[5], vertex_pos[4], vertex_pos[7], vertex_pos[6] }
	};

	//	�������ʂƏՓ˂��Ă��邩
	for (int i = 0; i < 6; i++)
	{
		//	�����̗��[�Q�_�Ɩʂ̒��S�_����̃x�N�g��
		SimpleMath::Vector3 v1 = center_pos[i] - b_pos;
		SimpleMath::Vector3 v2 = center_pos[i] - s_pos;

		//	�ʂ̖@���Ƃ̓��ς����߂�
		float n1 = surface_nvec[i].Dot(v1);
		float n2 = surface_nvec[i].Dot(v2);

		//	���߂����ς̐ς����̐��Ȃ�Փ˂��Ă��Ȃ�
		if (n1 * n2 > 0) continue;
		
		//	�����̔�����߂�
		float l1 = fabsf(surface_nvec[i].Dot(b_pos - center_pos[i])) / surface_nvec[i].Length();
		float l2 = fabsf(surface_nvec[i].Dot(s_pos - center_pos[i])) / surface_nvec[i].Length();

		float a = l1 / (l1 + l2);

		SimpleMath::Vector3 v3 = b_pos - surface_vertex[i][0];
		SimpleMath::Vector3 v4 = s_pos - surface_vertex[i][0];

		SimpleMath::Vector3 v5 = (1 - a) * v3+ a * v4;

		SimpleMath::Vector3 P3 = surface_vertex[i][0] + v5;
		
		//	�����܂ł�OK	/////////////////////////////////////////////
		
		//	4���_����̃x�N�g�������߂�
		SimpleMath::Vector3 around_v1 = surface_vertex[i][1] - surface_vertex[i][0];
		SimpleMath::Vector3 around_v2 = surface_vertex[i][2] - surface_vertex[i][1];
		SimpleMath::Vector3 around_v3 = surface_vertex[i][3] - surface_vertex[i][2];
		SimpleMath::Vector3 around_v4 = surface_vertex[i][0] - surface_vertex[i][3];
		//	�e���_����P3�܂ł̃x�N�g��
		SimpleMath::Vector3 P3_v1 = P3 - surface_vertex[i][1];
		SimpleMath::Vector3 P3_v2 = P3 - surface_vertex[i][2];
		SimpleMath::Vector3 P3_v3 = P3 - surface_vertex[i][3];
		SimpleMath::Vector3 P3_v4 = P3 - surface_vertex[i][0];

		//	��̊O��
		SimpleMath::Vector3 standard_n = around_v1.Cross(around_v2);
		//	�P�ʃx�N�g����
		standard_n.Normalize();

		//	�덷�p�Ɂ}1
		SimpleMath::Vector3 standard_n_max = standard_n + SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
		SimpleMath::Vector3 standard_n_min = standard_n - SimpleMath::Vector3(0.01f, 0.01f, 0.01f);

		//	��ڂ̊O��
		SimpleMath::Vector3 n = P3_v1.Cross(around_v1);
		//	�P�ʃx�N�g����
		n.Normalize();

		//	�x�N�g�����덷�͈͊O�������瓖�����ĂȂ�
		if ( standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			 standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			 standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		//	��ڂ̊O��
		n = P3_v2.Cross(around_v2);
		//	�P�ʃx�N�g����
		n.Normalize();

		//	�x�N�g�����덷�͈͊O�������瓖�����ĂȂ�
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		// �O�ڂ̊O��
		n = P3_v3.Cross(around_v3);
		//	�P�ʃx�N�g����
		n.Normalize();

		//	�x�N�g�����덷�͈͊O�������瓖�����ĂȂ�
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		// �l�ڂ̊O��
		n = P3_v4.Cross(around_v4);
		//	�P�ʃx�N�g����
		n.Normalize();

		//	�x�N�g�����덷�͈͊O�������瓖�����ĂȂ�
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		//	�������Ă���Ǝv���܂�
		return i + 1;
	}

	return -1;
}
//	�����������̒�����Փ˂����ʂ�����o��
int Collider::HitSurfaceNumber2(CollisionObject* sph, CollisionObject* box)
{
	//	�����蔻��ΏۊO
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	���̏d�S���W
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	���̏d�S���W
	SimpleMath::Vector3 b_pos = box->GetPos();
	//	�����狅�ւ̃x�N�g��
	SimpleMath::Vector3 b_s_vec = b_pos - s_pos;

	//	���̊e���̒P�ʃx�N�g�����擾
	SimpleMath::Vector3 b_forward = box->GetForward();			//	�O��
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	����
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	����
	b_vertical.Normalize();

	//	���̃T�C�Y���擾
	SimpleMath::Vector3 b_size = box->GetSca() / 2.0f;

	//	�e�ʂ̒��S�_�����߂�
	SimpleMath::Vector3 center_pos[6] =
	{
		(-b_forward * b_size.z) + b_pos,
		(-b_horizontal * b_size.x) + b_pos,
		(b_vertical * b_size.y) + b_pos,
		(-b_vertical * b_size.y) + b_pos,
		(b_horizontal * b_size.x) + b_pos,
		(b_forward * b_size.z) + b_pos,
	};
	//	�e�ʂ̖@���x�N�g��
	SimpleMath::Vector3 surface_nvec[6] =
	{
		-b_forward,
		-b_horizontal,
		b_vertical,
		-b_vertical,
		b_horizontal,
		b_forward,
	};

	//	���_�̍��W�����߂�
	SimpleMath::Vector3 vertex_pos[8] =
	{
		center_pos[0] + (b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[0] + (b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[0] + (-b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[0] + (-b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[5] + (b_horizontal * b_size.x) + (b_vertical * b_size.y),
		center_pos[5] + (b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[5] + (-b_horizontal * b_size.x) + (-b_vertical * b_size.y),
		center_pos[5] + (-b_horizontal * b_size.x) + (b_vertical * b_size.y),
	};
	//	���ꂼ��̖ʂ̒��_�Ƃ��Ċi�[����
	SimpleMath::Vector3 surface_vertex[6][4] =
	{
		{ vertex_pos[0], vertex_pos[1], vertex_pos[2], vertex_pos[3] },
		{ vertex_pos[3], vertex_pos[2], vertex_pos[6], vertex_pos[7] },
		{ vertex_pos[4], vertex_pos[0], vertex_pos[3], vertex_pos[7] },
		{ vertex_pos[1], vertex_pos[5], vertex_pos[6], vertex_pos[2] },
		{ vertex_pos[4], vertex_pos[5], vertex_pos[1], vertex_pos[0] },
		{ vertex_pos[5], vertex_pos[4], vertex_pos[7], vertex_pos[6] }
	};

	std::vector<int> hitNums;

	//	�������ʂƏՓ˂��Ă��邩
	for (int i = 0; i < 6; i++)
	{
		//	�����̗��[�Q�_�Ɩʂ̒��S�_����̃x�N�g��
		SimpleMath::Vector3 v1 = center_pos[i] - b_pos;
		SimpleMath::Vector3 v2 = center_pos[i] - s_pos;

		//	�ʂ̖@���Ƃ̓��ς����߂�
		float n1 = surface_nvec[i].Dot(v1);
		float n2 = surface_nvec[i].Dot(v2);

		//	���߂����ς̐ς����̐��Ȃ�Փ˂��Ă��Ȃ�
		if (n1 * n2 > 0) continue;

		hitNums.push_back(i);
	}
	//	�Փ˂����ʂ����݂��Ȃ��Ȃ�Ԃ��i���肦�Ȃ��j
	if (hitNums.size() == 0) return -1;
	//	�Փ˂����ʂ���Ȃ�Ԃ�
	if (hitNums.size() == 1) return hitNums[0] + 1;

	float min = (center_pos[hitNums[0]] - s_pos).Length();
	int num = hitNums[0];

	//	�q�b�g�����ʂ̒������ԋ߂�����T��
	for (int i = 1 ; i < hitNums.size() ; i++)
	{
		//	���̏d�S�_�Ɩʂ̒��S�_�̒������擾
		float length = (center_pos[hitNums[i]] - s_pos).Length();
		
		if (min < length) continue;

		min = length;
		num = hitNums[i];
	}

	return num + 1;
}


//	���Ɣ��̓����蔻��
bool Collider::BoxToBoxCheck(CollisionObject* box1, CollisionObject* box2)
{
	//	�����蔻��ΏۊO
	if (box1 == nullptr || box2 == nullptr) return false;
	if (box1->GetCollisionType() != CollisionType::Box || box2->GetCollisionType() != CollisionType::Box) return false;

	//	�L���X�g����
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(box1);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(box1);

	//	���Ƌ��̓����蔻��i�����y���j
	if (!SphereToSphereCheck(b1->GetSphereCollider(), b2->GetSphereCollider())) return false;

	//	�v�Z�ɕK�v�Ȓl
	SimpleMath::Vector3 nA1 = box1->GetForward();
	nA1.Normalize();
	SimpleMath::Vector3 A1 = nA1 * box1->GetSca().z / 2.0f;

	SimpleMath::Vector3 nA2 = box1->GetHorizontal();
	nA2.Normalize();
	SimpleMath::Vector3 A2 = nA2 * box1->GetSca().x / 2.0f;

	SimpleMath::Vector3 nA3 = box1->GetVertical();
	nA3.Normalize();
	SimpleMath::Vector3 A3 = nA3 * box1->GetSca().y / 2.0f;

	SimpleMath::Vector3 nB1 = box2->GetForward();
	nB1.Normalize();
	SimpleMath::Vector3 B1 = nB1 * box2->GetSca().z / 2.0f;

	SimpleMath::Vector3 nB2 = box2->GetHorizontal();
	nB2.Normalize();
	SimpleMath::Vector3 B2 = nB2 * box2->GetSca().x / 2.0f;

	SimpleMath::Vector3 nB3 = box2->GetVertical();
	nB3.Normalize();
	SimpleMath::Vector3 B3 = nB3 * box2->GetSca().y / 2.0f;

	SimpleMath::Vector3 distance = box1->GetPos() - box2->GetPos();

	// ������ : A1
	float rA = A1.Length();
	float rB = LenSegOnSeparateAxis(nA1, B1, B2, B3);
	float L = fabsf(distance.Dot(nA1));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false; 

	// ������ : A2
	rA = A2.Length();
	rB = LenSegOnSeparateAxis(nA2, B1, B2, B3);
	L = fabsf(distance.Dot(nA2));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : A3
	rA = A3.Length();
	rB = LenSegOnSeparateAxis(nA3, B1, B2, B3);
	L = fabsf(distance.Dot(nA3));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : B1
	rA = LenSegOnSeparateAxis(nB1, A1, A2, A3);
	rB = B1.Length();
	L = fabsf(distance.Dot(nB1));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : B2
	rA = LenSegOnSeparateAxis(nB2, A1, A2, A3);
	rB = B2.Length();
	L = fabsf(distance.Dot(nB2));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : B3
	rA = LenSegOnSeparateAxis(nB3, A1, A2, A3);
	rB = B3.Length();
	L = fabsf(distance.Dot(nB3));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C11
	SimpleMath::Vector3 Cross;
	Cross = nA1.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C12
	Cross = nA1.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C13
	Cross = nA1.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C21
	Cross = nA2.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C22
	Cross = nA2.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C23
	Cross = nA2.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C31
	Cross = nA3.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C32
	Cross = nA3.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// ������ : C33
	Cross = nA3.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// �Փ˂��Ă��Ȃ�
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}