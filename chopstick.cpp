#include "chopstick.hpp"

Chopstick::Chopstick(int id){
    this->id = id;
    isInUse = false;
    pthread_mutex_init(&mutex, NULL);
}

int Chopstick::get_id() const {
    return id;
}

void Chopstick::setInUse(bool inUse) {
     isInUse = inUse;
}

bool Chopstick::isInUseByPhilosopher(){
    return isInUse;
}


void Chopstick::pick_up() {
    pthread_mutex_lock(&mutex);
}
void Chopstick::put_down() {
    pthread_mutex_unlock(&mutex);
}