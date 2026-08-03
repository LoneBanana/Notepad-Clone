#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdbool.h>

#define X 500
#define Y 500
#define WIDTH 500
#define HEIGHT 500
#define BORDER_WIDTH 100


int main(void) {
    Display *dsp;
    Window root;
    int scr;

    dsp = XOpenDisplay(NULL);
    if (!dsp) {
        err(1, "Faulty dsp Pointer");
        exit(1);
        }
    
    scr = DefaultScreen(dsp);
    root = RootWindow(dsp, scr);

    Window win = XCreateSimpleWindow(dsp, root, X, Y, WIDTH, HEIGHT, BORDER_WIDTH, BlackPixel(dsp, scr), WhitePixel(dsp, scr));
    XMapWindow(dsp, win);
    
    XSelectInput(dsp, win, ButtonMotionMask | KeyPressMask); 
    XEvent ev;


    //Look into if there are alternative ways 
    

    GC gc = XCreateGC(dsp, win, 0, NULL);
    
    while (true) {
        XNextEvent(dsp, &ev);
        if (ev.type == MotionNotify) {
            if (ev.xmotion.state & Button1Mask) {
                 XSetForeground(dsp, gc, BlackPixel(dsp, scr));
            } else {
                XSetForeground(dsp, gc, WhitePixel(dsp, scr));
            }
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                XDrawPoint(dsp, win, gc, ev.xmotion.x - i, ev.xmotion.y-j);
                XDrawPoint(dsp, win, gc, ev.xmotion.x + i, ev.xmotion.y-j);
                XDrawPoint(dsp, win, gc, ev.xmotion.x - i, ev.xmotion.y+j);
                XDrawPoint(dsp, win, gc, ev.xmotion.x + i, ev.xmotion.y+j);
                }
            }
        } else if (ev.type == KeyPress) {
            KeySym key = XLookupKeysym(&ev.xkey, 0);
            if (key == XK_Escape) {
                break;
            }
        }

        XFlush(dsp); //Check if this may cause an error later
    } 
    
    XUnmapWindow(dsp, win);
    XFreeGC(dsp, gc);
    XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);
    return 0;
    }