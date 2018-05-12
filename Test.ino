#include <Arduboy2.h>
#include "Name.h"

constexpr const uint8_t NameCharacterSpacing = 7;
constexpr const uint8_t NameUnderlineWidth = 5;

enum class ProgramState : uint8_t
{
	GetName, ShowName,
};

Arduboy2 arduboy;
NameEditor<10> name;

ProgramState state = ProgramState::GetName;

void setup(void)
{
	arduboy.begin();
	arduboy.setFrameRate(15);

	name.retrieve(123);
}

void loop(void)
{
	if (!(arduboy.nextFrame()))
	return;
	
	arduboy.pollButtons();
	
	arduboy.clear();

	switch (state)
	{
		case ProgramState::GetName:
			getName();
			break;

		case ProgramState::ShowName:
			showName();
			break;
	}

	arduboy.display();
}

uint8_t xOffset = 42;
uint8_t yOffset = 10;

void getName(void)
{
	if (arduboy.justPressed(UP_BUTTON))
		name.incrementChar();
	
	if (arduboy.justPressed(DOWN_BUTTON))
		name.decrementChar();
	
	if (arduboy.justPressed(LEFT_BUTTON))
		name.decrementCharIndex();
		
	if (arduboy.justPressed(RIGHT_BUTTON))
		name.incrementCharIndex();

	if (arduboy.justPressed(A_BUTTON))
	{
		name.save(123);
		state = ProgramState::ShowName;
		return;
	}
	
	arduboy.setCursor(4, 9);
	arduboy.drawRect(xOffset - 2, yOffset - 2 , 73, 13);
	arduboy.print(F("Name:"));

	for (uint8_t i = 0; i < name.getLength(); i++)
	{
		const uint8_t spacing = (i * NameCharacterSpacing);
		arduboy.setCursor(xOffset + spacing, yOffset);
		if (name.getCharIndex() == i)
		{
			arduboy.drawLine(xOffset + spacing, yOffset + 9, xOffset + spacing + NameUnderlineWidth, yOffset + 9);
		}
		arduboy.print(name.getChar(i));
	}
}


void showName(void)
{
	name.retrieve(123);

	arduboy.setCursor(0, 12);
	arduboy.print(F("You entered :\n"));
	arduboy.print(name.getString());
}