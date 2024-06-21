#pragma once
#include "Agent.h"
class Zombie :
    public Agent
{
private:
    glm::vec2 direction;
public:
    Zombie();
    ~Zombie();
    void init(float speed, glm::vec2 position);
    void update(vector<string>& levelData, vector<Human*>& humans, glm::vec2 playerPosition, vector<Zombie*>& zombies);
    void setDirection(glm::vec2 newDirection)
    {
        direction = newDirection;
    }
};

