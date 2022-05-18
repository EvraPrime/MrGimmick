#pragma once
#include "Game.h"

class MainScene : public Game
{
public:
	MainScene(HINSTANCE hInstance);
	~MainScene();

	bool Init() override;
	void Update(float dt) override;
	void Render(float dt) override;
};
