#include <iostream>
#include <random>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

class Particle {
private:
    Position position;
    Position best_position;
    Velocity velocity;
public:
    Particle(float x_min, float x_max, float y_min, float y_max) {
        std::random_device rd{};
    }

    void update_position() {
        float new_x = position.x + velocity.x;
        float new_y = position.y + velocity.y;
        this->position = Position(new_x, new_y);
    }

    void update_velocity(float x, float y) {

    }
};

struct Position {
private:
    float x;
    float y;
public:
    Position(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

struct Velocity {
private:
    float x;
    float y;
public:
    Velocity(float x, float y) {
        this->x = x;
        this->y = y;
    }
};