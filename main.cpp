#include <iostream>
#include <vector>
#include <memory>
#include <pthread.h>
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

    pthread_t threads[numPhilosophers];

    for (int i = 0; i < numPhilosophers; ++i) {
        pthread_create(&threads[i], NULL, (void* (*)(void*)) &Philosopher::dineWrapper, &philosophers[i]);
    }

    for (unsigned long long thread : threads) {
        pthread_join(thread, NULL);
    }

    return 0;
}