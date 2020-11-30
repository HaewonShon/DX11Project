/*************************************************
* Name : Helepr.h
* Purpose : Header for helper functions
* Date : 2020-11-14
* ************************************************/
#pragma once

#include <string>

/*
* Converter for string-wstring, char-wchar_t 
*/

// wstring->string converter
std::string wstringTostring(std::wstring str);

// string->wstring converter
std::wstring stringTowstring(std::string str);

// wchar->char converter
const char* wcharTochar(const wchar_t* str);

// char->wchar converter
const wchar_t* charTowchar(const char* str);