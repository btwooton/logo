#include <cmath>
#include "turtle.hpp"

Turtle::Turtle() {
    this->x = 0.0;
    this->y = 0.0;
    this->heading = 0;
    this->pd = false;
    this->thickness = 1;
}

Turtle::Turtle(double x, double y, int heading, bool pd) {
    this->x = x;
    this->y = y;
    this->heading = heading;
    this->pd = pd;
    this->thickness = 1;
}

double Turtle::get_x() const {
    return x;
}

double Turtle::get_y() const {
    return y;
}

double Turtle::get_heading() const {
    return heading;
}

double Turtle::get_thickness() const {
    return thickness;
}

void Turtle::set_x(double x) {
    this->x = x;
}

void Turtle::set_y(double y) {
    this->y = y;
}

void Turtle::set_heading(int heading) {
    this->heading = heading;
}

void Turtle::set_thickness(double thickness) {
    this->thickness = thickness;
}

void Turtle::forward(double amt) {
    double new_x = x + cos((double)heading*PI/180.0) * amt;
    double new_y = y + sin((double)heading*PI/180.0) * amt;
    x = new_x;
    y = new_y;
}

void Turtle::backward(double amt) {
    double new_x = x - cos((double)heading*PI/180.0) * amt;
    double new_y = y - sin((double)heading*PI/180.0) * amt;
    x = new_x;
    y = new_y;
}

void Turtle::right(int amt) {
    heading = (heading - amt + 360) % 360;
}

void Turtle::left(int amt) {
    heading = (heading + amt) % 360;
}

void Turtle::penup() {
    pd = false;
}

void Turtle::pendown() {
    pd = true;
}

bool Turtle::isdown() const {
    return pd;
}
