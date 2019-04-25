#include <iostream>
#include <random>

using namespace std;

struct Vector {
public:
    float x;
    float y;

    Vector() {
        this->x = 0.0;
        this->y = 0.0;
    }

    Vector(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

// MARK :: Binary Operator for Vector Class
Vector operator +(const Vector u, const Vector v) {
    Vector w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    return w;
}

Vector operator -(const Vector u, const Vector v) {
    Vector w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    return w;
}

Vector operator *(const float a, const Vector u){	//内積 vector*vector
    Vector w;
    w.x = u.x * a;
    w.y = u.y * a;
    return w;
}

// MARK ::

class Particle {
private:
    const float w  = 0.5;
    const float c1 = 1.0;
    const float c2 = 1.0;

    Vector position;
    Vector best_position;
    Vector velocity;
public:
    Particle(Vector position) {
        this->position      = position;
        this->best_position = position;
        this->velocity      = Vector();
    }

    void update_position() {
        this->position = position + velocity;
    }

    void update_velocity(Vector global_best_position) {
        // memo :: Assign r1 and r2
        std::random_device engine;
        std::uniform_real_distribution<float> dist(0, 1.0);
        float r1 = dist(engine);
        float r2 = dist(engine);

        this->velocity = w * velocity
                            + (c1 * r1) * (best_position - position)
                            + (c2 * r2) * (global_best_position - position);
    }

    float value() {
        return 1.0;
    }
};

struct Application {
private:
    int particle_count;
    int loop_count;
    float x_min;
    float x_max;
    float y_min;
    float y_max;
public:
    Application(int particle_count, int loop_count, float x_min, float x_max, float y_min, float y_max) {
        this->particle_count = particle_count;
        this->loop_count     = loop_count;
        this->x_min          = x_min;
        this->x_max          = x_max;
        this->y_min          = y_min;
        this->y_max          = y_max;
    }

    void setup() {

    }

    void run() {
        std::random_device engine;
        std::uniform_real_distribution<float> x_dist(x_min, x_max);
        std::uniform_real_distribution<float> y_dist(y_min, y_max);

        for(int i = 0; i < particle_count; i++) {
            float x = x_dist(engine);
            float y = y_dist(engine);
            Vector position = Vector(x, y);
            Particle particle = Particle(position);
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

