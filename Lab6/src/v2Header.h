#pragma once


#include <cmath>
#include <cstring>
#include <ostream>
#include "vector.h"
#include "exceptions.h"

namespace Vector {

	template<class T>
	class Vec2 : public vecInterface<T> {
	public:

		// Constructors
		Vec2<T>() : x(0), y(0), _unit(false) {}

		Vec2<T>(T ax, T ay, bool unit = false) : x(ax), y(ay), _unit(unit) {}

		//copy constructor
		Vec2<T>(const T &other) { *this = other; }

		bool unit() {
			if (_unit)
				return true;
			if (squaredNorm() == 1) {
				_unit = true;
				return true;
			}
			return false;
		}

		// Operators
		//copy assignment
		Vec2<T> &operator=(const Vec2<T> other) {
			x = other.x;
			y = other.y;
			_unit = other._unit;
			return *this;
		}
		Vec2<T>& operator-() {
			return Vec2(-x, -y);
		}
		// Vector/Vector operations
		Vec2<T> operator+(const Vec2<T> &other) {
			return Vec2<T>(x + other.x, y + other.y);
		}

		Vec2<T> operator-(const Vec2<T> &other) {
			return Vec2<T>(x - other.x, y - other.y);
		}

		/*Vec2<T> operator*(const Vec2<T> &other) {
			return Vec2<T>(x * other.x, y * other.y);
		}*/

		int operator==(const Vec2<T> &other) {
			return x / other.x == y / other.y ? 1 : 0;
		}

		int operator!=(const Vec2<T> &other) {
			return !(*this == other);
		}
		// Vector scalar operations
		Vec2<T> operator+(float s) {
			return Vec2<T>(x + s, y + s);
		}

		Vec2<T> operator-(float s) {
			return Vec2<T>(x - s, y - s);
		}

		Vec2<T> operator*(float s) {
			return Vec2<T>(x * s, y * s);
		}

		Vec2<T> operator/(float s) {

			return Vec2<T>(x / s, y / s);
		}

		// Vector/Vector operations
		Vec2<T> &operator+=(const Vec2<T> &other) {
			x += other.x;
			y += other.y;
			_unit = false;
			return *this;
		}

		Vec2<T> &operator-=(const Vec2<T> &other) {
			x -= other.x;
			y -= other.y;
			_unit = false;
			return *this;
		}

		//        Vec2<T> &operator*=(const Vec2<T> &other) {
		//            x *= other.x;
		//            y *= other.y;
		//            _unit = false;
		//            return *this;
		//        }

				// Vector/Scalar operations
		Vec2<T> &operator+=(const T other) {
			x += other;
			y += other;
			_unit = false;
			return *this;
		}

		Vec2<T> &operator-=(const T other) {
			x -= other;
			y -= other;
			_unit = false;
			return *this;
		}

		Vec2<T> &operator*=(const T other) {
			x *= other;
			y *= other;
			_unit = false;
			return *this;
		}

		Vec2<T> &operator/=(const T other) {
			x /= other;
			y /= other;
			_unit = false;
			return *this;
		}

		// Functions


		void Print() override {
			std::cout << "x: " << x << "  y:" << y << std::endl;
		};

		void setX(T nValue) {
			x = nValue;
		}
		void setY(T nValue) {
			y = nValue;
		}

		T getX() {
			return x;
		};

		T getY() {
			return y;
		};

		T norm() { return ((_unit) ? 1 : sqrt(x * x + y * y)); }

		T squaredNorm() { return ((_unit) ? 1 : (x * x + y * y)); }

		void normalize() {
			if (_unit)
				return;
			T norm = this->norm();
			x /= norm;
			y /= norm;
			_unit = true;
		}

		// Destructor
		~Vec2() = default;

	private:
		T x;
		T y;
		bool _unit;
	};

};

