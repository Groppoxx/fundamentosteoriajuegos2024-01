#include "MainGame.h"
#include "Sprite.h"
#include <random>
#include <thread>
#include <chrono>

using namespace std;

MainGame::MainGame()
{
	window = NULL;
	width = 1000;
	height = 800;
	gameState = GameState::PLAY;
	startTime = 0;
	interval = 1500;
}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Multiple Rectangulos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	initShaders();
}

MainGame::~MainGame()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void MainGame::run()
{
	init();

	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.01;
	
	sprites.draw();

	program.unuse();
	SDL_GL_SwapWindow(window);
	SDL_Delay(10);
}

void MainGame::update()
{
	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<double> dist(-0.9, 0.9);

	while (gameState != GameState::EXIT) {		

		Uint32 currentTime = SDL_GetTicks();

		if (currentTime - startTime > interval) {
			Sprite* sprite = new Sprite();
			sprite->init(dist(eng), dist(eng), 0.1f, 0.1f);
			sprites.addSprite(sprite);

			startTime = currentTime;
			cout << "Elemento pusheado " 
				<< sprites.getSprite().size() << endl;
		}

		draw();
		
		processInput();
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");

	program.linkShader();
}