
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.c"


//============================================================================
//                                  Struct
//============================================================================

typedef struct
{
  int width;
  int height;
  u_char* data;
}img;

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
  FILE* ppm_input;
 
  ppm_read_from_file(&width, &height, &image, "gargouille.ppm");
  
  // Create image "newimage" and initialise its parameters
  img* newimage = (img*)malloc(sizeof(img));
  newimage->data = image;
  newimage->width = width;
  newimage->height = height;

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------

  // Copy image into image_bw
  int width_bw;
  int height_bw;
  char*image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));
  memcpy(image_bw, image, 3 * width * height * sizeof(*image_bw));

  // Desaturate image_bw
  ppm_desaturate(image_bw, width, height);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(width, height, image_bw, "gargouille_BW.ppm");

  // Free the desaturated image
  free(image_bw);

  // Create image "bw" and initialise its parameters
  img* bw = (img*)malloc(sizeof(img));
  bw->width = width_bw;
  bw->height = height_bw;
  bw->data = image_bw;

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------

  // Copy image into image_small
  int width_small; 
  int height_small;
  u_char* image_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*image_small));
  memcpy(image_small, image, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  ppm_shrink(&image_small, &width_small, &height_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(width_small, height_small, image_small, "gargouille_small.ppm");

  // Create image "small" and initialise its parameters
  img* small = (img*)malloc(sizeof(img));
  small->width = width_small;
  small->height = height_small;
  small->data = image_small;

  // Free the not yet freed images
  free(image);
  free(image_small);

  return 0;
}

