#ifndef CALCULATOR_H_INCLUDE
#define CALCULATOR_H_INCLUDE
#import "raylib.h"

enum CALCULATOR_RETURN_CODE {
  NO_CALCULATOR_STATUS_OBJECT = 5,
  DAWG,
  OKAY,
};

typedef struct History {
  float operand1;
  float operand2;
  char calcOperator;
  char *result;
} History;

typedef struct Button {
  Color color;
  char *text;
  void (*callback)(void *);
  int haveValue;
} Button;
typedef struct {
  float firstOp;
  char opType;
  float lastResult;
  char *tempStr;
  float secondOp;
  bool didOperation;
  History *history;
} CalculatorStatus;
typedef struct FontConfig {
  Color color;
  Font fontLocation;
  float fontsize;
} FontConfig;
void createButton(float x, float y, float height, float width, char *text,
                  void (*callback)(void *), void *data, bool callbackOnce,
                  FontConfig *fontConfig);

void generateGridView(CalculatorStatus *calStat, int col, int row, int maxWidth,
                      int maxHeight, Button *buttons, FontConfig *fontConfig);

enum CALCULATOR_RETURN_CODE generateHistorySideView(Vector2 topLeftStartPoint,
                                                    float width, float height,
                                                    CalculatorStatus *calc,
                                                    FontConfig *fontConfig);
#endif
