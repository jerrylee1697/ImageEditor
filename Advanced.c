#include "Advanced.h"

/* add noise to an image */
//void Noise( int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {

IMAGE *AddNoise(IMAGE *image, int n){
    assert(image);
    /* Init the random number generator with the current time */
    srand(time(NULL));
    unsigned i = 0;
    for (i = 0; i < n * ImageHeight(image) * ImageWidth(image) / 100; ++i) {
        /* Generate random pixel */
        int x = rand() % ImageWidth(image);
        int y = rand() % ImageHeight(image);
        SetPixelR(image, x, y, 255);
        SetPixelG(image, x, y, 255);
        SetPixelB(image, x, y, 255);
    }
    return image;
}

/* sharpen the image */
unsigned char ChangeCenterPixelR(IMAGE *m, int i, int j) {
    int v = - GetPixelR(m, i - 1, j - 1) - GetPixelR(m, i, j - 1) - GetPixelR(m, i + 1, j - 1)
            - GetPixelR(m, i - 1, j) + 9 * GetPixelR(m, i, j)     - GetPixelR(m, i + 1, j)
            - GetPixelR(m, i - 1, j + 1) - GetPixelR(m, i, j + 1) - GetPixelR(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}
unsigned char ChangeCenterPixelG(IMAGE *m, int i, int j) {
    int v = - GetPixelG(m, i - 1, j - 1) - GetPixelG(m, i, j - 1) - GetPixelG(m, i + 1, j - 1)
            - GetPixelG(m, i - 1, j) + 9 * GetPixelG(m, i, j)     - GetPixelG(m, i + 1, j)
            - GetPixelG(m, i - 1, j + 1) - GetPixelG(m, i, j + 1) - GetPixelG(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}
unsigned char ChangeCenterPixelB(IMAGE *m, int i, int j) {
    int v = - GetPixelB(m, i - 1, j - 1) - GetPixelB(m, i, j - 1) - GetPixelB(m, i + 1, j - 1)
            - GetPixelB(m, i - 1, j) + 9 * GetPixelB(m, i, j)     - GetPixelB(m, i + 1, j)
            - GetPixelB(m, i - 1, j + 1) - GetPixelB(m, i, j + 1) - GetPixelB(m, i + 1, j + 1);
    if (v < 0) { v = 0; }
    else if (v > 255) {v = 255;}
    return v;
}

IMAGE *Sharpen(IMAGE *image) {
    assert(image);
    IMAGE *imageCopy = CreateImage(ImageWidth(image), ImageHeight(image));
    int             x, y;
    for (y = 0; y < ImageHeight(image); y++){
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(imageCopy, x, y, GetPixelR(image, x, y));
            SetPixelG(imageCopy, x, y, GetPixelG(image, x, y));
            SetPixelB(imageCopy, x, y, GetPixelB(image, x, y));
        }
    }
    
    for (unsigned i = 1; i < ImageWidth(image) - 1; ++i) {
         for (unsigned j = 1; j < ImageHeight(image) - 1; ++j) {
            SetPixelR(image, i, j, ChangeCenterPixelR(imageCopy, i, j));
            SetPixelG(image, i, j, ChangeCenterPixelG(imageCopy, i, j));
            SetPixelB(image, i, j, ChangeCenterPixelB(imageCopy, i, j));
        }
    }
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
    DeleteImage(imageCopy);
    imageCopy = NULL;
    return image;
}

/* posterize the image */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits) {
    assert(image);
    for (unsigned i = 0; i < ImageWidth(image); ++i) {
        for (unsigned j = 0; j < ImageHeight(image); ++j) {
            SetPixelR(image, i, j, BitManipulation(rbits, GetPixelR(image, i, j)));
            SetPixelG(image, i, j, BitManipulation(gbits, GetPixelG(image, i, j)));
            SetPixelB(image, i, j, BitManipulation(bbits, GetPixelB(image, i, j)));
        }
    }
    return image;
}

unsigned int BitManipulation(unsigned int bits, unsigned char pixelValue) {
    unsigned int sigBit = 255; // 1111 1111 in binary
    unsigned int leastSig = 0;
    while (bits > 0) {
        bits -= 1;
        if (sigBit == 255) {
            sigBit -= 1;       // 1111 1110 in binary
            leastSig += 1;
            continue;
        }
        sigBit = sigBit << 1;
        if (bits > 0) {
            leastSig = 2 * leastSig + 1;
        }
    }
    
    unsigned int temp = pixelValue & sigBit;
    temp = temp | leastSig;
    return temp;

}    

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount) {
    assert(image);
    IMAGE *imageCopy = CreateImage(ImageWidth(image), ImageHeight(image));
    int             x, y;
    for (y = 0; y < ImageHeight(image); y++){
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(imageCopy, x, y, GetPixelR(image, x, y));
            SetPixelG(imageCopy, x, y, GetPixelG(image, x, y));
            SetPixelB(imageCopy, x, y, GetPixelB(image, x, y));
        }
    }
    
    for (unsigned i = 0; i < ImageWidth(image); ++i) {
        for(unsigned j = 0; j < ImageHeight(image); ++j) {
            SetPixelR(image, i, j, GetPixelR(image, i, j) / 2 + BlurRight(BlurAmount, image, imageCopy->R, i, j) / 2);
            SetPixelG(image, i, j, GetPixelG(image, i, j) / 2 + BlurRight(BlurAmount, image, imageCopy->G, i, j) / 2);
            SetPixelB(image, i, j, GetPixelB(image, i, j) / 2 + BlurRight(BlurAmount, image, imageCopy->B, i, j) / 2);
        }
    }
    DeleteImage(imageCopy);
    imageCopy = NULL;
    return image;
}

unsigned int BlurRight(int BlurAmount, IMAGE *image, unsigned char *pixelPointer, unsigned i, unsigned j) {
    unsigned int tmp = 0;
    // m starts 1 off from pixel being changed
    int m = 1;
    for (m = 1; m < BlurAmount && m + i < ImageWidth(image); ++m) {
        tmp += *(pixelPointer + m + i + j * ImageWidth(image));

    }
    tmp = tmp / (m );
    return tmp;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H) {
    assert(image);
    // Adjust new image size
    if (W + x > ImageWidth(image)) W = W - (W + x - ImageWidth(image)) ;
    if (H + x > ImageHeight(image)) H = H - (H + y - ImageHeight(image));
    IMAGE *croppedImage = CreateImage(W, H);
    // Export desired image parts within constraints
    for (unsigned i = 0; i < W; ++i) {
        for (unsigned j = 0; j < H; ++j) {
            SetPixelR(croppedImage, i, j, GetPixelR(image, i + x, j + y));
            SetPixelG(croppedImage, i, j, GetPixelG(image, i + x, j + y));
            SetPixelB(croppedImage, i, j, GetPixelB(image, i + x, j + y));
        }
    }
    DeleteImage(image);
    image = NULL;
    return croppedImage;
} 

IMAGE *Resize(IMAGE *image, int percentage) {
    assert(image);
    if (percentage == 100){
        return image;
    }
    IMAGE *newImage = NULL;

    double Width = ImageWidth(image) * ((double)(percentage) / 100.00);
    double Height = ImageHeight(image) * ((double)(percentage) / 100.00);
    
    int newWidth = (int)Width;
    int newHeight = (int)Height;
    
    newImage = CreateImage(newWidth, newHeight);
    
    for (unsigned i = 0; i < newWidth; ++i) {
        for (unsigned j = 0; j < newHeight; ++j) {
            // If % is larger than 100, enlarge and spread pixels
            if (percentage > 100) {
                int x = (int)((double)(i) / ((double)(percentage) / 100.00));
                int y = (int)((double)(j) / ((double)(percentage) / 100.00));
                SetPixelR(newImage, i, j, GetPixelR(image, x, y));
                SetPixelG(newImage, i, j, GetPixelG(image, x, y));
                SetPixelB(newImage, i, j, GetPixelB(image, x, y));
            }
            // If % smaller, condense pixels without losing too much information using averages
            if (percentage < 100) {
                int x1 = (int)((double)(i) / ((double)(percentage) / 100.00));
                int y1 = (int)((double)(j) / ((double)(percentage) / 100.00));
                int x2 = (int)((double)(i + 1) / ((double)(percentage) / 100.00));
                int y2 = (int)((double)(j + 1) / ((double)(percentage) / 100.00));
                int averageR = 0;
                int averageG = 0;
                int averageB = 0;
                int elements = 0;
                for (unsigned k = x1; k < x2 && k < ImageWidth(image); ++k) {
                    for (unsigned m = y1; m < y2 && m < ImageHeight(image); ++m) {
                        averageR += GetPixelR(image, k, m);
                        averageG += GetPixelG(image, k, m);
                        averageB += GetPixelB(image, k, m);
                        elements += 1;
                    }
                }
                SetPixelR(newImage, i, j, averageR / elements);
                SetPixelG(newImage, i, j, averageG / elements);
                SetPixelB(newImage, i, j, averageB / elements);
            }
        }
    }
    DeleteImage(image);
    image = NULL;
    return newImage;
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast) {
    if (brightness < -255) brightness = -255;
    
    if (brightness > 255)  brightness =  255;
    
    if (contrast < -255) contrast = -255;
    
    if (contrast > 255)  contrast =  255;
   
    double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));
    for (unsigned i = 0; i < ImageWidth(image); ++i) {
        for (unsigned j = 0; j < ImageHeight(image); ++j) {
            //int index = i + j * image->W;
            /* Adjust Birghtness */
            if (GetPixelR(image, i, j) + brightness > 255) {
                SetPixelR(image, i, j, 255);
            }
            else if (GetPixelR(image, i, j) + brightness < 0) { 
                SetPixelR(image, i, j, 0);
                }
            else {
                SetPixelR(image, i, j, GetPixelR(image, i, j) + brightness);
            }
            if (GetPixelG(image, i, j) + brightness > 255) {
                SetPixelG(image, i, j, 255);
            }
            else if (GetPixelG(image, i, j) + brightness < 0) { 
                SetPixelG(image, i, j, 0);
                }
            else {
                SetPixelG(image, i, j, GetPixelG(image, i, j) + brightness);
            }
            if (GetPixelB(image, i, j) + brightness > 255) {
                SetPixelB(image, i, j, 255);
            }
            else if (GetPixelB(image, i, j) + brightness < 0) { 
                SetPixelB(image, i, j, 0);
                }
            else {
                SetPixelB(image, i, j, GetPixelB(image, i, j) + brightness);
            }

            /* Adjust Contrast */
            int newR = (int)(factor * (GetPixelR(image, i, j) - 128) + 128); 
            int newG = (int)(factor * (GetPixelG(image, i, j) - 128) + 128);
            int newB = (int)(factor * (GetPixelB(image, i, j) - 128) + 128);
            if (newR > 255) {
                newR = 255;
            }
            if (newR < 0) {
                newR = 0;
            }
            SetPixelR(image, i, j, newR);
            if (newG > 255) {
                newG = 255;
            }
            if (newG < 0) {
                newG = 0;
            }
            SetPixelG(image, i, j, newG);
            //*(image->G + index)  = newG;
            if (newB > 255) {
                newB = 255;
            } 
            if (newB < 0) {
                newB = 0;
            }
            SetPixelB(image, i, j, newB);
            //*(image->B + index)  = newB;           
        }
    }
    return image;
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image) {
    assert(image);
    for (unsigned i = 0; i < ImageWidth(image); ++i) {
        for (unsigned j = 0; j < ImageHeight(image); ++j) {
            // Use modulo (%) to have watermark image roll around if smaller
            if (GetPixelR(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0 &&
                GetPixelG(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0 &&
                GetPixelB(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image)) == 0) {
                int newR = (int)((double)(GetPixelR(image, i, j)) * 1.45); 
                int newG = (int)((double)(GetPixelG(image, i, j)) * 1.45);
                int newB = (int)((double)(GetPixelB(image, i, j)) * 1.45);
            
                if (newR > 255) {newR = 255;}
                if (newG > 255) {newG = 255;}
                if (newB > 255) {newB = 255;}
                
                SetPixelR(image, i, j, newR);
                SetPixelG(image, i, j, newG);
                SetPixelB(image, i, j, newB);
            }
        }
    }
    return image;
}

