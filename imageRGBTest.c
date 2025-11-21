// imageRGBTest - A program that performs some operations on RGB images.
//
// This program is an example use of the imageRGB module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// The AED Team <jmadeira@ua.pt, jmr@ua.pt, ...>
// 2025

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "imageRGB.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  if (argc != 1) {
    error(1, 0, "Usage: imageRGBTest");
  }

  ImageInit();

  // Creating and displaying some images

  printf("1) ImageCreate\n");
  Image white_image = ImageCreate(100, 100);
  // ImageRAWPrint(white_image);

  printf("2) ImageCreateChess(black)+ ImageSavePBM\n");
  Image image_chess_1 = ImageCreateChess(150, 120, 30, 0x000000);  // black
  // ImageRAWPrint(image_chess_1);
  ImageSavePBM(image_chess_1, "chess_image_1.pbm");

  printf("3) ImageCreateChess(red) + ImageSavePPM\n");
  Image image_chess_2 = ImageCreateChess(20, 20, 8, 0xff0000);  // red
  ImageRAWPrint(image_chess_2);
  ImageSavePPM(image_chess_2, "chess_image_2.ppm");

  printf("4) ImageCreateChess(all black)\n");
  Image black_image = ImageCreateChess(100, 100, 100, 0x000000);  // all black
  // ImageRAWPrint(black_image);
  ImageSavePBM(black_image, "black_image.pbm");

  printf("5) ImageCopy\n");
  Image copy_image = ImageCopy(image_chess_1);
  // ImageRAWPrint(copy_image);
  if (copy_image != NULL) {
    ImageSavePBM(copy_image, "copy_image.pbm");
  }


  printf("9) ImageRotate90CW\n");
  Image rotated_90 = ImageRotate90CW(image_chess_2);
  printf("Original Image:\n");
  ImageRAWPrint(image_chess_2);
  printf("Rotated 90 degrees CW:\n");
  ImageRAWPrint(rotated_90);
  ImageSavePPM(rotated_90, "chess_image_rotated_90.ppm");

  printf("10) ImageRotate180CW\n");
  Image rotated_180 = ImageRotate180CW(image_chess_2);
  printf("Original Image:\n");
  ImageRAWPrint(image_chess_2);
  printf("Rotated 180 degrees CW:\n");
  ImageRAWPrint(rotated_180);
  ImageSavePPM(rotated_180, "chess_image_rotated_180.ppm");

  // Cleanup: destroy rotated images
  ImageDestroy(&rotated_90);
  ImageDestroy(&rotated_180);


  printf("6) ImageLoadPBM\n");
  Image image_1 = ImageLoadPBM("img/feep.pbm");
  ImageRAWPrint(image_1);

  printf("7) ImageLoadPPM\n");
  Image image_2 = ImageLoadPPM("img/feep.ppm");
  ImageRAWPrint(image_2);

  printf("8) ImageCreatePalete\n");
  Image image_3 = ImageCreatePalete(4 * 32, 4 * 32, 4);
  ImageSavePPM(image_3, "palete.ppm");
  
  //  imagens para testar tempos e numero de comparacoes de ImageIsEqual
  Image image_smaller = ImageCreate(25, 25);
  Image image_small = ImageCreate(50, 50);
  Image image_normal = ImageCreate(100, 100);
  Image image_big = ImageCreate(200, 200);
  Image image_bigger = ImageCreate(400, 400);

  //comparacoes de pares de imagens iguais
  printf("9) ImageComparisons\n");

  printf("Images 25 x 25:\n");
  InstrReset();
  int equal = ImageIsEqual(image_smaller, image_smaller); 
  InstrPrint();
  InstrReset();

  printf("Images 50 x 50:\n");

  equal = ImageIsEqual(image_small, image_small);
  InstrPrint();
  InstrReset();

  printf("Images 100 x 100:\n");

  equal = ImageIsEqual(image_normal, image_normal);
  InstrPrint();
  InstrReset();

  printf("Images 200 x 200:\n");
  equal = ImageIsEqual(image_big, image_big);
  InstrPrint();
  InstrReset();

  printf("Images 400 x 400:\n");
  equal = ImageIsEqual(image_bigger, image_bigger);
  InstrPrint();
  InstrReset();

  ImageDestroy(&white_image);
  ImageDestroy(&black_image);
  if (copy_image != NULL) {
    ImageDestroy(&copy_image);
  }
  ImageDestroy(&image_chess_1);
  ImageDestroy(&image_chess_2);
  ImageDestroy(&image_1);
  ImageDestroy(&image_2);
  ImageDestroy(&image_3);
  ImageDestroy(&image_smaller);
  ImageDestroy(&image_small);
  ImageDestroy(&image_normal);
  ImageDestroy(&image_big);
  ImageDestroy(&image_bigger);


  return 0;
}
