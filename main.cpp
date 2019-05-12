#include <iostream>
#include <random>
#include <tuple>
#include <cmath>

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

struct Vector10D {
    int n = 10;

    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
    float g;
    float h;
    float i;
    float j;

    Vector10D() {
        this->a = 0.0;
        this->b = 0.0;
        this->c = 0.0;
        this->d = 0.0;
        this->e = 0.0;
        this->f = 0.0;
        this->g = 0.0;
        this->h = 0.0;
        this->i = 0.0;
        this->j = 0.0;
    }

    Vector10D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
        this->e = e;
        this->f = f;
        this->g = g;
        this->h = h;
        this->i = i;
        this->j = j;
    }

    Vector10D& operator = (const Vector10D& v) {
        this->a = v.a;
        this->b = v.b;
        this->c = v.c;
        this->d = v.d;
        this->e = v.e;
        this->f = v.f;
        this->g = v.g;
        this->h = v.h;
        this->i = v.i;
        this->j = v.j;

        return *this;
    }
};

// MARK :: Binary Operator for Vector10D Class
Vector10D operator +(const Vector10D u, const Vector10D v) {
    Vector10D w;
    w.a = u.a + v.a;
    w.b = u.b + v.b;
    w.c = u.c + v.c;
    w.d = u.d + v.d;
    w.e = u.e + v.e;
    w.f = u.f + v.f;
    w.g = u.g + v.g;
    w.h = u.h + v.h;
    w.i = u.i + v.i;
    w.j = u.j + v.j;
    return w;
}

Vector10D operator -(const Vector10D u, const Vector10D v) {
    Vector10D w;
    w.a = u.a - v.a;
    w.b = u.b - v.b;
    w.c = u.c - v.c;
    w.d = u.d - v.d;
    w.e = u.e - v.e;
    w.f = u.f - v.f;
    w.g = u.g - v.g;
    w.h = u.h - v.h;
    w.i = u.i - v.i;
    w.j = u.j - v.j;
    return w;
}

Vector10D operator *(const float a, const Vector10D u){	//内積 vector*vector
    Vector10D w;
    w.a = u.a * a;
    w.b = u.b * a;
    w.c = u.c * a;
    w.d = u.d * a;
    w.f = u.f * a;
    w.g = u.g * a;
    w.h = u.h * a;
    w.i = u.i * a;
    w.j = u.j * a;
    return w;
}
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

class Particle10D {
    float w  = 0.5;
    float c1 = 1.0;
    float c2 = 1.0;

    Vector10D      position;
    Vector10D best_position;
    Vector10D      velocity;
    float        best_value;
    int         problem_num;

    float function_value() {
        if (problem_num == 0) {
            return position.a * position.a + position.b * position.b + position.c * position.c
                + position.d * position.d + position.e * position.e + position.f * position.f + position.g * position.g
                + position.h * position.h + position.i * position.i + position.j * position.j;
        } else if (problem_num == 1) {
            return 10 * position.n
                + (position.a * position.a - 10 * std::cos(2 * M_PI * position.a))
                + (position.b * position.b - 10 * std::cos(2 * M_PI * position.b))
                + (position.c * position.c - 10 * std::cos(2 * M_PI * position.c))
                + (position.d * position.d - 10 * std::cos(2 * M_PI * position.d))
                + (position.e * position.e - 10 * std::cos(2 * M_PI * position.e))
                + (position.f * position.f - 10 * std::cos(2 * M_PI * position.f))
                + (position.g * position.g - 10 * std::cos(2 * M_PI * position.g))
                + (position.h * position.h - 10 * std::cos(2 * M_PI * position.h))
                + (position.i * position.i - 10 * std::cos(2 * M_PI * position.i))
                + (position.j * position.j - 10 * std::cos(2 * M_PI * position.j));
        } else if (problem_num == 2) {
            return 1
                + (position.a * position.a + position.b * position.b + position.c * position.c
                    + position.d * position.d + position.e * position.e + position.f * position.f + position.g * position.g
                    + position.h * position.h + position.i * position.i + position.j * position.j) / 4000
                - std::cos(position.a / std::sqrt(1)) * std::cos(position.b / std::sqrt(2))
                    * std::cos(position.c / std::sqrt(3)) * std::cos(position.d / std::sqrt(4))
                    * std::cos(position.e / std::sqrt(5)) * std::cos(position.f / std::sqrt(6))
                    * std::cos(position.g / std::sqrt(7)) * std::cos(position.h / std::sqrt(8))
                    * std::cos(position.i / std::sqrt(9)) * std::cos(position.j / std::sqrt(10));
        } else {
            return 0.0;
        }
    }

public:
    Particle10D() {}

    Particle10D(Vector10D position, int problem_num) {
        this->position      = position;
        this->best_position = position;
        this->velocity      = Vector10D();
        this->problem_num   = problem_num;
        this->best_value    = function_value();
    }

    Vector10D get_best_position() {
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

    void update_velocity(Vector10D global_best_position) {
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

    static std::tuple<Vector10D, float> calculate_best_position_and_value(Particle10D *particles, int particle_count) {
        Vector10D best_position = particles[0].get_best_position();
        float     best_value    = particles[0].get_best_value();

        for(int i = 0; i < particle_count; i++) {
            Particle10D particle = particles[i];
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
        }
        std::cout << best_position.x << ", " << best_position.y << std::endl;
    }

    void run10D() {
        Particle10D particles[particle_count];
        float       best_value;
        Vector10D   best_position;

        std::random_device engine;
        std::uniform_real_distribution<float> x_dist(x_min, x_max);

        for(int k = 0; k < particle_count; k++) {
            float a = x_dist(engine);
            float b = x_dist(engine);
            float c = x_dist(engine);
            float d = x_dist(engine);
            float e = x_dist(engine);
            float f = x_dist(engine);
            float g = x_dist(engine);
            float h = x_dist(engine);
            float i = x_dist(engine);
            float j = x_dist(engine);

            Vector10D position = Vector10D(a, b, c, d, e, f, g, h, i, j);
            Particle10D particle = Particle10D(position, problem_num);
            particles[k] = particle;
        }

        std::tie(best_position, best_value) = calculate_best_position_and_value(particles, particle_count);

        for(int loop = 0; loop < loop_count; loop++) {
            // memo :: update particles
            for(int i = 0; i < particle_count; i++) {
                Particle10D particle = particles[i];
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

        }
        std::cout << best_position.a << ", " << best_position.b << ", " << best_position.c
                << ", " << best_position.d << ", " << best_position.e << ", " << best_position.f
                << ", " << best_position.g << ", " << best_position.h << ", " << best_position.i
                << ", " << best_position.j << std::endl;
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
            application.run10D();
            break;
        } else if (problem_num == 1) {
            PSOApplication application = PSOApplication(particle_count, 100, -5.0, 5.0, 1);
            application.run10D();
            break;
        } else if (problem_num == 2) {
            PSOApplication application = PSOApplication(particle_count, 100, -600.0, 600.0, 2);
            application.run10D();
            break;
        }
    }
    return 0;
}

