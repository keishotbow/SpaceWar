#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Math.h"

using namespace std;

class Actor {
public:
	// アクターの状態管理用
	enum State { EActive, EPaused, EDead };
	// コンストラクタとデストラクタ
	Actor(class Game* game);
	virtual ~Actor();

	// ゲームから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	// アクターが持つ全コンポーネントを更新(オーバーライド不可)
	void UpdateComponents(float deltaTime);
	// アクター独自の更新処理(オーバーライド可能)
	virtual void UpdateActor(float deltaTime);
	
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	// ゲッター＆セッター
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; } // アクターの状態を取得
	void SetState(State state) { mState = state; }

	class Game* GetGame() const { return mGame; }

	Vector2 GetForward() const { return Vector2(cosf(mRotation), -sinf(mRotation)); }

	// コンポーネントの追加と削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState; // アクターの状態
	// 座標変換
	Vector2 mPosition; // アクターの中心座標
	float mScale; // アクターのスケール(1.0fが100%)
	float mRotation; // 回転の角度
	// アクターが持つコンポーネント
	vector<class Component*> mComponents;
	class Game* mGame;
};

