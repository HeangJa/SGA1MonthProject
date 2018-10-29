#pragma once

class Camera : public singletonBase<Camera>
{
	POINT*	ptTarget;
	POINT*	ptPos;

	RECT	rcClient;
	RECT	rcWorld;

public:
	Camera();
	~Camera();

	void setTargetPos(POINT* _pt) { ptTarget = _pt; }
	void setPosition(POINT* _pt) { ptPos = _pt; }

	const POINT* getTargetPos() const { return ptTarget; }
	const POINT* getPosition() const { return ptPos; }

	void setClientRect(const RECT& _rt) { rcClient = _rt; }
	void setWorldRect(const RECT& _rt) { rcWorld = _rt; }

	const RECT& getClientRect() const { return rcClient; }
	const RECT& getWorldRect() const { return rcWorld; }

	bool operator==(const POINT* pObj) { return ptTarget == pObj; }
	bool operator!=(const POINT* pObj) { return ptTarget != pObj; }

	bool init(POINT* _pt, const RECT& _client, const RECT& _world);

	void update();
};

