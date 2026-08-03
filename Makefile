CC = cc
CFLAGS = -Wall -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11

%.o:%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
