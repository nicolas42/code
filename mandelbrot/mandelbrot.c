#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char** argv){



    int w = 800;
    int h = 800;
    int c = 4;
    double xcenter = 0;
    double ycenter = 0;
    double width = 4;
    double height = 4;

    char *image = malloc(w*h*c*sizeof(char));

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};
    
    for (int y = 0; y < h ; y += 1) {
        for (int x = 0; x < w; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride, i, imax;

            imax = 40;

            // image is flipped vertically
            cx = x * (width / w) - (xcenter + width/2);
            cy = y * (height / h) - (ycenter + height/2);
            zx = 0;
            zy = 0;
            is_in_set = 1;

            for(i = 1; i <= imax; i += 1){
                zxtmp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zxtmp;
                if(zx * zx + zy * zy > 4){
                    is_in_set = 0;
                    break;
                }
            }
            
            if (is_in_set) {
				image[y*w*c + x*c + 0] = (char)black[0];
                image[y*w*c + x*c + 1] = (char)black[1];
                image[y*w*c + x*c + 2] = (char)black[2];
                image[y*w*c + x*c + 3] = 255;
            } else {
				image[y*w*c + x*c + 0] = white[0] * i / imax;
                image[y*w*c + x*c + 1] = white[1] * i / imax;
                image[y*w*c + x*c + 2] = white[2] * i / imax;
                image[y*w*c + x*c + 3] = 255;
			}
        }
    }


//      int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
//    The functions create an image file defined by the parameters. The image
//    is a rectangle of pixels stored from left-to-right, top-to-bottom.
//    Each pixel contains 'comp' channels of data stored interleaved with 8-bits
//    per channel, in the following order: 1=Y, 2=YA, 3=RGB, 4=RGBA. (Y is
//    monochrome color.) The rectangle is 'w' pixels wide and 'h' pixels tall.
//    The *data pointer points to the first byte of the top-left-most pixel.
//    For PNG, "stride_in_bytes" is the distance in bytes from the first byte of
//    a row of pixels to the first byte of the next row of pixels.

    int success = stbi_write_png("out.png", w,h,c,image,w*c);

    return 0;
}