#include <windows.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

constexpr auto WINDOW_CLASS = "ApolloRuntimeContentWindow";
constexpr auto MOUSE_POSITION_BUFFER = 40;
constexpr auto WINDOW_UPDATE_INTERVAL = std::chrono::milliseconds(100);
constexpr auto WINDOW_SEEK_INTERVAL = std::chrono::seconds(5);

int main() 
{
	auto lastWindowTime = std::chrono::steady_clock::now();
	HWND window = NULL;

	printf("Cursor locked inside brawlhalla");

	while (true) 
	{
		if (window != GetForegroundWindow())
		{
			auto currentWindowTime = std::chrono::steady_clock::now();
			if ((currentWindowTime - lastWindowTime).count() >= WINDOW_UPDATE_INTERVAL.count()) 
			{
				lastWindowTime = currentWindowTime;
				window = FindWindowA(WINDOW_CLASS, nullptr);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		if (!window)
		{
			printf("Window not open\n");
			std::this_thread::sleep_for(WINDOW_SEEK_INTERVAL);
			continue;
		}

		RECT rect;
		GetWindowRect(window, &rect);

		POINT point;
		GetCursorPos(&point);

		const int mouseX = std::clamp(point.x, rect.left + MOUSE_POSITION_BUFFER, rect.right - MOUSE_POSITION_BUFFER);
		const int mouseY = std::clamp(point.y, rect.top + MOUSE_POSITION_BUFFER, rect.bottom - MOUSE_POSITION_BUFFER);

		SetCursorPos(mouseX, mouseY);
	}

	return 0;
}