
#include "sdl.h"
#include <SDL.h>
#include <cmath>

SDL::SDL(std::string wName, int wW, int wH) {
	win = SDL_CreateWindow(wName.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,wW,wH,SDL_WINDOW_SHOWN);
	w = wW;
	h = wH;
	if(win) {
		renderer = SDL_CreateRenderer((SDL_Window*)win,-1,SDL_RENDERER_ACCELERATED);
		if(renderer) {
			zoom = 10;
			clear();
		}
		else {
			SDL_DestroyWindow((SDL_Window*)win);	
		}
	}
}

SDL::~SDL() {
	SDL_DestroyWindow((SDL_Window*)win);
}

void SDL::setZoom(float z) {
	zoom = z;
	clear(); // otherwise need to trach all shapes - should do
}

float SDL::getZoom() {
	return zoom;
}

void SDL::clear() {
	SDL_RenderClear((SDL_Renderer*)renderer);
	setColor(255,255,255,255);
	rect r = {-zoom,-zoom,zoom*2,zoom*2};
	drawFillRect(r);
}

void SDL::render() {
	SDL_RenderPresent((SDL_Renderer*)renderer);
}

void SDL::drawAxes() {
	setColor(0,0,0,255);

	line l;
	l = {0,zoom,0,-zoom};
	drawLine(l);
	l = {-zoom,0,zoom,0};
	drawLine(l);
}

void SDL::setColor(uint8 R, uint8 G, uint8 B, uint8 A) {
	SDL_SetRenderDrawColor((SDL_Renderer*)renderer,R,G,B,A);
}
	
void SDL::drawLine(line l) {
	SDL_RenderDrawLine((SDL_Renderer*)renderer,std::round(l.x1*(w/2)/zoom) + (w/2),std::round(l.y1*(h/2)/zoom) + (h/2),
						std::round(l.x2*(w/2)/zoom) + (w/2),std::round(l.y2*(h/2)/zoom) + (h/2));
}

void SDL::drawPoint(point p) {

}

void SDL::drawPoints(std::vector<point> points) {

}
	
void SDL::drawRect(rect r) {

}

void SDL::drawRects(std::vector<rect> rects) {

}

void SDL::drawFillRect(rect r) {
	SDL_Rect sr;
	sr.x = std::round(r.x*(w/2)/zoom) + (w/2);
	sr.y = std::round(r.y*(h/2)/zoom) + (h/2);
	sr.w = std::round(r.w*(w/2)/zoom);
	sr.h = std::round(r.h*(h/2)/zoom);
	SDL_RenderFillRect((SDL_Renderer*)renderer,&sr);
}

void SDL::drawFillRects(std::vector<rect> rects) {

}
