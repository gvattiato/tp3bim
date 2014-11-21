
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img_class.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Create an img "image" and read file "gargouille.ppm" into it
  //--------------------------------------------------------------------------
  img image;
  image.ppm_read_from_file("gargouille.ppm");
  
 
  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------

  // Copy image into image_bw
  img image_bw(image);

  // Desaturate image_bw
  image_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  image_bw.ppm_write_to_file("gargouille_BW.ppm");


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------

  // Copy image into image_small
  img image_small(image);

  // Shrink image_small size 2-fold
  image_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  image_small.ppm_write_to_file("gargouille_small.ppm");


  return 0;
}

