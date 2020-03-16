#include "BGSpriteComponent.h"
#include "Actor.h"
#include <SDL.h>

BGSpriteComponent::BGSpriteComponent(Actor * owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures) {
		// x�I�t�Z�b�g���X�V����
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// ��ʊO�ɏo����I�t�Z�b�g���Ō�̔w�i�e�N�X�`���̉E�Ƀ��Z�b�g
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer * renderer) {
	// �S�w�i�e�N�X�`����`��
	for (auto& bg : mBGTextures) {
		SDL_Rect r;
		// �X�N���[���T�C�Y�̈�𐄒�
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// �w�i��`��
		SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
	}
}

void BGSpriteComponent::SetBGTextures(const vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.mTexture = tex;
		// ���ꂼ��̃e�N�X�`���͉�ʕ����̃I�t�Z�b�g������
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
