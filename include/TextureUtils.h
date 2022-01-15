#include <stdio.h>
#include <png.h>
#include <iostream>


#include <stdlib.h>



// #include <SDL_image-main/SDL_image.h>
// #include <SDL_image.h>
// #include <SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_opengl.h>
// #include <string>
// #include <SD

// SDL_Surface *texture;
// GLuint textureID=0;

// float x=0, y=0;

// int mode=GL_RGB;

// void loadTexture(std::string path){
//     texture=IMG_Load(path.c_str());

//     if(texture->format->BitsPerPixel>=4)
//         mode=GL_RGBA;
//     else
//         mode=GL_RGB;

//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_2D, textureID);

//     glTexImage2D(GL_TEXTURE_2D, 0, mode, texture->w, texture->h, 0, 
//                             mode, GL_UNSIGNED_BYTE, texture->pixels);


//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// }


// #ifdef _WIN32
// #include <GL/glut.h>
// #else
// #include <GLUT/glut.h>
// #endif
// #include <stdlib.h>
// #include <stdio.h>
// #include <png.h>
// #include <iostream>

GLubyte *textureImage;
// float rotateX = 0;
// float rotateY = 0;

// int mouseX;
// int mouseY;

bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
    
    if ((fp = fopen(name, "rb")) == NULL)
        return false;
    
    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
    
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
    
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }
    
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }
    
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
    
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
    
    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */

//     png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
    
//     //png_read_png(png_ptr, info_ptr);



// //        /* Expand paletted or RGB images with transparency to full alpha channels
// //     * so the data will be available as RGBA quartets.
// //     */
// //    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) != 0)
// //       png_set_tRNS_to_alpha(png_ptr);
    

//     png_uint_32 width, height;
//     int bit_depth;
//     png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
//                  &interlace_type, NULL, NULL);
//     outWidth = width;
//     outHeight = height;


 png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
 
 //png_read_image(png_ptr, info_ptr);//png_read_image(png, row_pointers);



    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    outWidth = width;
    outHeight = height;

    
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);
    
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }
    
    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    
    /* Close the file */
    fclose(fp);
    
    /* That's it */
    return true;
}

// void init(void) {
//     glClearColor(0.0, 0.0, 0.0, 0.0);


///// ***** alpa channel
//     glEnable(GL_DEPTH_TEST);


//     // The following two lines enable semi transparent
//     glEnable(GL_BLEND);
//     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
///// *****
    
//     int width, height;
//     bool hasAlpha;
//     char filename[] = "logo.png";
//     bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
//     if (!success) {
//         std::cout << "Unable to load png file" << std::endl;
//         return;
//     }
//     std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

///// ***** texture
//     glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
//                  height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
//                  textureImage);
///// *****

//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glEnable(GL_TEXTURE_2D);
//     glShadeModel(GL_FLAT);
// }

// void display(void) {
//     glLoadIdentity();
//     glTranslatef(0.0, 0.0, -3.6);
//     glRotatef(rotateX, 0,1,0);
//     glRotatef(rotateY, 1,0,0);
    
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glBegin(GL_QUADS);
//     glTexCoord2f(0.0, 0.0);
//     glVertex3f(-2.0, -1.0, 0.0);
//     glTexCoord2f(0.0, 1.0);
//     glVertex3f(-2.0, 1.0, 0.0);
//     glTexCoord2f(1.0, 1.0);
//     glVertex3f(0.0, 1.0, 0.0);
//     glTexCoord2f(1.0, 0.0);
//     glVertex3f(0.0, -1.0, 0.0);
    
//     glEnd();
//     glutSwapBuffers();
// }

// void myReshape(int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
//     glMatrixMode(GL_MODELVIEW);
// }

// void mousePassive(int x, int y){
//     mouseX = x;
//     mouseY = y;
// }

// void mouseMotion(int x, int y){
//     const float SPEED = 2;
    
//     rotateX += (mouseX-x)/SPEED;
//     rotateY += (mouseY-y)/SPEED;
//     mousePassive(x, y);
//     glutPostRedisplay();
// }

// int
// main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
//     glutCreateWindow("PNG texture");
//     glutMotionFunc(mouseMotion);
//     glutPassiveMotionFunc(mousePassive);
//     init();
//     glutReshapeFunc(myReshape);
//     glutDisplayFunc(display);
//     std::cout << "Use mouse drag to rotate." << std::endl;
//     glutMainLoop();
//     return 0;
// }


///// Source:

/// https://blog.nobel-joergensen.com/2010/11/07/loading-a-png-as-texture-in-opengl-using-libpng/





////////




////? rewrite
int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers = NULL;

void read_png_file(char *filename, int &outWidth, int &outHeight, GLubyte **outData) { ///(filename, width, height, hasAlpha, &textureImage) (char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData)
  
  
//   int width, height;
// png_byte color_type;
// png_byte bit_depth;
// png_bytep *row_pointers = NULL;

  
  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  if (row_pointers) abort();

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for(int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info)); /// 
  }

  png_read_image(png, row_pointers);
///

    // int outWidth = width;
    // int outHeight = height;


    // GLubyte **outData;


    outWidth = width;
    outHeight = height;
    
    unsigned int row_bytes = png_get_rowbytes(png,info); ///(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight); /// GLuint //GLubyte 
    unsigned char *CharData = (unsigned char*) malloc(row_bytes * outHeight);
    
    png_bytepp row_pointers1 = png_get_rows(png,info); ///(png_ptr, info_ptr);
    
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped

        memcpy(*outData + (row_bytes * (outHeight-1-i)), row_pointers1[i], row_bytes);

        // memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);

        // memcpy(*CharData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }



///
  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);
}

void write_png_file(char *filename) {
  int y;

  FILE *fp = fopen(filename, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
    png,
    info,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
  // Use png_set_filler().
  //png_set_filler(png, 0, PNG_FILLER_AFTER);

  if (!row_pointers) abort();

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);

  fclose(fp);

  png_destroy_write_struct(&png, &info);
}

void process_png_file() {
  for(int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]);
      // Do something awesome for each pixel here...
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
    }
  }
}












/////

/////FlipImage by uv:

// https://stackoverflow.com/questions/19770296/should-i-vertically-flip-the-lines-of-an-image-loaded-with-stb-image-to-use-in-o

// Since this is a matter of opposite assumptions between image libraries in general and OpenGL, Id say the best way is to manipulate the vertical UV-coord. This takes minimal effort and is always relevant when loading images using any image library and passing it to OpenGL.

// Either feed tex-coords with 1.0f-uv.y in vertex-population OR reverse in shader.

//  fcol = texture2D( tex, vec2(uv.x,1.-uv.y) );


/////FlipImage by pixels:



//https://stackoverflow.com/questions/26706036/flip-an-image-vertically



// const int width = 100;
// const int height = width;
// const int components = 3;
// unsigned char pixels[width * height * components];
// glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
// unsigned char flipPixels[width * height * components];
// for (int i = 0; i < width; ++i) {
//     for (int j = 0; j < height; ++j) {
//         for (int k = 0; k < components; ++k) {
//             flipPixels[i + j * width + k] = pixels[(height) * (width) - ((j+1) * width) + i + k];
//         }
//     }
// }

// ***flipPixels[(i + j * width) * components + k] = pixels[(i + (height - 1 - j) * width) * components + k];

///https://www.gamedev.net/forums/topic/457659-png-image-upside-down-what-do-i-do-using-libpng/

// /*WHERE THE PIXEL DATA IS STORED*/
// 	CompleteImageData->i_pixels = new unsigned char[png_ptr->rowbytes*png_ptr->height];

// /*LOOP TO ORGANISE THE PIXELATION OF MY LOADER, IT MAKES THE IMAGE RENDER UPSIDE DOWN :-(*/
// 	int p=0;
// 	for (unsigned int row = 0; row < png_ptr->height; row++)
// 	{
// 		for (unsigned int i=0; i<png_ptr->rowbytes; i++)
// 		{
// 	CompleteImageData->i_pixels=(char)info_ptr->row_pointers[row];
// 		p++;
// 		}
// 	}


// ***    for (unsigned int row = 0; row < png_ptr->height; row++)
// ***
// ***with:
// ***for (unsigned int row = png_ptr->height - 1; row >= 0 ; row--)
