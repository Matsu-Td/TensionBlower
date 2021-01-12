
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

/*bool ObjectBase::IsHit(ObjectBase& obj)
{
}*/