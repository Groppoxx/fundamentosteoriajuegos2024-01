#include "MainGame.h"

MainGame::MainGame()
{
	window = nullptr;
	width = 1024;
	height = 768;
	gameState = GameState::PLAY;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Motorv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

void MainGame::run()
{
	init();
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT)
	{
		draw();
	}
}

void MainGame::processInput()
{
}

MainGame::~MainGame()
{
}
