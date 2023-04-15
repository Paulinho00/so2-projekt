#include <chrono>
#include <iostream>
#include <pthread.h>
#include <thread>
#include "philosopher.hpp"

Philosopher::Philosopher(int id, std::shared_ptr<Chopstick> leftChopstick, std::shared_ptr<Chopstick> rightChopstick,
                         std::queue<Philosopher*>& waitQueue, pthread_mutex_t& queueMutex, pthread_cond_t& nextPhilosopher) {
    name = "Philosopher " + std::to_string(id);
    this->eatenMealsCounter = 0;
    this->id = id;
    this->leftChopstick = leftChopstick;
    this->rightChopstick = rightChopstick;
    this->waitQueue = &waitQueue;
    this->queueMutex = &queueMutex;
    this->nextPhilosopher = &nextPhilosopher;
}

void Philosopher::incrementMealsCounter() {
    eatenMealsCounter++;
}

int Philosopher::getMealsCounter() {
    return eatenMealsCounter;
}

void* Philosopher::dine() {
    for (int i = 0; i < 100; ++i) {
        think();
        eat();
    }
    print_text("END");

    return NULL;
}

void Philosopher::think() {
    print_text("is thinking");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Philosopher::eat() {
    bool hasForks = false;
    bool leftLocked = false;
    bool rightLocked = false;
    while(!hasForks) {
        if(leftChopstick->get_id() < rightChopstick->get_id()) {

            // try to acquire mutex locks for forks
            leftChopstick->pick_up();
            leftChopstick->setInUse(true);
            leftLocked = true;
            if (!rightChopstick->isInUseByPhilosopher()) {

                rightChopstick->pick_up();
                rightLocked = true;
                hasForks = true;

                rightChopstick->setInUse(true);

                print_text("is eating");
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                incrementMealsCounter();

                leftChopstick->setInUse(false);
                rightChopstick->setInUse(false);

                leftChopstick->put_down();
                rightChopstick->put_down();
                // Signal the next philosopher in line
                pthread_mutex_lock(queueMutex);
                if (!waitQueue->empty()) {
                    pthread_cond_broadcast(nextPhilosopher);
                }
                pthread_mutex_unlock(queueMutex);
            } else {
                //if right fork is in use
                leftChopstick->put_down();
                leftLocked = false;
            }
        }
        else {
            // try to acquire mutex locks for forks
            rightChopstick->pick_up();
            rightChopstick->setInUse(true);
            rightLocked = true;
            if (!leftChopstick->isInUseByPhilosopher()) {
                leftChopstick->pick_up();
                rightLocked = true;
                hasForks = true;

                leftChopstick->setInUse(true);


                print_text("is eating");
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                leftChopstick->setInUse(false);
                rightChopstick->setInUse(false);

                leftChopstick->put_down();
                rightChopstick->put_down();
                // Signal the next philosopher in line
                pthread_mutex_lock(queueMutex);
                if (!waitQueue->empty()) {
                    pthread_cond_broadcast(nextPhilosopher);
                }
                pthread_mutex_unlock(queueMutex);
            } else {
                //if right fork is in use
                rightChopstick->put_down();
                rightLocked = false;
            }

        }

        // if we get here, we failed to acquire both forks
        if (!hasForks && !leftLocked && !rightLocked) {
            // if we didn't acquire left fork, add ourselves to queue
            pthread_mutex_lock(queueMutex);
            waitQueue->push(this);
            while (waitQueue->front() != this) {
                pthread_cond_wait(nextPhilosopher, queueMutex);
            }
            waitQueue->pop();
            pthread_mutex_unlock(queueMutex);
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