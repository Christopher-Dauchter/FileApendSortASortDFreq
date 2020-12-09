#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int countString(char str[]){
  int i=0;
  int charCount=0;
  while (str[i]!='\0'){
    charCount++;
    i++;
  }
  return charCount;
}

int main()
{

   char letter[10000]; // Scanned string pointer from file
   char stringRead[10000]; // Scanned string literal from letter
   char datafileStandard[50] = "Datafile_"; //The standard file name.
   char datafile[50]; // File location for the input file
   char copyFile[50]; // File location for the output file
   char copyFileString[10000]; // The holding for input string
   char writeString[4][10000]={"\n$$$", "\n%%%", "\n&&&","\n0000"}; // Things to Append to the files, in order of datafile
   char datafileVars[4][10000]={"Sort_Ascend","Sort_Descend","Freq","Append"}; //the suffixs for the output files
   char hexChar[1000][1000];// temp storange of hex strings
   char numChar[3]; // holds the char version of i
   unsigned int hexArr[1000]; // If file is hex file, this holds the hex values
   unsigned int unsignTemp; // holds the values of the hex during sorting
   int progNum = 4; // How many programs to run over each file
   int length; // length of the input string
   int addedLength; // the length of apended string
   int hexLength; // the size of the hex array
   int hexFileFlag = 0; // tells the system that it's a hex file 
   int  i, j, k, m, n, o, p, q, r, s, t = 0, u = 0, v ,w, temp, count=0; // various integers used in for loops. temp is for holding values during sorting, count is for counting the frequency of values

   FILE *fptr;
   FILE *copyFPtr;

  for (i = 1; i <= 4; i++){
    //Building the file input location string
    strcpy(datafile, datafileStandard);
    sprintf(numChar, "%d", i);
    strcat(datafile, numChar);
    strcat(datafile, ".txt");
    printf("\n%s\n",datafile);

   if ((fptr = fopen(datafile,"r")) == NULL){
              printf("Error! opening file");
   // Program exits if the file pointer returns NULL.
       return(1);
   }

   //Mainly for debug, tells the user what the original is
   if (fscanf(fptr, "%s", &letter) != '\0'){
    printf("The string in the file is\n");
    puts(letter);
    printf("\n");
    //checking the length of input string 
    length = countString(letter);
    //printf("\nLength: %d",countString(letter));
    //putting letter into string literal stringRead
    sscanf(letter, "%s", stringRead);
    //Check if string is a hex file, a hex file is one that starts with 0x or 0X
    if((stringRead[0] == '0' || stringRead[0] == 0) && (stringRead[1] == 'x' || stringRead[1] == 'X')){
      hexFileFlag = 1;
      //divides up the various hex values into a seperate array
      for(r = 0; r < length; r++){
        if(((stringRead[r] == '0' || stringRead[r] == 0) && (stringRead[r+1] == 'x' || stringRead[r+1] == 'X'))){
          //setting up the hex array
          hexChar[t][0]='0';
          hexChar[t][1]='x';
          u=0;
          //adding the hex values number by number into their seperate spaces
          for(s=r+2; (!((stringRead[s] == '0' || stringRead[s] == 0) && (stringRead[s+1] == 'x' || stringRead[s+1] == 'X'))); s++ ){
            hexChar[t][u+2] = stringRead[s];
            if(stringRead[s] == '\0'){
              break;
            }
            u++;
          }
          t++;
          //move the scanner to the end of the last stored value
          r = s-2;
        }
      }
    } else {hexFileFlag = 0;}
    for(v=0; hexChar[v][1] != '\0'; v++){
      //converts the strings from the hex temporary storage to actual hex
      hexArr[v] = strtoul(hexChar[v], NULL, 0);
    }
    //taking the amount of strings in tempsotrage as length for new hex array
    hexLength = v;
    //For each data file in the queue run the various programs.
    for (n = 0; n <= progNum-1; n++){
      //Building the file output location string
      sprintf(numChar, "%d", i);
      strcpy(copyFile, datafileStandard);
      strcat(copyFile, numChar);
      strcat(copyFile, "_");
      strcat(copyFile, datafileVars[n]);
      strcat(copyFile, ".txt");

      //itterates through each program
      switch (n) {

        case 0:
          //Sort Ascending
          copyFPtr = fopen (copyFile,"w");

          if(hexFileFlag == 1){
            for (p = 0; p < hexLength - 1; p++){
              for (q = p + 1; q < hexLength; q++){
                if (hexArr[p] > hexArr[q]){
                  unsignTemp =  hexArr[p];
                  hexArr[p] = hexArr[q];
                  hexArr[q] = unsignTemp;
                }
              }
            }
            for(w = 0; w < hexLength; w++){
              fprintf(copyFPtr,"%#x\n", hexArr[w]);
              printf("%#x\n", hexArr[w]);
            }
            printf("\n");
            break;
          } else {
            for (p = 0; p < length - 1; p++){
              for (q = p + 1; q < length; q++){
                if (stringRead[p] > stringRead[q]){
                  temp =  stringRead[p];
                  stringRead[p] = stringRead[q];
                  stringRead[q] = temp;
                }
              }
            }
            fprintf(copyFPtr,"%s\n", stringRead);
            printf("%s\n", stringRead);
            printf("\n");
            break;
          }

        case 1:
          //Sort Descending
          copyFPtr = fopen (copyFile,"w");

          if(hexFileFlag == 1){
            for (p = 0; p < hexLength - 1; p++){
              for (q = p + 1; q < hexLength; q++){
                if (hexArr[p] < hexArr[q]){
                  unsignTemp =  hexArr[p];
                  hexArr[p] = hexArr[q];
                  hexArr[q] = unsignTemp;
                }
              }
            }
            for(w = 0; w < hexLength; w++){
              fprintf(copyFPtr,"%#x\n", hexArr[w]);
              printf("%#x\n", hexArr[w]);
            }
            printf("\n");
            break;
          } else {
            for (p = 0; p < length - 1; p++){
              for (q = p + 1; q < length; q++){
                if (stringRead[p] < stringRead[q]){
                  temp =  stringRead[p];
                  stringRead[p] = stringRead[q];
                  stringRead[q] = temp;
                }
              }
            }
            fprintf(copyFPtr,"%s\n", stringRead);
            printf("%s\n", stringRead);
            printf("\n");
            break;
          }

        case 2:   
          //Counting Frequency
          copyFPtr = fopen (copyFile,"w");
          printf("\n");

          if(hexFileFlag){ //Tell user that the program is not run due to unique values
            fprintf(copyFPtr,"Unique Hex Values, Skipping\n");
            printf("Unique Hex Values, Skipping\n");
            break;
          } else {
          for(m=0; m < length;m++)  
          {
            count=1;
            if(stringRead[m]){
              for(o = m+1; o < length;o++){   
                if(stringRead[m]==stringRead[o]){
                  count++;
                  stringRead[o]='\0';
                }
              }  
              fprintf(copyFPtr,"Char: |  %-3c| %3d  | :Count\n",stringRead[m],count);
              printf("Char: |  %-3c| %3d  | :Count\n",stringRead[m],count);
            }
          }
          break;
          }
        case 3:

          //Apend a new string in middle of file
          printf("\nWriting: %s to the middle of file\n", writeString[i-1]);
          copyFPtr = fopen (copyFile,"w");
          for(j = 0; j < length/2; j++){
          fprintf(copyFPtr,"%c",letter[j]);}
          fputs(writeString[i-1],copyFPtr);
          addedLength = countString(writeString[i-1]);
          for(k = 1; k < (length/2); k++){
          fprintf(copyFPtr,"%c",letter[k+(length/2)+1]);}
          break;

      }
      //closing the current file
      fclose(copyFPtr);
      //erasing the file path for next itteration
      memset(copyFile,0,strlen(copyFile));   
    }
   }
   //Closing all of the files 
  fclose(fptr);
  fclose(copyFPtr);    
  //erasing the file path for the next itteration
  memset(datafile,0,strlen(datafile));
  }
   return 0;
}