/*************************************************
* Name : Keyboard.cpp
* Purpose : Source for keyboard input
* Date : 2020-11-30
* ************************************************/

#include "Keyboard.h"

Keyboard::Keyboard()
{}

bool Keyboard::IsKeyPressed(unsigned char code) const noexcept
{
	return keyStates[code];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
	if (!eventQueue.empty())
	{
		Event e = eventQueue.front();
		eventQueue.pop();
		return e;
	}
	else
	{
		return std::optional<Keyboard::Event>();
	}
}

char Keyboard::ReadChar() noexcept
{
	if (!charQueue.empty())
	{
		char c = charQueue.front();
		charQueue.pop();
		return c;
	}
	else
	{
		return -1;
	}
}

bool Keyboard::IsKeyEmpty() const noexcept
{
	return eventQueue.empty();
}

bool Keyboard::IsCharEmpty() const noexcept
{
	return charQueue.empty();
}

void Keyboard::FlushKeys() noexcept
{
	eventQueue = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept
{
	charQueue = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKeys();
	FlushChar();
}

void Keyboard::OnKeyPressed(unsigned char code) noexcept
{
	keyStates[code] = true;
	eventQueue.push(Keyboard::Event(Keyboard::Event::Type::PRESSED, code));
	TrimBuffer(eventQueue);
}

void Keyboard::OnKeyReleased(unsigned char code) noexcept
{
	keyStates[code] = false;
	eventQueue.push(Keyboard::Event(Keyboard::Event::Type::RELEASED, code));
	TrimBuffer(eventQueue);
}

void Keyboard::OnChar(char ch) noexcept
{
	charQueue.push(ch);
	TrimBuffer(charQueue);
}

void Keyboard::ClearStates() noexcept
{
	keyStates.reset();
}

template <typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}