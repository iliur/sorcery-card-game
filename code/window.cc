#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <cstring>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[6][10]={"white", "black", "red", "green", "blue", "lightblue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawRectangle(int x, int y, int width, int height, int colour) {
  XDrawRectangle(d, w, gc, x, y, width, height);
}
void Xwindow::drawLine(int x1, int y1, int x2, int y2) {
  XDrawLine(d, w, gc, x1, y1, x2, y2);
}

void Xwindow::drawSorcery(int x, int y) {
  XFontStruct *fontInfo = XLoadQueryFont(d, "-tiro-plantagenet cherokee-medium-r-normal--0-0-0-0-p-0-iso10646-1"); //-tiro-plantagenet cherokee-medium-r-normal--0-0-0-0-p-0-iso10646-1
  //-schumacher-clean-medium-r-normal--8-80-75-75-c-80-iso646.1991-irv
  XSetFont(d, gc, fontInfo->fid);
  XDrawString(d, w, gc, x, y, "SORCERY", 7);
}


void Xwindow::drawWrappedString(int x, int y, int maxWidth, string msg) {
  // drawWrappedText(d, w, gc, fontInfo, msg.c_str(), x, y, maxWidth);
  int newWidth = maxWidth / 6.5;
  int numLine = 0;
  int len = msg.length();
  while (len > newWidth) {
    string tempString = msg.substr(0, newWidth);
    msg = msg.erase(0, newWidth);
    drawString(x, y + numLine * 20, tempString);
    len -= newWidth;
    numLine++;
  }
  drawString(x, y + numLine * 20, msg);

}
