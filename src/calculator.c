
#include "calculator.h"
#include <stdbool.h>
void generateGridView(CalculatorStatus *calStat, int col, int row, int maxWidth,
                      int maxHeight, Button *buttons, FontConfig *fontConfig) {
  float yOffset = 100;
  float rowHeightUnit = ((float)maxHeight - (yOffset / row)) / row;
  float colWidthUnit = (float)maxWidth / col;
  int buttonIndex = 0;
  for (int ii = 0; ii < row; ii++) {
    for (int jj = 0; jj < col; jj++) {
      if (buttons[buttonIndex].haveValue == 1) {
        createButton(jj * colWidthUnit,
                     (ii * (rowHeightUnit)) + (yOffset / row),
                     ((float)maxHeight - (yOffset / row)) / row,
                     (float)maxWidth / col, buttons[buttonIndex].text,
                     buttons[buttonIndex].callback, calStat, true, fontConfig);
      } else {
        break;
      }
      buttonIndex++;
    }
  }
}
