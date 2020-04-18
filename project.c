#include "spimcore.h"


/* ALU */
/* 10 Points */
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

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //Halt if not word aligned
    if (PC % 4 !=0)
        return 1;
    //Get intended instruction from Mem and write to instruction
    *instruction = Mem[PC >>2];
    return 0;
}




/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

  *offset = (instruction & 0xFFFF);
  *funct = (instruction & 0x3F);
  *jsec = (instruction & 0x3FFFFFF);
  *op = (instruction & 0xFC000000) >> 26;
  *r1 = (instruction & 0x3E00000) >> 21;
  *r2 = (instruction & 0x1F0000) >> 16;
  *r3 = (instruction & 0xF800) >> 11;

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */


//void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  if (ALUSrc == 1)//extended_value passes as B
  {
    if (ALUOp == 7){
      switch(funct){
        case 32: ALU(data1, extended_value, 0, &ALUresult, &Zero); return 0;
        case 34: ALU(data1, extended_value, 1, &ALUresult, &Zero); return 0;
        case 36: ALU(data1, extended_value, 4, &ALUresult, &Zero); return 0;
        case 37: ALU(data1, extended_value, 5, &ALUresult, &Zero); return 0;
        case 42: ALU(data1, extended_value, 2, &ALUresult, &Zero); return 0;
        case 43: ALU(data1, extended_value, 3, &ALUresult, &Zero); return 0;
        case 0: ALU(data1, extended_value, 6, &ALUresult, &Zero); return 0;
        case 39: ALU(data1, extended_value, 7, &ALUresult, &Zero); return 0;
      }
    }
    if (ALUOp != 7){
      ALU(data1, extended_value, ALUOp, &ALUresult, &Zero);
      return 0;
    }
  }

  if(ALUSrc == 0)//data2 passes as B
  {
    if (ALUOp == 7){
      switch(funct){
        case 32: ALU(data1, data2, 0, &ALUresult, &Zero); return 0;
        case 34: ALU(data1, data2, 1, &ALUresult, &Zero); return 0;
        case 36: ALU(data1, data2, 4, &ALUresult, &Zero); return 0;
        case 37: ALU(data1, data2, 5, &ALUresult, &Zero); return 0;
        case 42: ALU(data1, data2, 2, &ALUresult, &Zero); return 0;
        case 43: ALU(data1, data2, 3, &ALUresult, &Zero); return 0;
        case 0: ALU(data1, data2, 6, &ALUresult, &Zero); return 0;
        case 39: ALU(data1, data2, 7, &ALUresult, &Zero); return 0;
      }
    }
    if (ALUOp != 7){
      ALU(data1, data2, ALUOp, &ALUresult, &Zero);
      return 0;
    }
  }
  printf("\na Halt condition has occured at the ALU_operations function.\n");
  return 1;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    //If MemWrite is 1, write value of data 2 to ALUresult
    if (MemWrite == 1] {
        if (ALUresult % 4 == 0) //Check word alignment
            Mem[ALUresult >> 2] = data2;
    else
        return 1;
    }
    
    if (MemRead == 1) {
        if (ALUresult % 4 == 0)
            *memdata = Mem[ALUresult >> 2];
    else
        return 1;
    }
    

}

  



/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    if (RegWrite == 1) {
        if (MemtoReg == 1) {
            if (RegDst == 1) {
                Reg[r3] = memdata;  //writing memdata to rd
            else
                Reg[r2] = memdata; //writing memdata to rt
            }
        else
            if (RegDst == 1)
                Reg [r3] = ALUresult; //writing ALUresult to rd
            else
                Reg [r2] = ALUresult; //Writing ALUresult to rt
            
        }
    }
    

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
