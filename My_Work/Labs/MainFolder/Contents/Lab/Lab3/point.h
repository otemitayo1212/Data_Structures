// Add include guards to prevent multiple inclusions
#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
  // CONSTRUCTOR
  Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  // ACCESSORS
  double get_x() const { return x_; }
  double get_y() const { return y_; }
  double get_z() const { return z_; }
private:
  // REPRESENTATION
  double x_, y_, z_;
};

// A helper function to print a Point.
std::ostream& operator<< (std::ostream &ostr, const Point &p);

// A helper function to compute the slope between two Points.
double compute_slope(const Point &a, const Point &b);

#endif // POINT_H

