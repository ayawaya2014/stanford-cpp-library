/*
 * File: qgtypes.cpp
 * ----------------
 * This file implements the classes in the qgtypes.h interface.
 *
 * @version 2018/07/14
 * - initial version, based on qgtypes.h
 */

#include "qgtypes.h"
#include <cmath>
#include <sstream>
#include <string>
#include "collections.h"
#include "error.h"
#include "gmath.h"
#include "hashcode.h"
#include "strlib.h"

/*
 * Implementation notes: QGDimension class
 * ---------------------------------------
 * The QGDimension class itself is entirely straightforward.  The
 * relational operators compare the width first, followed by the height.
 * The hashCode function computes the exclusive-or of the individual words.
 */

QGDimension::QGDimension(double width, double height)
        : _width(width),
          _height(height) {
    // empty
}

double QGDimension::getWidth() const {
    return _width;
}

double QGDimension::getHeight() const {
    return _height;
}

std::string QGDimension::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

std::ostream& operator <<(std::ostream& os, const QGDimension& dim) {
    return os << "(" << dim._width << ", " << dim._height << ")";
}

bool operator ==(const QGDimension& d1, const QGDimension& d2) {
    return floatingPointEqual(d1._width, d2._width)
            && floatingPointEqual(d1._height, d2._height);
}

bool operator !=(const QGDimension& d1, const QGDimension& d2) {
    return !(d1 == d2);
}

bool operator <(const QGDimension& d1, const QGDimension& d2) {
    return d1._width < d2._width
            || (floatingPointEqual(d1._width, d2._width) && d1._height < d2._height);
}

bool operator <=(const QGDimension& d1, const QGDimension& d2) {
    return d1 < d2 || d1 == d2;
}

bool operator >(const QGDimension& d1, const QGDimension& d2) {
    return d2 < d1;
}

bool operator >=(const QGDimension& d1, const QGDimension& d2) {
    return d1 > d2 || d1 == d2;
}

QGDimension operator *(const QGDimension& d, double scale) {
    return QGDimension(d._width * scale, d._height * scale);
}

int hashCode(const QGDimension& dim) {
    return hashCode2(dim._width, dim._height);
}

/*
 * Implementation notes: QGPoint class
 * -----------------------------------
 * The QGPoint class itself is entirely straightforward.  The relational
 * operators compare the x components first, followed by the y component.
 * The hashCode function computes the exclusive-or of the individual words.
 */

QGPoint::QGPoint(double x, double y)
        : _x(x),
          _y(y) {
    // empty
}

double QGPoint::getX() const {
    return _x;
}

double QGPoint::getY() const {
    return _y;
}

std::string QGPoint::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

std::ostream& operator <<(std::ostream& os, const QGPoint& pt) {
    return os << "(" << pt._x << ", " << pt._y << ")";
}

bool operator ==(const QGPoint& p1, const QGPoint& p2) {
    return floatingPointEqual(p1._x, p2._x)
            && floatingPointEqual(p1._y, p2._y);
}

bool operator !=(const QGPoint& p1, const QGPoint& p2) {
    return !(p1 == p2);
}

bool operator <(const QGPoint& p1, const QGPoint& p2) {
    return p1._x < p2._x || (floatingPointEqual(p1._x, p2._x) && p1._y < p2._y);
}

bool operator <=(const QGPoint& p1, const QGPoint& p2) {
    return p1 < p2 || p1 == p2;
}

bool operator >(const QGPoint& p1, const QGPoint& p2) {
    return p2 < p1;
}

bool operator >=(const QGPoint& p1, const QGPoint& p2) {
    return p1 > p2 || p1 == p2;
}

QGPoint operator *(const QGPoint& p, double scale) {
    return QGPoint(p._x * scale, p._y * scale);
}

int hashCode(const QGPoint& pt) {
    return hashCode2(pt._x, pt._y);
}

/*
 * Implementation notes: QGRectangle class
 * ---------------------------------------
 * The QGRectangle class itself is entirely straightforward.  The
 * relational operators compare the components in the following order:
 * x, y, width, height.  The hashCode function computes the exclusive-or
 * of the individual words.
 */

QGRectangle::QGRectangle(double x, double y, double width, double height)
        : _x(x),
          _y(y),
          _width(width),
          _height(height) {
    // empty
}

QGRectangle::QGRectangle(double x, double y, const QGDimension& size)
        : _x(x),
          _y(y),
          _width(size.getWidth()),
          _height(size.getHeight()) {
    // empty
}

QGRectangle::QGRectangle(const QGPoint& p, double width, double height)
        : _x(p.getX()),
          _y(p.getY()),
          _width(width),
          _height(height) {
    // empty
}

QGRectangle::QGRectangle(const QGPoint& p, const QGDimension& size)
        : _x(p.getX()),
          _y(p.getY()),
          _width(size.getWidth()),
          _height(size.getHeight()) {
    // empty
}

QGRectangle QGRectangle::enlargedBy(double amount) {
    return QGRectangle(_x - amount, _y - amount, _width + 2 * amount, _height + 2 * amount);
}

double QGRectangle::getX() const {
    return _x;
}

double QGRectangle::getY() const {
    return _y;
}

double QGRectangle::getWidth() const {
    return _width;
}

double QGRectangle::getHeight() const {
    return _height;
}

bool QGRectangle::isEmpty() const {
    return _width <= 0 || _height <= 0;
}

bool QGRectangle::contains(double x, double y) const {
    return x >= this->_x && y >= this->_y
            && x < this->_x + _width
            && y < this->_y + _height;
}

bool QGRectangle::contains(const QGPoint& pt) const {
    return contains(pt.getX(), pt.getY());
}

std::string QGRectangle::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

std::ostream& operator <<(std::ostream& os, const QGRectangle& rect) {
    return os << "(" << rect.getX() << ", " << rect.getY() << ", "
              << rect.getWidth() << ", " << rect.getHeight() << ")";
}

bool operator ==(const QGRectangle& r1, const QGRectangle& r2) {
    return floatingPointEqual(r1._x, r2._x)
            && floatingPointEqual(r1._y, r2._y)
            && floatingPointEqual(r1._width, r2._width)
            && floatingPointEqual(r1._height, r2._height);
}

bool operator !=(const QGRectangle& r1, const QGRectangle& r2) {
    return !(r1 == r2);
}

bool operator <(const QGRectangle& r1, const QGRectangle& r2) {
    return stanfordcpplib::collections::compareTo4(
            r1._x, r2._x, r1._y, r2._y, r1._width, r2._width, r1._height, r2._height) < 0;
}

bool operator <=(const QGRectangle& r1, const QGRectangle& r2) {
    return r1 < r2 || r1 == r2;
}

bool operator >(const QGRectangle& r1, const QGRectangle& r2) {
    return r2 < r1;
}

bool operator >=(const QGRectangle& r1, const QGRectangle& r2) {
    return r1 > r2 || r1 == r2;
}

int hashCode(const QGRectangle& r) {
    return hashCode4(r._x, r._y, r._width, r._height);
}