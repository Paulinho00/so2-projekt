#include <chrono>
#include <iostream>
#include <pthread.h>
#include <thread>
#include "philosopher.hpp"

Philosopher::Philosopher(int id, std::shared_ptr<Chopstick> leftChopstick, std::shared_ptr<Chopstick> rightChopstick,
                         std::queue<Philosopher*>& waitQueue, pthread_mutex_t& queueMutex, pthread_cond_t& nextPhilosopher) {
    name = "Philosopher " + std::to_string(id);
    this->id = id;
    this->leftChopstick = leftChopstick;
    this->rightChopstick = rightChopstick;
    this->waitQueue = &waitQueue;
    this->queueMutex = &queueMutex;
    this->nextPhilosopher = &nextPhilosopher;
}

void* Philosopher::dine() {
    for (int i = 0; i < 2; ++i) {
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
    bool hasForks = false;
    while(!hasForks) {
        // try to acquire mutex locks for forks
        leftChopstick->pick_up();
        leftChopstick->setInUse(true);
        bool leftLocked = true;
        if (!rightChopstick->isInUseByPhilosopher()) {

            rightChopstick->pick_up();
            bool rightLocked = true;
            hasForks = true;

            rightChopstick->setInUse(true);

            print_text("is eating");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            leftChopstick->setInUse(false);
            rightChopstick->setInUse(false);

            leftChopstick->put_down();
            rightChopstick->put_down();
            print_text("koniec zarcia");
            // Signal the next philosopher in line
            pthread_mutex_lock(queueMutex);
            if (!waitQueue->empty()) {
                print_text("wysyła na sygnał");
                pthread_cond_signal(nextPhilosopher);
            }
            pthread_mutex_unlock(queueMutex);
        } else {
            //if right fork is in use
            leftChopstick->put_down();
            leftLocked = false;
        }

        // if we get here, we failed to acquire both forks
        if (!hasForks && !leftLocked) {
            // if we didn't acquire left fork, add ourselves to queue
            pthread_mutex_lock(queueMutex);
            waitQueue->push(this);
            pthread_mutex_unlock(queueMutex);

            print_text("czeka na sygnał");
            leftChopstick->pick_up();
            pthread_mutex_lock(queueMutex);
            while (waitQueue->front() != this) {
                pthread_cond_wait(nextPhilosopher, queueMutex);
            }
            waitQueue->pop();
            pthread_mutex_unlock(queueMutex);
            print_text("doczekał się");
        }
    }
}

void Philosopher::print_text(const std::string& text) {
    std::cout << name << " " << text << std::endl;
}

void* Philosopher::dineWrapper(void* arg) {
    Philosopher* philosopher = static_cast<Philosopher*>(arg);
    return philosopher->dine();
}