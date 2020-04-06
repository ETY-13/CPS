#include"CPS.hpp"

#include<math.h>
using std::cos;
using std::sin;
using std::floor;
using std::make_shared;

#include<string>
using std::string;

// Circle

Circle::Circle(double radius) :_radius_(radius) {}

double Circle::getHeight() const {
	return _radius_ * 2;
}

double Circle::getWidth() const {
	return getHeight();
}

void Circle::generatePostScript(std::ostream& os) const {
	os << "gsave\nnewpath\n288 396 translate\n";
	os << "0 0 " << getHeight() / 2 << " 0 360 arc\n";
	os << "closepath\nstroke\n";
	os << "grestore\n\n";
	os << "showpage\n\n";
}

// Polygon

Polygon::Polygon(int numSides, double sideLength) :_numSides_(numSides), _sideLength_(sideLength) {}

double Polygon::getHeight() const {
	double height = 0.0;

	if (_numSides_ % 2 == 0) {
		height = (_sideLength_ * cos(3.14 / _numSides_)) / sin(3.14 / _numSides_);
	}
	else {
		height = (_sideLength_ * (1 + cos(3.14 / _numSides_))) / (2 * sin(3.14 / _numSides_));
	}
	return floor(height * 10.0 + 0.5) / 10.0;
}

double Polygon::getWidth() const {
	double width = 0.0;

	if (_numSides_ % 4 == 0) {
		width = (_sideLength_ * cos(3.14 / _numSides_)) / sin(3.14 / _numSides_);
	}
	else if (_numSides_ % 2 == 0) {
		width = _sideLength_ / sin(3.14 / _numSides_);
	}
	else {
		width = (_sideLength_ * sin(3.14 * (_numSides_ - 1.0) / (2.0 * _numSides_))) / sin(3.14 / _numSides_);
	}
	return floor(width * 10.0 + 0.5) / 10.0;
}

void Polygon::generatePostScript(std::ostream& os) const {
	os << "gsave\nnewpath\n";
	os << "288 396 translate\n 0 0 moveto\n ";
	for (auto i = 0; i < (_numSides_ - 1); i++) {
		os << 360/_numSides_ << " rotate\n";
		os << _sideLength_ << " 0 rlineto\n";
	}
	os << "closepath\nstroke\n";
	os << "grestore\n\n";
	os << "showpage\n\n";
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
	os << "gsave\nnewpath\n288 396 translate\n" << "0 0 moveto\n";
	os << getWidth() << " 0 rlineto\n0 " << getHeight() << " rlineto\n"<<-getWidth()<<" 0 rlineto\n";
	os << " closepath\nstroke\n";
	os << "grestore\n";
	os << "showpage\n\n";
}

// Spacer

Spacer::Spacer(double width, double height) : Rectangle(width, height) {}

// Square

Square::Square(double sideLength) : Polygon(4, sideLength) {}

// Triangle

Triangle::Triangle(double sideLength) : Polygon(3, sideLength) {
}

// Rotated Shape

RotatedShape::RotatedShape(std::shared_ptr<Shape> s, Angle a) : _s_(s) {
	switch (a)
	{
	case Angle::R90:
	    _degrees_ = 90;
		_height_ = s->getWidth();
		_width_ = s->getHeight();
		break;
	case Angle::R180:
	    _degrees_ = 180;
		_height_ = s->getHeight();
		_width_ = s->getWidth();
		break;
	case Angle::R270:
	    _degrees_ = 270;
		_height_ = s->getWidth();
		_width_ = s->getHeight();
		break;
	default:
		_height_ = 0.0;
		_width_ = 0.0;
	}
}
double RotatedShape::getHeight() const {
	return _height_;
}
double RotatedShape::getWidth() const {
	return _width_;
}
void RotatedShape::generatePostScript(std::ostream& os) const {
	os << "gsave\n" << _degrees_ << " rotate\n";
	_s_->generatePostScript(os);
	os << "grestore\n\n";
}

// ScaledShape

ScaledShape::ScaledShape(std::shared_ptr<Shape> s, double sx, double sy) :_width_(s->getWidth()* sx), _height_(s->getHeight()* sy), _s_(s),_sx_(sx),_sy_(sy) {}
double ScaledShape::getHeight() const {
	return _height_;
}
double ScaledShape::getWidth() const {
	return _width_;
}
void ScaledShape::generatePostScript(std::ostream& os) const {
	os << "gsave\n" <<  _sx_ << " " << _sy_ << " scale\n";
	_s_->generatePostScript(os);
	os << "grestore\n\n";
}

// LayeredShape

LayeredShape::LayeredShape(std::initializer_list<std::shared_ptr<Shape>> i) : _shape_(i){
	double height = 0.0;
	double width = 0.0;
	for (auto shape : i) {
		if (shape->getHeight() > height) {
			height = shape->getHeight();
		}

		if (shape->getWidth() > width) {
			width = shape->getWidth();
		}
	}

	_height_ = height;
	_width_ = width;
}
double LayeredShape::getHeight() const {
	return _height_;
}
double LayeredShape::getWidth() const {
	return _width_;
}
void LayeredShape::generatePostScript(std::ostream& os) const {
	os << "gsave\n";
	for (const auto& shape : _shape_) {
		shape->generatePostScript(os);
	}
	os << "grestore\n\n";
}

// VerticalShape

VerticalShape::VerticalShape(std::initializer_list<std::shared_ptr<Shape>> i) : _shape_(i) {
	double height = 0.0;
	double width = 0.0;
	for (auto shape : i) {

		if (shape->getWidth() > width) {
			width = shape->getWidth();
		}

		height += shape->getHeight();
	}

	_height_ = height;
	_width_ = width;
}
double VerticalShape::getHeight() const {
	return _height_;
}
double VerticalShape::getWidth() const {
	return _width_;
}
void VerticalShape::generatePostScript(std::ostream& os) const {
	os << "gsave\n";
	os << getWidth() / 2.0 << " 0 translate\n";
	for (const auto& shape : _shape_) {
		os << "0 " << (shape->getHeight()) / 2.0 << " translate\n";  //Check this
		shape->generatePostScript(os);
		os << "0 " << (shape->getHeight()) / 2.0 << " translate\n"; //Check this
	}
	os << "grestore\n\n";

}

// HorizontalShape

HorizontalShape::HorizontalShape(std::initializer_list<std::shared_ptr<Shape>> i) : _shape_(i) {
	double height = 0.0;
	double width = 0.0;
	for (auto shape : i) {

		if (shape->getHeight() > height) {
			height = shape->getHeight();
		}

		width += shape->getWidth();
	}

	_heigth_ = height;
	_width_ = width;
}
double HorizontalShape::getHeight() const {
	return _heigth_;
}
double HorizontalShape::getWidth() const {
	return _width_;
}
void HorizontalShape::generatePostScript(std::ostream& os) const {
	os << "gsave\n";
	os << "0 " << getHeight() / 2.0 << " translate\n";
	for (const auto& shape : _shape_) {
		os << (shape->getWidth()) / 2.0 << " 0 translate\n";  //Check this
		shape->generatePostScript(os);
		os << (shape->getWidth()) / 2.0 << " 0 translate\n"; //Check this
	}
	os << "grestore\n\n";
}


// Custom arcOfShapes

arcOfShapes::arcOfShapes(std::initializer_list<std::shared_ptr<Shape>> i, Angle a, double radius) :_shape_(i), _radius_(radius){
	auto dummy = 0.0;
	numOfShapes = 0;
	for (auto shape : i) {
    numOfShapes++;
	}
	switch (a)
	{
	case Angle::R90:
		_degrees_ = 90;
		_width_ = radius;
		_height_ = radius;
		break;
	case Angle::R180:
		_degrees_ = 180;
		_width_ = radius*2;
		_height_ = radius;
		break;
	case Angle::R270:
		_degrees_ = 270;
		_width_ = radius*2;
		_height_ = radius*2;
		break;
	default:
		_degrees_ = 0;
		_height_ = dummy;
		_width_ = dummy;
	}
}
double arcOfShapes::getHeight()const {
	return _height_;
}

double arcOfShapes::getWidth() const {
	return _width_;
}

void arcOfShapes::generatePostScript(std::ostream& os) const {

	/*
	0 5 360 {              % Go from 0 to 360 degrees in 10 degree steps
	  gsave                 % Keep rotations temporary
		300 300 moveto
		rotate              % Rotate by degrees on stack from 'for'
		72 0 box stroke
	  grestore              % Get back the unrotated state
	} for
	*/
}

// Utility functions

std::shared_ptr<Shape> makeCircle(double radius) {
	return make_shared<Circle>(radius);
}

std::shared_ptr<Shape> makePolygon(int numSides, double length) {
	return make_shared<Polygon>(numSides, length);
}

std::shared_ptr<Shape> makeRectangle(double width, double height) {
	return make_shared<Rectangle>(width, height);
}

std::shared_ptr<Shape> makeSpacer(double width, double height) {
	return make_shared<Spacer>(width, height);
}

std::shared_ptr<Shape> makeSquare(double length) {
	return make_shared<Square>(length);
}

std::shared_ptr<Shape> makeTriangle(double length) {
	return make_shared<Triangle>(length);
}

std::shared_ptr<Shape> makeRotatedShape(std::shared_ptr<Shape> s, Angle a) {
	return make_shared<RotatedShape>(s, a);
}

std::shared_ptr<Shape> makeScaledShape(std::shared_ptr<Shape> s, double sx, double sy) {
	return make_shared<ScaledShape>(s, sx, sy);
}

std::shared_ptr<Shape> makeLayeredShape(std::initializer_list<std::shared_ptr<Shape>> i) {
	return make_shared<LayeredShape>(i);
}

std::shared_ptr<Shape> makeVerticalShape(std::initializer_list<std::shared_ptr<Shape>> i) {
	return make_shared<VerticalShape>(i);
}

std::shared_ptr<Shape> makeHorizontalShape(std::initializer_list<std::shared_ptr<Shape>> i) {
	return make_shared<HorizontalShape>(i);
}
