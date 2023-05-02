#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <string>
#include <memory>
#include <queue>
#include "chopstick.hpp"

class Philosopher {
public:
    Philosopher(int id, std::shared_ptr<Chopstick> leftChopstick, std::shared_ptr<Chopstick> rightChopstick,
                std::queue<Philosopher*>& waitQueue, pthread_mutex_t& queueMutex, pthread_cond_t& nextPhilosopher);
    Philosopher() = default;
    void* dine();
    static void* dineWrapper(void* arg);
    float getWaitingTime();
    static void set_philosopher_status();

private:
    int id;
    float waitingTimeCounter;
    std::string name;
    std::shared_ptr<Chopstick> leftChopstick;
    std::shared_ptr<Chopstick> rightChopstick;
    std::queue<Philosopher*>* waitQueue;
    pthread_mutex_t* queueMutex;
    pthread_mutex_t drawMutex;
    pthread_cond_t* nextPhilosopher;
    void think();
    void incrementMealsCounter(float addValue);
    void eat();
    void print_text(const std::string& text);
    static int* philosopher_status;
};

#endif