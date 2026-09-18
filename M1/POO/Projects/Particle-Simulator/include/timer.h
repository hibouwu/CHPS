#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>

class Timer {
    using clk = std::chrono::high_resolution_clock;
    std::string n;
    clk::time_point t0;

public:
    Timer(std::string name) : n(name) {
        t0 = clk::now();
    }
    
    void stop() {
        auto t1 = clk::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "[" << n << "] Elapsed time: " << ms << " ms" << std::endl;
    }
};

#endif
