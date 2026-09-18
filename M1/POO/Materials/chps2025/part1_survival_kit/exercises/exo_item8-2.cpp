#include <iostream>

struct Point {
  virtual ~Point() = default;
  virtual void print() {std::cout << "Point" << std::endl;}
};

struct Point2D : public Point {
  void print() override {std::cout << "Point2D" << std::endl;}
};

struct Point3D : public Point {
  void print() override {std::cout << "Point3D" << std::endl;}
};

void func(Point& point){
  point.print();
}

int main(){
  Point2D point_2D{};
  Point3D point_3D{};
  func(point_2D);
  func(point_3D);
}