#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=1500, int height=850);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, LightBlue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawRectangle(int x, int y, int width, int height, int colour=Black);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawWrappedString(int x, int y, int maxWidth, std::string msg);
  void drawSorcery(int x, int y);

};

#endif
