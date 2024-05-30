#include <avr/io.h>


#include "zrtos_vm.h"

unsigned a = 0;
unsigned b = 0;

void *callback0(void *args){
	static uint64_t a = 0;
	return 1;
}

void *callback1(void *args){
	static uint64_t a = 0;
	return 1;
}

int main(void){

}

