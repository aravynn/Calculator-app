#pragma once

// definitions for buttons later on. 
#define BU_VIEW 1000
#define BU_ONE 1001
#define BU_TWO 1002
#define BU_THREE 1003
#define BU_FOUR 1004
#define BU_FIVE 1005
#define BU_SIX 1006
#define BU_SEVEN 1007
#define BU_EIGHT 1008
#define BU_NINE 1009
#define BU_ZERO 1010
#define BU_PLUS 1011
#define BU_MINUS 1012
#define BU_MULTIPLY 1013
#define BU_DIVIDE 1014
#define BU_EQUALS 1015
#define BU_POINT 1016

#include "resource.h"
#include "framework.h"

#include <string>

// basic number containers for use in calculations. 
extern double numberOne;
extern double numberTwo;
extern char equation;
extern bool numReset;
extern int decimal;

// view functions for calculator app
bool resizeWindow(HWND hWnd);
bool createCalcControls(HWND hWnd);
bool resetViewBox(std::wstring msg, HWND hWnd);

// computation functions for calculator app.
void digitInsert(int digit, HWND hWnd);
void setEquation(char type, HWND hWnd);
void setDecimal();
