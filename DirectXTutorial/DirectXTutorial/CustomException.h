/*************************************************
* Name : CustomException.h
* Purpose : Header for custom exception class.
* Date : 2020-11-13
* ************************************************/
#pragma once

#include <exception>
#include <string>

class CustomException : public std::exception
{
public:
	// inherits from std::exception
	const char* what() const noexcept override;
	
	CustomException(int line, const char* file) noexcept;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};