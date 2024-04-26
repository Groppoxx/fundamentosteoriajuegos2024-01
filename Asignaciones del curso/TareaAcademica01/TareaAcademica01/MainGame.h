#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <iostream>
#include <vector>
#include <random>
#include "Sprite.h"
#include "GLS_Program.h"
#include "Sprites.h"
using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame
{
private:
	Sprites sprites;

	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext glContext;

	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;

	Uint32 startTime;
	Uint32 interval;

public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();

	void push_sprite();
};

