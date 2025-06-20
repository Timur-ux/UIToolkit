#ifndef UI_ENTITY_HPP_
#define UI_ENTITY_HPP_
/*
 * Interface for all renderable entities
 */

namespace ui {
class IEntity {
public:
	virtual IEntity& render() = 0;

	virtual ~IEntity() = default;
};
} // namespace ui
#endif // !UI_ENTITY_HPP_
