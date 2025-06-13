#ifndef UI_MESH_BASE_HPP_
#define UI_MESH_BASE_HPP_

#include <tuple>
#include "Point.hpp"
namespace core {

using PointsTriplet = std::tuple<Point, Point, Point>;
class MeshBase {
private:
	PointsTriplet anchors;
public:
	MeshBase(	PointsTriplet anchors) : anchors(anchors) {}
	
};
} // namespace core

#endif // !UI_MESH_BASE_HPP_
