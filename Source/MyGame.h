#pragma once
#include "Game.h"

class MyGame : public Game {
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};
public:
	MyGame(Engine* engine) : Game{ engine } {

	}

	// Inherited via Game
	bool Initialize() override;

	void Shutdown() override;

	void Update(float dt) override;

	void Draw(Renderer& renderer) override;

private:
	eState m_state{ eState::Title };
	float m_spawnTimer = 0;
	float m_spawnTime = 0;
};