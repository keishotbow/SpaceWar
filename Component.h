#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Component {
public:
	// updateOrderが小さいコンポーネント程早く更新される
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	// このコンポーネントをデルタタイムで更新する
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyState);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner; // 所有アクター
	int mUpdateOrder; // コンポーネントの更新順番

};

