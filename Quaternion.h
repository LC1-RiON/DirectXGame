#pragma once
#include <DirectXMath.h>

using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMMATRIX = DirectX::XMMATRIX;

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

// 成分指定のクォータニオン作成
Quaternion quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
// 任意軸まわりの回転指定のクォータニオン作成
Quaternion quaternion(XMFLOAT3 v, float angle);

// 内積
float dot(const Quaternion& q1, const Quaternion& q2);

// ノルム（長さ）
float length(const Quaternion& q);

// 正規化
Quaternion normalize(const Quaternion& q);

// 共役四元数
Quaternion conjugate(const Quaternion& q);

// 単項演算子オーバーロード
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);

// 代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

// 二項演算子オーバーロード
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);

// クォータニオンの球面線形補間
Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
// クォータニオンの線形補間
Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);
// クォータニオンから回転行列の変換
XMMATRIX rotate(const Quaternion& q);
// 回転行列からクォータニオンを求める
Quaternion quaternion(XMMATRIX m);
// 回転軸算出
XMFLOAT3 GetAxis(const Quaternion& q);
