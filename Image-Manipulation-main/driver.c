//Arpeet Naik
//CPSC 1020 Fall 2021
//PA1

//The main driver file holds the files and opens them in order to gray scale the images.
/* driver for lab 4 - ppm image lab */

// there are 5 numbered comments where code needs to be completed
// the first one is on line #18

#include <stdio.h>
#include <stdlib.h>
#include "ppm_info.h"

//command-line arguments
int main(int argc, char* argv[]) {

   filePtr_t* outputFiles = NULL;
   int count = 1;
   filePtr_t *Ptr1;
   filePtr_t *Ptr2;

   //opening oldImage1 file
   FILE *oldImage1 = fopen(argv[1], "r");

   //call read_ppm function
   image_t *image1 = read_ppm(oldImage1);

   //dynamically allocating memory
   Ptr1 = (filePtr_t *) malloc(sizeof(filePtr_t));

   Ptr1->theFile = oldImage1;
   Ptr1->imageFileName = argv[1];
   Ptr1->theImage = image1;
   Ptr1->next = NULL;

   outputFiles = Ptr1;

   //opening oldImage2 file
   FILE *oldImage2 = fopen(argv[2], "r");

   //call read_ppm function
   image_t *image2 = read_ppm(oldImage2);

   //dynamically allocating memory
   Ptr2 = (filePtr_t *) malloc(sizeof(filePtr_t));


   Ptr2->theFile = oldImage2;
   Ptr2->imageFileName = argv[2];
   Ptr2->theImage = image2;
   Ptr2->next = NULL;
   outputFiles->next = Ptr2;

	// check for correct number of arguments entered on the command-line
   if(argc != 3) {
      printf("USAGE: <executable> <oldImage> <newImage>\n\n");
      return -1;
   }


	// check that the files opened successfully
   if(!oldImage1 || !oldImage2) {
      printf("ERROR: File(s) could not be opened.\n");
      return -1;  
   }


   int selectChoice;
   selectChoice = printMenu();

   filePtr_t *newFilePtr;

   //while loop to allow file manipulation
   while(selectChoice != 0){
      if(selectChoice == 1){
         newFilePtr = printList(outputFiles);
         gray_scale(newFilePtr, &outputFiles, count);
         count++;
      }
      else if(selectChoice == 2){
         newFilePtr = printList(outputFiles);
         mirror(newFilePtr, &outputFiles, count);
         count++;
      }
      else if(selectChoice == 3){
         fprintf(stderr,"\nThe Clemson Paw image will be copied on top of which of the following Disney images: \n");
         newFilePtr = printList(outputFiles);
         green_screen(Ptr1, Ptr2, &outputFiles, count);
         count++;
      }
      else{
         exit(0);
      }
      selectChoice = printMenu();
   }

   return 0;

}

