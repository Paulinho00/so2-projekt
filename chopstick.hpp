#ifndef CHOPSTICK_HPP
#define CHOPSTICK_HPP

#include <pthread.h>

class Chopstick {
public:
    explicit Chopstick(int id);

    int get_id() const;
    void pick_up();
    void put_down();
    bool isInUseByPhilosopher();
    void setInUse(bool inUse);

private:
    int id;
    pthread_mutex_t mutex;
    bool isInUse;
};

#endif