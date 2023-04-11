#ifndef CHOPSTICK_HPP
#define CHOPSTICK_HPP

#include <pthread.h>
#include <semaphore.h>

class Chopstick {
public:
    explicit Chopstick(int id);
    ~Chopstick();

    int get_id() const;
    void pick_up();
    void put_down();

private:
    int id;
    sem_t mutex;
};

#endif