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

    Vector& operator = (const Vector& v) {
        this->x = v.x;
        this->y = v.y;
        return *this;
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
    float  best_value;
public:
    Particle() {}

    Particle(Vector position) {
        this->position      = position;
        this->best_position = position;
        this->velocity      = Vector();
        this->best_value    = function_value();
    }

    void update_position() {
        this->position = position + velocity;
    }

    void update_best_position_and_value() {
        float new_value = function_value();
        if (new_value < best_value) {
            this->best_position = position;
            this->best_value    = new_value;
        }
    }

    void update_velocity(Vector global_best_position) {
        // memo :: assign r1 and r2
        std::random_device engine;
        std::uniform_real_distribution<float> dist(0, 1.0);
        float r1 = dist(engine);
        float r2 = dist(engine);

        this->velocity = w * velocity
                            + (c1 * r1) * (best_position - position)
                            + (c2 * r2) * (global_best_position - position);
    }

    float function_value() {
        return position.x * position.x + position.y * position.y;
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
        Particle particles[particle_count];
        float    best_value;
        Vector   best_position;

        std::random_device engine;
        std::uniform_real_distribution<float> x_dist(x_min, x_max);
        std::uniform_real_distribution<float> y_dist(y_min, y_max);

        for(int i = 0; i < particle_count; i++) {
            float x = x_dist(engine);
            float y = y_dist(engine);
            Vector position = Vector(x, y);
            Particle particle = Particle(position);
        }

        // TODO :: Calculate Best Value and Position

        for(int loop = 0; loop < loop_count; loop++) {
            // memo :: update particles
            for(Particle particle: particles) {
                particle.update_position();
                particle.update_velocity(best_position);
                particle.update_best_position_and_value();
            }
        }
    }


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

