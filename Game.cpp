#include "Game.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Ship.h"
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "EnemyBattlePlane.h"

Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
	, mWindowWidth(1024)
	, mWindowHeight(768)
	, mSummonEBPTime(0.0f)
	, mMaxEBPNum(10)
{
}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in c++ (Chapter 2)", 100, 100, mWindowWidth, mWindowHeight, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();
	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor * actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor * actor) {
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

// スプライトコンポーネントを追加する
void Game::AddSprite(SpriteComponent * sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++) {
		if (myDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

// スプライトコンポーネントを削除する
void Game::RemoveSprite(SpriteComponent * sprite) {
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end()) {
		mSprites.erase(iter);
	}
}

SDL_Texture * Game::GetTexture(const string & fileName) {
	SDL_Texture* tex = nullptr;
	
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) { // テクスチャが連想配列に既に存在する場合
		tex = iter->second;
	}
	else {
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file: %s", SDL_GetError());
			return nullptr;
		}

		// surfaceからtextureを作成する
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to create surface to texture for %s", SDL_GetError());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}

	return tex;
}

void Game::AddEBP(EnemyBattlePlane * enemy) {
	mEBPs.emplace_back(enemy);
}

void Game::RemoveEBP(EnemyBattlePlane * enemy) {
	auto iter = find(mEBPs.begin(), mEBPs.end(), enemy);
	if (iter != mEBPs.end()) {
		mEBPs.erase(iter);
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;

	// 船の操舵入力
	mShip->ProcessKeyboard(keyState);
}

void Game::UpdateGame() {

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mElapse += deltaTime; // 経過時間
	if (deltaTime > 0.5f) {
		deltaTime = 0.5f;
	}
	mTicksCount = SDL_GetTicks();

	mSummonEBPTime -= deltaTime;
	if (mSummonEBPTime <= 0.0f && mMaxEBPNum > 0) {
		new EnemyBattlePlane(this);
		mMaxEBPNum--;
		mSummonEBPTime = 5.0f;
	}

	// 全アクターを更新
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 待ちになっていたアクターをmActorsに移動
	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 死んだアクターを一時配列に追加
	vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	// 死んだアクターをmActorsから削除する
	for (auto actor : deadActors) {
		delete actor;
	}

}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// 全スプライトコンポーネントを描画する
	for (auto sprite : mSprites) {
		sprite->Draw(mRenderer);
	}

	// レンダラーの中身を描画する
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData() {
	// プレイヤーの船を作成
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// 背景用のアクターを作成する
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	
	// 遠い背景を作成
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	
	// 近い背景を作成
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData() {
	// アクターを削除
	while (!mActors.empty()) {
		delete mActors.back();
	}

	// テクスチャを削除
	for (auto i : mTextures) {
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}
