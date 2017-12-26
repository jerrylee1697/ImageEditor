#ifndef DIPS_H_
#define DIPS_H

#include "Constants.h"
#include "Image.h"

IMAGE *BlackNWhite(IMAGE *image);

IMAGE *Negative(IMAGE *image);

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);


/* Helper Functions*/
    unsigned char ChangeCenterR(IMAGE *m, int i, int j);
    unsigned char ChangeCenterR(IMAGE *m, int i, int j);
    unsigned char ChangeCenterR(IMAGE *m, int i, int j); 

IMAGE *Edge(IMAGE *image);

IMAGE *VFlip(IMAGE *image);

IMAGE *VMirror(IMAGE *image);

IMAGE *AddBorder(IMAGE *image, char *color, int border_width);

IMAGE *Shuffle(IMAGE *image);


/* change color image to black & white */
//void *BlackNWhite(IMAGE *image);

/* reverse image color */
//void *Negative(IMAGE *image);

/* color filter */
//void *ColorFilter(IMAGE *image);

/* edge detection */
//void *Edge(IMAGE *image);

/* Shuffle the image */
//void *Shuffle(IMAGE *image);

/* flip image horizontally */
//void *HFlip(IMAGE *image);

/* mirror image vertically */
//void *VMirror(IMAGE *image);

/* flip image vertically */
//void *VFlip(IMAGE *image);

/* add border */
//void *AddBorder(IMAGE *image);

#endif
