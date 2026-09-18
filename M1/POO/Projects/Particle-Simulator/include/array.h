#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class Array {
private:
    std::vector<double> d;

public:
    Array(std::size_t n, double val = 0.0) : d(n, val) {}
    
    std::size_t size() const { return d.size(); }
    
    double& operator[](std::size_t i) { return d[i]; }
    const double& operator[](std::size_t i) const { return d[i]; }
    
    auto begin() { return d.begin(); }
    auto end() { return d.end(); }
    auto begin() const { return d.begin(); }
    auto end() const { return d.end(); }
    
    void fill(double v) {
        std::fill(d.begin(), d.end(), v);
    }
    
    void print(const std::string& name) const {
        std::ofstream f(name, std::ios::app);
        if(f) {
            for(auto v : d) f << v << " ";
        }
    }
};

#endif
