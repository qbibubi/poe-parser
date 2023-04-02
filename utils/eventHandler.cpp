#include "eventHandler.h"

// Constant values of key states
const bool shiftRestState = GetAsyncKeyState(VK_SHIFT) & 0x8000;
const bool leftMouseRestState= GetAsyncKeyState(VK_LBUTTON);

void EventHandler::currencyUsed() {
	bool leftMouseClicked = GetKeyState(VK_LBUTTON);
	bool shiftHeld = GetKeyState(VK_SHIFT) & 0x8000;

	if ((shiftHeld == shiftRestState) && (leftMouseClicked == leftMouseRestState)) {
		return;
	}

	copyItemData();
}

// Simulate CTRL + ALT + C
void EventHandler::copyItemData() {
	INPUT inputs[6] = {};
	ZeroMemory(inputs, sizeof(inputs));

	// Press CTRL
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_CONTROL;

	// Press ALT
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_MENU;

	// Press C
	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = 0x43;

	// Unpress C
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = 0x43;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	// Unpress ALT
	inputs[4].type = INPUT_KEYBOARD;
	inputs[4].ki.wVk = VK_MENU;
	inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

	// Unpress CTRL
	inputs[5].type = INPUT_KEYBOARD;
	inputs[5].ki.wVk = VK_CONTROL;
	inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(inputs));
	if (uSent != ARRAYSIZE(inputs)) {
		std::cout << "Sending input failed." << std::endl;
	}
}

std::string EventHandler::getClipboardData() {
	HANDLE clipboard;
	if (OpenClipboard(NULL)) {
		clipboard = GetClipboardData(CF_TEXT);
		std::string clipString = (char*)clipboard;
		return clipString;
	}

	return "";
}