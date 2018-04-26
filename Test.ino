#include <Arduboy2.h>
#include "Name.h"

Arduboy2 arduboy;
Name name;

uint8_t xOffset = 42;
uint8_t yOffset = 10;
uint8_t state = 0;


void setup() {

  arduboy.begin();
  arduboy.setFrameRate(15);

  name.retrieve(123);

}


void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();

  switch (state) {

    case 0:
      getName();
      break;

    case 1:
      showName();
      break;

  }

  arduboy.display();

}


void getName() {

  arduboy.setCursor(4, 9);
  arduboy.drawRect(xOffset - 2, yOffset - 2 , 73, 13);
  arduboy.print(F("Name:"));



  for (uint8_t x = 0; x < NAME_LENGTH; x++) {

    arduboy.setCursor(xOffset + (x * NAME_CHARACTER_SPACING), yOffset);

    if (name.getCharIndex() == x) {
      arduboy.drawLine(xOffset + (x * NAME_CHARACTER_SPACING), yOffset + 9, xOffset + (x * NAME_CHARACTER_SPACING) + NAME_UNDERLINE_WIDTH, yOffset + 9, WHITE);
    }

    arduboy.print(name.getChar(x));

  }


  // Handle buttons ..

  uint8_t charIndex = name.getCharIndex();

  if (arduboy.justPressed(UP_BUTTON))       { name.incChar(charIndex); }
  if (arduboy.justPressed(DOWN_BUTTON))     { name.decChar(charIndex); }
  if (arduboy.justPressed(LEFT_BUTTON))     { name.decCharIndex(); } 
  if (arduboy.justPressed(RIGHT_BUTTON))    { name.incCharIndex(); } 

  if (arduboy.justPressed(A_BUTTON))        { name.save(123); state = 1; }


}


void showName() {

  name.retrieve(123);

  arduboy.setCursor(0, 12);
  arduboy.print("You entered :\n");
  arduboy.print(name.getString());


}