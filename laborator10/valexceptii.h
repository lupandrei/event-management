#pragma once
#include<exception>
#include <string>
using std::exception;
using std::string;
class ValidationException : public  exception {
private:
	string message;
public:
	ValidationException(const string& message) :message{ message } {}
	const string& get_message()const noexcept {
		return this->message;
	}
};