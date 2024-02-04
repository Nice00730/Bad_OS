char* IRQ = (char*)0xFE6;
int* arg0 = (int*)0xFE1;
int* arg1 = (int*)0xFDD;
int* arg2 = (int*)0xFD9;
int* arg3 = (int*)0xFD5;

//char* ex_file_root = (char*)0xFD4;
//int* ex_file = (int*)0xFD0;

char scht;

typedef void (*fs)(void);

void main()
{

	asm volatile
	(
		//"mov $0x6FFF, %eax\n\t"
		"mov $0x6FFF, %esp"
	);

	fs OS = (fs) 0x10000;
	while(1)
	{
		if(!scht)
		{
			*IRQ = 0x7E;
			scht = 0x1;
		}
		else if(*arg3 == 0x7F)
		{
			*IRQ = 0x7F;
		}
		else if(scht == 0x1)
		{
			char _0[] = "GRAPHIT";
			char _1[] = "CUTE";
			*IRQ = 0x7F;
			*arg0 = _0;
			*arg1 = _1;
		}
		OS();
	}
}
