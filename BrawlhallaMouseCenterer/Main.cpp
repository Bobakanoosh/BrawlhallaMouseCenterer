#include <windows.h>
#include <chrono>
#include <thread>
#include <iostream>

#define WINDOW_CLASS "ApolloRuntimeContentWindow"

int main() 
{
	bool enabled = false;
	while (true) 
	{
		if (GetAsyncKeyState(VK_F5))
		{
			enabled = !enabled;
			printf("%s\n", enabled ? "enabled" : "disabled");

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		if (enabled)
		{
			HWND window = FindWindowA(WINDOW_CLASS, nullptr);
			if (!window)
			{
				printf("Window not open\n");
				std::this_thread::sleep_for(std::chrono::seconds(5));
				continue;
			}

			if (window != GetForegroundWindow())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				continue;
			}

			RECT rect;
			GetWindowRect(window, &rect);

			const int mouseX = rect.left + 50;
			const int mouseY = rect.top + 500;

			SetCursorPos(mouseX, mouseY);
		}
	}

	return 0;
}