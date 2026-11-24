#include "base-types.hpp"

namespace kuryanov {
  class Shape
  {
  public:
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(point_t oth) = 0;
    virtual void scale(double k) = 0;
    virtual ~Shape() = default;
  };

  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, point_t center):
      rect {width, height, center}
    {}
    double getArea() const override
    {
      return rect.height * rect.width;
    }
    rectangle_t getFrameRect() const override
    {

    }
    void move(double dx, double dy) override
    {
      rect.pos.x += dx;
      rect.pos.y += dy;
    }
    void move(point_t oth) override
    {
      rect.pos.x = oth.x;
      rect.pos.y = oth.y;
    }
    void scale(double k) override
    {
      rect.height *= k;
      rect.width *= k;
    }
  private:
    rectangle_t rect;
  };
}