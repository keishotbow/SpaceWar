#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const string& fileName);

	int GetWindowWidth() const { return mWindowWidth; }
	int GetWindowHeight() const { return mWindowHeight; }

	void TerminateGame() { mIsRunning = false; }

	float GetElapse() const { return mElapse; }

	// ゲーム固有関数
	void AddEBP(class EnemyBattlePlane* enemy);
	void RemoveEBP(class EnemyBattlePlane* enemy);

	class Ship* GetShip() { return mShip; }
	vector<class EnemyBattlePlane*>& GetEBPs() { return mEBPs; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	unordered_map<string, SDL_Texture*> mTextures;

	vector<class Actor*> mActors; // ゲーム内の全アクター
	vector<class Actor*> mPendingActors; // 保留中のアクター
	vector<class SpriteComponent*> mSprites; // スプライトコンポーネント

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;

	float mElapse; // 経過時間

	bool mIsRunning;
	bool mUpdatingActors; // 更新中のアクターかどうか確認用
	float mSummonEBPTime; // 敵戦闘機を呼び出す時間
	int mMaxEBPNum; // 敵戦闘機の最大数

	int mWindowWidth;
	int mWindowHeight;

	// ゲーム固有メンバ
	class Ship* mShip; // プレイヤーの船
	//class EnemyBattlePlane* mEBP; // 敵プレイヤーの船
	vector<class EnemyBattlePlane*> mEBPs;
};

