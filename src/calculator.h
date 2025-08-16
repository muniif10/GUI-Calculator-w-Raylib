#ifndef CALCULATOR_H_INCLUDE
#define CALCULATOR_H_INCLUDE
#import "raylib.h"

typedef struct Button {
  Color color;
  char *text;
  void (*callback)(void*) ;
  int haveValue;
} Button;
typedef struct{
float firstOp;
char opType;
float lastResult;
char* tempStr;
float secondOp;
} CalculatorStatus ;
typedef struct FontConfig {
  Color color;
  Font fontLocation;
  float fontsize;
} FontConfig;
void createButton(float x, float y,float height, float width, char *text,
                  void (*callback)(void*), void *data, bool callbackOnce, FontConfig* fontConfig);

void generateGridView(CalculatorStatus *calStat, int col, int row, int maxWidth,
                      int maxHeight, Button* buttons, FontConfig* fontConfig);

#endif
