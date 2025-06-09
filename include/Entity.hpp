#ifndef UI_ENTITY_HPP_
#define UI_ENTITY_HPP_
/*
 * Interface for all renderable entities
 */

class IEntity {
public:
	virtual IEntity& render() = 0;
};
#endif // !UI_ENTITY_HPP_
