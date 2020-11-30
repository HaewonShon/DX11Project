/*************************************************
* Name : Keyboard.h
* Purpose : Header for Keyboard class and event class which is for handling keyboard event
* Date : 2020-11-30
* ************************************************/
#pragma once

#include <bitset>
#include <queue>
#include <optional>

class Keyboard
{
	friend class Window;
public:
	/* Event class for handling keyboard events */
	class Event
	{
	public:
		enum class Type
		{
			PRESSED,
			RELEASED,
			INVALID,
		};
		Event(Type type, unsigned char code) noexcept : type(type), code(code) {}
	public:
		Type type;
		unsigned char code;
	};

public:
	/* class member functions */
	Keyboard();
	bool IsKeyPressed(unsigned char code) const noexcept;
	std::optional<Event> ReadKey() noexcept;
	char ReadChar() noexcept;
	bool IsKeyEmpty() const noexcept;
	bool IsCharEmpty() const noexcept;
	void FlushKeys() noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

private:
	/* event handling functions, will be used in Window class */
	void OnKeyPressed(unsigned char code) noexcept;
	void OnKeyReleased(unsigned char code) noexcept;
	void OnChar(char ch) noexcept;
	void ClearStates() noexcept;
	template <typename T> static void TrimBuffer(std::queue<T>& buffer) noexcept;

private:
	/* class memebers */
	static constexpr unsigned int bufferSize = 16;

	std::queue<Event> eventQueue{};
	std::queue<char> charQueue{};
	std::bitset<256> keyStates{};
	
private:
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
};