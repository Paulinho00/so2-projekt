#include <iostream>
#include <vector>
#include <memory>
#include <pthread.h>
#include "philosopher.hpp"

int main() {
    const int numPhilosophers = 10;
    std::vector<std::shared_ptr<Chopstick>> chopsticks(numPhilosophers);

    std::queue<Philosopher*> waitQueue;
    pthread_mutex_t queueMutex;
    pthread_mutex_init(&queueMutex, NULL);

    pthread_cond_t nextPhilosopher;
    pthread_cond_init(&nextPhilosopher, NULL);

    for (int i = 0; i < numPhilosophers; ++i) {
        chopsticks[i] = std::make_shared<Chopstick>(i);
    }

    std::vector<Philosopher> philosophers(numPhilosophers);

    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers[i] = Philosopher(i, chopsticks[i], chopsticks[(i + 1) % numPhilosophers], waitQueue, queueMutex, nextPhilosopher);
    }

    pthread_t threads[numPhilosophers];

    for (int i = 0; i < numPhilosophers; ++i) {
        pthread_create(&threads[i], NULL, (void* (*)(void*)) &Philosopher::dineWrapper, &philosophers[i]);
    }

    for (unsigned long long thread : threads) {
        pthread_join(thread, NULL);
    }

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&nextPhilosopher);

    return 0;
}