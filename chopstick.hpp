#ifndef CHOPSTICK_HPP
#define CHOPSTICK_HPP

#include <mutex>

class Chopstick {
public:
    explicit Chopstick(int id) : id(id) {}
    Chopstick() = default;

    int get_id() const;
    void pick_up();
    void put_down();

private:
    int id;
    std::mutex mutex;
};

#endif