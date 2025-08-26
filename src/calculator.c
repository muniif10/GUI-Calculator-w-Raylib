#include "calculator.h"
#include "raylib.h"
#include "stb_ds.h"
#include <stdbool.h>
#include <stdio.h>
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
enum CALCULATOR_RETURN_CODE generateHistorySideView(Vector2 topLeftStartPoint,
                                                    float width, float height,
                                                    CalculatorStatus *calc,
                                                    FontConfig *fontConfig) {
  float xCoordinate = topLeftStartPoint.x;
  float yCoordinate = topLeftStartPoint.y;
  // Height should maintain the values coming from the main application
  // Width should be the leftover from the calculation
  if (calc != NULL) {
    int arrlength = arrlen(calc->history);
    TraceLog(LOG_INFO, "%d", arrlength);
    // Get the string
    // Calculate the length is okay or not to draw text over to the edge of
    if (arrlength > 0) {
      float yPos = 0.0;
      for (int ii = 0; ii < arrlength; ii++) {
        History his = calc->history[ii];
        char outStr[51];
        memset(outStr, 0, 51);
        snprintf(outStr, 50, "%.2f %c %.2f = %s", his.operand1,
                 his.calcOperator, his.operand2, his.result);
        TraceLog(LOG_INFO, "first round::%s::", outStr);
        Vector2 size = MeasureTextEx(fontConfig->fontLocation, outStr,
                                     fontConfig->fontsize, 1);
        TraceLog(LOG_INFO, "size: %.2f\twidth:%.2f", size.x, width);
        if (size.x > width) {
          TraceLog(LOG_INFO, "second round: %s", outStr);
          memset(outStr, 0, 51);
          snprintf(outStr, 50, "%.2f %c %.2f =\n %s", his.operand1,
                   his.calcOperator, his.operand2, his.result);
          size = MeasureTextEx(fontConfig->fontLocation, outStr,
                               fontConfig->fontsize, 1);
        }
        DrawTextEx(fontConfig->fontLocation, outStr,
                   (Vector2){topLeftStartPoint.x, yPos}, fontConfig->fontsize,
                   1, BLACK);
        yPos = yPos + size.y;
      }
    }
    // screen If exceed window's limit, we need to emulate carriage return else
    // draw as it is.
    return OKAY;
  } else {
    // Error on this shit dawg
    return NO_CALCULATOR_STATUS_OBJECT;
  }
}
