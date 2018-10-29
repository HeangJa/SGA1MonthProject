#include "Game.h"
#include "Effect.h"
#include "Animation.h"

Effect::Effect()
	: _effectImage(NULL),
	_effectAnimation(NULL),
	_isRunning(false), _x(0), _y(0)
{
}

Effect::~Effect()
{
}

HRESULT Effect::init(Image * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage)
		return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation)
		_effectAnimation = new Animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();

	return S_OK;
}

void Effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void Effect::update()
{
	if (!_isRunning)
		return;

	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay())
		killEffect();
}

void Effect::render()
{
	if (!_isRunning)
		return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}

void Effect::killEffect()
{
	_isRunning = false;
}

void Effect::startEffect(int x, int y)
{
	if (!_effectImage || !_effectAnimation)
		return;

	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}
