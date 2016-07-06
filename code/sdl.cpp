
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
			axes = true;
			clear();
		}
		else {
			SDL_DestroyWindow((SDL_Window*)win);	
		}
	}
}

SDL::~SDL() {
	SDL_DestroyWindow((SDL_Window*)win);
	for(shape* s : shapes)
		delete s;
	shapes.clear();
}

void SDL::setZoom(float z) {
	zoom = z;
}

float SDL::getZoom() {
	return zoom;
}

void SDL::toggleAxes() {
	axes = !axes;
}

void SDL::redraw() {
	SDL_RenderClear((SDL_Renderer*)renderer);
	setColor(255,255,255,255);
	drawRect(rect(-zoom,-zoom,zoom*2,zoom*2,true));
	shapes.pop_back();
	
	if(axes) drawAxes();
	setColor(0,0,0,255);
	for(shape* s : shapes) {
		if(point* p = dynamic_cast<point*>(s)) drawPoint(*p);
		else if(line* l = dynamic_cast<line*>(s)) drawLine(*l);
		else if(rect* r = dynamic_cast<rect*>(s)) drawRect(*r);
		shapes.pop_back();
	}
}

void SDL::clear() {
	SDL_RenderClear((SDL_Renderer*)renderer);
	setColor(255,255,255,255);
	drawRect(rect(-zoom,-zoom,zoom*2,zoom*2,true));

	for(shape* s : shapes)
		delete s;
	shapes.clear();
	if(axes) drawAxes();
}

void SDL::show() {
	SDL_RenderPresent((SDL_Renderer*)renderer);
}

void SDL::drawAxes() {
	setColor(0,0,0,255);
	SDL_RenderDrawLine((SDL_Renderer*)renderer,w/2,0,w/2,h);
	SDL_RenderDrawLine((SDL_Renderer*)renderer,0,h/2,w,h/2);
}

void SDL::setColor(uint8 R, uint8 G, uint8 B, uint8 A) {
	SDL_SetRenderDrawColor((SDL_Renderer*)renderer,R,G,B,A);
}
	
void SDL::drawLine(line l) {
	shapes.push_back(new line(l));
	SDL_RenderDrawLine((SDL_Renderer*)renderer,std::round(l.x1*(w/2)/zoom) + (w/2),std::round(l.y1*(h/2)/zoom) + (h/2),
						std::round(l.x2*(w/2)/zoom) + (w/2),std::round(l.y2*(h/2)/zoom) + (h/2));
}

void SDL::drawPoint(point p) {
	shapes.push_back(new point(p));
	SDL_RenderDrawPoint((SDL_Renderer*)renderer,std::round(p.x*(w/2)/zoom) + (w/2),std::round(p.y*(h/2)/zoom) + (h/2));
}

void SDL::drawPoints(std::vector<point> points) {
	for(point p : points) {
		shapes.push_back(new point(p));
		drawPoint(p);
	}
}

void SDL::drawRect(rect r) {
	shapes.push_back(new rect(r));
	SDL_Rect sr;
	sr.x = std::round(r.x*(w/2)/zoom) + (w/2);
	sr.y = std::round(r.y*(h/2)/zoom) + (h/2);
	sr.w = std::round(r.w*(w/2)/zoom);
	sr.h = std::round(r.h*(h/2)/zoom);
	if(r.filled)
		SDL_RenderFillRect((SDL_Renderer*)renderer,&sr);
	else
		SDL_RenderDrawRect((SDL_Renderer*)renderer,&sr);
}

void SDL::drawRects(std::vector<rect> rects) {
	for(rect r : rects) { 
		shapes.push_back(new rect(r));
		drawRect(r);
	}
}
