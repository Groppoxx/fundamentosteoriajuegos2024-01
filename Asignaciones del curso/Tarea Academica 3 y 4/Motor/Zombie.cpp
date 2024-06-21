#include "Zombie.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	color.set(0, 180, 0, 255);
	this->position = position;
	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, glm::vec2 playerPosition, vector<Zombie*>& zombies)
{
    glm::vec2 direction = glm::normalize(playerPosition - position);
    position += direction * speed;

    std::mt19937 randomEngine(time(nullptr));
    std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);
    if (collideWithLevel(levelData)) {
        direction = glm::rotate(direction, randRotate(randomEngine));
    }
    for (auto& zombie : zombies) {
        if (this != zombie && collideWithAgent(zombie)) {
           //Cambiar la direccion de los zombies
           /* glm::vec2 newDirection = glm::normalize(glm::vec2(randRotate(randomEngine), randRotate(randomEngine)));
            direction = newDirection;
            zombie->setDirection(newDirection);*/

            //Que no colisionen entre ellos
            glm::vec2 repelForce = glm::normalize(position - zombie->getPosition());
            float repelStrength = 10.0f;
            position += repelForce * repelStrength;
            zombie->getPosition() -= repelForce * repelStrength;
        }
    }

}
