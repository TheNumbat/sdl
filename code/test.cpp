
#include "sdl.h"

#include <stack>
#include <queue>

const int SIZE = 100;

SDL win("test",640,480);
float zoom = win.getZoom();

bool** region;

void floodfill4_rec(int x, int y) {

	region[x][y] = true;

	win.setColor(0,0,255,255);
	win.drawRect(rect(2*(x-(SIZE/2))/zoom,2*(y-(SIZE/2))/zoom,zoom/(SIZE/2),zoom/(SIZE/2),true));
	win.show();

	// change the order of these to change how the fill progresses
	if(x > 0 && !region[x-1][y]) floodfill4_rec(x-1,y);
	if (y > 0 && !region[x][y-1]) floodfill4_rec(x,y-1);
	if(x < SIZE - 1 && !region[x+1][y]) floodfill4_rec(x+1,y);
	if (y < SIZE - 1 && !region[x][y+1]) floodfill4_rec(x,y+1);
}

void floodfill8_rec(int x, int y) {

	region[x][y] = true;

	win.setColor(0,0,255,255);
	win.drawRect(rect(2*(x-(SIZE/2))/zoom,2*(y-(SIZE/2))/zoom,zoom/(SIZE/2),zoom/(SIZE/2),true));
	win.show();

	// change the order of these to change how the fill progresses
	if(x > 0 && y > 0 && !region[x-1][y-1]) floodfill8_rec(x-1,y-1);
	if (y > 0 && !region[x][y-1]) floodfill8_rec(x, y - 1);
	if(x < SIZE - 1 && y > 0 && !region[x+1][y-1]) floodfill8_rec(x+1,y-1);

	if(x > 0 && !region[x-1][y]) floodfill8_rec(x-1,y);
	if(x < SIZE - 1 && !region[x+1][y]) floodfill8_rec(x+1,y);

	if(x > 0 && y < SIZE - 1 && !region[x-1][y+1]) floodfill8_rec(x-1,y+1);
	if (y < SIZE - 1 && !region[x][y+1]) floodfill8_rec(x, y + 1);
	if(x < SIZE - 1 && y < SIZE - 1 && !region[x+1][y+1]) floodfill8_rec(x+1,y+1);
}

void floodfill4_stack(int x, int y) {

	struct pt {
		pt(int _x, int _y) {x=_x;y=_y;}
		int x, y;
	};
	std::stack<pt> st;
	region[x][y] = true;
	st.push(pt(x,y));
	
	while(!st.empty()) {
		pt point = st.top();
		st.pop();

		win.setColor(0,0,255,255);
		win.drawRect(rect(2*(point.x-(SIZE/2))/zoom,2*(point.y-(SIZE/2))/zoom,zoom/(SIZE/2),zoom/(SIZE/2),true));
		win.show();

		if(point.x > 0 && !region[point.x-1][point.y]) {
			region[point.x-1][point.y] = true;
			st.push(pt(point.x-1,point.y));
		}
		if(point.y > 0 && !region[point.x][point.y - 1]) {
			region[point.x][point.y-1] = true;
			st.push(pt(point.x,point.y-1));
		}
		if(point.x < SIZE - 1 && !region[point.x+1][point.y]) {
			region[point.x+1][point.y] = true;
			st.push(pt(point.x+1,point.y));
		}
		if(point.y < SIZE - 1 && !region[point.x][point.y + 1]) {
			region[point.x][point.y+1] = true;
			st.push(pt(point.x,point.y+1));
		}
	}
}

void floodfill4_queue(int x, int y) {

	struct pt {
		pt(int _x, int _y) {x=_x;y=_y;}
		int x, y;
	};
	std::queue<pt> qu;
	region[x][y] = true;
	qu.push(pt(x,y));
	
	while(!qu.empty()) {
		pt point = qu.front();
		qu.pop();

		win.setColor(0,0,255,255);
		win.drawRect(rect(2*(point.x-(SIZE/2))/zoom,2*(point.y-(SIZE/2))/zoom,zoom/(SIZE/2),zoom/(SIZE/2),true));
		win.show();

		if(point.x > 0 && !region[point.x-1][point.y]) {
			region[point.x-1][point.y] = true;
			qu.push(pt(point.x-1,point.y));
		}
		if(point.y > 0 && !region[point.x][point.y - 1]) {
			region[point.x][point.y-1] = true;
			qu.push(pt(point.x,point.y-1));
		}
		if(point.x < SIZE - 1 && !region[point.x+1][point.y]) {
			region[point.x+1][point.y] = true;
			qu.push(pt(point.x+1,point.y));
		}
		if(point.y < SIZE - 1 && !region[point.x][point.y + 1]) {
			region[point.x][point.y+1] = true;
			qu.push(pt(point.x,point.y+1));
		}
	}
}

void clearRegion() {
	for(int i = 0; i < SIZE; i++)
		memset(region[i],0,sizeof(bool)*SIZE);
}

int main() {
	win.toggleAxes();
	win.redraw();

	region = new bool*[SIZE];
	for(int i = 0; i < SIZE; i++)
		region[i] = new bool[SIZE]();

	floodfill4_rec(SIZE/2,SIZE/2);
	win.clear();
	clearRegion();

	if(!win.updateEvents()) {
		return 0;
	}

	floodfill8_rec(SIZE/2,SIZE/2);
	win.clear();
	clearRegion();

	if(!win.updateEvents()) {
		return 0;
	}
	
	floodfill4_stack(SIZE/2,SIZE/2);
	win.clear();
	clearRegion();
	
	if(!win.updateEvents()) {
		return 0;
	}

	floodfill4_queue(SIZE/2,SIZE/2);
	win.clear();
	clearRegion();

	while(win.updateEvents());

	for(int i = 0; i < SIZE; i++)
		delete[] region[i];
	delete[] region;
}
