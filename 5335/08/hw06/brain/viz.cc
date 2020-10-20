/*
A simple example of using the gfx library.
CSE 20211
9/7/2011
by Prof. Thain

Modified by Nat Tuck, Oct 2020
*/

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <mutex>

extern "C" {
#include "gfx.h"
}

using namespace std;
typedef lock_guard<mutex> guard;

mutex mx;
static int viz_init = 0;

int 
viz_hit(float range, float angle)
{
  guard _gg(mx);
  if (!viz_init) {
    puts("viz skip");
    return 0;
  }

  puts("viz hit");

  int ww = 500;
  int hh = 500;
  int dd = min(ww, hh) / 2;

  angle += (M_PI / 2.0);
  float dx = 0.5 * range * cos(angle);
  float dy = 0.5 * range * sin(angle);

  int xx = dd + (dd*dx);
  int yy = hh - (dd + (dd*dy));

  gfx_point(xx, yy);

  return 0;
}

void 
viz_run()
{
  int ysize = 500;
  int xsize = 500;

  char c;

  // Open a new window for drawing.
  gfx_open(xsize,ysize,"Example Graphics Program");

  // Set the current drawing color to green.
  gfx_color(0,200,100);

	// Draw a triangle on the screen.
	gfx_line(100,100,200,100);
	gfx_line(200,100,150,150);
	gfx_line(150,150,100,100);

  {
    guard _gg(mx);
    viz_init = 1;
  }
  
	while(1) {
		// Wait for the user to press a character.
		c = gfx_poll();

		// Quit if it is the letter q.
		if(c=='q') break;
    usleep(50000);
	}
}
