#include "Calculator-app.h"
#include "framework.h"

std::vector<HWND> controls;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

enum class ctrlS {
	VIEW,
	ONE, 
	TWO,
	THREE,
	FOUR, 
	FIVE, 
	SIX, 
	SEVEN,
	EIGHT,
	NINE, 
	ZERO,
	MULTIPLY,
	DIVIDE,
	ADD,
	SUBTRACT,
	EQUAL,
	POINT
};

bool createCalcControls(HWND hWnd) {
	// create the control structure for the calculator. 
	// this will include the management of the elements for later deletion, if required for complex design. 

	// controls managed in vector for future usage, like all good things about this programming style, 
	// we're going global elements. Hooray! First, create the Basic structure for the buttons, 1-0, +-*/= and a static for the display, to be reset whenever a button is pressed. 

	if (controls.size() > 0) {
		// controls already exist, delete all controls.
		for (int i{ 0 }; i < (int)controls.size(); ++i) {
			DestroyWindow(controls.at(i));
		}
	}

	// resize for new data.
	controls.resize(17);

		// 0 is our static view.
		controls.at((int)ctrlS::VIEW) = CreateWindowW(L"STATIC", L"0", WS_CHILD | WS_VISIBLE | SS_RIGHT, 10, 10, 180, 30, hWnd, (HMENU)BU_VIEW, NULL, NULL) ;

		HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));
		controls.at((int)ctrlS::ONE) = CreateWindowW(L"BUTTON", L"1", WS_CHILD | WS_VISIBLE, 0, 60, 40, 40, hWnd, (HMENU)BU_ONE, NULL, NULL);
		controls.at((int)ctrlS::TWO) = CreateWindowW(L"BUTTON", L"2", WS_CHILD | WS_VISIBLE, 40, 60, 40, 40, hWnd, (HMENU)BU_TWO, NULL, NULL);
		controls.at((int)ctrlS::THREE) = CreateWindowW(L"BUTTON", L"3", WS_CHILD | WS_VISIBLE, 80, 60, 40, 40, hWnd, (HMENU)BU_THREE, NULL, NULL);
		controls.at((int)ctrlS::FOUR) = CreateWindowW(L"BUTTON", L"4", WS_CHILD | WS_VISIBLE, 0, 100, 40, 40, hWnd, (HMENU)BU_FOUR, NULL, NULL);
		controls.at((int)ctrlS::FIVE) = CreateWindowW(L"BUTTON", L"5", WS_CHILD | WS_VISIBLE, 40, 100, 40, 40, hWnd, (HMENU)BU_FIVE, NULL, NULL);
		controls.at((int)ctrlS::SIX) = CreateWindowW(L"BUTTON", L"6", WS_CHILD | WS_VISIBLE, 80, 100, 40, 40, hWnd, (HMENU)BU_SIX, NULL, NULL);
		controls.at((int)ctrlS::SEVEN) = CreateWindowW(L"BUTTON", L"7", WS_CHILD | WS_VISIBLE, 0, 140, 40, 40, hWnd, (HMENU)BU_SEVEN, NULL, NULL);
		controls.at((int)ctrlS::EIGHT) = CreateWindowW(L"BUTTON", L"8", WS_CHILD | WS_VISIBLE, 40, 140, 40, 40, hWnd, (HMENU)BU_EIGHT, NULL, NULL);
		controls.at((int)ctrlS::NINE) = CreateWindowW(L"BUTTON", L"9", WS_CHILD | WS_VISIBLE, 80, 140, 40, 40, hWnd, (HMENU)BU_NINE, NULL, NULL);
		controls.at((int)ctrlS::ZERO) = CreateWindowW(L"BUTTON", L"0", WS_CHILD | WS_VISIBLE, 40, 180, 40, 40, hWnd, (HMENU)BU_ZERO, NULL, NULL);

		controls.at((int)ctrlS::ADD) = CreateWindowW(L"BUTTON", L"+", WS_CHILD | WS_VISIBLE, 120, 60, 40, 40, hWnd, (HMENU)BU_PLUS, NULL, NULL);
		controls.at((int)ctrlS::SUBTRACT) = CreateWindowW(L"BUTTON", L"-", WS_CHILD | WS_VISIBLE, 120, 100, 40, 40, hWnd, (HMENU)BU_MINUS, NULL, NULL);
		controls.at((int)ctrlS::MULTIPLY) = CreateWindowW(L"BUTTON", L"x", WS_CHILD | WS_VISIBLE, 120, 140, 40, 40, hWnd, (HMENU)BU_MULTIPLY, NULL, NULL);
		controls.at((int)ctrlS::DIVIDE) = CreateWindowW(L"BUTTON", L"/", WS_CHILD | WS_VISIBLE, 120, 180, 40, 40, hWnd, (HMENU)BU_DIVIDE, NULL, NULL);
		controls.at((int)ctrlS::EQUAL) = CreateWindowW(L"BUTTON", L"=", WS_CHILD | WS_VISIBLE, 80, 180, 40, 40, hWnd, (HMENU)BU_EQUALS, NULL, NULL);
		controls.at((int)ctrlS::POINT) = CreateWindowW(L"BUTTON", L".", WS_CHILD | WS_VISIBLE, 0, 180, 40, 40, hWnd, (HMENU)BU_POINT, NULL, NULL);

		resizeWindow(hWnd);


		//std::wstring retval{ L"Some Number" };
		//resetViewBox(retval.c_str());

		return true;
}

bool resizeWindow(HWND hWnd) {
	// controls the resizing functions for the main window, to allow buttons to dynamically resize with the rest of the window.

	RECT rect;

	int WndWidth{0};
	int WndHeight{0};
	int BtnWidth{0};
	int BtnHeight{0};


	if (GetWindowRect(hWnd, &rect))
	{
		WndWidth = rect.right - rect.left - 16;
		WndHeight = rect.bottom - rect.top - 56;

		// button sizes based on window dimensions.
		BtnWidth = WndWidth / 4;
		BtnHeight = WndHeight / 5;
	}
	else {
		return false;
	}

	if (controls.size() < 1) {
		return false; // no controls to resize. 
	}
	
	std::vector<std::pair<int, int>> controlPos{ {0,0}, {0,1}, {1,1}, {2,1}, {0,2}, {1,2}, {2,2}, {0,3}, {1,3}, {2,3}, {1,4}, {3,1}, {3,2}, {3,3}, {3,4}, {2,4}, {0,4} };

	SetWindowPos(controls.at((int)ctrlS::VIEW), NULL, 10, BtnHeight / 2 - 8, WndWidth - 20, 16, SWP_NOZORDER);


	for (int i{ 1 }; i < (int)controls.size(); ++i) {
		// for each control, use the size system to resize to the appropriate shape. skip 0, for the data. 
		SetWindowPos(controls.at(i), NULL, controlPos.at(i).first * BtnWidth, controlPos.at(i).second * BtnHeight, BtnWidth, BtnHeight, SWP_NOZORDER);
	}




	return true;
}

bool resetViewBox(std::wstring msg, HWND hWnd) {

	RECT rect;
	GetClientRect(controls.at((int)ctrlS::VIEW), &rect);
	InvalidateRect(controls.at((int)ctrlS::VIEW), &rect, TRUE);
	MapWindowPoints(controls.at((int)ctrlS::VIEW), hWnd, (POINT*)&rect, 2);
	RedrawWindow(hWnd, &rect, NULL, RDW_ERASE | RDW_INVALIDATE);

	size_t remove{ 0 };

	for (size_t i{ msg.size() - 1}; i >= 0; --i) {
		// for each value from end to start, check for zeros until we hit ., then stop

		if (msg.at(i) != '0' && msg.at(i) != '.') {
			// remove this. we need to keep this digit as well, it is relevent. 
			remove = i + 1;
			break;
		}
	}

	msg.erase(remove, msg.size() - remove);

	//remove = 3;

	std::wstring finalMsg = msg.substr(0, remove);

	SetWindowText(controls.at((int)ctrlS::VIEW), finalMsg.c_str());
	SetFocus(hWnd); // to allow continues keyboard use after button pres.

	return true;

}