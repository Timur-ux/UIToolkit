#ifndef CORE_POINT_HPP_
#define CORE_POINT_HPP_

// -------------------
// |  OpenGL vertex  |
// -------------------

#include "core/OpenGLHeaders.hpp"
namespace core {
namespace render {

class IVertex {
public:
	virtual GLfloat x () const = 0;
	virtual GLfloat y () const = 0;
	virtual GLfloat z () const = 0;

	virtual ~IVertex() = default;
};

class Vertex : public IVertex {
private:
  double x_;
  double y_;
  double z_;
public:
  Vertex(double x, double y, double z);
  Vertex(double x, double y);

	GLfloat x() const override;	
	GLfloat y() const override;
	GLfloat z() const override;
};
} // namespace render
} // namespace core
#endif // !CORE_POINT_HPP_
