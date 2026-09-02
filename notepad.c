/*

LOTS OF IMPROVEMENTS NEED TO BE MADE:
1. Using tree or some sort of data structure to simulate Ctrl + Z
2. Memory safety needs to be made better
3. Readability is not very good
4. Dynamic memory allocation for array buffers when rendering data
*/



#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <err.h>
#include <ctype.h>

#define X 0
#define Y 0
#define HEIGHT 500
#define WIDTH 500
#define BORDER_WIDTH 100

#define MAX_LEN 1024
#define CR_PX_SIZE 10

int main(void) {

	char buf[MAX_LEN] = {0};
	size_t len = 0;

	Display *dsp = XOpenDisplay(NULL);
	int scr;
	Window root;
	if (!dsp) {
		err(1, "Faulty display pointer");
	}
	char c;	
	scr = DefaultScreen(dsp);
	root = RootWindow(dsp, scr);

	Window win = XCreateSimpleWindow(dsp, root, 0, 0, 500, 500, 100, BlackPixel(dsp, scr), WhitePixel(dsp, scr));
	XMapWindow(dsp, win);
	size_t numLines = 0;	
	GC gc = XCreateGC(dsp, win, 0, NULL); //Default values 0 and NULL for used graphics context
	XSelectInput(dsp, win, ExposureMask | KeyPressMask);
	XEvent ev;
	KeySym keysym;
	char *tmp = buf;
	while (true) {
		XNextEvent(dsp, &ev);
		if (ev.type == Expose) {
			XClearWindow(dsp, win);
			for (int i = 0; i <= numLines; i++) {
				XDrawString(dsp, win, gc, 10, 50+i*CR_PX_SIZE, tmp, len);
				tmp += strlen(tmp) + 1;
			}

		} else if (ev.type == KeyPress) {
				XLookupString(&ev.xkey, &c, 1, &keysym, NULL);
				if (c == '\b') {
					buf[len--] = 0;
				} else if (len >= MAX_LEN - 1) {	
					for (int i = 0; i < MAX_LEN-1; i++) {
						buf[i] = 0;
					}
					len = 0;
					numLines = 0;
				} else if (keysym == XK_Return || keysym == XK_KP_Enter) {
						len++;
						numLines++;
				} else if (isalnum(c) || isspace(c)) {
				buf[len++] = c; 
				}
				XClearWindow(dsp, win);
				size_t tmpLen;
				tmp = buf;
				for (int i = 0; i <= numLines; i++) {
					tmpLen = strlen(tmp);
					XDrawString(dsp, win, gc, 10, 50+i*CR_PX_SIZE, tmp, tmpLen);
					tmp += tmpLen + 1;
				}
		}

	}

	XUnmapWindow(dsp, win);
	XUnmapWindow(dsp, root);	
	XDestroyWindow(dsp, win);
	XDestroyWindow(dsp, root);


	return 0;

}
