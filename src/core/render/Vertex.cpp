#include "core/render/Vertex.hpp"

using namespace core::render;

Vertex::Vertex(double x, double y, double z) : x_(x), y_(y), z_(z) {}

Vertex::Vertex(double x, double y) : x_(x), y_(y), z_(0) {}

GLfloat Vertex::x() const { return x_; }

GLfloat Vertex::y() const { return y_; }

GLfloat Vertex::z() const { return z_; }
