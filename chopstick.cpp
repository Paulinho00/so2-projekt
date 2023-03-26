#include "chopstick.hpp"

int Chopstick::get_id() const {
    return id;
}

void Chopstick::pick_up() {
    mutex.lock();
}

void Chopstick::put_down() {
    mutex.unlock();
}