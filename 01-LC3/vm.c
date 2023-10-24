#include <stdio.h>

void codeRunner(FILE *fPtr){

}

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <file>", &argv[0]);
    } else{
        FILE *fPtr;
        fPtr = fopen("%s", argv[1]);
        codeRunner(fPtr);    
    }
    return 0;
}