#ifndef CPS_HPP
#define CPS_HPP

#include<ostream>


class Shape {
public:
	virtual ~Shape() = default;
	virtual double getHeight() const = 0;
	virtual double getWidth() const = 0;
	virtual void generatePostScript(std::ostream& os) const = 0;
};

class Circle: public Shape {
public:
	Circle(double radius);
	double getHeight() const override;
	double getWidth() const override;
	void generatePostScript(std::ostream& os) const override;

private:
	double _radius_;
};

class Polygon: public Shape {
public:
	Polygon(int numSides, double sideLength);
	double getHeight() const override;
	double getWidth() const override;
	void generatePostScript(std::ostream& os) const override;

private:
	int _numSides_;
	double _sideLength_;
};

class Rectangle: public Shape {
public:
	Rectangle(double width, double height);
	double getHeight() const override;
	double getWidth() const override;
	void generatePostScript(std::ostream& os) const override;

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


// Utility functions for making each shape
std::shared_ptr<Shape> makeCircle(double radius);
std::shared_ptr<Shape> makePolygon(int numSides, double length);
std::shared_ptr<Shape> makeRectangle(double width, double height);
std::shared_ptr<Shape> makeSpacer(double width, double height);
std::shared_ptr<Shape> makeSquare(double length);
std::shared_ptr<Shape> makeTriangle(double length);
enum class Angle { R90, R180, R270 };
std::shared_ptr<Shape> makeRotatedShape(std::shared_ptr<Shape> s, Angle a);
std::shared_ptr<Shape> makeScaledShape(std::shared_ptr<Shape> s, double sx, double sy);
std::shared_ptr<Shape> makeLayeredShape(std::initializer_list<Shape> i);
std::shared_ptr<Shape> makeVerticalShape(std::initializer_list<Shape> i);
std::shared_ptr<Shape> makeHorizontalShape(std::initializer_list<Shape> i);
#endif // !CPS_HPP

