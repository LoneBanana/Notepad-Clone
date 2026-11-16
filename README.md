# Notepad-Clone

A small Notepad-style text editor and a paint program written in C on top of Xlib, plus the experiments that led up to them.

## Overview

This project is a test of the C and data structures skills I have built through self-study: write a Notepad clone with as much as possible done from scratch. The long-term goal is to go as low as practical, ideally including window creation and event handling, to understand how these pieces work under the hood.

Right now the windowing and input layer is Xlib (X11). On top of it there is a minimal text editor (`notepad.c`) and a simple paint program (`draw.c`). The `build-up/` folder holds smaller command-line programs written along the way.

## What's inside

- `notepad.c` - opens a 500x500 X11 window and draws typed text. Letters, digits, and whitespace are added to a fixed 1024-byte buffer, and Enter starts a new line. The window is redrawn on every key press, and the buffer is cleared when it fills up.
- `draw.c` - a basic paint program. Dragging with the left mouse button draws in black, dragging with another button draws in white (an eraser), and Escape closes the window.
- `Makefile` - a pattern rule that compiles and links any `X.c` against Xlib into an executable named `X.o`.
- `build-up/cat-clone/cat-clone.c` - a clone of `cat` that prints a file, or standard input when no file is given.
- `build-up/min-editor/min-editor.c` - a line-based editor: it asks which line of a file to edit and overwrites that line with input from the terminal. `og` and `text` are a sample file before and after an edit.
- `build-up/testing/` - short experiments with temporary files (`mkstemp`), `snprintf` with `system`, pointer arithmetic, and reading input. `tmp-files-testing.c` is the prototype of a "compile and run C from the terminal" tool.
- `.vscode/c_cpp_properties.json` - editor settings that add the XQuartz include path.

## Building and running

The X11 programs need an X server and Xlib headers. The Makefile expects them under `/opt/X11`, which is where XQuartz installs them on macOS.

```sh
make notepad.o
./notepad.o

make draw.o
./draw.o
```

Because of how the Makefile rule is written, the `.o` files are finished executables, not object files.

The `build-up/` programs are single files with no dependencies, for example:

```sh
cc build-up/cat-clone/cat-clone.c -o cat-clone
./cat-clone README.md
```

## Status

Both X11 programs are basic. In the editor, Backspace only moves the insert position back: the old character stays on screen until it is typed over. There is no cursor movement, scrolling, file open or save, or undo, and no quit key (stop it with Ctrl+C in the terminal). The comment at the top of `notepad.c` lists the planned improvements: undo (Ctrl+Z) backed by a data structure, better memory safety, more readable code, and dynamically sized buffers. Replacing Xlib with home-made windowing and event handling is still a goal.

## Tech

C, Xlib (X11 / XQuartz), Make.
