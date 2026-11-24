#include "base-types.hpp"

class Shape
{
public:
  virtual double getArea() const;
  virtual double getFrameRect() const;
  virtual void move(double dx, double dy);
  virtual void move(point_t oth);
  virtual void scale(size_t k);  
};

class Rectangle: public Shape
{
public:
  double getArea() const override
  {
    return rect.height * rect.width;
  }
  double getFrameRect() const override
  {

  }
  void move(double dx, double dy) override
  {
    rect.pos.x += dx;
    rect.pos.y += dy;
  }
  void move(point_t oth)
  {
    rect.pos.x = oth.x;
    rect.pos.y = oth.y;
  }
  void scale(size_t k) override
  {
    rect.height *= k;
    rect.width *= k;
  }
private:
  rectangle_t rect;
};