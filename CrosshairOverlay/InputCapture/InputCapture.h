#pragma once

#include <unordered_map>
#include <string>
#include <vector>


#include <Windows.h>

class InputCapture {
public:
	
	InputCapture();

	~InputCapture();

	void Initialize();

    void Update() {
        
    };
	
    bool IsKeyPressed(int key) {
        
        for (int key : keyCodes) {
            if (GetAsyncKeyState(key) & 0x8000) {
                // Do smt
            };
        };
    };

    bool IsMousePressed(int button) {
        
        for (int button : buttonCodes) {
            if (GetAsyncKeyState(button) & 0x8000) {
                // Do smt
            };
        };
    };

private:
    // Keyboard
    std::vector<int> keyCodes = {
        // Letters (A-Z)
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 
        78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,

        // Numbers (0-9)
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,

        // Modifier keys
        VK_CONTROL, VK_MENU, VK_SHIFT, VK_CAPITAL, VK_ESCAPE, VK_LWIN, VK_RWIN, VK_TAB, VK_BACK,
        VK_SPACE, VK_RETURN,

        // Navigation keys
        VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_HOME, VK_END, VK_PRIOR, VK_NEXT,

        // Function keys (F1-F12)
        VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,

        // Special keys
        VK_INSERT, VK_DELETE, VK_SNAPSHOT, VK_SCROLL, VK_NUMLOCK, VK_PAUSE
    };
    // Letters (A-Z) - Represented by ASCII values
    /*  65,  // 'A'
        66,  // 'B'
        67,  // 'C'
        68,  // 'D'
        69,  // 'E'
        70,  // 'F'
        71,  // 'G'
        72,  // 'H'
        73,  // 'I'
        74,  // 'J'
        75,  // 'K'
        76,  // 'L'
        77,  // 'M'
        78,  // 'N'
        79,  // 'O'
        80,  // 'P'
        81,  // 'Q'
        82,  // 'R'
        83,  // 'S'
        84,  // 'T'
        85,  // 'U'
        86,  // 'V'
        87,  // 'W'
        88,  // 'X'
        89,  // 'Y'
        90,  // 'Z'

        // Numbers (0-9) - Represented by ASCII values
        48,  // '0'
        49,  // '1'
        50,  // '2'
        51,  // '3'
        52,  // '4'
        53,  // '5'
        54,  // '6'
        55,  // '7'
        56,  // '8'
        57,  // '9'
    */

    // Mouse
    std::vector<int> buttonCodes = {
        // Mouse buttons
        VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_SCROLL  
    };

};