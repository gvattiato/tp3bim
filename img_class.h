
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//============================================================================
//                            Class declaration
//============================================================================

class img {

 private:
  u_char* data;
  int width;
  int height;

 public:
  // Getters
  int getWidth(void) const;
  int getHeight(void) const;
  u_char* getData(void) const;

  // Default constructor
  img(void);

  // Copy constructor
  img(const img& original);

  // Destructor
  ~img(void);

  //Functions

  // Write the image contained in <data> (of size <width> * <height>)
  // into plain RGB ppm file <fileName>
  void ppm_write_to_file(const char* fileName);

  // Read the image contained in plain RGB ppm file <fileName>
  // into <data> and set <width> and <height> accordingly
  // Warning: data is malloc_ed, don't forget to free it
  void ppm_read_from_file(const char* fileName);

  // Desaturate (transform to B&W) <image> (of size <width> * <height>)
  void ppm_desaturate(void);

  // Shrink image (of original size <width> * <height>) by factor <factor>
  // <width> and <height> are updated accordingly
   void ppm_shrink(int factor);

};
