#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "types.h"



void camera_init(camera **c,double angle,double aspect_ratio,double *lookfrom,double *lookat,double *vup,double aperture,double focus_dist);
void clear_camera(camera **cam);
#endif