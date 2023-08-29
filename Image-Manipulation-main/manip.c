//Arpeet Naik
//CPSC 1020 Fall 2021
//PA1

#include <stdio.h>
#include <stdlib.h>
#include "ppm_info.h"

// make each color pixel the average of the r, g, b components
// which will gray-scale the image
// inputs:  the image pointer
// outputs:  none
void gray_scale(filePtr_t* image, filePtr_t** theList, int count) {
   int row = 0;
   int col = 0;
	int avg = 0;

//creates newImage with new header while keeping oldImage
header_t header  = image->theImage->header;
image_t* newImage = image->theImage;
newImage->header = header;

    // after declaring a new image_t and allocating memory for it:
   char fileName[30] = "g";  // for the gray scale function
   strcat(fileName, image->imageFileName);

   // see if image already exists in the list
   // if the 2nd letter is a lower case 'g', then it already exists
   if(fileName[1] != 'g') {
      char buf[5];
       fileName[strlen(fileName)-4] = '\0';
       snprintf(buf, 5, "%d", count);
       char* imageName = (char*)malloc(50);
       sprintf(imageName, "%s%02d.ppm", fileName, count);

       FILE* grayedImage = fopen(imageName, "w");
       if (!grayedImage) {
         fprintf(stderr, "grayed image file could not open\n\n");
        exit(1);
    }
       // then continue with initializing the header for the new image
       // and the 2 for loops, etc.

      for(row = 0; row < header.height; row++) {
         for(col = 0; col < header.width; col++) {
			// calculate the average of the r, g, b values for the pixel
			avg = ( newImage->pixels[row][col].r +
			        newImage->pixels[row][col].g +
					  newImage->pixels[row][col].b ) / 3;

			// 6.  assign avg to each r, g, b value of the pixel
         newImage->pixels[row][col].r = avg;
         newImage->pixels[row][col].g = avg;
         newImage->pixels[row][col].b = avg;

            }
          }

   //call write_p6 function
   write_p6(grayedImage,newImage);
   //close the file
   fclose(grayedImage);
   //call addToList to add picture to list
   addToList(*theList,grayedImage,newImage,imageName);
   }
}



//mirror function tto flip pictures horizontally
void mirror(filePtr_t* image, filePtr_t** theList, int count){

header_t header = image->theImage->header;
image_t* newImage = image->theImage;
newImage->header = header;

// after declaring a new image_t and allocating memory for it:
  char fileName[30] = "m";  // for the mirror function
  strcat(fileName, image->imageFileName);

    if(fileName[1] != 'm') {  //for mirroring images
       char buf[5];
       fileName[strlen(fileName)-4] = '\0';
       snprintf(buf, 5, "%d", count);
       char* imageName = (char*)malloc(50);
       sprintf(imageName, "%s%02d.ppm", fileName, count);

       FILE* mirroredImage = fopen(imageName, "w");
       if (!mirroredImage) {
          fprintf(stderr, "mirrored image file could not open\n\n");
          exit(1);
       }

       int row;
       int col;

       for(row = 0; row < header.height; row++){
          for(col = 0; col < header.width/2; col++){
             pixel_t temp = newImage -> pixels[row][col];
             newImage -> pixels[row][col] = newImage -> pixels[row][newImage -> header.width-col-1];
             newImage -> pixels[row][newImage -> header.width-col-1] = temp;
          }
       }

   //call write_p6 function
   write_p6(mirroredImage, newImage);
   //close the file
   fclose(mirroredImage);
   //call addToList to add picture to list
   addToList(*theList, mirroredImage, newImage, imageName);
   }
}

//green screen function to green screen pictures
void green_screen(filePtr_t* image1, filePtr_t* image2, filePtr_t** theList, int count){

//image1
header_t header1;
header1 = image1->theImage->header;
image_t* oldImage1 = image1->theImage;
image_t* newImage1 = allocate_memory(header1);
newImage1->header = header1;

//image2
header_t header2;
header2 = image2->theImage->header;
image_t* oldImage2 = image2->theImage;
image_t* newImage2 = allocate_memory(header2);
newImage2->header = header2;

 char fileName[30] = "gs";  // for the green screen function
  strcat(fileName, image1->imageFileName);

    if(fileName[1] != 'g' && fileName[2] != 's') {  //for green screening images
       char buf[5];
       fileName[strlen(fileName)-4] = '\0';
       snprintf(buf, 5, "%d", count);
       char* imageName = (char*)malloc(50);
       sprintf(imageName, "%s%02d.ppm", fileName, count);

       FILE* greenscreenedImage = fopen(imageName, "w");
       if (!greenscreenedImage) {fprintf(stderr, "green screened image file could not open\n\n");
       exit(1);
       }

       for(int row = 0; row < header1.height; row++){
          for(int col = 0; col < header1.width; col++){

             if((image2 -> theImage -> pixels[row][col].g == 255) && (image2 -> theImage -> pixels[row][col].b == 0) && (image2 -> theImage -> pixels[row][col].r == 0)){
                newImage1 -> pixels[row][col].g = oldImage1 -> pixels[row][col].g;
                newImage1 -> pixels[row][col].b = oldImage1 -> pixels[row][col].b;
                newImage1 -> pixels[row][col].r = oldImage1 -> pixels[row][col].r;
             }
             else{
                newImage1 -> pixels[row][col].g = oldImage2 -> pixels[row][col].g;
                newImage1 -> pixels[row][col].b = oldImage2 -> pixels[row][col].b;
                newImage1 -> pixels[row][col].r = oldImage2 -> pixels[row][col].r;
             }
          }
       }

   //call write_p6 function
   write_p6(greenscreenedImage, newImage1);
   //close the file
   fclose(greenscreenedImage);
   //call addToList to add picture to list
   addToList(*theList, greenscreenedImage, newImage1, imageName);
    }
}

//add manipulated pictures to the list
void addToList(filePtr_t* frontOfList, FILE* newImage, image_t* theNewImage, char* nameOfImage){

   filePtr_t *current = frontOfList;

   filePtr_t *newFilePtr = (filePtr_t *) malloc(sizeof(filePtr_t));

   newFilePtr -> theFile = newImage;
   newFilePtr -> imageFileName = nameOfImage;
   newFilePtr -> theImage = theNewImage;
   newFilePtr -> next = NULL;

   if(frontOfList == NULL){
      frontOfList = newFilePtr;
   }

   else{
      while(current -> next != NULL){
         current = current -> next;
      }
      current -> next = newFilePtr;
   }
}
