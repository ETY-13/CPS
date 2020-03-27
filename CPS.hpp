#ifndef CPS_HPP
#define CPS_HPP
#include<ostream>
class Shape {
public:
	virtual ~Shape() = default;
	virtual double height() const = 0;
	virtual double width() const = 0;

};

class Circle: public Shape {
public:
	Circle(double radius);
	double height() const override;
	double width() const override;
private:
	double _radius_;
};

class Polygon: public Shape {
public:
	Polygon(int numSides, double sideLength);
	double height() const override;
	double width() const override;

private:
	int _numSides_;
	double _sideLength_;
};

class Rectangle: public Shape {
public:
	Rectangle(double width, double height);
	double height() const override;
	double width() const override;

private:
	double _width_;
	double _height_;

};

class Spacer: public Rectangle {
public:
	Spacer(double widht, double height);
};

class Square: public Polygon {
public:
	Square(double sideLength);
};

class Triangle: public Polygon {
public:
	Triangle(double sideLength);
};

#endif // !CPS_HPP

