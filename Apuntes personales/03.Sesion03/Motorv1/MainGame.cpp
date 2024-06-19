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
	initShaders();
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", 
		"Shaders/colorShaderFrag.txt");
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShaders();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.0002;
	sprite.draw();
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::run()
{
	init();
	sprite.init(-1, -1, 1, 1);
	update();
}

void MainGame::update()
{
	while (gameState != GameState::EXIT)
	{
		processInput();
		draw();
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << "Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

MainGame::~MainGame()
{
}
