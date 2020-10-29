#ifndef VIZ_H
#define VIZ_H

int viz_run(int argc, char **argv);
int viz_hit(float range, float angle);
int viz_color_cell(long xx, long yy, long vv);
int viz_simulate_click();

#endif
