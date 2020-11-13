/*************************************************
* Name : CustomException.cpp
* Purpose : Source for custom exception class.
* Date : 2020-11-13
* ************************************************/

#include "CustomException.h"

const char* CustomException::what() const noexcept
{}

CustomException::CustomException(int line, const char* file) noexcept
{}