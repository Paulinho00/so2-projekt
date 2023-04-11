#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <string>
#include <memory>
#include "chopstick.hpp"

class Philosopher {
public:
    Philosopher(int id, std::shared_ptr<Chopstick> leftChopstick, std::shared_ptr<Chopstick> rightChopstick);
    Philosopher() = default;
    void* dine();
    static void* dineWrapper(void* arg);

private:
    int id;
    std::string name;
    std::shared_ptr<Chopstick> leftChopstick;
    std::shared_ptr<Chopstick> rightChopstick;

    void think();
    void eat();
    void print_text(const std::string& text);
};

#endif