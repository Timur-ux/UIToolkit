#ifndef CORE_POINT_HPP_
#define CORE_POINT_HPP_

namespace core {
class Point {
private:
  double x_;
  double y_;
  double z_;
public:
  Point(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  Point(double x, double y) : x_(x), y_(y), z_(0) {}

	double x() const {
		return x_;
	}
	
	double y() const {
		return y_;
	}

	double z() const {
		return z_;
	}
};

} // namespace core
#endif // !CORE_POINT_HPP_
