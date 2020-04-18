#include "spimcore.h"
#include <stdlib.h>
#include <stdio.h>


void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{



      unsigned digitHolder[8];//will hold individual digits of the hexa-dec instruction
      unsigned fullBinInstr[32];//will hold the full 32 digit binary instruction

      //creating memory for each instruction
      op = (unsigned *) malloc(6 * sizeof(unsigned));
      r1 = (unsigned *) malloc(5 * sizeof(unsigned));
      r2 = (unsigned *) malloc(5 * sizeof(unsigned));
      r3 = (unsigned *) malloc(5 * sizeof(unsigned));
      funct = (unsigned *) malloc(6 * sizeof(unsigned));
      offset = (unsigned *) malloc(16 * sizeof(unsigned));
      jsec = (unsigned *) malloc(26 * sizeof(unsigned));

      //splitting the hexa-dec instruction into individual digits
      digitHolder[0] = instruction >> 28 & 0xf;
      digitHolder[1] = instruction >> 24 & 0xf;
      digitHolder[2] = instruction >> 20 & 0xf;
      digitHolder[3] = instruction >> 16 & 0xf;
      digitHolder[4] = instruction >> 12 & 0xf;
      digitHolder[5] = instruction >> 8 & 0xf;
      digitHolder[6] = instruction >> 4 & 0xf;
      digitHolder[7] = instruction >> 0 & 0xf;

      //the for-loop allows us to access every digit of the hexa-dec
      //instruction array
      for (int i = 0; i <= 7; i++)
      {
        /* Switch statement to assign the binary instruction to the
        fullBinInstr array based on the hexa-deci digit.
        Since each hexa digit holds 4 binary digits, i will be
        multiplied by 4 and either 0, 1, 2, or 3 will be added to the
        array index to move the index up and avoid overlap*/
        switch (digitHolder[i])
        {
          case 0x0:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0x1:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0x2:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0x3:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0x4:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0x5:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0x6:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0x7:
              fullBinInstr[i*4] = 0;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0x8:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0x9:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0xA:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0xB:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 0;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0xC:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0xD:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 0;
              fullBinInstr[(i*4)+3] = 1;
              break;

          case 0xE:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 0;
              break;

          case 0xF:
              fullBinInstr[i*4] = 1;
              fullBinInstr[(i*4)+1] = 1;
              fullBinInstr[(i*4)+2] = 1;
              fullBinInstr[(i*4)+3] = 1;
              break;
        }
      }

      //a counter-variable was made for each of the
      //instructions
      int jseccounter = 0;
      int offsetcounter = 0;
      int functcounter = 0;
      int r3counter = 0;
      int r2counter = 0;
      int r1counter = 0;
      int opcounter = 0;

      //in this for-loop, the fullBinInstr array is chopped up into
      //the separate instructions
      for (int i = 0; i < 32; i++)
      {
        if (i >= 6){
          jsec[jseccounter] = fullBinInstr[i];
          jseccounter++;
        }

        if (i >= 16){
          offset[offsetcounter] = fullBinInstr[i];
          offsetcounter++;
        }

        if(i >= 26){
          funct[functcounter] = fullBinInstr[i];
          functcounter++;
        }

        if(i >= 16 && i <= 20){
          r3[r3counter] = fullBinInstr[i];
          r3counter++;
        }

        if(i >= 11 && i <= 15){
          r2[r2counter] = fullBinInstr[i];
          r2counter++;
        }

        if(i >= 6 && i <= 10){
          r1[r1counter] = fullBinInstr[i];
          r1counter++;
        }

        if(i >= 0 && i <= 5){
          op[opcounter] = fullBinInstr[i];
          opcounter++;
        }
      }
}
