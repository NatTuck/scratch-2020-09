
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <map>
#include <utility>
#include <deque>
#include <vector>
#include <math.h>

#include "viz.hh"

using namespace std;

typedef pair<long,long> posn;

map<posn, long> grid;
deque<posn> tasks;

// Start at 0,0
// Traverse the grid out to neighboring cells
// Color in cells as we go.

void
color_cell(posn pp, long vv)
{
    viz_color_cell(pp.first, pp.second, vv);
}

vector<posn>
neibs(posn aa)
{
  long xx = aa.first;
  long yy = aa.second;

  vector<posn> ys;
  ys.push_back(make_pair(xx, yy+1));
  ys.push_back(make_pair(xx, yy-1));
  ys.push_back(make_pair(xx+1, yy));
  ys.push_back(make_pair(xx-1, yy));
  return ys;
}

string
show(posn xx)
{
  stringstream buf;
  buf << xx.first;
  buf << ",";
  buf << xx.second;
  return buf.str();
}

bool
posn_seen(posn xx)
{
  if (grid.find(xx) != grid.end()) {
     return true;
  }

  for (auto yy : tasks) {
     if (xx == yy) {
       return true;
     }
  } 

  return false;
}

void
on_click()
{
    cout << "click" << endl;

    if (!tasks.empty()) {
      posn next_cell = tasks.front();
      tasks.pop_front();
      cout << "next: " << show(next_cell) << endl;
      grid[next_cell] = 1;
      color_cell(next_cell, 255);

      auto ns = neibs(next_cell);
      for (auto xx : ns) {
         cout << "show? " << show(xx) << " ";
         if (!posn_seen(xx)) {
            tasks.push_back(xx);
            cout << "yes" << endl;
         }
         else {
            cout << "no" << endl;
         }
      }
    }
}


int
main(int argc, char* argv[])
{
    tasks.push_back(make_pair(0, 0));
    return viz_run(argc, argv);
}
