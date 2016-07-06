
#ifdef SDL_EXPORT
#define SDL_API __declspec(dllexport)
#else
#define SDL_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

struct shape {virtual ~shape() {}};
struct point : shape {
	float x; float y;
	point(point& p) {x=p.x;y=p.y;}
	point(float _x, float _y) {x=_x;y=_y;}
};
struct rect : shape {
	float x; float y; float w; float h; 
	bool filled;
	rect(rect& r) {x=r.x;y=r.y;w=r.w;h=r.h;filled=r.filled;}
	rect(float _x,float _y,float _w,float _h,bool _f) {x=_x;y=_y;w=_w;h=_h;filled=_f;}
};
struct line : shape {
	float x1; float y1; float x2; float y2; 
	line(line& l) {x1=l.x1;y1=l.y1;x2=l.x2;y2=l.y2;}
	line(float _x1,float _y1,float _x2,float _y2) {x1=_x1;y1=_y1;x2=_x2;y2=_y2;}
};
typedef unsigned char uint8;

class SDL_API SDL {
public:
	SDL(std::string wName, int wW, int wH);
	~SDL();

	void setZoom(float z);
	float getZoom();

	void clear();
	void show();
	void toggleAxes();
	void redraw();
	void updateEvents();

	void setColor(uint8 R, uint8 G, uint8 B, uint8 A);
	
	void drawLine(line l);

	void drawPoint(point p);
	void drawPoints(std::vector<point> points);
	
	void drawRect(rect r);
	void drawRects(std::vector<rect> rects);

private:
	void drawAxes();
	bool axes;
	void* win;
	void* renderer;
	float zoom;
	int w, h;
	std::vector<shape*> shapes;
};
