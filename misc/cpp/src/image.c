
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// typedef struct {
//     int w;
//     int h;
//     int c;
//     float *data;
// } image;

// image load_image_stb(char *filename, int channels)
// {
//     int w, h, c;
//     unsigned char *data = stbi_load(filename, &w, &h, &c, channels);
//     if (!data) {
//         fprintf(stderr, "Cannot load image \"%s\"\nSTB Reason: %s\n", filename, stbi_failure_reason());
//         exit(0);
//     }
//     if(channels) c = channels;
//     int i,j,k;
//     image im = make_image(w, h, c);
//     for(k = 0; k < c; ++k){
//         for(j = 0; j < h; ++j){
//             for(i = 0; i < w; ++i){
//                 int dst_index = i + w*j + w*h*k;
//                 int src_index = k + c*i + c*w*j;
//                 im.data[dst_index] = (float)data[src_index]/255.;
//             }
//         }
//     }
//     free(data);
//     return im;
// }

// image load_image(char *filename, int w, int h, int c)
// {
// #ifdef OPENCV
//     image out = load_image_cv(filename, c);
// #else
//     image out = load_image_stb(filename, c);
// #endif

//     if((h && w) && (h != out.h || w != out.w)){
//         image resized = resize_image(out, w, h);
//         free_image(out);
//         out = resized;
//     }
//     return out;
// }

// image load_image_color(char *filename, int w, int h)
// {
//     return load_image(filename, w, h, 3);
// }



// void save_image_options(image im, const char *name, IMTYPE f, int quality)
// {
//     char buff[256];
//     //sprintf(buff, "%s (%d)", name, windows);
//     if(f == PNG)       sprintf(buff, "%s.png", name);
//     else if (f == BMP) sprintf(buff, "%s.bmp", name);
//     else if (f == TGA) sprintf(buff, "%s.tga", name);
//     else if (f == JPG) sprintf(buff, "%s.jpg", name);
//     else               sprintf(buff, "%s.png", name);
//     unsigned char *data = calloc(im.w*im.h*im.c, sizeof(char));
//     int i,k;
//     for(k = 0; k < im.c; ++k){
//         for(i = 0; i < im.w*im.h; ++i){
//             data[i*im.c+k] = (unsigned char) (255*im.data[i + k*im.w*im.h]);
//         }
//     }
//     int success = 0;
//     if(f == PNG)       success = stbi_write_png(buff, im.w, im.h, im.c, data, im.w*im.c);
//     else if (f == BMP) success = stbi_write_bmp(buff, im.w, im.h, im.c, data);
//     else if (f == TGA) success = stbi_write_tga(buff, im.w, im.h, im.c, data);
//     else if (f == JPG) success = stbi_write_jpg(buff, im.w, im.h, im.c, data, quality);
//     free(data);
//     if(!success) fprintf(stderr, "Failed to write image %s\n", buff);
// }

// void save_image(image im, const char *name)
// {
//     save_image_options(im, name, JPG, 80);
// }
