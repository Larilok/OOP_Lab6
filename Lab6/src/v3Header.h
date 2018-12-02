#pragma once

#include <cmath>
#include <string>
#include <cstring>
#include <ostream>
#include <vector>
#include <functional>

#include "vector.h"
#include "exceptions.h"

namespace Vector {
	template<class T>
	class Vec3 : public vecInterface<T> {
	public:

		// Constructors
		Vec3<T>() : x(0), y(0), z(0), _unit(false) {}

		Vec3<T>(T ax, T ay, T az, bool unit = false) : x(ax), y(ay), z(az), _unit(unit) {}

		Vec3<T>(const T &other) { *this = other; }

		bool unit(int i) {
			if (_unit)
				return true;
			if (squaredNorm() == 1) {
				_unit = true;
				return true;
			}
			return false;
		}

		// Operators
		Vec3<T> &operator=(const Vec3<T> other) {
			x = other.x;
			y = other.y;
			z = other.z;
			_unit = other._unit;
			return *this;
		}

		Vec3<T> operator-() const {
			return Vec3<T>(-x, -y, -z);
		}

		// Vector/Vector operations
		Vec3<T> operator+(const Vec3<T> &other) const {
			return Vec3<T>(x + other.x, y + other.y, z + other.z);
		}

		Vec3<T> operator-(const Vec3<T> &other) const {
			return Vec3<T>(x - other.x, y - other.y, z - other.z);
		}
		Vec3<T> operator*(const Vec3<T>& other) const
		{
			return Vec3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
		}

		int operator==(const Vec3<T> &other)  const {
			if (other.x == 0)
				throw DivideByZero("int operator==(const Vec3<T> &other)", "other.x = 0");
			else if(other.y == 0) 
				throw DivideByZero("int operator==(const Vec3<T> &other)", "other.y = 0"); 
			else if(other.z == 0)
				throw DivideByZero("int operator==(const Vec3<T> &other)", "other.z = 0");
				
			return x / other.x == y / other.y == z / other.z ? 1 : 0;
		}

		int operator!=(const Vec3<T> &other)  const {
			return !(*this == other);
		}

		// Vector scalar operations
		Vec3<T> operator+(float s) const {
			return Vec3<T>(x + s, y + s, z + s);
		}

		Vec3<T> operator-(float s) const {
			return Vec3<T>(x - s, y - s, z - s);
		}

		Vec3<T> operator*(float s) const {
			return Vec3<T>(x * s, y * s, z * s);
		}

		Vec3<T> operator/(float s) const {
			if(s == 0) throw DivideByZero("in Vec3<T> operator/(float s) const ", "s = 0")
			return Vec3<T>(x / s, y / s, z / s);
		}

		// Vector/Vector operations
		Vec3<T> &operator+=(const Vec3<T> &other) {
			x += other.x;
			y += other.y;
			z += other.z;
			_unit = false;
			return *this;
		}

		Vec3<T> &operator-=(const Vec3<T> &other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			_unit = false;
			return *this;
		}

		Vec3<T>& operator*=(const Vec3<T> &other) {
			x = y * other.z - z * other.y;
			y = z * other.x - x * other.z;
			z = x * other.y - y * other.x;
			_unit = false;
			return *this;
		}

		// Vector/Scalar operations
		Vec3<T> &operator+=(const T s) {
			x += s;
			y += s;
			z += s;
			_unit = false;
			return *this;
		}

		Vec3<T> &operator-=(const T s) {
			x -= s;
			y -= s;
			z -= s;
			_unit = false;
			return *this;
		}

		Vec3<T> &operator*=(const T s) {
			x *= s;
			y *= s;
			z *= s;
			_unit = false;
			return *this;
		}

		Vec3<T> &operator/=(const T s) {
			if (s == 0) throw DivideByZero("Vec3<T> &operator/=(const T s)", "s = 0");
			x /= s;
			y /= s;
			z /= s;
			_unit = false;
			return *this;
		}

		void clear() {
			this->setX(0).setY(0).setZ(0);
		}
		void Print() override {
			std::cout << "x: " << x << "  y: " << y << "  z: " << z << std::endl;
		};

		Vec3<T> &setX(std::string& nValue) {
			x = stoi(nValue);
			_unit = false;
			return *this;
		};
		
		Vec3<T> &setX(int nValue) {
			x = nValue;
			_unit = false;
			return *this;
		};

		Vec3<T> &setY(std::string& nValue) {
			y = stoi(nValue);
			_unit = false;
			return *this;
		};
		Vec3<T> &setY(int nValue) {
			y = nValue;
			_unit = false;
			return *this;
		};

		Vec3<T> &setZ(std::string& nValue) {
			z = stoi(nValue);
			_unit = false;
			return *this;
		};

		Vec3<T> &setZ(int nValue) {
			z = nValue;
			_unit = false;
			return *this;
		};

		T getX() {
			return x;
		};

		T getY() {
			return y;
		};

		T getZ() {
			return z;
		};


		// Functions
		T norm() const { return ((_unit) ? 1 : sqrt(x * x + y * y + z * z)); }

		T squaredNorm() const { return ((_unit) ? 1 : (x * x + y * y + z * z)); }

		Vec3<T>& normalize() {
			if (_unit)
				return;
			T norm = this->norm();
			if (norm == 0) throw DivideByZero("normalize()", "norm = 0");
			x /= norm;
			y /= norm;
			z /= norm;
			_unit = true;
			return *this;
		}

		// Destructor

		~Vec3() = default;
	private:
		bool _unit;
		T x;
		T y;
		T z;
		friend std::istream& operator>> (std::istream &in, Vec3<T> &vec);
	
	};
	
	std::istream & operator>>(std::istream & in, Vec3<int>& vec)
	{
		std::string buffer;

		auto eraseLeadingZeroes = [&buffer](const char* where) ->void		//correctly deal with all 0 case
		{
			buffer.erase(0, (buffer.find_first_not_of('0') < buffer.size() - 1 ? buffer.find_first_not_of('0') : buffer.size() - 1));
		};

		auto isNumber = [&buffer](const char* where) ->void		
		{ 
			if ((buffer[0] - 48) > 9 && !(buffer[0] == '-') && !(buffer[0] == '+') || (buffer[0] - 48) < 0 && !(buffer[0] == '-') && !(buffer[0] == '+')) 
				throw NotaNumber(where, buffer.c_str());
			for (int i = 1; i < buffer.length()-1; i++)
				if ((buffer[i] - 48) > 9 || (buffer[i] - 48) < 0) throw NotaNumber(where, buffer.c_str());
		};

		auto inIntBoundaries = [&buffer](const char* where) ->void
		{
			if (stoll(buffer) > std::numeric_limits<int>::max() || stoll(buffer) < std::numeric_limits<int>::min()) {
				throw Out_of_Range(where, buffer.c_str());
			}
		};

		std::vector<std::function<void(const char*)>> functions{ eraseLeadingZeroes, isNumber, inIntBoundaries };

		auto testInput = [&functions](const char* msg) ->void
		{
			for (auto& func : functions)
			{
				func(msg);
			}
		};
		
		for (;;) {			
			try {
				std::cout << "Enter x: ";
				in >> buffer;
				testInput("X");
				vec.setX(buffer);

				std::cout << "Enter y: ";
				in >> buffer;
				testInput("Y");
				vec.setY(buffer);

				std::cout << "Enter z: ";
				in >> buffer;
				testInput("Z");
				vec.setZ(buffer);
			}
			catch (InputExeption& e) {
				std::cout <<" \n You failed in " << e.what() << "\n the culprit: " << e.getCulprit() << "\n\n";
				vec.clear();
				continue;
			}
			catch (MathEx& e) {
				std::cout << '\n' << e.what() << "\n the culprit: " << e.getCulprit() << "\n\n";
				vec.clear();
				continue;
			}
			catch (std::out_of_range& e) {
				std::cout << "out_of_range ~~~~~~ message: " << e.what() << '\n';
				vec.clear();
				continue;
			}
			break;
		}
		return in;
	}

};

