#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"
#include "Test.h"

void PrintMenu();

/* Test all functions */
/* void AutoTest(void); */


int main() {
    //unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
    //unsigned char   G[WIDTH][HEIGHT];
    //unsigned char   B[WIDTH][HEIGHT];

    int rc = -1;

    #ifdef DEBUG
    rc = AutoTest();
    return 0;
    #endif

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */
    char colorOption[SLEN];
    char watermark_name[] = "watermark_template";
    PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

    //int rc = -1;			/* return code of ReadImage() */
    /* ColorFilter() parameters */
    int target_r, target_g, target_b, threshold;
    double factor_r, factor_g, factor_b;
    /* AddBorder() parameter */
    int border_width;
    
    /* MotionBlur Parameter */
    int BlurAmount;

    /* AddNoise Parameter */
    int n;

    /* Posterize Parameter */
    int Rinput, Ginput, Binput;

    /* Crop Parameters */
    int XOffset, YOffset, CWidth, CHeight;

    /* Resize Parameter */
    int percentage;
    IMAGE *image = NULL;
    
    /* Birght & Contrast Parameters */
    int brightness, contrast;


    //IMAGE *watermark_image = LoadImage(watermark_name);    
    IMAGE *watermark_image = NULL;
    /*
    if (*image == NULL) {
        printf("No image to process!\n");
    }*/
    if (option < 1 || option > 20) {
        printf("Invalid Selection!\n");
    }
    
    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            if (image) {
                DeleteImage(image);
                image = NULL;
            }
            //rc = LoadImage(fname, R, G, B);
            image = LoadImage(fname);
        }
        /* menu item 2 - 10 requires image is loaded first */
        else if (option >= 2 && option <= 19) {
            /*if (option == 18) {
                LoadImage(watermark_name);
            }*/
            
            if (image == NULL && option != 19)	 {
                printf("No image to process!\n");
            }
            /* now image is loaded */
            else {
                switch(option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, image);
                        break;
                    case 3:
                        image = BlackNWhite(image);
                        printf("\"Black & White\" operation is done!\n");
                        break;
					case 4:
                        image = Negative(image);
                        printf("\"Negative\" operation is done!\n");
                        break;
                    case 5:
                        printf("Enter Red   component for the target color: ");
                        scanf("%d", &target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d", &target_g);
                        printf("Enter Blue  component for the target color: ");
                        scanf("%d", &target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d", &threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%lf", &factor_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%lf", &factor_g);
                        printf("Enter value for Blue  component in the target color: ");
                        scanf("%lf", &factor_b);
						
                        image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                        printf("\"Color Filter\" operation is done!\n");
                        break;
                    case 6:
                        image = Edge(image);
                        printf("\"Edge\" operation is done!\n");
                        break;
                    case 7:
                        image = Shuffle(image);
                        printf("\"Shuffle\" operation is done!\n");
                        break;
					case 8:
                        image = VFlip(image);
                        printf("\"VFlip\" operation is done!\n");
                        break;
					case 9:
                        image = VMirror(image);
                        printf("\"Vertically Mirror\" operation is done!\n");
                        break;
                    case 10:
                        printf("Enter border width:");
                        scanf("%d", &border_width);
                        printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                        printf("Select border color from the options: ");
                        scanf("%s",colorOption);
                        image = AddBorder(image, colorOption, border_width);
                        printf("\"Border\" operation is done!\n");
                        break;
					case 11:
                        printf("Please input noise percentage:");
                        scanf("%d", &n);
                        image = AddNoise(image, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 12:
                        image = Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 13:
                        printf("Enter the number of posterization bits for R channel (1 to 8): ");
                        scanf("%d", &Rinput);
                        printf("Enter the number of posterization bits for G channel (1 to 8): ");
                        scanf("%d", &Ginput);
                        printf("Enter the number of posterization bits for B channel (1 to 8): ");
                        scanf("%d", &Binput);
                        image = Posterize(image, Rinput, Ginput, Binput) ;
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 14:
                        printf("Please input blur amount: ");
                        scanf("%d", &BlurAmount);
                        image = MotionBlur(image, BlurAmount);
                        printf("\"Motion Blur\" operation is done!");
                        break;
                    case 15:
                        printf("Please enter the X offset value: ");
                        scanf("%d", &XOffset);
                        printf("Please enter the Y offset value: ");
                        scanf("%d", &YOffset);
                        printf("Please input the crop width: ");
                        scanf("%d", &CWidth);
                        printf("Please input the crop height: ");
                        scanf("%d", &CHeight);
                        image = Crop(image, XOffset, YOffset, CWidth, CHeight);
                        printf("\"Crop\" operation is done!\n");
                        break;
                    case 16:
                        printf("Please input the resizing percentage (integer between 1 - 500): ");
                        scanf("%d", &percentage);
                        image = Resize(image, percentage);
                        printf("\"Resizing the image\" operation is done!\n");
                        break;
                    case 17:
                        printf("Please input the brightness level (integer between -255 - 255): ");
                        scanf("%d", &brightness);
                        printf("Please input the contrast level (integer between -255 - 255): ");
                        scanf("%d", &contrast);
                        image = BrightnessAndContrast(image, brightness, contrast);
                        printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
                        break;
                    case 18:
                        watermark_image = LoadImage(watermark_name);
                        image = Watermark(image, watermark_image);
                        printf("\"Watermark\" operation is done!\n");
                        break;
                    case 19:
                        rc = AutoTest();
                        if (rc != 0) {
                            printf("AutoTest failed, error code %d\n", rc);
                            break;
                        }
                        printf("AutoTest finished successfully.\n");
                        break;
                    
                    default:
                        break;
                }
            }
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
    }
    if (image) {
        DeleteImage(image);
        image = NULL;
        //DeleteImage(watermark_image);
        //watermark_image = NULL;
    }
    if (watermark_image) {
        DeleteImage(watermark_image);
        watermark_image = NULL;
    }
    printf("You exit the program.\n");
    return 0;
}

void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Make a negative of an image\n");
    printf(" 5: Color filter an image\n");
    printf(" 6: Sketch the edge of an image\n");
    printf(" 7: Shuffle an image\n");
    printf(" 8: Flip an image vertically\n");
    printf(" 9: Mirror an image vertically\n");
    printf("10: Add border to an image\n");
    printf("11: Add noise to an image\n");
    printf("12: Sharpen an image\n");
    printf("13: Posterize an image\n");
    printf("14: Blur an image\n");
    printf("15: Crop an image\n");
    printf("16: Resize an image\n");
    printf("17: Adjust the Brightness and Contrast of an image\n");
    printf("18: Add Watermark to an image\n");
    printf("19: Test all functions\n");
    printf("20: Exit\n");
    
}

/*
void AutoTest(void) {

    unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];     
    char fname[SLEN] = "HSSOE";

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    #ifdef DEBUG
    printf("Black & White tested!\n\n");
	#else
    printf("\n");
    #endif

	LoadImage(fname, R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
    #ifdef DEBUG
    printf("Negative tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    SaveImage("colorfilter", R, G, B);
    #ifdef DEBUG
    printf("Color Filter tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
    #ifdef DEBUG
    printf("Edge Detection tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    VMirror(R, G, B);
    SaveImage("vmirror", R, G, B);
    #ifdef  DEBUG
    printf("VMirror tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    #ifdef DEBUG
    printf("VFlip tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
    #ifdef DEBUG
    printf("Shuffle tested!\n\n");	
	#else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    AddBorder (R, G, B, "yellow", 32);
    SaveImage("border", R, G, B);
    #ifdef DEBUG
    printf("Border tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    Noise(30, R, G, B) ;
    SaveImage("noise", R, G, B) ;
    #ifdef DEBUG
    printf("Noise tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    Sharpen(R, G, B) ;
    SaveImage("sharpen", R, G, B) ;
    #ifdef DEBUG
    printf("Sharpen tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    Posterize(R, G, B, 7, 7, 7) ;
    SaveImage("posterize", R, G, B) ;
    #ifdef DEBUG
    printf("Posterize tested!\n\n");
    #else
    printf("\n");
    #endif

    LoadImage(fname, R, G, B);
    MotionBlur(50, R, G, B) ;
    SaveImage("blur", R, G, B) ;
    #ifdef DEBUG
    printf("MotionBlur tested!\n\n");
    #else
    printf("\n");
    #endif
}*/

