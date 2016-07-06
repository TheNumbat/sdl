
#include "sdl.h"

int main() {
	SDL win("hello",640,480);
	
	rect r(-5,-5,10,10,false);

	win.drawRect(r);
	win.show();

	system("pause");

	win.setZoom(50);
	win.toggleAxes();

	win.redraw();
	win.show();

	system("pause");

	win.clear();
	win.toggleAxes();
	win.setZoom(5);
	win.setColor(0,0,0,255);
	win.drawPoint(point(1,1));
	win.redraw();
	win.show();

	system("pause");

	return 0;	
}
