#include "DIPs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//const int WIDTH = 600;		/* image width */
//const int HEIGHT = 400;		/* image height */



/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    int tmp;
    assert(image);
    
    int x, y;
    for (y = 0; y < ImageHeight(image); y++)
    {   
        for (x = 0; x < ImageWidth(image); x++) 
        {
            //int index = x + y * image->W;
            tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
            
            //tmp = (*(image->R + index) + *(image->G + index) + *(image->B + index)) / 3;
            //*(image->R + index) = *(image->G + index) = *(image->B + index) = tmp; 
        }
    }
    return image;
}

/* reverse image color */
IMAGE *Negative(IMAGE *image) {
    int x, y;
    assert(image);
    
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
            SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
            SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
            //*(image->R + x + y * image->W) = MAX_PIXEL - *(image->R + x + y * image->W); 
            //*(image->G + x + y * image->W) = MAX_PIXEL - *(image->G + x + y * image->W); 
            //*(image->B + x + y * image->W) = MAX_PIXEL - *(image->B + x + y * image->W);
        }
    }
    return image;
}

IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
    assert(image);
    
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_g = (replace_g > MAX_PIXEL)? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
    replace_b = (replace_b > MAX_PIXEL)? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;
    
    
    int x, y;
    for (y = 0; y < ImageHeight(image); y++){
        for (x = 0; x < ImageWidth(image); x++){
            //int index = x + y * image->W;
            if (abs(GetPixelR(image, x, y)) <= threshold &&
                abs(GetPixelG(image, x, y)) <= threshold &&
                abs(GetPixelB(image, x, y)) <= threshold) {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
            /*
            if (abs(*(image->R + index) - target_r) <= threshold && 
                abs(*(image->G + index) - target_g) <= threshold &&
                abs(*(image->B + index) - target_b) <= threshold) {
            *(image->R + index) = replace_r;
            *(image->G + index) = replace_g;
            *(image->B + index) = replace_b;
            }*/
        }
    }
    return image;
}
unsigned char ChangeCenterR(IMAGE *m, int i, int j) {
    int v = - GetPixelR(m, i - 1, j - 1) - GetPixelR(m, i, j - 1) - GetPixelR(m, i + 1, j - 1)
            - GetPixelR(m, i - 1, j) + 8 * GetPixelR(m, i, j)     - GetPixelR(m, i + 1, j)
            - GetPixelR(m, i - 1, j + 1) - GetPixelR(m, i, j + 1) - GetPixelR(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}
unsigned char ChangeCenterG(IMAGE *m, int i, int j) {
    int v = - GetPixelG(m, i - 1, j - 1) - GetPixelG(m, i, j - 1) - GetPixelG(m, i + 1, j - 1)
            - GetPixelG(m, i - 1, j) + 8 * GetPixelG(m, i, j)     - GetPixelG(m, i + 1, j)
            - GetPixelG(m, i - 1, j + 1) - GetPixelG(m, i, j + 1) - GetPixelG(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}
unsigned char ChangeCenterB(IMAGE *m, int i, int j) {
    int v = - GetPixelB(m, i - 1, j - 1) - GetPixelB(m, i, j - 1) - GetPixelB(m, i + 1, j - 1)
            - GetPixelB(m, i - 1, j) + 8 * GetPixelB(m, i, j)     - GetPixelB(m, i + 1, j)
            - GetPixelB(m, i - 1, j + 1) - GetPixelB(m, i, j + 1) - GetPixelB(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}

IMAGE *Edge(IMAGE *image){
    assert(image);
    IMAGE *copyImage = CreateImage(ImageWidth(image), ImageHeight(image));
    
    for (int i = 0; i < ImageWidth(image); ++i) {
        for (int j = 0; j < ImageHeight(image); ++j) {
            SetPixelR(copyImage, i, j, GetPixelR(image, i, j));
            SetPixelG(copyImage, i, j, GetPixelG(image, i, j));
            SetPixelB(copyImage, i, j, GetPixelB(image, i, j));
        }
    }

    for (int i = 1; i < ImageWidth(image) - 1; i++){
        for (int j = 1; j < ImageHeight(image) - 1; j++){
            SetPixelR(image, i, j, ChangeCenterR(copyImage, i, j));
            SetPixelG(image, i, j, ChangeCenterG(copyImage, i, j));
            SetPixelB(image, i, j, ChangeCenterB(copyImage, i, j));
        }
    }
    DeleteImage(copyImage);
    copyImage = NULL;
    
    /* set all four borders to 0 */
    for (int y = 0; y < ImageHeight(image); y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);
        SetPixelR(image, ImageWidth(image) - 1, y, 0);
        SetPixelG(image, ImageWidth(image) - 1, y, 0);
        SetPixelB(image, ImageWidth(image) - 1, y, 0);
    }
    for (int x = 0; x < ImageWidth(image); x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);
        SetPixelR(image, x, ImageHeight(image) - 1, 0);
        SetPixelG(image, x, ImageHeight(image) - 1, 0);
        SetPixelB(image, x, ImageHeight(image) - 1, 0);
    }
    return image;
}


/* flip image vertically */
IMAGE *VFlip(IMAGE *image) {
    assert(image);
    unsigned char   r, g, b;

    for (int y = 0; y < ImageHeight(image)/2; y++) {
        for (int x = 0; x < ImageWidth(image); x++) {
            r = GetPixelR(image, x, ImageHeight(image) - 1 - y);
            g = GetPixelG(image, x, ImageHeight(image) - 1 - y);
            b = GetPixelB(image, x, ImageHeight(image) - 1 - y);
            
            SetPixelR(image, x, ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, ImageHeight(image) - 1 - y, GetPixelB(image, x, y));

            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
            }
    }
    return image;
}

/* mirror image vertically */
IMAGE *VMirror(IMAGE *image) {
    assert(image);
    int x, y;
    for (y = 0; y < ImageHeight(image) / 2; y ++) {
        for (x = 0; x < ImageWidth(image); x ++) {
            SetPixelR(image, x, ImageHeight(image) - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, ImageHeight(image) - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, ImageHeight(image) - 1 - y, GetPixelB(image, x, y));
        }
    }
    return image;
}


/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image){
    assert(image);
    IMAGE *copyImage = CreateImage(ImageWidth(image), ImageHeight(image));
    for (int i = 0; i < ImageWidth(image); ++i) {
        for (int j = 0; j < ImageHeight(image); ++j) {
            SetPixelR(copyImage, i, j, GetPixelR(image, i, j));
            SetPixelG(copyImage, i, j, GetPixelG(image, i, j));
            SetPixelB(copyImage, i, j, GetPixelB(image, i, j));
        }
    }
 
    int block_width = image->W/4;
    int block_height = image->H/4;
    int width_starting_point[16] = {0, 0, 0, 0,
                                    block_width, block_width, block_width, block_width,
                                    2 * block_width, 2 * block_width,
                                    2 * block_width, 2 * block_width,
                                    3 * block_width, 3 * block_width,
                                    3 * block_width, 3 * block_width};
    int height_starting_point[16] = {0, block_height, 2 * block_height, 3 * block_height,
                                    0, block_height, 2 * block_height, 3 * block_height,
                                    0, block_height, 2 * block_height, 3 * block_height,
                                    0, block_height, 2 * block_height, 3 * block_height};
    

    
    unsigned int og_counter_w = 0;
    unsigned int og_counter_h = 0;
    int blocks = 0;
    unsigned top = 0;

        
    while (blocks < 16) {
        srand(time(NULL));
    
        int x = 0;
        int y = 0;
        // If value is -1 in array, it has been used
        while (width_starting_point[x] == -1) {
            x = rand() % 16;
            y = x;
        }
    
        // Insert blocks where they should be and stop when reached end of block
        for (unsigned i = width_starting_point[x];
            i < width_starting_point[x] + block_width; ++i) {
            for (unsigned j = height_starting_point[y];
                j < height_starting_point[y] + block_height; ++j) {
                
                SetPixelR(image, i, j, GetPixelR(copyImage, og_counter_w, og_counter_h));
                SetPixelG(image, i, j, GetPixelG(copyImage, og_counter_w, og_counter_h));
                SetPixelB(image, i, j, GetPixelB(copyImage, og_counter_w, og_counter_h));
                og_counter_h++;
            }
            og_counter_w++;
            og_counter_h = top;
        }
        // Track where in the photo is being altered and adjust accordingly
        if (og_counter_w >= ImageWidth(image)) {
            og_counter_w = 0;
            top += block_height;
        }
      
        // Set counter for # of blocks placed so far
        blocks += 1;
        width_starting_point[x]  = -1;
        height_starting_point[y] = -1;
    }       
    DeleteImage(copyImage); 
    copyImage = NULL;
    printf("\"Shuffle\" operation is done!\n");
    return image;

}

/* add border to the image */
IMAGE *AddBorder(IMAGE *image, char *color, int border_width) {
    int x, y;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
        return image;
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            if ((y < border_width) || (y > ImageHeight(image) - 1 - border_width) ||
                    (x < X_BORDER_WIDTH) || (x > ImageWidth(image) - 1 - X_BORDER_WIDTH)) {
                SetPixelR(image, x, y, border_r);
                SetPixelG(image, x, y, border_g);
                SetPixelB(image, x, y, border_b);
            }
        }
    }
    return image;
}


