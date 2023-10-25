# Implementing basic LC-3 vm

## Resources 
1. https://www.andreinc.net/2021/12/01/writing-a-simple-vm-in-less-than-125-lines-of-c
2. https://www.cs.utexas.edu/users/fussell/courses/cs310h/lectures/Lecture_10-310h.pdf

## Starter Notes
- Using max 16-bit = 2^16 = 65536 instructions --> Can only store 128KB 😔
```c
#define MEMORY_MAX (1 << 16)
__uint_16t memory[MEMORY_MAX];
```
We just created virtual memory for the VM

## CPU Registers (Total 10)
- 8 General Purpose Register (R0-R7)
- Program Counter 
- [Condition Flag Register](#condition-flag-register-r_cond)  

We will store registers in array Since we are creating Stack based VM

### Condition flag register (R_COND)
Contains information about the state of the processor after executing an instruction, and also contains status flags from last operation. Called as **Condition Bits**

It includes - 
1. Negative [FL_NEG]
2. Zero [FL_ZRO]
3. Positive [FL_POS]

## OP Codes (16)
- Instruction is 16bit long, left 4 bits storing the OP Code 
```c
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};
```
- Since instruction set are less, it is called as **RISC**

## What 2 DO? (summary)
1. Load one instruction from memory at the address of the PC register.
2. Increment the PC register.
3. Look at the opcode to determine which type of instruction it should perform.
4. Perform the instruction using the parameters in the instruction.
5. Go back to step 1.

### Sign extending n bits to 16 bits
Because in immediate mode it only has 5 bits but needed to be extended to 16bits to perform operations.

### Updating flags 
Earlier we defined a condition flags enum. Now Any time a value is written to a register, we need to update the flags to indicate its sign.

```c
void update_flags(uint16_t r)
{
    if (reg[r] == 0)
    {
        reg[R_COND] = FL_ZRO;
    }
    else if (reg[r] >> 15) /* a 1 in the left-most bit indicates negative */
    {
        reg[R_COND] = FL_NEG;
    }
    else
    {
        reg[R_COND] = FL_POS;
    }
}
```