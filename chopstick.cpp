#include "chopstick.hpp"

Chopstick::Chopstick(int id){
    this->id = id;
    sem_init(&mutex, 0, 1);
}

Chopstick::~Chopstick() {
    sem_destroy(&mutex);
}

int Chopstick::get_id() const {
    return id;
}

void Chopstick::pick_up() {
    sem_wait(&mutex);
}
void Chopstick::put_down() {
    sem_post(&mutex);
}