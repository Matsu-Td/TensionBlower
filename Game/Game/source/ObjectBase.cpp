/**
 * @file  ObjectBase.cpp
 * @brief �I�u�W�F�N�g���N���X
 *
 * @date  2021/01/15
 */

#include "DxLib.h"
#include "ObjectBase.h"
#include "math.h"

ObjectBase::ObjectBase() {

	Initialize();
}

ObjectBase::~ObjectBase() {
}

/**
 * ������
 */
void ObjectBase::Initialize() {

	_cut = 0;
}

/**
 * �t���[�������F�v�Z
 */
void ObjectBase::Process() {

	_cut++;
}

/**
 * �t���[�������F�`��
 */
void ObjectBase::Render() {

}

/**
 * ���f���ƃX�e�[�W�̓����蔻��
 */
bool ObjectBase::IsHitStage(ObjectBase& obj, float r) {

	obj._hitPolyDim = MV1CollCheck_Capsule(obj._mh, -1, _capsulePos1, _capsulePos2, r);
	if (obj._hitPolyDim.HitNum >= 1) {
		return true;
	}

	return false;
}

/**
 * �J�v�Z�����m�̓����蔻��
 */
bool ObjectBase::IsHitLineSegment(ObjectBase& obj, float r) {

	float length = Segment_Segment_MinLength(obj._capsulePos1, obj._capsulePos2, _capsulePos1, _capsulePos2);

	if (length <= r) {
		return true;
	}

	return false;
}

/**
 * �X�N���[�����W��̓����蔻��
 */
bool ObjectBase::IsHitScrnPos(ObjectBase& obj) {

	if (_scrnPos.x + _hitX < obj._scrnPos.x + obj._hitX + obj._hitW && obj._scrnPos.x + obj._hitX < _scrnPos.x + _hitX + _hitW
		&& _scrnPos.y + _hitY < obj._scrnPos.y + obj._hitY + obj._hitH && obj._scrnPos.y + obj._hitY < _scrnPos.y + _hitY + _hitH)
	{
		return true;
	}
	return false;
}

/**
 * ���ςł̓����蔻��
 */
bool ObjectBase::IsDot(ObjectBase& obj) {

	float sx = obj._vPos.x - _vPos.x;
	float sz = obj._vPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);

	VECTOR vec = VSub(obj._vPos, _vPos);

	float dot = VDot(vec, obj._vDir);
	if (length < 40.0f && dot < -2.0f) {
		return true;
	}

	return false;
}

/**
 * �~�ʂƋ��̓����蔻��
 */
bool ObjectBase::IsHitArc_Sphere(ObjectBase& obj) {

	float sx = obj._vPos.x - _vPos.x;
	float sz = obj._vPos.z - _vPos.z;
	float length = sqrt(sx * sx + sz * sz);

	VECTOR dir = VNorm(_vDir);
	VECTOR vec = VSub(obj._vPos, _vPos);

	VECTOR Nor;
	Nor.x = vec.x / length;
	Nor.z = vec.z / length;
	float dot = VDot(Nor, dir);

	if (length < 22.0f) {
		if (cos(45.0f / 180.0f * DX_PI_F) < dot) {
			return true;
		}
	}
	return false;
}