#include "calculator.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "stb_ds.c"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPLIT_FACTOR 3

void clearCalcState(void *data) {
  CalculatorStatus *calcStat = (CalculatorStatus *)data;
  calcStat->firstOp = 0;
  calcStat->secondOp = 0;
  calcStat->didOperation = false;
  // NOTE: After first operation, must not clear the tempStr
  // Second press on clear will perform
  free(calcStat->tempStr);
  calcStat->tempStr = malloc(sizeof(char) * 64);
  for (int ii = 0; ii < 64; ii++) {
    if (ii == 0) {
      calcStat->tempStr[ii] = '\0';
    } else {
      calcStat->tempStr[ii] = ' ';
    }
  }
  calcStat->lastResult = 0;
}

void addDigit(CalculatorStatus *calc, char digit) {
  char digitStr[2] = {digit, '\0'};
  regex_t regex;
  int reti = regcomp(&regex, "[[:digit:]]", 0);
  if (reti) {
    regfree(&regex);
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  reti = regexec(&regex, digitStr, 0, NULL, 0);
  if (!reti) {
    regfree(&regex);
    // Match
    // Append to current value of string
    strcat(calc->tempStr, digitStr);

    char myOperand[64];
    for (int ii = 0; ii < 64; ii++) {
      myOperand[ii] = ' ';
    }

    // Store the original float operand to char*
    sprintf(myOperand, "%.0f", calc->firstOp);
    TraceLog(LOG_INFO, "myOperand:%s",
             myOperand); // Just printing for sanity check
    TraceLog(LOG_INFO, "digitStr:%s",
             digitStr); // Just printing for sanity check
    char tempFirstOp[64];
    // Append the new digit to the original operand
    strcat(myOperand, digitStr);
    // NOTE: Enforce base 10
    calc->firstOp = strtol(myOperand, NULL, 10);
    TraceLog(LOG_INFO, "%.3f", calc->firstOp);

    TraceLog(LOG_INFO, "first: %.3f :: second: %.3f", calc->firstOp,
             calc->secondOp);
  } else if (reti == REG_NOMATCH) {
    regfree(&regex);
    // No regex match
    puts("No matches, you clicked a digit?");
  } else {
    regfree(&regex);
    // Regex failures, etc..
  }
}

void doDivOperation(void *data) {
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->secondOp == 0) {
    calc->opType = '/';
    calc->secondOp = calc->firstOp;
    calc->firstOp = 0;
    char operatorDone[2] = {'/', '\0'};
    // Append to current value of string
    strcat(calc->tempStr, operatorDone);
  } else {
    memset(calc->tempStr, 0, 64);
    // free(calc->tempStr);
    // calc->tempStr = malloc(sizeof(char) * 64);
    // for (int ii = 0; ii < 64; ii++) {
    //   calc->tempStr[ii] = ' ';
    // }
    float result = calc->secondOp / calc->firstOp;
    gcvt(result, 9, calc->tempStr);
    calc->lastResult = result;
    History his;
    his.operand1 = calc->secondOp;
    his.operand2 = calc->firstOp;
    his.calcOperator = calc->opType;
    TraceLog(LOG_INFO, "lastResult = %.2f", calc->lastResult);
    char *resultStringForHistory = malloc(sizeof(char) * 20);
    strcpy(resultStringForHistory, calc->tempStr);
    sprintf(resultStringForHistory, "%.2f", calc->lastResult);
    his.result = resultStringForHistory;
    calc->didOperation = true;
    arrput(calc->history, his);
    TraceLog(LOG_INFO, "Result: %f from %f and %f", calc->lastResult,
             calc->firstOp, calc->secondOp);
    clearCalcState(calc);
  }
}

void doMulOperation(void *data) {
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->secondOp == 0) {
    calc->opType = '*';
    calc->secondOp = calc->firstOp;
    calc->firstOp = 0;
    char operatorDone[2] = {'*', '\0'};
    // Append to current value of string
    strcat(calc->tempStr, operatorDone);
  } else {
    memset(calc->tempStr, 0, 64);
    // free(calc->tempStr);
    // calc->tempStr = malloc(sizeof(char) * 64);
    // for (int ii = 0; ii < 64; ii++) {
    //   calc->tempStr[ii] = ' ';
    // }
    float result = calc->secondOp * calc->firstOp;
    gcvt(result, 9, calc->tempStr);
    calc->lastResult = result;
    History his;
    his.operand1 = calc->secondOp;
    his.operand2 = calc->firstOp;
    his.calcOperator = calc->opType;
    char *resultStringForHistory = malloc(sizeof(char) * 20);
    strcpy(resultStringForHistory, calc->tempStr);
    sprintf(resultStringForHistory, "%.2f", calc->lastResult);
    his.result = resultStringForHistory;
    calc->didOperation = true;
    arrput(calc->history, his);
    TraceLog(LOG_INFO, "Result: %f from %f and %f", calc->lastResult,
             calc->firstOp, calc->secondOp);
    clearCalcState(calc);
  }
}

void doSubOperation(void *data) {
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->secondOp == 0) {
    calc->opType = '-';
    calc->secondOp = calc->firstOp;
    calc->firstOp = 0;
    char operatorDone[2] = {'-', '\0'};
    // Append to current value of string
    strcat(calc->tempStr, operatorDone);
  } else {
    memset(calc->tempStr, 0, 64);
    // free(calc->tempStr);
    // calc->tempStr = malloc(sizeof(char) * 64);
    // for (int ii = 0; ii < 64; ii++) {
    //   calc->tempStr[ii] = ' ';
    // }
    float result = calc->secondOp - calc->firstOp;
    gcvt(result, 9, calc->tempStr);
    calc->lastResult = result;
    History his;
    his.operand1 = calc->secondOp;
    his.operand2 = calc->firstOp;
    his.calcOperator = calc->opType;
    // his.result = calc->tempStr;
    char *resultStringForHistory = malloc(sizeof(char) * 20);
    strcpy(resultStringForHistory, calc->tempStr);
    sprintf(resultStringForHistory, "%.2f", calc->lastResult);
    his.result = resultStringForHistory;
    calc->didOperation = true;
    arrput(calc->history, his);
    TraceLog(LOG_INFO, "Result: %f from %f and %f", calc->lastResult,
             calc->firstOp, calc->secondOp);
    clearCalcState(calc);
  }
}

void doAddOperation(void *data) {
  CalculatorStatus *calc = (CalculatorStatus *)data;
  if (calc->secondOp == 0) {
    calc->opType = '+';
    calc->secondOp = calc->firstOp;
    calc->firstOp = 0;
    char operatorDone[2] = {'+', '\0'};
    // Append to current value of string
    strcat(calc->tempStr, operatorDone);
  } else {
    memset(calc->tempStr, 0, 64);
    // free(calc->tempStr);
    // calc->tempStr = malloc(sizeof(char) * 64);
    // for (int ii = 0; ii < 64; ii++) {
    //   calc->tempStr[ii] = ' ';
    // }
    float result = calc->firstOp + calc->secondOp;
    gcvt(result, 9, calc->tempStr);
    calc->lastResult = result;
    History his;
    his.operand1 = calc->secondOp;
    his.operand2 = calc->firstOp;
    his.calcOperator = calc->opType;
    // his.result = calc->tempStr;
    char *resultStringForHistory = malloc(sizeof(char) * 20);
    strcpy(resultStringForHistory, calc->tempStr);
    sprintf(resultStringForHistory, "%.2f", calc->lastResult);
    his.result = resultStringForHistory;
    calc->didOperation = true;
    arrput(calc->history, his);
    TraceLog(LOG_INFO, "Result: %f from %f and %f", calc->lastResult,
             calc->firstOp, calc->secondOp);
    clearCalcState(calc);
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
  SetTraceLogLevel(LOG_ALL);
  SearchAndSetResourceDir("resources");
  // Shader blurShader = LoadShader(0, "blur.glsl");
  // int blurDirectionLoc = GetShaderLocation(blurShader, "direction");
  CalculatorStatus calStat;
  calStat.opType = 'X';
  calStat.firstOp = 0;
  calStat.secondOp = 0;
  calStat.lastResult = 0;

  History *history = NULL;

  calStat.history = history;
  // calStat.history = (char* []) {"ada","sok"};
  calStat.tempStr = malloc(sizeof(char) * 64);

  if (calStat.tempStr == NULL) {
    fprintf(stderr, "Failed to allocate memory for tempStr\n");
    exit(1);
  }
  // printf("Pointer: %p\nCapacity: %d\n", &queue.operations, queue.capacity);
  // Tell the window to use vsync and work on high DPI displays

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);
  // Set height and width of windows
  int height = 500;
  int width = 500;
  float effectiveCalculatorWidth = width / SPLIT_FACTOR;
  // Create the window and OpenGL context
  InitWindow(width, height, "Calculator!");
  SetTargetFPS(60);
  // Utility function from resource_dir.h to find the resources folder and set
  // it as the current working directory so we can load from it

  Button buttons[] = {
      {.color = ORANGE, "+", doAddOperation, .haveValue = 1},
      {.color = ORANGE, "-", doSubOperation, .haveValue = 1},
      {.color = ORANGE, "*", doMulOperation, .haveValue = 1},
      {.color = BLUE, "1", addDigit1, .haveValue = 1},
      {.color = BLUE, "2", addDigit2, .haveValue = 1},
      {.color = BLUE, "3", addDigit3, .haveValue = 1},
      {.color = BLUE, "4", addDigit4, .haveValue = 1},
      {.color = BLUE, "5", addDigit5, .haveValue = 1},
      {.color = BLUE, "6", addDigit6, .haveValue = 1},
      {.color = BLUE, "7", addDigit7, .haveValue = 1},
      {.color = BLUE, "8", addDigit8, .haveValue = 1},
      {.color = BLUE, "9", addDigit9, .haveValue = 1},
      {.color = BLUE, "CLR", clearCalcState, .haveValue = 1},
      {.color = BLUE, "0", addDigit0, .haveValue = 1},
      {.color = ORANGE, "/", doDivOperation, .haveValue = 1},
  };

  // Font configs
  FontConfig fontConfig = {
      .fontsize = 14,
      .color = WHITE,
      .fontLocation =
          LoadFontEx("GoogleSansCode-VariableFont_wght.ttf", 120, NULL, 0)};

  FontConfig fontConfigHistory = {
      .fontsize = 14, .color = WHITE, .fontLocation = fontConfig.fontLocation};

  // game loop
  while (!WindowShouldClose()) // run the loop untill the user presses
                               // ESCAPE or presses the Close button on the
                               // window draw
  {
    BeginDrawing();
    generateGridView(&calStat, 3, 5, width - effectiveCalculatorWidth, height,
                     buttons, &fontConfig);
    DrawText(calStat.tempStr, 0, 0, 24, BLACK);
    enum CALCULATOR_RETURN_CODE res = generateHistorySideView(
        (Vector2){width - effectiveCalculatorWidth, 0},
        effectiveCalculatorWidth, height, &calStat, &fontConfigHistory);
    if (res == NO_CALCULATOR_STATUS_OBJECT) {
      return NO_CALCULATOR_STATUS_OBJECT;
    }
    // createButton(100, 100, 50, 50, "Button", doSomething, &queue, true);
    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(WHITE);
    // DrawFPS(width - 100, 0);
    // draw some text using the default font
    EndDrawing();
  }

  free(calStat.tempStr);
  arrfree(history);
  free(history);
  UnloadFont(fontConfig.fontLocation);
  // cleanup
  // unload our texture so it can be cleaned up

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
