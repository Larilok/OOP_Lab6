#pragma once

#include <string>
#include <iostream>

class Exception {

private :
	const char* message;
public:

	virtual std::string what()  const noexcept{
		return message;
	};

	Exception(const char* msg) noexcept : message(msg)
	{}

	Exception() = delete;
	Exception(const Exception&) = delete;
	Exception& operator=(Exception&) = delete;

	virtual ~Exception() {};
};



class MathEx : public Exception {
private: 
	const char* culprit;
public:
	MathEx() = delete;
	MathEx(const char* msg, const char* culprit) noexcept : Exception(msg), culprit(culprit) {};

	std::string getCulprit() const noexcept {
		return culprit;
	};
	

};

class DivideByZero : public MathEx{
public:

	explicit DivideByZero(const char* msg, const char* culprit) noexcept : MathEx(msg,culprit) {};
};


class Out_of_Range : public MathEx{
public:

	explicit Out_of_Range(const char* msg, const char* culprit) noexcept : MathEx(msg,culprit) {};

	std::string what() const noexcept {
		
		
		return Exception::what() + " does not fits int limits";
	}
};



class InputExeption : public Exception{
private:
	const char* culprit;
public:
	InputExeption(const char* msg, const char* culprit) noexcept : Exception(msg), culprit(culprit) {};

	std::string getCulprit() const noexcept {
		return culprit;
	};
};

class NotaNumber : public InputExeption {
public:
	explicit NotaNumber(const char* msg, const char* culprit) noexcept: InputExeption(msg, culprit) {}

	std::string what() const noexcept {


		return Exception::what() + " input";
	}
};