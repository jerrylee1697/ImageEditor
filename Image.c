#include "Image.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y) {
    int oneDimensionIndex = y * image->W + x;
    return *(image->R + oneDimensionIndex);
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y) {
    int oneDimensionIndex = y * image->W + x;
    return *(image->G + oneDimensionIndex);
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y) {
    int oneDimensionIndex = y * image->W + x;
    return *(image->B + oneDimensionIndex);
} 

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r) {
    int oneDimensionIndex = y * image->W + x;
    *(image->R + oneDimensionIndex) = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g) {
    int oneDimensionIndex = y * image->W + x;
    *(image->G + oneDimensionIndex) = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b) {
    int oneDimensionIndex = y * image->W + x;
    *(image->B + oneDimensionIndex) = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height) {
    IMAGE *image;
    image = malloc(sizeof(IMAGE) + 1);
    if (!image) {
        perror("Out of memory! Aborting\n");
        return image;
    }
    image->R = malloc(sizeof(unsigned char) * Width * Height + 1);
    image->G = malloc(sizeof(unsigned char) * Width * Height + 1);
    image->B = malloc(sizeof(unsigned char) * Width * Height + 1);
    image->W = Width;
    image->H = Height;   
    return image;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image) {
    assert(image);
    free(image->R);
    image->R = NULL;
    free(image->G);
    image->G = NULL;
    free(image->B);
    image->B = NULL;
    free(image);
    image = NULL;
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image) {
    assert(image);
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image) {
    assert(image);
    return image->H;
}


