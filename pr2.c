/*
 * Author: Luka Gajic kalahnar@uw.edu
 * Project: pr2.c
 * Version: 1.0
 * Worked on: Ubuntu 16.04 LTS Desktop 32-bit
*/
#include <stdio.h>
#define HEADER_SIZE 54
#define CONTRAST 2.9695
int main(){
    
    //initializing variables
    char fName[64], header[HEADER_SIZE];
    int i, j, k;
    unsigned int height, width;
    printf("Enter the file name: ");
    scanf ("%s", fName);
    sprintf(fName, "%s.bmp", fName);//i found code online how to append string 
    //opening the file same as in the instructions
    FILE *infile = fopen(fName, "rb"); 
    printf("Enter height and width (in pixels) : ");
    scanf ("%u %u", &height, &width);
    FILE *outfile1 = fopen("copy1.bmp", "wb");
    FILE *outfile2 = fopen("copy2.bmp", "wb");
    FILE *outfile3 = fopen("copy3.bmp", "wb");
    FILE *outfile4 = fopen("copy4.bmp", "wb");
    unsigned char pixels[height][width * 3];
    unsigned char outgoing[height][width * 3];
    //reading file same as in instructions
    fread(header, 1, HEADER_SIZE, infile);
    fread(pixels, 1, height * width * 3, infile);
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
     * This for-loop goes through the image pixel by pixel
     * and increases every value(blue,gree,red) by 50
     * In case if the value of the spill goes above 255 
     * because it will start from 0 again I just check to see 
     * if it is spilled over and set it to 255 as instructed.
    */
    for( i = 0; i < height; i++){//brightness
         for(j = 0; j < width * 3; j++){
	           
             outgoing[i][j] = pixels[i][j] + 50;
             if(outgoing[i][j] < pixels [i][j]){
                outgoing[i][j] = 255;
             }
             
         }
    }
    fwrite(header, sizeof(char), HEADER_SIZE, outfile1);
    fwrite(outgoing, sizeof(char), height * width * 3, outfile1);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
     * This for-loop goes through the image pixel by pixel
     * and as instructed in the assignment description I use
     * the forumla given to us. 
     * I check for spills on both sides because we aren't brightening now 
     * so the value can go less than 0 and more than 255 so i check for both cases.
    */
        for( i = 0; i < height; i++){//contrast
             for(j = 0; j < width * 3; j++){
	               float temp = (float) pixels[i][j];
	               temp = CONTRAST * (temp - 128) + 128;
	               if(temp > 255){
	                  temp = 255;
	               } else if (temp < 0) {
	                  temp = 0;
	               }
	               outgoing[i][j] =  temp;
         }
    }
    fwrite(header, sizeof(char), HEADER_SIZE, outfile2);
    fwrite(outgoing, sizeof(char), height * width * 3, outfile2);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
     * This for-loop goes through the image pixel by pixel
     * and to be honest I was experimenting with the formulas a lot.
     * so the first part [i] of the outgoing [i]j[] i figured quickly
     * because height will just get fliped so the matrices as shown in the assignemnt files
     * will flip the image and the second part [j] of the outgoing[i][j] i used k 
     * because that is an idividual value for blue,green and red. 
     * So in pixels[i][j], [i] stays the same because height has been dealt with but 
     * the second part was very similar to the outgoing in logix as in i needed individual k 
     * value which is where the + k comes from.
    */
    for( i = 0; i < height; i++){//flipping horizontally
         for(j = 0; j < width; j++){
             for(k = 0; k < 3; k++){
                 outgoing[height - i -1][(width - j) * 3 - (3-k)] = pixels[i][j * 3 + k];
              }
         }
    }
    fwrite(header, sizeof(char), HEADER_SIZE, outfile3);
    fwrite(outgoing, sizeof(char), height * width * 3, outfile3);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
     * This for-loop goes through the image pixel by pixel
     * and the outgoing is same as pixels last part in operation to flip horizontally.
     * Pixels [i] i multiplied the i with 2 and then % height because i needed to shrink it and
     * first time i tried i divided so when that made is larger i tried multiplying and it worked
     * in making it smaller but it only worked for the half of the picture. 
     * For the second part[j] i multiplied j by 6 because we have 3 colors and i needed every 
     * other becase we are making the width of the new picture 2 times smaller than the original
     * so 6 comes from there. For % i borrowed from the first part and simply did width *3 for
     * every color individually but i was getting it to get crazy look so i tried adding k and
     * it worked because i was missing the loop for every color individually.
    */
    for( i = 0; i < height  ; i++){//resizing
         for(j = 0; j < width; j++){
             for(k = 0; k < 3; k++){
                 outgoing[i][j * 3 + k] = pixels[(i*2)%height][(j*6)%(width*3) + k];
             }   
         }
    }
    fwrite(header, sizeof(char), HEADER_SIZE, outfile4);
    fwrite(outgoing, sizeof(char), height * width * 3, outfile4);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    printf("Done. Check the generated images.\n ");
    
}



