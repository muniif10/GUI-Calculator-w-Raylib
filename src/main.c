
#include "calculator.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Func takes the current result in calcStat

void doNothing(char *data) {}

void addDigit(CalculatorStatus *calc, char digit) {
  char digitStr[2] = {digit, '\0'};
  regex_t regex;
  int reti = regcomp(&regex, "[[:digit:]]", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  reti = regexec(&regex, digitStr, 0, NULL, 0);
  if (!reti) {
    // Match
    // Append to current value of string
    strcat(calc->tempStr, digitStr);

    char myOperand[64];

    // Store the original float operand to char*
    sprintf(myOperand, "%.0f", calc->firstOp);
    TraceLog(LOG_INFO, "myOperand:%s",
             myOperand); // Just printing for sanity check
    TraceLog(LOG_INFO, "digitStr:%s",
             digitStr); // Just printing for sanity check
    char tempFirstOp[64];
    // Append the new digit to the original operand
    strcat(myOperand, digitStr);
    calc->firstOp = strtol(myOperand, NULL, 0);
    TraceLog(LOG_INFO, "%.3f", calc->firstOp);
    // TraceLog(LOG_INFO, const char *text, ...)

  } else if (reti == REG_NOMATCH) {
    // No regex match
    puts("No matches, you clicked a number?");
  } else {
    // Regex failures, etc..
  }
  // Convert the value to integer
}

void addOperation(void *data) {
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->secondOp == 0) {
    calc->opType = '+';
    calc->secondOp = calc->firstOp;
    calc->firstOp = 0;
    char operatorDone[2] = {'+', '\0'};
    // Append to current value of string
    strcat(calc->tempStr, operatorDone);
  } else {
    float result = calc->firstOp + calc->secondOp;
    gcvt(result, 2, calc->tempStr);
    // free(calc->tempStr);
    // calc->tempStr= malloc(sizeof(char)*64);
    // for (int ii = 0; ii < 64; ii++) {
    //   calc->tempStr[ii] = ' ';
    // }
    calc->lastResult = result;
    TraceLog(LOG_INFO, "Result: %f from %f and %f", calc->lastResult,
             calc->firstOp, calc->secondOp);
  }
}

void addDigit1(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '1');
}
void addDigit2(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '2');
}
void addDigit3(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '3');
}
void addDigit4(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '4');
}
void addDigit5(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '5');
}
void addDigit6(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '6');
}
void addDigit7(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '7');
}
void addDigit8(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '8');
}
void addDigit9(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '9');
}
void addDigit0(void *data) {
  if (data == NULL) {
    TraceLog(LOG_WARNING, "addDigit: data is NULL — ignoring");
    return;
  }
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->tempStr == NULL) {
    TraceLog(LOG_ERROR, "tempStr is NULL");
    return;
  }
  addDigit(calc, '0');
}

int main() {
  CalculatorStatus calStat;
  calStat.opType = 'X';
  calStat.firstOp = 0;
  calStat.secondOp = 0;
  calStat.lastResult = 0;
  calStat.tempStr = malloc(sizeof(char) * 64);
  if (calStat.tempStr == NULL) {
    fprintf(stderr, "Failed to allocate memory for tempStr\n");
    exit(1);
  }
  // printf("Pointer: %p\nCapacity: %d\n", &queue.operations, queue.capacity);
  // Tell the window to use vsync and work on high DPI displays

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  int height = 500;
  int width = 500;
  // Create the window and OpenGL context
  InitWindow(width, height, "Calculator!");
  SetTargetFPS(60);
  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");

  Button buttons[] = {
      {.color = ORANGE, "+", addOperation, .haveValue = 1},
      {.color = ORANGE, "-", addOperation, .haveValue = 1},
      {.color = ORANGE, "*", addOperation, .haveValue = 1},
      {.color = BLUE, "1", addDigit1, .haveValue = 1},
      {.color = BLUE, "2", addDigit2, .haveValue = 1},
      {.color = BLUE, "3", addDigit3, .haveValue = 1},
      {.color = BLUE, "4", addDigit4, .haveValue = 1},
      {.color = BLUE, "5", addDigit5, .haveValue = 1},
      {.color = BLUE, "6", addDigit6, .haveValue = 1},
      {.color = BLUE, "7", addDigit7, .haveValue = 1},
      {.color = BLUE, "8", addDigit8, .haveValue = 1},
      {.color = BLUE, "9", addDigit9, .haveValue = 1},
      {.color = BLUE, "0", addDigit0, .haveValue = 1},
  };

  // Font configs
  FontConfig fontConfig = {
      .fontsize = 14,
      .color = WHITE,
      .fontLocation = LoadFont("GoogleSansCode-VariableFont_wght.ttf")};

  // game loop
  while (!WindowShouldClose()) // run the loop untill the user presses
                               // ESCAPE or presses the Close button on the
                               // window draw
  {
    BeginDrawing();
    generateGridView(&calStat, 3, 5, width, height, buttons, &fontConfig);
    DrawText(calStat.tempStr, 0, 0, 24, BLACK);
    // createButton(100, 100, 50, 50, "Button", doSomething, &queue, true);
    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);
    DrawFPS(width - 100, 0);
    // draw some text using the default font
    EndDrawing();
  }
  // cleanup
  // unload our texture so it can be cleaned up

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
