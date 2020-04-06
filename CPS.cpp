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
	os << "gsave\n";
	os << "0 0 " << getHeight() / 2 << " 0 360 arc\n";
	os << "closepath\nstroke\n";
	os << "grestore\n\n";

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
	int interiorAngle = 180 - (((_numSides_ - 2) * 180) / _numSides_);
	os << "gsave\n";
	os << "0 0 moveto\n ";
	for (auto i = 0; i < (_numSides_ - 1); i++) {
		os << 360/_numSides_ << " rotate\n";
		os << _sideLength_ << " 0 rlineto\n";
	}
	os << "closepath\nstroke\n";
	os << "grestore\n\n";
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
	os << "gsave\n" << -(_width_ + 5)<<" 0 "<<"translate\n"<<"0 0 moveto\n";
	os << getWidth() << " 0 rlineto\n0 " << getHeight() << " rlineto\n"<<-getWidth()<<" 0 rlineto\n";
	os << " closepath\nstroke\n";
	os << "grestore\n";
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
		_degrees_ = 0;
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
	os << "grestore\n";
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
	os << "grestore\n";

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
		_shape_.push_back(shape);
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

	auto maxHeight = 0.0;
	for (auto i = 0; i < _shape_.size(); ++i) {
		os << " gsave ";

		if (i > 0) {
			maxHeight += _shape_[i - 1] -> getHeight();
			os << "0 " << maxHeight<< " " << "translate\n";
		}
		_shape_[i]->generatePostScript(os);
		os << " grestore \n";
	}

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
	auto maxHeight = 0.0;
	for (auto i = 0; i < _shape_.size(); ++i) {
		os << " gsave\n";
		maxHeight += _shape_[i]->getWidth()/2 + 5 *i;
		if (i > 0) {		
			os << maxHeight << " 0 " << "translate\n";
		}
		_shape_[i]->generatePostScript(os);
		os << " grestore \n";
	}

}

// Custom arcOfShapes

arcOfShapes::arcOfShapes(std::initializer_list<std::shared_ptr<Shape>> i, Angle a, double radius) :_shape_(i), _radius_(radius){
	_numOfShapes_ = 0;
	for (auto shape : i) {
    _numOfShapes_++;
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
		_height_ = 0.0;
		_width_ = 0.0;
	}
}
double arcOfShapes::getHeight()const {
	return _height_;
}

double arcOfShapes::getWidth() const {
	return _width_;
}

void arcOfShapes::generatePostScript(std::ostream& os) const {
    auto sections = _degrees_/_numOfShapes_;
    auto degFirst = 0;
    auto degSecond = sections;
    auto xCord = cos(degSecond*(3.14/180))*_radius_;
    auto yCord = sin(degSecond*(3.14/180))*_radius_;

    os << "gsave\nnewpath\n288 396 translate\n" << "0 0 moveto\n";
    for (auto i = 0; i < _shape_.size(); ++i) {
        os << "gsave\n";
        os << "0 0 " << _radius_ << " " << degFirst << " " << degSecond << " arc\n";
        os << xCord << " " << yCord-((_shape_[i]->getHeight())/2) << " translate\n";

        _shape_[i]->generatePostScript(os);
        degFirst += sections;
        degSecond += sections;
        xCord = cos(degSecond*(3.14/180))*_radius_;
        yCord = sin(degSecond*(3.14/180))*_radius_;
        os << "grestore\n";
    }
	os << "grestore\n\n";
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
std::shared_ptr<Shape>makeArcShape(std::initializer_list<std::shared_ptr<Shape>> i,Angle a,double rad) {
	return make_shared<arcOfShapes>(i,a,rad);
}

string inCenter() {
	return ("288 396 translate\n");
}
string show() {
	return ("showpage\n");
}

