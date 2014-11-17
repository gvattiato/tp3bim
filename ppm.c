
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                                  Struct
//============================================================================

typedef struct 
{
  FILE* img;
  u_char* data;
  int width;
  int height;
}image;

//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(int width, int height, u_char* data, FILE* file);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(int *width, int *height, u_char** data, FILE* file);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(u_char* image, int width, int height);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(u_char** image, int *width, int *height, int factor);



//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  u_char* image = NULL;
  int width;
  int height;
  FILE* ppm_input = fopen("gargouille.ppm", "rb");
  ppm_read_from_file(&width, &height, &image, ppm_input);
  fclose(ppm_input);


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  int width_bw  = width;
  int height_bw = height;
  u_char* image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));
  memcpy(image_bw, image, 3 * width * height * sizeof(*image_bw));

  // Desaturate image_bw
  ppm_desaturate(image_bw, width, height);

  // Write the desaturated image into "gargouille_BW.ppm"
  FILE* ppm_output = fopen("gargouille_BW.ppm", "wb");
  ppm_write_to_file(width, height, image_bw, ppm_output);
  fclose(ppm_output);

  // Free the desaturated image
  free(image_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = width;
  int height_small = height;
  u_char* image_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*image_small));
  memcpy(image_small, image, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  ppm_shrink(&image_small, &width_small, &height_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_output = fopen("gargouille_small.ppm", "wb");
  ppm_write_to_file(width_small, height_small, image_small, ppm_output);
  fclose(ppm_output);

  // Free the not yet freed images
  free(image);
  free(image_small);

  return 0;
}



//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(int width, int height, u_char* data, FILE* file)
{
  // Write header
  fprintf(file, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3, width*height, file);
}

void ppm_read_from_file(int *width, int *height, u_char** data, FILE* file)
{
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", width, height);

  // Allocate memory according to width and height
  *data = (u_char*) malloc(3 * (*width) * (*height) * sizeof(**data));

  // Read the actual image data
  fread(*data, 3, (*width) * (*height), file);
}

void ppm_desaturate(u_char* image, int width, int height)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < width ; x++)
  {
    for (y = 0 ; y < height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image[ 3 * (y * width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&image[3 * (y * width + x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(u_char** image, int *width, int *height, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (*width) / factor;
