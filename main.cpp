#include <iostream>
#include <random>
#include <tuple>
#include <cmath>
#include <fstream>

struct Vector {
public:
    int n = 2;

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
    float w  = 0.5;
    float c1 = 1.0;
    float c2 = 1.0;

    Vector      position;
    Vector best_position;
    Vector      velocity;
    float     best_value;
    int      problem_num;

    float function_value() {
        if (problem_num == 0) {
            return position.x * position.x + position.y * position.y;
        } else if (problem_num == 1) {
            return 10 * position.n
                + (position.x * position.x - 10 * std::cos(2 * M_PI * position.x))
                + (position.y * position.y - 10 * std::cos(2 * M_PI * position.y));
        } else if (problem_num == 2) {
            return 1
                + ((position.x * position.x) + (position.y * position.y)) / 4000
                - std::cos(position.x / std::sqrt(1)) * std::cos(position.y / std::sqrt(2));
        } else {
            return 0.0;
        }
    }
public:
    Particle() {}

    Particle(Vector position, int problem_num) {
        this->position      = position;
        this->best_position = position;
        this->velocity      = Vector();
        this->problem_num   = problem_num;
        this->best_value    = function_value();
    }

    Vector get_best_position() {
        return best_position;
    }

    float get_best_value() {
        return best_value;
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
};


struct PSOApplication {
private:
    int particle_count;
    int     loop_count;
    float        x_min;
    float        x_max;
    int    problem_num;

    static std::tuple<Vector, float> calculate_best_position_and_value(Particle *particles, int particle_count) {
        Vector best_position = particles[0].get_best_position();
        float  best_value    = particles[0].get_best_value();

        for(int i = 0; i < particle_count; i++) {
            Particle particle = particles[i];
            if (particle.get_best_value() < best_value) {
                best_position = particle.get_best_position();
                best_value    = particle.get_best_value();
            }
        }

        return std::forward_as_tuple(best_position, best_value);
    };
    
public:
    PSOApplication(int particle_count, int loop_count, float x_min, float x_max, int problem_num) {
        this->particle_count = particle_count;
        this->loop_count     = loop_count;
        this->x_min          = x_min;
        this->x_max          = x_max;
        this->problem_num    = problem_num;
    }

    void run() {
        Particle particles[particle_count];
        float    best_value;
        Vector   best_position;

        std::random_device engine;
        std::uniform_real_distribution<float> x_dist(x_min, x_max);

        for(int i = 0; i < particle_count; i++) {
            float x = x_dist(engine);
            float y = x_dist(engine);
            Vector position = Vector(x, y);
            Particle particle = Particle(position, problem_num);
            particles[i] = particle;
        }

        std::tie(best_position, best_value) = calculate_best_position_and_value(particles, particle_count);

        std::ofstream outputfile("pso.txt");

        for(int loop = 0; loop < loop_count; loop++) {
            // memo :: update particles
            for(int i = 0; i < particle_count; i++) {
                Particle particle = particles[i];
                particle.update_position();
                particle.update_velocity(best_position);
                particle.update_best_position_and_value();
                particles[i] = particle;
            }

            // memo :: calculate global best position and value after all particles are updated
            std::tie(best_position, best_value) = calculate_best_position_and_value(particles, particle_count);

//            std::cout << "  ----- LOOP : " << loop << " ------" << std::endl;
//            std::cout << "GLOBAL BEST VALUE    : " << best_value << std::endl;
//            std::cout << "GLOBAL BEST POSITION : (" << best_position.x << ", " << best_position.y << ")" << std::endl;

            std::cout << best_value << std::endl;

            outputfile << best_value << std::endl;
        }
        std::cout << best_position.x << ", " << best_position.y << std::endl;

        outputfile.close();
    }
};

int main() {
    while (true) {
        int particle_count;
        int    problem_num;
        std::cout << "Input Particle Count:";
        std::cin >> particle_count;
        std::cout << "Input problem number [0]Sphere [1]Rastrigin [2]Griewank :";
        std::cin >> problem_num;
        if (problem_num == 0) {
            PSOApplication application = PSOApplication(particle_count, 100, -5.0, 5.0, 0);
            application.run();
            break;
        } else if (problem_num == 1) {
            PSOApplication application = PSOApplication(particle_count, 100, -5.0, 5.0, 1);
            application.run();
            break;
        } else if (problem_num == 2) {
            PSOApplication application = PSOApplication(particle_count, 100, -600.0, 600.0, 2);
            application.run();
            break;
        }
    }
    return 0;
}

