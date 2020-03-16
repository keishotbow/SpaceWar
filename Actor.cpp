#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game * game)
	: mState(EActive),
	mPosition(Vector2(0.0f, 0.0f)),
	mScale(1.0f),
	mRotation(0.0f),
	mGame(game) {
	mGame->AddActor(this);
}

Actor::~Actor() {
	mGame->RemoveActor(this);

	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime) {
	if (mState == EActive) {
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime) {
	for (auto comp : mComponents) {
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime) {

}

void Actor::ProcessInput(const uint8_t * keyState) {
	if (mState == State::EActive) {
		for (auto comp : mComponents) {
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t * keyState)
{
}

void Actor::AddComponent(Component * component) {
	// �\�[�g�ς݃x�N�g���ɂ����đ}������ꏊ��������
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++) {
		if (myOrder < (*iter)->GetUpdateOrder()) break;
	}
	// �C�e���[�^�̎�O�̈ʒu�ɗv�f��}������
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component * component) {
	auto iter = find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end()) {
		mComponents.erase(iter);
	}
}
