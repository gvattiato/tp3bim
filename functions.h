
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                           Function definition
//============================================================================

// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(int width, int height, u_char* data, const char* fileName);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(int& width, int& height, u_char** data, const char* fileName);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(u_char* image, int width, int height);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(u_char** image, int& width, int& height, int factor);
