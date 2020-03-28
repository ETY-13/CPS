
#include"CPS.hpp"

#include<math.h>
using std::cos;
using std::sin;

using std::make_shared;

// Circle

Circle::Circle(double radius):_radius_(radius) {}

double Circle::getHeight() const {
	return _radius_ * 2;
}

double Circle::getWidth() const{
	return getHeight();
}

void Circle::generatePostScript(std::ostream& os) const {

}

// Polygon

Polygon::Polygon(int numSides, double sideLength):_numSides_(numSides),_sideLength_(sideLength) {}

double Polygon::getHeight() const {
	double height = 0.0;

	if (_numSides_ % 2 == 0) {
		height = (_sideLength_ * cos(3.14 / _numSides_)) / sin(3.14 / _numSides_);
	}
	else {
		height = (_sideLength_ * (1 + cos(3.14 / _numSides_))) / (2 * sin(3.14 / _numSides_));
	}
	return height;
}

double Polygon::getWidth() const {
	double width = 0.0;

	if (_numSides_ % 4 == 0) {
		width = (_sideLength_ * cos(3.14 / _numSides_)) / sin(3.14 / _numSides_);
	}
	else if(_numSides_ % 2 ==0) {
		width = _sideLength_ / sin(3.14 / _numSides_);
	}
	else {
		width = (_sideLength_ * sin(3.14 * (_numSides_ - 1.0) / 2 * _numSides_)) / (sin(3.14 / _numSides_));
	}
	return width;
}

void Polygon::generatePostScript(std::ostream& os) const {

}

// Rectangle

Rectangle::Rectangle(double width, double height) : _width_(width), _height_(height) {}

double Rectangle::getHeight() const {
	return _height_;
}

double Rectangle::getWidth() const {
	return _width_;
}

void Rectangle::generatePostScript(std::ostream& os) const {

}

// Spacer

Spacer::Spacer(double width, double height): Rectangle(width, height) {}

// Square

Square::Square(double sideLength): Polygon(4, sideLength) {}

// Traingle

Triangle::Triangle(double sideLength): Polygon(3, sideLength) {}


// Utility functions

std::shared_ptr<Shape> makeCircle(double radius) {
	return make_shared<Circle>(radius);
}

std::shared_ptr<Shape> makePolygon(int numSides, double length) {
	return make_shared<Polygon>(numSides,length);
}

std::shared_ptr<Shape> makeRectangle(double width, double height) {
	return make_shared<Rectangle>(width,height);
}

std::shared_ptr<Shape> makeSpacer(double width, double height) {
	return make_shared<Spacer>(width,height);
}

std::shared_ptr<Shape> makeSquare(double length) {
	return make_shared<Square>(length);
}

std::shared_ptr<Shape> makeTriangle(double length) {
	return make_shared<Triangle>(length);
}