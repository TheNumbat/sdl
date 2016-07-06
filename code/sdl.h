
#ifdef SDL_EXPORT
#define SDL_API __declspec(dllexport)
#else
#define SDL_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

typedef struct {float x; float y;} point;
typedef struct {float x; float y; float w; float h;} rect;
typedef struct {float x1; float y1; float x2; float y2;} line;
typedef unsigned char uint8;

class SDL_API SDL {
public:
	SDL(std::string wName, int wW, int wH);
	~SDL();

	void setZoom(float z);
	float getZoom();

	void clear();
	void render();
	void drawAxes();

	void setColor(uint8 R, uint8 G, uint8 B, uint8 A);
	
	void drawLine(line l);

	void drawPoint(point p);
	void drawPoints(std::vector<point> points);
	
	void drawRect(rect r);
	void drawRects(std::vector<rect> rects);
	void drawFillRect(rect r);
	void drawFillRects(std::vector<rect> rects);

private:
	void* win;
	void* renderer;
	float zoom;
	int w, h;
};
