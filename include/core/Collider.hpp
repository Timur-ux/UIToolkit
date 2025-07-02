#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_
#include "core/IModel.hpp"
#include "core/render/IMesh.hpp"
#include "event.hpp"
#include <list>
#include <memory>
namespace core {
class ICollider : public IModel {
public:
  ICollider(event::IEvent<float> &theOnWidthChanged,
            event::IEvent<float> &theOnHeightChanged)
      : onHeightChanged(theOnHeightChanged), onWidthChanged(theOnWidthChanged) {
  }

  virtual ~ICollider() = default;

  virtual float width() const = 0;
  virtual float height() const = 0;

  virtual ICollider &unionX(std::shared_ptr<ICollider> &other) = 0;
  virtual ICollider &unionY(std::shared_ptr<ICollider> &other) = 0;

  // -------------------------------------------------------------------------------
  // |  maybe it can be used for auto update parent colliders when childs
  // changed  |
  // -------------------------------------------------------------------------------

  event::IEvent<float> &onHeightChanged, &onWidthChanged;
};

class Collider : public ICollider {
  float width_ = 1, height_ = 1, x_ = 0, y_ = 0;
  std::shared_ptr<render::IMesh> mesh_;
  std::list<std::shared_ptr<ICollider>> xChilds_, yChilds_;
  void forallModel_(std::function<void(IModel &)> handler) {
    handler(*mesh_);
    for (auto &child : xChilds_)
      handler(*child);
    for (auto &child : yChilds_)
      handler(*child);
  }

  event::Event<float> onWidthChanged_, onHeightChanged_;

public:
  Collider(std::shared_ptr<render::IMesh> mesh, float width = 1,
           float height = 1)
      : ICollider(onWidthChanged_, onHeightChanged_), mesh_(mesh),
        height_(height), width_(width) {}

  float width() const override { return width_; }
  float height() const override { return height_; }

  IModel &moveTo(const glm::vec3 &pos) override {
    auto handler = [&pos](IModel &model) { model.moveTo(pos); };
    forallModel_(handler);
    return *this;
  }

  IModel &shiftBy(const glm::vec3 &vec) override {
    auto handler = [&vec](IModel &model) { model.shiftBy(vec); };
    forallModel_(handler);
    return *this;
  }

  IModel &scale(const glm::vec3 &scaleFactors) override {
    auto handler = [&scaleFactors](IModel &model) {
      model.scale(scaleFactors);
    };
    forallModel_(handler);
    return *this;
  }

  ICollider &unionX(std::shared_ptr<ICollider> &other) override {
    if (other->height() > height_) {
      glm::vec3 diff{0, other->height() - height(), 0};
      for (auto &child : yChilds_)
        child->shiftBy(diff);
      height_ = other->height();
			onHeightChanged_.invoke(height_);
    }

    width_ += other->width();
    xChilds_.push_back(other);

    return *this;
  }

  ICollider &unionY(std::shared_ptr<ICollider> &other) override {
    if (other->width() > width()) {
      glm::vec3 diff{other->width() - width(), 0, 0};
      for (auto &child : xChilds_)
        child->shiftBy(diff);
      width_ = other->width();
			onWidthChanged_.invoke(width_);
    }

    height_ += other->height();
    yChilds_.push_back(other);

    return *this;
  }
};
} // namespace core
#endif // !COLLIDER_HPP_
