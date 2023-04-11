#include <chrono>
#include <thread>
#include <iostream>
#include "philosopher.hpp"

Philosopher::Philosopher(int id, std::shared_ptr<Chopstick> leftChopstick, std::shared_ptr<Chopstick> rightChopstick)
    : id(id), leftChopstick(leftChopstick), rightChopstick(rightChopstick) {
    name = "Philosopher " + std::to_string(id);
}

void* Philosopher::dine() {
    for (int i = 0; i < 100; ++i) {
        think();
        eat();
    }

    return NULL;
}

void Philosopher::think() {
    print_text("is thinking");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Philosopher::eat() {
    print_text("is eating");
    if(leftChopstick->get_id() < rightChopstick->get_id()) {
        leftChopstick->pick_up();
        rightChopstick->pick_up();
    }
    else{
        rightChopstick->pick_up();
        leftChopstick->pick_up();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    leftChopstick->put_down();
    rightChopstick->put_down();
}

void Philosopher::print_text(const std::string& text) {
    std::cout << name << " " << text << std::endl;
}

void* Philosopher::dineWrapper(void* arg) {
    Philosopher* philosopher = static_cast<Philosopher*>(arg);
    return philosopher->dine();
}