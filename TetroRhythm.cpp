// TetroRythm.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Initilize Masterclass and window. Start game
#pragma comment(lib,"Shell32.lib") 
#pragma comment(lib,"User32.lib") 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <filesystem>

#include "Enums.h"
#include "MasterClass.h"

using namespace std;
using namespace sf;

string importedPath = "BeatMaps/Tetris_theme";

LONG_PTR originalsfmlcallback = 0x0;

LRESULT CALLBACK dragdropfileCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DROPFILES)
	{
		HDROP hdrop = reinterpret_cast<HDROP>(wParam);
		POINT p;
		p.x = 0;
		p.y = 0;
		if (DragQueryPoint(hdrop, &p))
			std::printf("Point is %d, %d\n", p.x, p.y);
		else
			std::cout << "Failed to get point" << std::endl;

		const UINT filescount = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		for (UINT i = 0; i < filescount; ++i)
		{
			const UINT bufsize = DragQueryFile(hdrop, i, NULL, 0);
			std::wstring str;
			str.resize(bufsize + 1);
			if (DragQueryFile(hdrop, i, &str[0], bufsize + 1))
			{
				std::string stdstr;
				sf::Utf8::fromWide(str.begin(), str.end(), std::back_inserter(stdstr));
				std::cout << stdstr << std::endl;
				std::filesystem::path a = stdstr;
				if (filesystem::is_directory(a) && filesystem::exists(a))
				{
					cout << filesystem::absolute(a).string() << endl;
					importedPath = filesystem::absolute(a).string();

				}
			}
		}
		DragFinish(hdrop);
		std::cout << "-------------" << std::endl;
	}//if WM_DROPFILES
	return CallWindowProcW(reinterpret_cast<WNDPROC>(originalsfmlcallback), handle, message, wParam, lParam);
}

int main()
{

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	// randomize init
	srand(static_cast<unsigned int> (time(NULL)));


	RenderWindow window(sf::VideoMode(1536, 864), "TetroRhythm", Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::View view(FloatRect(0.f, 0.f, 2048.f, 1152.f));
	window.setView(view);

	Image icon;
	icon.loadFromFile("Images/logo.png");
	window.setIcon(32, 32, icon.getPixelsPtr());

	HWND handle = window.getSystemHandle();
	DragAcceptFiles(handle, TRUE);
	originalsfmlcallback = SetWindowLongPtrW(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(dragdropfileCallback));


	MasterClass gameMC(window);
	gameMC.run();
	return 0;
}


 