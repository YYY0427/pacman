#pragma once
#include "../vec2.h"
#include <memory>

class Player;

class BackGround
{
public:
	BackGround(int handle);
	virtual~BackGround(){};

	void Update();

	void Draw();

	void SetPlayer(std::shared_ptr<Player>player) { pPlayer_ = player; }
private:
	int handle_;

	Vec2 size_;

	std::shared_ptr<Player> pPlayer_;

	// それぞれの方向に表示する枚数
	int width_;
	int height_;

	int scroll_;
};