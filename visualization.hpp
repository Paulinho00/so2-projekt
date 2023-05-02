#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include "visualization.hpp"
#include <mutex>

class Visualization {
    public:
        static void draw_faces(int*);
        static void draw_table();
        static void draw_fork_0(int);
        static void draw_fork_1(int);
        static void draw_fork_2(int);
        static void draw_fork_3(int);
        static void draw_fork_4(int);
        static void draw_fork_5(int);
        static void draw_fork_6(int);
        static void draw_fork_7(int);
        static void draw_fork_8(int);
        static void draw_fork_9(int);
        static void drawing(int*);
    private:
        static std::mutex coutMutex;
};

#endif