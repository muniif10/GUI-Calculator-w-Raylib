#include "calculator.h"
#include "raylib.h"

void createButton(float x, float y, float height, float width, char *text,
                  void (*callback)(void *), void *data, bool callbackOnce,
                  FontConfig *fontConfig) {
  Color buttonColor = GRAY;
  Color hoverColor = SKYBLUE;
  Color pressedColor = BLACK;
  Rectangle buttonRec = {x, y, width, height};

  if (CheckCollisionPointRec(GetMousePosition(), buttonRec)) {
    if (callbackOnce == true ? IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
                             : IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      buttonColor = pressedColor;
      // Call the callback
      callback(data);
    } else {
      buttonColor = hoverColor;
    }
  } else {
    buttonColor = GRAY;
  }
  // Draw the rectangle
  DrawRectangleRec(buttonRec, buttonColor);
  // Create vector2
  Vector2 vect = {(buttonRec.width - MeasureTextEx(fontConfig->fontLocation,text, 16,28).x) / 2 + buttonRec.x,
                  (buttonRec.height - 16) / 2 + buttonRec.y};
  // Draw the text
  DrawTextEx(fontConfig->fontLocation, text, vect, 32, fontConfig->fontsize,
             fontConfig->color);
}
