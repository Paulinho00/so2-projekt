#include <ncurses.h>
#include <cmath>
#include "visualization.hpp"

std::mutex Visualization::coutMutex;

void Visualization::draw_faces(int* philosophers){
    // Obliczenie położenia środka koła
    int center_y = LINES / 2;
    int center_x = COLS / 2;

    // Obliczenie promienia koła
    int radius = std::min(LINES, COLS) / 4;

    int counter = 0;

    // Ustawienie koloru i rysowanie uśmiechniętych buziek
    for (int angle = 0; angle < 360; angle += 36) {

        if(philosophers[counter] == 1)
            attron(COLOR_PAIR(1));
        else
            attron(COLOR_PAIR(2));

        int x = center_x + std::cos(angle * M_PI / 180.0) * radius * 1.5;
        int y = center_y + std::sin(angle * M_PI / 180.0) * radius * 1.5;
        mvaddch(y-3, x-3, '/');
        mvaddch(y-3, x+3, '\\');
        mvaddch(y-2, x-4, '(');
        mvaddch(y-2, x-3, '_');
        mvaddch(y-2, x-2, '_');
        mvaddch(y-2, x-1, '_');
        mvaddch(y-2, x, '_');
        mvaddch(y-2, x+1, '_');
        mvaddch(y-2, x+2, '_');
        mvaddch(y-2, x+3, ')');
        mvaddch(y-1, x-4, '|');
        mvaddch(y-1, x-3, ' ');
        mvaddch(y-1, x-2, 'o');
        mvaddch(y-1, x-1, ' ');
        mvaddch(y-1, x, 'o');
        mvaddch(y-1, x+1, ' ');
        mvaddch(y-1, x+2, '|');
        mvaddch(y, x-4, '|');
        mvaddch(y, x-3, ' ');
        mvaddch(y, x-2, ' ');
        mvaddch(y, x-1, ' ');
        mvaddch(y, x, ' ');
        mvaddch(y, x+1, ' ');
        mvaddch(y, x+2, '|');
        mvaddch(y+1, x-4, '\\');
        mvaddch(y+1, x-3, '_');
        mvaddch(y+1, x-2, '_');
        mvaddch(y+1, x , '_');
        mvaddch(y+1, x-1, '_');
        mvaddch(y+1, x, '_');
        mvaddch(y+1, x+1, '_');
        mvaddch(y+1, x+2, '/');

        if(philosophers[counter] == 1)
            attroff(COLOR_PAIR(1));
        else
            attroff(COLOR_PAIR(2));

        counter ++;
    }
}

void Visualization::draw_table(){
    // Obliczenie położenia środka koła
    int center_y = LINES / 2;
    int center_x = COLS / 2;

    // Obliczenie promienia koła
    int radius = std::min(LINES, COLS) / 4;

    // Ustawienie koloru i rysowanie koła
    attron(COLOR_PAIR(1));
    for (int angle = 0; angle <= 360; angle += 10) {
        int x = center_x + std::cos(angle * M_PI / 180.0) * radius;
        int y = center_y + std::sin(angle * M_PI / 180.0) * radius;
        mvaddch(y, x, 'o');
    }
    attroff(COLOR_PAIR(1));
}

void Visualization::draw_fork_8(int color){
    //0
    attron(COLOR_PAIR(color));
    mvaddch(10, 110, '_');
    mvaddch(10, 111, '_');
    mvaddch(10, 112, '_');
    mvaddch(10, 113, '_');
    mvaddch(10, 114, '_');
    mvaddch(10, 115, '_');
    mvaddch(10, 116, '_');
    mvaddch(10, 117, '_');
    mvaddch(10, 118, '_');
    mvaddch(10, 119, '_');
    mvaddch(10, 120, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_9(int color){
    //1
    attron(COLOR_PAIR(color));
    mvaddch(20, 115, '_');
    mvaddch(20, 116, '_');
    mvaddch(20, 117, '_');
    mvaddch(20, 118, '_');
    mvaddch(20, 119, '_');
    mvaddch(20, 120, '_');
    mvaddch(20, 121, '_');
    mvaddch(20, 122, '_');
    mvaddch(20, 123, '_');
    mvaddch(20, 124, '_');
    mvaddch(20, 125, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_0(int color){
    //2
    attron(COLOR_PAIR(color));
    mvaddch(32, 115, '_');
    mvaddch(32, 116, '_');
    mvaddch(32, 117, '_');
    mvaddch(32, 118, '_');
    mvaddch(32, 119, '_');
    mvaddch(32, 120, '_');
    mvaddch(32, 121, '_');
    mvaddch(32, 122, '_');
    mvaddch(32, 123, '_');
    mvaddch(32, 124, '_');
    mvaddch(32, 125, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_1(int color){
    //3
    attron(COLOR_PAIR(color));
    mvaddch(40, 110, '_');
    mvaddch(40, 111, '_');
    mvaddch(40, 112, '_');
    mvaddch(40, 113, '_');
    mvaddch(40, 114, '_');
    mvaddch(40, 115, '_');
    mvaddch(40, 116, '_');
    mvaddch(40, 117, '_');
    mvaddch(40, 118, '_');
    mvaddch(40, 119, '_');
    mvaddch(40, 120, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_2(int color){
    //4
    attron(COLOR_PAIR(color));
    mvaddch(42, 100, '|');
    mvaddch(43, 100, '|');
    mvaddch(44, 100, '|');
    mvaddch(45, 100, '|');
    mvaddch(46, 100, '|');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_3(int color){
    //5
    attron(COLOR_PAIR(color));
    mvaddch(40, 81, '_');
    mvaddch(40, 82, '_');
    mvaddch(40, 83, '_');
    mvaddch(40, 84, '_');
    mvaddch(40, 85, '_');
    mvaddch(40, 86, '_');
    mvaddch(40, 87, '_');
    mvaddch(40, 88, '_');
    mvaddch(40, 88, '_');
    mvaddch(40, 89, '_');
    mvaddch(40, 90, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_4(int color){
    //6
    attron(COLOR_PAIR(color));
    mvaddch(32, 75, '_');
    mvaddch(32, 76, '_');
    mvaddch(32, 77, '_');
    mvaddch(32, 78, '_');
    mvaddch(32, 79, '_');
    mvaddch(32, 80, '_');
    mvaddch(32, 81, '_');
    mvaddch(32, 82, '_');
    mvaddch(32, 83, '_');
    mvaddch(32, 84, '_');
    mvaddch(32, 85, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_5(int color){
    //7
    attron(COLOR_PAIR(color));
    mvaddch(20, 75, '_');
    mvaddch(20, 76, '_');
    mvaddch(20, 77, '_');
    mvaddch(20, 78, '_');
    mvaddch(20, 79, '_');
    mvaddch(20, 80, '_');
    mvaddch(20, 81, '_');
    mvaddch(20, 82, '_');
    mvaddch(20, 83, '_');
    mvaddch(20, 84, '_');
    mvaddch(20, 85, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_6(int color){
    //8
    attron(COLOR_PAIR(color));
    mvaddch(10, 81, '_');
    mvaddch(10, 82, '_');
    mvaddch(10, 83, '_');
    mvaddch(10, 84, '_');
    mvaddch(10, 85, '_');
    mvaddch(10, 86, '_');
    mvaddch(10, 87, '_');
    mvaddch(10, 88, '_');
    mvaddch(10, 89, '_');
    mvaddch(10, 90, '_');
    mvaddch(10, 91, '_');
    attroff(COLOR_PAIR(color));
}

void Visualization::draw_fork_7(int color){
    //9
    attron(COLOR_PAIR(color));
    mvaddch(5, 100, '|');
    mvaddch(6, 100, '|');
    mvaddch(7, 100, '|');
    mvaddch(8, 100, '|');
    mvaddch(9, 100, '|');
    attroff(COLOR_PAIR(color));
}

void Visualization::drawing(int* philosophers){

    std::lock_guard<std::mutex> coutLock(coutMutex);

    // Inicjalizacja biblioteki ncurses
    initscr();

    // Ustawienie trybu wyświetlania
    cbreak();
    noecho();

    // Ukrycie kursora
    curs_set(0);

    // Ustawienie kolorów
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    draw_faces(philosophers);
    draw_table();

    int color[10];

    for(int i = 0; i < 10; i++){
        color[i] = 2;
    }

    for(int i = 0; i < 10; i++){
        if(philosophers[i] == 1){
            color[i] = 1;
            if(i < 1)
                color[9] = 1;
            else
                color[i - 1] = 1;
        }
    }

    draw_fork_0(color[0]);
    draw_fork_1(color[1]);
    draw_fork_2(color[2]);
    draw_fork_3(color[3]);
    draw_fork_4(color[4]);
    draw_fork_5(color[5]);
    draw_fork_6(color[6]);
    draw_fork_7(color[7]);
    draw_fork_8(color[8]);
    draw_fork_9(color[9]);

    refresh();

    napms(100);
    // Zakończenie pracy z biblioteką ncurses
    endwin();
}
