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

// �����w��̃N�H�[�^�j�I���쐬
Quaternion quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
// �C�ӎ��܂��̉�]�w��̃N�H�[�^�j�I���쐬
Quaternion quaternion(XMFLOAT3 v, float angle);

// ����
float dot(const Quaternion& q1, const Quaternion& q2);

// �m�����i�����j
float length(const Quaternion& q);

// ���K��
Quaternion normalize(const Quaternion& q);

// �����l����
Quaternion conjugate(const Quaternion& q);

// �P�����Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);

// ������Z�q�I�[�o�[���[�h
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

// �񍀉��Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);

// �N�H�[�^�j�I���̋��ʐ��`���
Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
// �N�H�[�^�j�I���̐��`���
Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);
// �N�H�[�^�j�I�������]�s��̕ϊ�
XMMATRIX rotate(const Quaternion& q);
// ��]�s�񂩂�N�H�[�^�j�I�������߂�
Quaternion quaternion(XMMATRIX m);
// ��]���Z�o
XMFLOAT3 GetAxis(const Quaternion& q);
