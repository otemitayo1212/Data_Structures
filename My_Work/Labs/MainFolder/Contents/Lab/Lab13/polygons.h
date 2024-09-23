#ifndef _POLYGONS_H_
#define _POLYGONS_H_

#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include "utilities.h"

class Polygon {

public:
    std::string name;
    std::vector<Point> vertices;
    
    Polygon(const std::string &n, const std::vector<Point> &v) : name(n), vertices(v) {
        if (vertices.size() < 3)
            throw 1;
    }

     virtual ~Polygon() {}

    std::string getName() const {
        return name;
    }

    bool HasAllEqualSides() const {
    if (vertices.size() < 2)
        return false; // Not enough vertices to form sides
    double firstSide = DistanceBetween(vertices[0], vertices[1]);
    for (size_t i = 2; i < vertices.size(); ++i) {
        double side = DistanceBetween(vertices[i-1], vertices[i]);
        if (!EqualSides(firstSide, side))
            return false; // Found a side that is not equal to the first side
    }
    // Check the last side
    double lastSide = DistanceBetween(vertices[vertices.size() - 1], vertices[0]);
    if (!EqualSides(firstSide, lastSide))
        return false; // Last side is not equal to the first side
    return true; // All sides are equal
}
};

class Triangle : public Polygon {
public:
    Triangle(const std::string &n, const std::vector<Point> &v) : Polygon(n, v) {
        if (vertices.size() != 3)
            throw 1;
    }
};

class Quadrilateral : public Polygon {
public:
    Quadrilateral(const std::string &n, const std::vector<Point> &v) : Polygon(n, v) {
        if (vertices.size() != 4)
            throw 1;
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(const std::string &n, const std::vector<Point> &v) : Triangle(n, v) {
        if (v.size() != 3)
            throw 1; // Not a triangle
        // Check if any two sides are equal
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[0]);
        if (!(EqualSides(side1, side2) || EqualSides(side1, side3) || EqualSides(side2, side3)))
            throw 1;
    }
};
class RightTriangle : public Triangle {
public:
    RightTriangle(const std::string &n, const std::vector<Point> &v) : Triangle(n, v) {
        if (v.size() != 3)
            throw 1; // Not a triangle
        // Check if sides satisfy Pythagoras' theorem
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[0]);
        if (!(IsRightTriangle(side1, side2, side3)))
            throw 1;
    }

private:
    bool IsRightTriangle(double a, double b, double c) {
        // Sort the sides
        double sides[3] = {a, b, c};
        std::sort(sides, sides + 3);
        
        // Check if the sides satisfy Pythagoras' theorem
        return (fabs(sides[0]*sides[0] + sides[1]*sides[1] - sides[2]*sides[2]) < 1e-9); // tolerance for floating point comparison
    }
};

#include <cmath> // For mathematical functions like sqrt()

class IsoscelesRightTriangle : public Triangle {
public:
    IsoscelesRightTriangle(const std::string &n, const std::vector<Point> &v) : Triangle(n, v) {
        if (v.size() != 3)
            throw 1; // Not a triangle
        // Check if sides satisfy Pythagoras' theorem and at least two sides are equal
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[0]);
        if (!(IsRightTriangle(side1, side2, side3) && (EqualSides(side1, side2) || EqualSides(side1, side3) || EqualSides(side2, side3))))
            throw 1;
    }

private:
    bool IsRightTriangle(double a, double b, double c) {
        // Sort the sides
        double sides[3] = {a, b, c};
        std::sort(sides, sides + 3);
        
        // Check if the sides satisfy Pythagoras' theorem
        return (fabs(sides[0]*sides[0] + sides[1]*sides[1] - sides[2]*sides[2]) < 1e-9); // tolerance for floating point comparison
    }

    bool EqualSides(double a, double b) {
        return fabs(a - b) < 1e-9; // tolerance for floating point comparison
    }
};


class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(const std::string &n, const std::vector<Point> &v) : Triangle(n, v) {
        if (v.size() != 3)
            throw 1; // Not a triangle
        // Check if all three sides are equal
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[0]);
        if (!(EqualSides(side1, side2) && EqualSides(side1, side3)))
            throw 1; // Equilateral triangle condition is not met
    }
};

class Rectangle : public Quadrilateral {
public:
    Rectangle(const std::string &n, const std::vector<Point> &v) : Quadrilateral(n, v) {
        if (v.size() != 4)
            throw 1; // Not a quadrilateral
        // Check if opposite sides are equal
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[3]);
        double side4 = DistanceBetween(v[3], v[0]);
        if (!(EqualSides(side1, side3) && EqualSides(side2, side4)))
            throw 1; // Rectangle condition is not met
    }
};

class Square : public Rectangle {
public:
    Square(const std::string &n, const std::vector<Point> &v) : Rectangle(n, v) {
        if (v.size() != 4)
            throw 1; // Not a quadrilateral
        // Check if all sides are equal
        double side1 = DistanceBetween(v[0], v[1]);
        double side2 = DistanceBetween(v[1], v[2]);
        double side3 = DistanceBetween(v[2], v[3]);
        double side4 = DistanceBetween(v[3], v[0]);
        if (!(EqualSides(side1, side2) && EqualSides(side1, side3) && EqualSides(side1, side4)))
            throw 1; // Square condition is not met
    }
};




#endif