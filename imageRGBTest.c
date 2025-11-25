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

  Image image_rectangle1 = ImageCreate(10, 50);
  Image image_rectangle2 = ImageCreate(20, 100);
  Image image_rectangle_chess1 = ImageCreateChess(50, 10, 5,0xff0000);
  Image image_rectangle_chess2 = ImageCreateChess(100, 20, 5, 0xff0000);

  //comparacoes de imagens iguais (Worst Case)
  //imagens simples quadradas
  printf("9) SimpleImageComparisons\n");
  for( uint32 i = 25; i<=400; i *= 2){
    printf("Images %d x %d:\n", i, i);
    Image img = ImageCreate(i, i);
    InstrReset();
    ImageIsEqual(img, img); 
    InstrPrint();
    ImageDestroy(&img);
  }

  // imagens em xadrez quadradas
  printf("\n10) DetailedImageComparisons\n");
  for( uint32 i = 25, j = 5; i<=400; i *= 2, j *= 2){
    printf("Images %d x %d, %d:\n", i, i, j);
    Image img = ImageCreateChess(i, i, j, 0xff0000);
    InstrReset();
    ImageIsEqual(img, img); 
    InstrPrint();
    ImageDestroy(&img);
  }
  
  // imagens retangulares
  printf("\n11) RectangleImageComparisons\n");
  printf("Images 10 x 50:\n");
  InstrReset();
  ImageIsEqual(image_rectangle1, image_rectangle1); 
  InstrPrint();

  printf("Images 20 x 110:\n");
  InstrReset();
  ImageIsEqual(image_rectangle2, image_rectangle2); 
  InstrPrint();

  printf("Images 50 x 10, 5:\n");
  InstrReset();
  ImageIsEqual(image_rectangle_chess1, image_rectangle_chess1);
  InstrPrint();

  printf("Images 100 x 20, 5:\n");
  InstrReset();
  ImageIsEqual(image_rectangle_chess2, image_rectangle_chess2);
  InstrPrint();

  // imagens diferentes (Best Case)
  printf("\n12) DifferentImageComparisons\n");
  for( uint32 i = 25, j =100; i<=100; i *= 2, j *= 2){
    printf("Images %d x %d and %d x %d:\n", i, i, j, j);
    Image img = ImageCreate(i, i);
    Image img2 = ImageCreate(j,j);
    InstrReset();
    ImageIsEqual(img, img2); 
    InstrPrint();
    ImageDestroy(&img);
    ImageDestroy(&img2);

  }

  printf("\n13) ImageSegmentationQueue\n");
  Image img1 = ImageCreateChess(30, 30, 10, 0x00ff00);
  ImageSavePPM(img1, "img_beforeQueue.ppm");
  printf("regioes encontradas: %d, regioes esperadas: 4\n", ImageSegmentation(img1, ImageRegionFillingWithQUEUE));
  ImageSavePPM(img1, "img_afterQueue.ppm");

  printf("\n14) ImageSegmentationStack\n");
  img1 = ImageCreateChess(20, 20, 5, 0x000000);
  ImageSavePPM(img1, "img_beforeStack.ppm");
  printf("regioes encontradas: %d, regioes esperadas: 8\n", ImageSegmentation(img1, ImageRegionFillingWithSTACK));
  ImageSavePPM(img1, "img_afterStack.ppm");

  printf("\n15) ImageSegmentationRecursive\n");
  img1 = ImageCreateChess(25, 25, 5, 0xff0000);
  ImageSavePPM(img1, "img_beforeRec.ppm");
  printf("regioes encontradas: %d, regioes esperadas: 12\n", ImageSegmentation(img1, ImageRegionFillingRecursive));
  ImageSavePPM(img1, "img_afterRec.ppm");
  ImageDestroy(&img1);
  

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
  ImageDestroy(&image_rectangle1);
  ImageDestroy(&image_rectangle2);
  ImageDestroy(&image_rectangle_chess1);
  ImageDestroy(&image_rectangle_chess2);

  return 0;
}
