#include <X11/Xlib.h>
#include <stdio.h>
#include <err.h>
int main(void) {
	Display *dsp = XCreateDisplay(NULL);
	int scr;
	Window root;
	if (!dsp) {
		err(1, "Faulty display pointer!");
	}
	
	

 

	return 0;

}