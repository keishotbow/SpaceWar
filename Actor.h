#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Math.h"

using namespace std;

class Actor {
public:
	// �A�N�^�[�̏�ԊǗ��p
	enum State { EActive, EPaused, EDead };
	// �R���X�g���N�^�ƃf�X�g���N�^
	Actor(class Game* game);
	virtual ~Actor();

	// �Q�[������Ăяo�����X�V�֐�(�I�[�o�[���C�h�s��)
	void Update(float deltaTime);
	// �A�N�^�[�����S�R���|�[�l���g���X�V(�I�[�o�[���C�h�s��)
	void UpdateComponents(float deltaTime);
	// �A�N�^�[�Ǝ��̍X�V����(�I�[�o�[���C�h�\)
	virtual void UpdateActor(float deltaTime);
	
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	// �Q�b�^�[���Z�b�^�[
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; } // �A�N�^�[�̏�Ԃ��擾
	void SetState(State state) { mState = state; }

	class Game* GetGame() const { return mGame; }

	Vector2 GetForward() const { return Vector2(cosf(mRotation), -sinf(mRotation)); }

	// �R���|�[�l���g�̒ǉ��ƍ폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState; // �A�N�^�[�̏��
	// ���W�ϊ�
	Vector2 mPosition; // �A�N�^�[�̒��S���W
	float mScale; // �A�N�^�[�̃X�P�[��(1.0f��100%)
	float mRotation; // ��]�̊p�x
	// �A�N�^�[�����R���|�[�l���g
	vector<class Component*> mComponents;
	class Game* mGame;
};

