
#include "DxLib.h"
#include "ObjectBase.h"
#include "math.h"

ObjectBase::ObjectBase()
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	_cut = 0;
}

void ObjectBase::Process()
{
	_cut++;
}

void ObjectBase::Render()
{

}

bool ObjectBase::IsHitStage(ObjectBase& obj, float r)
{

	obj._hitPolyDim = MV1CollCheck_Capsule(obj._mh, -1, _capsulePos1, _capsulePos2, r);
	if (obj._hitPolyDim.HitNum >= 1) {
		return true;
	}

	return false;
}

bool ObjectBase::IsHitLineSegment(ObjectBase& obj, float r)
{
	float length = Segment_Segment_MinLength(obj._capsulePos1, obj._capsulePos2, _capsulePos1, _capsulePos2);

	if (length <= r) {
		return true;
	}
	
	return false;
}

bool ObjectBase::IsHitScrnPos(ObjectBase& obj)
{
	if (_scrnPos.x + _hitX < obj._scrnPos.x + obj._hitX + obj._hitW && obj._scrnPos.x + obj._hitX < _scrnPos.x + _hitX + _hitW
		&& _scrnPos.y + _hitY < obj._scrnPos.y + obj._hitY + obj._hitH && obj._scrnPos.y + obj._hitY < _scrnPos.y + _hitY + _hitH)
	{
		return true;
	}
	return false;
}