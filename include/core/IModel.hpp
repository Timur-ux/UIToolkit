#ifndef IMODEL_HPP_
#define IMODEL_HPP_
// -------------------------------------------------------------------------------------------------
// |  There a interface definition for all entities binded with model(shift, move and scale opts)  |
// -------------------------------------------------------------------------------------------------

#include <glm/glm.hpp>

class IModel {
public:
	virtual IModel & shiftBy(const glm::vec3 & vec) = 0;
	virtual IModel & moveTo(const glm::vec3 & position) = 0;
	virtual IModel & scale(const glm::vec3 & scaleFactors) = 0;
};
#endif // !IMODEL_HPP_
