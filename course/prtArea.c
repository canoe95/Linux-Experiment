#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int bss_var;
int data_var0 = 1;

int main(int argc, char **argv)
{
	printf("Bellow are addresses  of types of process's memory:\n");
	printf("Text Location:\n");      /*代码段*/
	printf("\tAddress of main(Code Segment):%p\n", main);
	printf("--------------------------------\n");
	
	int stack_var0 = 2;
	printf("Stack Location:\n");     /*栈*/
	printf("\tInitial end of stack:%p\n", &stack_var0);
	int stack_var1 = 3;
	printf("\tnew end of stack:%p\n", &stack_var1);
	printf("--------------------------------\n");
	
	printf("Data Location:\n");      /*数据段*/
	printf("\tAddress of data_var(Data segment): %p\n", &data_var0);
	static int data_var1 = 4;
	printf("\tnew end of data_var(Data Segment):%p\n", &data_var1);
	printf("--------------------------------\n");
	
	printf("BSS Location:\n");        /*BSS*/
	printf("\tAddress of bss_var:%p\n", &bss_var);
	printf("--------------------------------\n");
	
	char *b = sbrk((ptrdiff_t)0);
	printf("Heap Location:\n");        /*堆*/
	printf("\tInitial end of heap:%p\n", b);
	brk(b+4);
	b = sbrk((ptrdiff_t)0);
	printf("\tNew end of heap:%p\n", b);
	
	return 0;
}
