#include "Calculator-app.h"
#include "framework.h"


double numberOne{ 0 };
double numberTwo{ 0 };
char equation{ 'n' };
bool numReset{ false };
int decimal{ 0 };

void digitInsert(int digit, HWND hWnd) {
	// insert a digit to second number or first number if equation is 'n'
	if (numReset) {
		numReset = false;
		numberTwo = 0;
	}

	if (equation == 'n') {
		if (decimal > 0) {
			numberOne = numberOne + (digit / pow(10, decimal));
			++decimal;
		}
		else {
			numberOne = 10 * numberOne + digit; 
		}
		resetViewBox(std::to_wstring(numberOne), hWnd);
	}
	else {
		if (decimal > 0) {
			numberTwo = numberTwo + (digit / pow(10, decimal));
			++decimal;
		}
		else {
			numberTwo = 10 * numberTwo + digit;
		}
		
		resetViewBox(std::to_wstring(numberTwo), hWnd);
	}

}

void setEquation(char type, HWND hWnd) {
	//calculate out and move 2 to 1.

	numReset = true;
	decimal = 0;

	if (type == equation || type == '=') {
		switch (equation) {
		case '*':
		case 'x':
		case 'X':
			// multiply 
			numberOne = (equation != 'n' ? numberTwo : 1.0) * numberOne;
			break;
		case '+':
			numberOne += numberTwo;
			break;
		case '-':
			numberOne -= numberTwo;
			break;
		case '/':
			numberOne = (equation != 'n' ? numberOne / numberTwo : numberTwo);
			break;
		case '=':
			setEquation(equation, hWnd);
			break;
		default:
			// do nothing
			break;
		}
	}

	//numberTwo = 0.0;

	if(type != '=')
		equation = type;

	std::wstring msg = std::to_wstring(numberOne);// +L" " + std::to_wstring(numberTwo);

	

	// refresh the number
	resetViewBox(msg, hWnd);
}

void setDecimal() {
	decimal = 1;
}

void resetButton() {
	numberOne = 0 ;
	numberTwo = 0;
	equation = 'n';
	numReset = false;
	decimal = 0;
}