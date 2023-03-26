#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include "philosopher.hpp"

int main() {
    const int numPhilosophers = 5;
    std::vector<std::shared_ptr<Chopstick>> chopsticks(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i) {
        chopsticks[i] = std::make_shared<Chopstick>(i);
    }

    std::vector<Philosopher> philosophers(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers[i] = Philosopher(i, chopsticks[i], chopsticks[(i + 1) % numPhilosophers]);
    }

    std::vector<std::thread> threads(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i) {
        threads[i] = std::thread(&Philosopher::dine, &philosophers[i]);
    }

    for (int i = 0; i < numPhilosophers; ++i) {
        threads[i].join();
    }

    return 0;
}