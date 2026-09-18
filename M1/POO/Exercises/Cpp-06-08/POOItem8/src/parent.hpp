#ifndef PARENT_HPP
#define PARENT_HPP

#include <iostream>

struct Parent {
private:
    int v;

public:
    Parent(int value = 0) {
        v = value;
    }

    void print_parent() const {
        std::cout << "Parent ; v = " << get_v() << std::endl;
    }

    int get_v() const {
        return v;
    }

    void set_v(int value) {
        v = value;
    }
};

struct Son : public Parent {
public:
    Son() : Parent(0) {}
    
    void set_value(int value) {
        set_v(value);
    }
    
    void print() const {
        std::cout << "The Child, Parent ; v =" << get_v() << std::endl;
    }
};

struct Point{
    virtual void print() const = 0; // Méthode virtuelle pure
    virtual ~Point() = default; // Destructeur virtuel

};


struct Point2D : public Point {
    double x;
    double y;

    Point2D(double x_val, double y_val) : x(x_val), y(y_val) {}

    void print() const {
        std::cout << "Point2D(" << x << ", " << y << ")" << std::endl;
    }

    double distance_to_origin() const {
        return std::sqrt(x * x + y * y);
    }
};

#endif