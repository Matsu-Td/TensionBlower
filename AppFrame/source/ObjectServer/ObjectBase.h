#pragma once


// オブジェクトクラス
class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	enum class OBJECTTYPE {

	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();

	virtual	bool	IsHit(ObjectBase& o);
	virtual	void	Damage() {}

protected:


};
