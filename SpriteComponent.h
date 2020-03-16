#pragma once
#include <SDL.h>
#include "Component.h"

class SpriteComponent : public Component {
public:
	// �`�揇��(drawOrder)���Ⴂ�قǉ����ɒu�����
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

private:
	SDL_Texture* mTexture; // �`�悷��e�N�X�`��
	int mDrawOrder; // ��ƃA���S���Y���ŕ`�悷�鏇��

	int mTexWidth;
	int mTexHeight;

};

