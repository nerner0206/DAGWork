//--------------------------------------------------------------------------------------
// File: Collider.cpp
//
// 当たり判定クラスのソースファイル
//
// Author: 村田　廉
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Collider.h"

#include "GameObjects/PlayScene/CollisionObjects/BoxCollider.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
Collider::Collider() :
	m_distance(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Collider::~Collider()
{

}

/// <summary>
/// 球同士の当たり判定
/// </summary>
/// <param name="sph1">球の当たり判定クラスのポインタ1</param>
/// <param name="sph2">球の当たり判定クラスのポインタ2</param>
/// <returns>衝突判定</returns>
bool Collider::SphereToSphereCheck(CollisionObject* sph1, CollisionObject* sph2)
{
	//	当たり判定対象外
	if (sph1 == nullptr || sph2 == nullptr) return false;
	if (sph1->GetCollisionType() != CollisionType::Sphere || sph2->GetCollisionType() != CollisionType::Sphere) return false;

	//	キャストする
	SphereCollider* s1 = dynamic_cast<SphereCollider*>(sph1);
	SphereCollider* s2 = dynamic_cast<SphereCollider*>(sph2);

	//	球の半径の取得
	float r1 = s1->GetRadius();
	float r2 = s2->GetRadius();

	//	球の座標の取得
	SimpleMath::Vector3 pos1 = sph1->GetPos();
	SimpleMath::Vector3 pos2 = sph2->GetPos();

	//	２つの球の距離の計算（二乗）
	float length = (pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) + (pos2.z - pos1.z) * (pos2.z - pos1.z);
	//	２つの球の半径の和の計算（二乗）
	float L = (r1 + r2) * (r1 + r2);

	//	球同士の距離が球同士の半径の和以下の場合衝突している（二乗同士の判定）
	if (length <= L)
	{
		//	めり込み量の計算
		m_distance = std::sqrtf(L) - std::sqrtf(length);

		//	衝突している
		return true;
	}

	//	衝突していない
	return false;
}

/// <summary>
/// 球と箱の当たり判定
/// </summary>
/// <param name="sph">球の当たり判定クラスのポインタ</param>
/// <param name="box">箱の当たり判定クラスのポインタ</param>
/// <returns>衝突判定</returns>
bool Collider::SphereToBoxCheck(CollisionObject* sph, CollisionObject* box)
{
	//	当たり判定対象外
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	キャストする
	BoxCollider* b = dynamic_cast<BoxCollider*>(box);

	//	球と球の当たり判定（処理軽減）
	if (!SphereToSphereCheck(sph, b->GetSphereCollider())) return false;

	//	キャストする
	SphereCollider* s = dynamic_cast<SphereCollider*>(sph);

	//	球の半径の取得
	float s_r = s->GetRadius();
	//	球の座標の取得
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	箱の拡大率の取得
	SimpleMath::Vector3 b_size = box->GetSca();
	//	箱の座標の取得
	SimpleMath::Vector3 b_pos = box->GetPos();

	//	箱の各軸の単位ベクトルを取得
	SimpleMath::Vector3 b_forward = box->GetForward();			//	前方
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	水平
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	垂直
	b_vertical.Normalize();

	//	球の中心から箱の中心までのベクトル
	SimpleMath::Vector3 s_b_vec = s_pos - b_pos;

	//	for文で回せるように格納する
	//	各軸の単位ベクトル
	SimpleMath::Vector3 shafts[3] = { b_forward, b_horizontal, b_vertical };
	//	箱のサイズの半分（重心から各軸への長さ）
	float L[3] = { b_size.z / 2.0f, b_size.x / 2.0f, b_size.y / 2.0f };

	//	長さを求めるためのベクトル
	SimpleMath::Vector3 vec = SimpleMath::Vector3::Zero;

	//	各軸との計算
	for (int i = 0; i < 3; i++)
	{
		//	長さが０以下なら処理不可
		if (L[i] <= 0.0f) continue;
		//	軸方向のはみ出して割合を求める＜-1～s～１の間ならはみ出していない＞
		float s = (s_b_vec.Dot(shafts[i])) / L[i];

		//	sの絶対値を取得
		s = fabsf(s);
		//	はみ出した部分があればそのベクトルを加算
		if (s > 1.0f) vec += (1 - s) * L[i] * shafts[i];
	}
	//	距離を求める
	float length = vec.Length();

	//	衝突判定
	if (length <= s_r)
	{
		//	めり込み量の計算
		m_distance = s_r - length;
		
		//	衝突している
		return true;
	}

	return false;
}

//	当たった箱の中から衝突した面を割り出す
int Collider::HitSurfaceNumber1(CollisionObject* sph, CollisionObject* box)
{
	//	当たり判定対象外
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	球の重心座標
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	箱の重心座標
	SimpleMath::Vector3 b_pos = box->GetPos();
	//	箱から球へのベクトル
	SimpleMath::Vector3 b_s_vec = b_pos - s_pos;

	//	箱の各軸の単位ベクトルを取得
	SimpleMath::Vector3 b_forward = box->GetForward();			//	前方
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	水平
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	垂直
	b_vertical.Normalize();

	//	箱のサイズを取得
	SimpleMath::Vector3 b_size = box->GetSca() / 2.0f;

	//	各面の中心点を求める
	SimpleMath::Vector3 center_pos[6] =
	{
		(-b_forward * b_size.z) + b_pos,
		(-b_horizontal * b_size.x) + b_pos,
		(b_vertical * b_size.y) + b_pos,
		(-b_vertical * b_size.y) + b_pos,
		(b_horizontal * b_size.x) + b_pos,
		(b_forward * b_size.z) + b_pos,
	};
	//	各面の法線ベクトル
	SimpleMath::Vector3 surface_nvec[6] =
	{
		-b_forward,
		-b_horizontal,
		b_vertical,
		-b_vertical,
		b_horizontal,
		b_forward,
	};

	//	頂点の座標を求める
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

	//	それぞれの面の頂点として格納する
	SimpleMath::Vector3 surface_vertex[6][4] =
	{
		{ vertex_pos[0], vertex_pos[1], vertex_pos[2], vertex_pos[3] },
		{ vertex_pos[3], vertex_pos[2], vertex_pos[6], vertex_pos[7] },
		{ vertex_pos[4], vertex_pos[0], vertex_pos[3], vertex_pos[7] },
		{ vertex_pos[1], vertex_pos[5], vertex_pos[6], vertex_pos[2] },
		{ vertex_pos[4], vertex_pos[5], vertex_pos[1], vertex_pos[0] },
		{ vertex_pos[5], vertex_pos[4], vertex_pos[7], vertex_pos[6] }
	};

	//	無限平面と衝突しているか
	for (int i = 0; i < 6; i++)
	{
		//	線分の両端２点と面の中心点からのベクトル
		SimpleMath::Vector3 v1 = center_pos[i] - b_pos;
		SimpleMath::Vector3 v2 = center_pos[i] - s_pos;

		//	面の法線との内積を求める
		float n1 = surface_nvec[i].Dot(v1);
		float n2 = surface_nvec[i].Dot(v2);

		//	求めた内積の積が正の数なら衝突していない
		if (n1 * n2 > 0) continue;
		
		//	距離の比を求める
		float l1 = fabsf(surface_nvec[i].Dot(b_pos - center_pos[i])) / surface_nvec[i].Length();
		float l2 = fabsf(surface_nvec[i].Dot(s_pos - center_pos[i])) / surface_nvec[i].Length();

		float a = l1 / (l1 + l2);

		SimpleMath::Vector3 v3 = b_pos - surface_vertex[i][0];
		SimpleMath::Vector3 v4 = s_pos - surface_vertex[i][0];

		SimpleMath::Vector3 v5 = (1 - a) * v3+ a * v4;

		SimpleMath::Vector3 P3 = surface_vertex[i][0] + v5;
		
		//	ここまではOK	/////////////////////////////////////////////
		
		//	4頂点からのベクトルを求める
		SimpleMath::Vector3 around_v1 = surface_vertex[i][1] - surface_vertex[i][0];
		SimpleMath::Vector3 around_v2 = surface_vertex[i][2] - surface_vertex[i][1];
		SimpleMath::Vector3 around_v3 = surface_vertex[i][3] - surface_vertex[i][2];
		SimpleMath::Vector3 around_v4 = surface_vertex[i][0] - surface_vertex[i][3];
		//	各頂点からP3までのベクトル
		SimpleMath::Vector3 P3_v1 = P3 - surface_vertex[i][1];
		SimpleMath::Vector3 P3_v2 = P3 - surface_vertex[i][2];
		SimpleMath::Vector3 P3_v3 = P3 - surface_vertex[i][3];
		SimpleMath::Vector3 P3_v4 = P3 - surface_vertex[i][0];

		//	基準の外積
		SimpleMath::Vector3 standard_n = around_v1.Cross(around_v2);
		//	単位ベクトルへ
		standard_n.Normalize();

		//	誤差用に±1
		SimpleMath::Vector3 standard_n_max = standard_n + SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
		SimpleMath::Vector3 standard_n_min = standard_n - SimpleMath::Vector3(0.01f, 0.01f, 0.01f);

		//	一つ目の外積
		SimpleMath::Vector3 n = P3_v1.Cross(around_v1);
		//	単位ベクトルへ
		n.Normalize();

		//	ベクトルが誤差範囲外だったら当たってない
		if ( standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			 standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			 standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		//	二つ目の外積
		n = P3_v2.Cross(around_v2);
		//	単位ベクトルへ
		n.Normalize();

		//	ベクトルが誤差範囲外だったら当たってない
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		// 三つ目の外積
		n = P3_v3.Cross(around_v3);
		//	単位ベクトルへ
		n.Normalize();

		//	ベクトルが誤差範囲外だったら当たってない
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		// 四つ目の外積
		n = P3_v4.Cross(around_v4);
		//	単位ベクトルへ
		n.Normalize();

		//	ベクトルが誤差範囲外だったら当たってない
		if (standard_n_max.x >= n.x && standard_n_min.x <= n.x &&
			standard_n_max.y >= n.y && standard_n_min.y <= n.y &&
			standard_n_max.z >= n.z && standard_n_min.z <= n.z) continue;

		//	当たっていると思います
		return i + 1;
	}

	return -1;
}
//	当たった箱の中から衝突した面を割り出す
int Collider::HitSurfaceNumber2(CollisionObject* sph, CollisionObject* box)
{
	//	当たり判定対象外
	if (sph == nullptr || box == nullptr) return false;
	if (sph->GetCollisionType() != CollisionType::Sphere || box->GetCollisionType() != CollisionType::Box) return false;

	//	球の重心座標
	SimpleMath::Vector3 s_pos = sph->GetPos();

	//	箱の重心座標
	SimpleMath::Vector3 b_pos = box->GetPos();
	//	箱から球へのベクトル
	SimpleMath::Vector3 b_s_vec = b_pos - s_pos;

	//	箱の各軸の単位ベクトルを取得
	SimpleMath::Vector3 b_forward = box->GetForward();			//	前方
	b_forward.Normalize();
	SimpleMath::Vector3 b_horizontal = box->GetHorizontal();		//	水平
	b_horizontal.Normalize();
	SimpleMath::Vector3 b_vertical = box->GetVertical();			//	垂直
	b_vertical.Normalize();

	//	箱のサイズを取得
	SimpleMath::Vector3 b_size = box->GetSca() / 2.0f;

	//	各面の中心点を求める
	SimpleMath::Vector3 center_pos[6] =
	{
		(-b_forward * b_size.z) + b_pos,
		(-b_horizontal * b_size.x) + b_pos,
		(b_vertical * b_size.y) + b_pos,
		(-b_vertical * b_size.y) + b_pos,
		(b_horizontal * b_size.x) + b_pos,
		(b_forward * b_size.z) + b_pos,
	};
	//	各面の法線ベクトル
	SimpleMath::Vector3 surface_nvec[6] =
	{
		-b_forward,
		-b_horizontal,
		b_vertical,
		-b_vertical,
		b_horizontal,
		b_forward,
	};

	//	頂点の座標を求める
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
	//	それぞれの面の頂点として格納する
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

	//	無限平面と衝突しているか
	for (int i = 0; i < 6; i++)
	{
		//	線分の両端２点と面の中心点からのベクトル
		SimpleMath::Vector3 v1 = center_pos[i] - b_pos;
		SimpleMath::Vector3 v2 = center_pos[i] - s_pos;

		//	面の法線との内積を求める
		float n1 = surface_nvec[i].Dot(v1);
		float n2 = surface_nvec[i].Dot(v2);

		//	求めた内積の積が正の数なら衝突していない
		if (n1 * n2 > 0) continue;

		hitNums.push_back(i);
	}
	//	衝突した面が存在しないなら返す（ありえない）
	if (hitNums.size() == 0) return -1;
	//	衝突した面が一つなら返す
	if (hitNums.size() == 1) return hitNums[0] + 1;

	float min = (center_pos[hitNums[0]] - s_pos).Length();
	int num = hitNums[0];

	//	ヒットした面の中から一番近い物を探す
	for (int i = 1 ; i < hitNums.size() ; i++)
	{
		//	球の重心点と面の中心点の長さを取得
		float length = (center_pos[hitNums[i]] - s_pos).Length();
		
		if (min < length) continue;

		min = length;
		num = hitNums[i];
	}

	return num + 1;
}


//	箱と箱の当たり判定
bool Collider::BoxToBoxCheck(CollisionObject* box1, CollisionObject* box2)
{
	//	当たり判定対象外
	if (box1 == nullptr || box2 == nullptr) return false;
	if (box1->GetCollisionType() != CollisionType::Box || box2->GetCollisionType() != CollisionType::Box) return false;

	//	キャストする
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(box1);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(box1);

	//	球と球の当たり判定（処理軽減）
	if (!SphereToSphereCheck(b1->GetSphereCollider(), b2->GetSphereCollider())) return false;

	//	計算に必要な値
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

	// 分離軸 : A1
	float rA = A1.Length();
	float rB = LenSegOnSeparateAxis(nA1, B1, B2, B3);
	float L = fabsf(distance.Dot(nA1));
	if (L > rA + rB)
		// 衝突していない
		return false; 

	// 分離軸 : A2
	rA = A2.Length();
	rB = LenSegOnSeparateAxis(nA2, B1, B2, B3);
	L = fabsf(distance.Dot(nA2));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : A3
	rA = A3.Length();
	rB = LenSegOnSeparateAxis(nA3, B1, B2, B3);
	L = fabsf(distance.Dot(nA3));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : B1
	rA = LenSegOnSeparateAxis(nB1, A1, A2, A3);
	rB = B1.Length();
	L = fabsf(distance.Dot(nB1));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : B2
	rA = LenSegOnSeparateAxis(nB2, A1, A2, A3);
	rB = B2.Length();
	L = fabsf(distance.Dot(nB2));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : B3
	rA = LenSegOnSeparateAxis(nB3, A1, A2, A3);
	rB = B3.Length();
	L = fabsf(distance.Dot(nB3));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C11
	SimpleMath::Vector3 Cross;
	Cross = nA1.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C12
	Cross = nA1.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C13
	Cross = nA1.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A2, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C21
	Cross = nA2.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C22
	Cross = nA2.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C23
	Cross = nA2.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A1, A3);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C31
	Cross = nA3.Cross(nB1);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B2, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C32
	Cross = nA3.Cross(nB2);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B1, B3);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離軸 : C33
	Cross = nA3.Cross(nB3);
	rA = LenSegOnSeparateAxis(Cross, A1, A2);
	rB = LenSegOnSeparateAxis(Cross, B1, B2);
	L = fabsf(distance.Dot(Cross));
	if (L > rA + rB)
		// 衝突していない
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}