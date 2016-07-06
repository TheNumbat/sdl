
#include "sdl.h"

int main() {
	SDL win("hello",640,480);
	
	rect r = {-5,-5,10,10};

	win.drawAxes();
	win.drawFillRect(r);
	win.render();

	win.setZoom(10);
	
	win.drawAxes();
	win.drawFillRect(r);
	win.render();

	system("pause");
}
