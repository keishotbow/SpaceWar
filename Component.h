#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Component {
public:
	// updateOrder���������R���|�[�l���g�������X�V�����
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	// ���̃R���|�[�l���g���f���^�^�C���ōX�V����
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyState);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner; // ���L�A�N�^�[
	int mUpdateOrder; // �R���|�[�l���g�̍X�V����

};

