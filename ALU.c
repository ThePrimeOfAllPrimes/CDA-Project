#include <stdio.h>
#include <stdlib.h>

unsigned ALUresult;
char Zero;
unsigned A;
unsigned B;
char ALUContol;

void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero);

void main()
{
  ALU(10, 20, 6, &ALUresult, &Zero);
}


void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  int z;
  switch(ALUControl)
  {
    case 0: z = A + B; break;
    case 1: z = A - B;
    case 2:
      if((signed)A < (signed)B){
        z = 1;
      }else{
        z = 0;
      } break;
    case 3:
      if(A < B){
        z = 1;
      }else{
        z = 0;
      } break;
    case 4: z = A & B; break;
    case 5: z = A | B; break;
    case 6: z = B << 16; break;
    case 7: z = !(A);break;
  }
  if (z == 0)
  {
    *Zero = 1;
  }else{
    *Zero = 0;
  }
  ALUresult = &z;
}
