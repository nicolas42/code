
struct image {
    char* data;
    int w,h,c;
}

int mandelbrot_simple(int pixel_width, int pixel_height, double xcenter, \
    double ycenter, double width, double height)
{

    // to see full image: mandelbrot_with_void_pointer_argument(1000,1000,0,0,4,4);

    // center, width
    // double xcenter,ycenter, width, height;
    double xmin, xmax, ymin, ymax;

    // xcenter = 0; ycenter = 0; width = 4; height = 4;
    xmin = xcenter - width/2;
    xmax = xcenter + width/2;
    ymin = ycenter - height/2;
    ymax = ycenter + height/2;

    const unsigned char black[4] = {0, 0, 0, 255};
    const unsigned char white[4] = {255, 255, 255, 255};

    // length per pixel
    const double width_per_pixel = (xmax - xmin) / pixel_width;
    const double height_per_pixel = (ymax - ymin) / pixel_height;
    
    // Open file and write header
	char* filename = "mandelbrot_with_void_pointer_argument.ppm";
	FILE *fp = fopen(filename, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", pixel_width, pixel_height);

    for (int y = 0; y < pixel_height; y += 1) {
        for (int x = 0; x < pixel_width; x += 1) {

            double zx, zxtmp, zy, cx, cy;
            int is_in_set, stride, i, imax;

            stride = 3;
            imax = 40;

            // image is flipped vertically
            cx = x * width_per_pixel - xmax;
            cy = y * height_per_pixel - ymax;
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
				fwrite(black, 1, 3, fp);
				// printf("*");
            } else {
				fputc(white[0] * i / imax, fp);
				fputc(white[1] * i / imax, fp);
				fputc(white[2] * i / imax, fp);
				// printf(" ");
			}
        }
		// printf("\n");
    }

  (void) fclose(fp);
  return 0;
}
