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

	// �Q�[���ŗL�֐�
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

	vector<class Actor*> mActors; // �Q�[�����̑S�A�N�^�[
	vector<class Actor*> mPendingActors; // �ۗ����̃A�N�^�[
	vector<class SpriteComponent*> mSprites; // �X�v���C�g�R���|�[�l���g

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;

	float mElapse; // �o�ߎ���

	bool mIsRunning;
	bool mUpdatingActors; // �X�V���̃A�N�^�[���ǂ����m�F�p
	float mSummonEBPTime; // �G�퓬�@���Ăяo������
	int mMaxEBPNum; // �G�퓬�@�̍ő吔

	int mWindowWidth;
	int mWindowHeight;

	// �Q�[���ŗL�����o
	class Ship* mShip; // �v���C���[�̑D
	//class EnemyBattlePlane* mEBP; // �G�v���C���[�̑D
	vector<class EnemyBattlePlane*> mEBPs;
};

