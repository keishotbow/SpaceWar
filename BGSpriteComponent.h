#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>

using namespace std;

class BGSpriteComponent : public SpriteComponent {
public:
	// �w�i�Ȃ̂ŗD��I�ɕ`��
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// �X�V�ƕ`��͐e����I�[�o�[���C�h
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// �w�i�p�̃e�N�X�`�����Z�b�g����
	void SetBGTextures(const vector<SDL_Texture*>& textures);
	// ��ʃT�C�Y�ƃX�N���[�����x�̐ݒ�Ǝ擾
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }

private:
	// �X�̔w�i�摜�ƃI�t�Z�b�g���J�v�Z��������\����
	struct BGTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

