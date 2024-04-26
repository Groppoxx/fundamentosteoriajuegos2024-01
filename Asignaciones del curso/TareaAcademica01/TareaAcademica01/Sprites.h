#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "Sprite.h"
using namespace std;

class Sprites
{
public:
	Sprites() {
		sprites = vector<Sprite*>();
	}
	~Sprites() {
		// Liberar la memoria de cada Sprite
		for (int i = 0; i < sprites.size(); i++) {
			delete sprites[i];
		}
		// Limpiar el vector
		sprites.clear();
	}

	void draw() {
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i]->draw();
		}
	}

	void addSprite(Sprite* sprite) {
		sprites.push_back(sprite);
	}

	vector<Sprite*> getSprite() {
		return sprites;
	}

private:
	vector<Sprite*> sprites;
};