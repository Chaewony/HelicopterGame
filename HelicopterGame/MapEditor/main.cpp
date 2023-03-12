#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Position.h"
#include "Input.h"
#include "Panel.h"
#include "HelicopterEditor.h"

using namespace std;



int main()
{
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto helicopter = new HelicopterEditor;

	while (helicopter->isGameOver() == false)
	{
		screen->clear();

		input->readInputs();

		//helicopter->internalUpdate();
		//helicopter->updatePos(false); // the location of the root game object won't be changed.
		//helicopter->internalDraw();

		helicopter->update();

		screen->render();

		Sleep(100);
	}

	delete helicopter;

	return 0;
}