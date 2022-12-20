#pragma once
namespace item {
class item {
public:
  double x, y, angle;
  item() {}
  virtual void draw(int) = 0;
  virtual void setxy(double, double, double) = 0;
  virtual double dis(double, double) = 0;
  virtual item *clone() const = 0;
};
} // namespace item