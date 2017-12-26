#ifndef ADVANCED_H_
#define ADVANCED_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Image.h"
#include "Constants.h"
#include "FileIO.h"

/* add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);
unsigned char ChangeCenterPixelR(IMAGE *m, int i, int j);
unsigned char ChangeCenterPixelG(IMAGE *m, int i, int j);
unsigned char ChangeCenterPixelB(IMAGE *m, int i, int j);

/* Helper function to change pixels in Sharpen */
//int ChangeCenterPixel(unsigned char P[WIDTH][HEIGHT], int i, int j);

/* posterize the image */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

/* Helper for bit manipulation */
unsigned int BitManipulation(unsigned int bits, unsigned char pixelValue);

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount);

/* Helper Function for Blur */
unsigned int BlurRight(int BlurAmount, IMAGE* image, unsigned char *pixelPointer, unsigned i, unsigned j); 

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H);

IMAGE *Resize(IMAGE *image, int percentage);

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image);

#endif
