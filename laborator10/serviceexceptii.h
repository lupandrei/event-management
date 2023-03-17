#pragma once
#include <exception>
#include <string>
using std::exception;
using std::string;
class ServiceException : public exception {
private:
	string message;
public:
	ServiceException(const string& _message) :message{ _message } {}

	const string& get_message()const noexcept {
		return this->message;
	}
	//const char* what() const noexcept override {
	//	return this->message.c_str();
	//}
};
