void started(char num, int arg0, int arg1, int arg2);
void starter();
void call();
char read_IRQ();
void crt();
void del();
void log();
void write_c();
void write_i();
void read_c();
void read_i();
void SVIS();
void LF();
//void TFA();

typedef void (*fs)(void);

char IRQ = 0x0;
int* arg0 = (int*)0xFE1;
int* arg1 = (int*)0xFDD;
int* arg2 = (int*)0xFD9;
int* arg3 = (int*)0xFD5;
int* arg4 = (int*)0xFD1;
int* arg5 = (int*)0xFCD;

char* ex_file_root = (char*)0xFCC;
int* ex_file = (int*)0xFC8;

char* buttonread = (char*)0xFEB;
int* timer = (int*)0xFE7;

char* alfabet = (char*)0x30000;

char* start = (char*)0xFE6;

char* videostrt = (char*)0xA0000;
char* videofin = (char*)0xA0000+0xFFFF;

int filesysfrom = 0x40000;
char* filesys = 0x0;
int filesys_size = 0x400;

int file_from = 0x0;
int file_to = 0x0;
int file_place_size = 0x200000;

//short int *globalx = 0x0;
//short int *globaly = 0x0;

int* globalx = (int*)0xE00;
int* globaly = (int*)0xE04;

char color = 0x2;
char warcolor = 0x4;
char attcolor = 0x6;

char animationspeed = 0x1;

int masslen = 37;

char clear_on_off = 0x1;

void main()
{
	filesys = (char*)filesysfrom;
	file_from = filesysfrom+filesys_size;
	file_to = file_from+file_place_size;

	IRQ = read_IRQ();

	if(IRQ == 0x3)
	{
		write_c();
	}
	else if(IRQ == 0x5)
	{
		read_c();
	}
	else if(IRQ == 0x4)
	{
		write_i();
	}
	else if(IRQ == 0x6)
	{
		read_i();
	}
	else if(IRQ == 0x7E)
	{
		starter();
	}
	else if(IRQ == 0x7F)
	{
		call();
	}
	else if(IRQ == 0x1)
	{
		crt();
	}
	else if(IRQ == 0x2)
	{
		del();
	}
	else if(IRQ == 0x7)
	{
		SVIS();
	}
	else if(IRQ == 0x8)
	{
		LF();
	}
	else if(IRQ == 0x9)
	{
		take_len();
	}
	else if(IRQ == 0xA)
	{
		f_f();
	}
	else if(IRQ == 0xB)
	{
		take_file_flags();
	}
	else if(IRQ == 0xC)
	{
		set_file_flags();
	}
/*	else if(IRQ == 0x9) у тебя есть read
	{
		TFA();
	}*/
	else if(IRQ == 0x1F)
	{
		log();
	}
	else if(IRQ == 0x20)
	{
		clear(*arg0, *arg1);
	}
	else if(IRQ == 0x30)
	{
		exit();
	}
	return;
}

#include "primc_lib_graphics.c"
#include "primc_lib_main.c"

/*void TFA()
{
	int adr = take_file_adr(find_file(*arg0, *arg1))+2;
	if(!adr)
	{
		*arg2 = 0x1;
	}
	else
	{
		*arg2 = 0x0;
		*arg0 = adr;
	}
}*/

char read_IRQ()
{
	char out = 0x0;
	asm volatile(
	"movl $0xFE6, %%eax\n"
	"movb (%%eax), %0"
	:"=g"(out)
	:
	:"eax"
	);
	return out;
}

void exit()
{
	if(*arg5 == 0x30)
	{
		*arg3 = 0x0;
		*arg5 = 0x0;
		clear(0x0, 0xFFFF);
	}
	fs prog = (fs) 0x4000;
	load_num(0xF00000, 0xFFFFF, 0x0);
	prog();
}

void call()
{
	fs prog = (fs) 0xF00000;
	char* gfhm = (char*)take_file_adr(find_file(*arg0, *arg1))+2;
        int* ki = (int*)find_file(*arg0, *arg1);
        if(srav_string("CUTE", *arg1, 0x0) && take_file_size(find_file(*arg0, *arg1))*0x200 < 0xFFFFF && ki && take_file_root(find_file(*arg0, *arg1)) & 0b100)
	{
		*ex_file_root = take_file_priv(find_file(*arg0, *arg1));
		*ex_file = find_file(*arg0, *arg1);
        	//load_num(0xF00000, take_file_size(find_file(*arg0, *arg1))*0x200, 0x0);
		load_num(0xF00000, 0xFFFFF, 0x0);
        	load(take_file_adr(find_file(*arg0, *arg1))+2, 0xF00000, take_file_size(find_file(*arg0, *arg1))*0x200-4);
        	asm volatile(
        		"movb $0xC3, (0xFFFFFF)"
        	);
		prog();
        	*arg2 = 0x0;
        }
        else if(!srav_string("CUTE", *arg1, 0x0) && ki)
        {
        	*arg2 = 0x1;
        	//strprint_to_global(print_string(*globalx, *globaly, "This is not an executable", warcolor, 0x0, 0x0));
        }
        else if(ki)
        {
        	*arg2 = 0x2;
        	//strprint_to_global(print_string(*globalx, *globaly, "Executable file is very large", warcolor, 0x0, 0x0));
        }
        else if(!(take_file_root(find_file(*arg0, *arg1)) & 0b100) && ki)
        {
        	*arg2 = 0x3;
        	//strprint_to_global(print_string(*globalx, *globaly, "No root to execute", warcolor, 0x0, 0x0));
        }
        else
        {
        	*arg2 = 0x4;
        	//strprint_to_global(print_string(*globalx, *globaly, "No such file exists", warcolor, 0x0, 0x0));
        }

	if(*arg2)
	{
		*arg3 = 0xFE;
	}
	else
	{
		*arg3 = 0x0;
	}
	exit();
	//return;
}

void starter()
{
	load(0x1000, 0x30000, 0x1100);
	load_num(0x1000, 0x1100, 0x0);

	print_string(0, 1, "Object", color, 0x1, 0x1);
	print_string(6, 1, "|", color, 0x1, 0x1);
	print_string(13, 0, "CORP.", warcolor, 0x1, 0x1);
	print_string(12, 1, "Twelwe", color, 0x1, 0x2);
	read_rastr_0(16*8, 10*8, alfabet+0xE00, 0x2, 0x0, 0x3);
	print_string(14, 12, "SIS is SIS", attcolor, 0x1, 0x1);
	square(12*8, 7*8, 1*8, 10*8, warcolor);
	short int ghj = 7;
	int time = *timer;
	while(time+40 > *timer)
	{
		fill_square(12*8+1, ghj*8+1, 1*8-2, 1*8-2, attcolor);
		wait(0x3);
		ghj++;
	}
	wait(0x5);
	clear(0x0, 0xFFFF);

	filesys = (char*)filesysfrom;
	file_from = filesysfrom+filesys_size;
	file_to = file_from+file_place_size;


	if (create_filesys(filesys, filesys_size, 0x0))
	{
		wait(0x10);
		clear(0x0, 0xFFFF);
		strprint_to_global(print_string(*globalx, *globaly, "Can't create filesys, please reboot you PC", warcolor, 0x0, 0x1));
		while(1==1){}
	}

	create_file("GAME", "CUTE", 0x20, filesys, 0b100);
	load(0xF0F000, take_file_adr(find_file("GAME", "CUTE"))+2, 0x20*0x200-4);
	//load_num(0xF0F000, 0x20*0x200, 0x0);
	set_file_priv(find_file("GAME", "CUTE"), 0x3);

	create_file("RETEXT", "CUTE", 0x21, filesys, 0b100);
	load(0xF1F000, take_file_adr(find_file("RETEXT", "CUTE"))+2, 0x21*0x200-4);
	//load_num(0xF1F000, 0x21*0x200, 0x0);
	set_file_vis(find_file("RETEXT", "CUTE"), 0x0);
	set_file_priv(find_file("RETEXT", "CUTE"), 0x2);

	create_file("COMPILER", "CUTE", 0x1D, filesys, 0b100);
	load(0xF2A000, take_file_adr(find_file("COMPILER", "CUTE"))+2, 0x1D*0x200-4);
	//load_num(0xF2A000, 0x1D*0x200, 0x0);
	set_file_vis(find_file("COMPILER", "CUTE"), 0x0);
	set_file_priv(find_file("COMPILER", "CUTE"), 0x2);

	create_file("GRAPHIT", "CUTE", 0x3F, filesys, 0b100);
	/*load(0x4200, take_file_adr(find_file("GRAPHIT", "CUTE"))+2, take_file_size(find_file("GRAPHIT, "CUTE"))*0x200-4);
	load_num(0x4200, take_file_size(find_file("GRAPHIT", "CUTE"))*0x200, 0x0);*/
	load(0xF00000, take_file_adr(find_file("GRAPHIT", "CUTE"))+2, 0x3F*0x200-4);
	//load_num(0xF00000, 0x3F*0x200, 0x0);
	set_file_vis(find_file("GRAPHIT", "CUTE"), 0x0);
	set_file_priv(find_file("GRAPHIT", "CUTE"), 0x1);

	wait(0x12);
	clear(0x0, 0xFFFF);

	return;
}

void f_f()
{
	*arg2 = find_file(*arg0, *arg1);
}

void crt()
{
	*arg2 = create_file(*arg0, *arg1, *arg2, filesys, *arg3);

	if(*arg4 < *ex_file_root && !*arg2)
	{
		set_file_priv(find_file(*arg0, *arg1), *ex_file_root);
	}
	else if(*arg4 >= *ex_file_root && !*arg2)
	{
		set_file_priv(find_file(*arg0, *arg1), *arg4);
	}
}

void set_file_flags()
{
	if(*ex_file_root <= take_file_priv(find_file(*arg0, *arg1)) && *arg2 <= 0b111 && *arg2 >= 0x0)
        {
        	set_file_root(find_file(*arg0, *arg1), *arg2);
		*arg2 = 0x0;
        }
	else if(*arg2 > 0b111 || *arg2 <= 0x0)
	{
		*arg2 = 0x1;
	}
	else
        {
                *arg2 = 0x4;// root error
        }
}

void take_file_flags()
{
	if(*ex_file_root <= take_file_priv(find_file(*arg0, *arg1)))
        {
		*arg3 = take_file_root(find_file(*arg0, *arg1));
	}
	else
        {
                *arg2 = 0x4;// root error
        }
}

void take_len()
{
	if(*ex_file_root <= take_file_priv(find_file(*arg0, *arg1)))
        {
		*arg3 = take_file_size(find_file(*arg0, *arg1));
	}
	else
        {
                *arg2 = 0x4;// root error
        }
}

void del()
{
	if(*ex_file_root <= take_file_priv(find_file(*arg0, *arg1)))
	{
		*arg2 = delete_file(*arg0, *arg1, filesys);
	}
	else
	{
		*arg2 = 0x4;// root error
	}
}

void log()
{
	int size = str_to_int(*arg1);
        int start = str_to_int(*arg0);
        int* ki = (int*)start;
        int plus = 0x0;
        while(plus < size)
        {
        	ki = (int*)(start+plus);
        	strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
                plus++;
        }
}

void write_c()
{
	if(!find_file(*arg0, *arg1))
	{
		*arg2 = 0x1;
	}
	else if(take_file_size(find_file(*arg0, *arg1))*0x200-7 <= *arg2 && *arg2 < 0x0)
	{
		*arg2 = 0x2;
	}
	else if(!(take_file_root(find_file(*arg0, *arg1)) & 0b010))
	{
		*arg2 = 0x3;
	}
	else if(*ex_file_root > take_file_priv(find_file(*arg0, *arg1)))
	{
		*arg2 = 0x4;
	}
	else
	{
		int goa = take_file_adr(find_file(*arg0, *arg1))+*arg2+2;
		char* go = (char*)take_file_adr(find_file(*arg0, *arg1))+*arg2+2;
		*go = *arg3;
		*arg2 = 0x0;
	}
}

void write_i()
{
	if(!find_file(*arg0, *arg1))
	{
		*arg2 = 0x1;
	}
	else if(take_file_size(find_file(*arg0, *arg1))*0x200-7 <= *arg2 && *arg2 < 0x0)
	{
		*arg2 = 0x2;
	}
	else if(!(take_file_root(find_file(*arg0, *arg1)) & 0b010))
	{
		*arg2 = 0x3;
	}
	else if(*ex_file_root > take_file_priv(find_file(*arg0, *arg1)))
	{
		*arg2 = 0x4;
	}
	else
	{
		int goa = take_file_adr(find_file(*arg0, *arg1))+*arg2+2;
		int* go = (int*)goa;
		*go = *arg3;
		*arg2 = 0x0;
	}
}

void read_c()
{
	if(!find_file(*arg0, *arg1))
	{
		*arg2 = 0x1;
	}
	else if(take_file_size(find_file(*arg0, *arg1))*0x200-7 <= *arg2 && *arg2 < 0x0)
	{
		*arg2 = 0x2;
	}
	else if(!(take_file_root(find_file(*arg0, *arg1)) & 0b001))
	{
		*arg2 = 0x3;
	}
	else if(*ex_file_root > take_file_priv(find_file(*arg0, *arg1)))
	{
		*arg2 = 0x4;
	}
	else
	{
		int goa = take_file_adr(find_file(*arg0, *arg1))+*arg2+2;
		char* go = (char*)goa;
		*arg3 = *go;
		*arg2 = 0x0;
	}
}

void read_i()
{
	if(!find_file(*arg0, *arg1))
	{
		*arg2 = 0x1;
	}
	else if(take_file_size(find_file(*arg0, *arg1))*0x200-7 <= *arg2 && *arg2 < 0x0)
	{
		*arg2 = 0x2;
	}
	else if(!(take_file_root(find_file(*arg0, *arg1)) & 0b001))
	{
		*arg2 = 0x3;
	}
	else if(*ex_file_root > take_file_priv(find_file(*arg0, *arg1)))
	{
		*arg2 = 0x4;
	}
	else
	{
		int goa = take_file_adr(find_file(*arg0, *arg1))+*arg2+2;
		int* go = (int*)goa;
		*arg3 = *go;
		*arg2 = 0x0;
	}
}

void SVIS()
{
	if(find_file(*arg0, *arg1) && *arg3 != 0x45)
	{
		set_file_vis(find_file(*arg0, *arg1), *arg2);
	}
	else if(*arg3 == 0x45)
	{
		if(!take_file_vis(find_file(*arg0, *arg1)))
		{
			set_file_vis(find_file(*arg0, *arg1), 0x1);
		}
		else
		{
			set_file_vis(find_file(*arg0, *arg1), 0x0);
		}
	}
	else
	{
		*arg2 = 0x1;
		return;
	}
        *arg2 = 0x0;
}

void LF()
{
        int sdvg = 0x0;

        while(1==1)
        {
    	    if(*(filesys+sdvg)+0x10 == 0xE && *(filesys+sdvg+1)+0x10 == 0xF)
            {
            	break;
            }
            else if((*(filesys+sdvg)+0x10 == 0xC && *(filesys+sdvg+1)+0x10 == 0xF) && (take_file_vis(filesys+sdvg) || *arg0))
            {
            	int file = filesys+sdvg;
                sdvg+=0xE;

                struct strprint p = print_string(*globalx, *globaly, filesys+sdvg, warcolor, 0x0, 0x0);
                sdvg += p.len;
                strprint_to_global(p);
                sdvg++;

                strprint_to_global(print_string(*globalx, *globaly, ".", warcolor, 0x0, 0x0));

                p = print_string(*globalx, *globaly, filesys+sdvg, warcolor, 0x0, 0x0);
                sdvg += p.len;
                strprint_to_global(p);

                if(*arg1)
                {
                	strprint_to_global(print_string(*globalx, *globaly, "|", warcolor, 0x0, 0x0));
                        strprint_to_global(print_int(*globalx, *globaly, take_file_size(file), warcolor, 0x0, 0x3));
                	strprint_to_global(print_string(*globalx, *globaly, "|", warcolor, 0x0, 0x0));
			if(take_file_root(file) & 0b001)
			{
				strprint_to_global(print_string(*globalx, *globaly, "r", warcolor, 0x0, 0x0));
			}
			if(take_file_root(file) & 0b010)
			{
				strprint_to_global(print_string(*globalx, *globaly, "w", warcolor, 0x0, 0x0));
			}
			if(take_file_root(file) & 0b100)
			{
				strprint_to_global(print_string(*globalx, *globaly, "e", warcolor, 0x0, 0x0));
			}
                	strprint_to_global(print_string(*globalx, *globaly, "|", warcolor, 0x0, 0x0));
                        strprint_to_global(print_int(*globalx, *globaly, take_file_priv(file), warcolor, 0x0, 0x0));
                	strprint_to_global(print_string(*globalx, *globaly, "\n", warcolor, 0x0, 0x0));
		}

                if(!*arg1)
                {
                	strprint_to_global(print_string(*globalx, *globaly, ",", warcolor, 0x0, 0x0));
		}
            }
            else if((*(filesys+sdvg)+0x10 == 0xC && *(filesys+sdvg+1)+0x10 == 0xF) && (!take_file_vis(filesys+sdvg) && !*arg0))
            {
            	while(1==1)
                {
                	if(*(filesys+sdvg)+0x10 == 0xD && *(filesys+sdvg+1)+0x10 == 0xF)
                        {
                        	break;
                        }
                        	sdvg++;
                }
            }
            sdvg++;
	}
        strprint_to_global(print_string(*globalx, *globaly, "\b", attcolor, 0x0, 0x0));
}

/*void started(char num, int arg0, int arg1, int arg2)
{
	if(*start == 0x1)
	{
		strprint_to_global(print_string(*globalx, *globaly, "System crashed, please reboot you PC :/", warcolor, 0x0, 0x1));
		while(1==1){}
	}
	else
	{
		starter();
		*start = 0x1;
	}

	filesys = (char*)filesysfrom;
	file_from = filesysfrom+filesys_size;
	file_to = file_from+file_place_size;

	//int masslen = 37;//39*24*2;//37
	char massive0[masslen+1];
	char massive1[masslen+1];
	char massive2[masslen+1];

	short int stack_size = 0x5;
	char stack[stack_size*(masslen+1)];
	char* stk = (char*)stack;

	//strprint_to_global(print_int(*globalx, *globaly, stk, warcolor, 0x0, 0x6));

	while(1==1)
	{
		wait(0x2);
		load_num(massive0, masslen, 0x0);
		load_num(massive1, masslen, 0x0);
		load_num(massive2, masslen, 0x0);
		strprint_to_global(print_string(*globalx, *globaly, ">>", attcolor, 0x0, 0x1));
		strprint_to_global(read_string(massive0, masslen, *globalx, *globaly, 0x0, stk, stack_size));
		strprint_to_global(print_string(*globalx, *globaly, "\n", attcolor, 0x0, 0x0));

		stack_mandge(massive0, stack, stack_size, masslen);

		if(*globaly >= 24)
		{
			clear(0x0, 0xFFFF);
		}

		if(srav_string("DIE", massive0, 0x0))
		{
			strprint_to_global(print_string(*globalx, *globaly, "Nope", warcolor, 0x0, 0x1));
		}
		else if(srav_string("CRT ", massive0, 0x2))
		{
			redakt_string(redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, ' ', 0x0).str0, massive0, '.', 0x0);
			create_file(massive1, massive0, str_to_int(massive2), filesys, 0x0);
		}
		else if(srav_string("DEL ", massive0, 0x2))
		{
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			delete_file(massive1, massive2, filesys);
		}
		else if(srav_string("FLOG ", massive0, 0x2))
		{
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);

			int* ki = (int*)(find_file(massive1, massive2));
			char* sled = (char*)(find_file(massive1, massive2));
			short int plus = 0x0;
			if(ki)
			{
                        	strprint_to_global(print_int(*globalx, *globaly, ki, warcolor, 0x0, 0x6));
                        	strprint_to_global(print_string(*globalx, *globaly, "|", attcolor, 0x0, 0x0));
				while(1==1)
                        	{
                        		ki = (int*)(find_file(massive1, massive2)+plus);
                        		if(*(sled)+0x10 == 0xD && *(sled+1)+0x10 == 0xF)
                        		{
                        			break;
                        		}
                        	        strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
					sled++;
                        	        plus++;
                        	}
				for(int i = 0; i < 0x2; i++)
				{
                        		ki = (int*)(find_file(massive1, massive2)+plus);
                        		plus++;
                        		strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
                        	}
                        	strprint_to_global(print_string(*globalx, *globaly, "|", attcolor, 0x0, 0x0));
				for(int i = 0; i < 0x2; i++)
				{
                        		ki = (int*)(take_file_adr(find_file(massive1, massive2))+i);
                        		strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
                        	}
                        	strprint_to_global(print_string(*globalx, *globaly, "|", attcolor, 0x0, 0x0));
				for(int i = 0x2; i >= 0x1; i--)
				{
                        		ki = (int*)(take_file_adr(find_file(massive1, massive2))+take_file_size(find_file(massive1, massive2))*0x200-i);
                        		strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
                        	}
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "No such file", warcolor, 0x0, 0x0));
			}
		}
		else if(srav_string("LOG ", massive0, 0x2))
		{
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, ' ', 0x0);
			int size = str_to_int(massive2);
			int start = str_to_int(massive1);
			int* ki = (int*)start;
			int plus = 0x0;
			while(plus < size)
			{
				ki = (int*)(start+plus);
				strprint_to_global(print_int(*globalx, *globaly, *ki, warcolor, 0x0, 0x1));
				plus++;
			}
		}
		else if(srav_string("LF", massive0, 0x0) || srav_string("LF ", massive0, 0x2))
		{
			if(srav_string("LF ", massive0, 0x2))
			{
				redakt_string(massive0, massive1, ' ', 0x0);
			}

			int sdvg = 0x0;

			while(1==1)
			{
				if(*(filesys+sdvg)+0x10 == 0xE && *(filesys+sdvg+1)+0x10 == 0xF)
				{
					break;
				}
				else if((*(filesys+sdvg)+0x10 == 0xC && *(filesys+sdvg+1)+0x10 == 0xF) && (take_file_vis(filesys+sdvg) || (srav_string("LF", massive0, 0x1) && srav_string("H", massive1, 0x1))))
				{
					int file = filesys+sdvg;
					sdvg+=0xE;

					struct strprint p = print_string(*globalx, *globaly, filesys+sdvg, warcolor, 0x0, 0x0);
					sdvg += p.len;
					strprint_to_global(p);
					sdvg++;

					strprint_to_global(print_string(*globalx, *globaly, ".", warcolor, 0x0, 0x0));


					p = print_string(*globalx, *globaly, filesys+sdvg, warcolor, 0x0, 0x0);
					sdvg += p.len;
					strprint_to_global(p);

					if(srav_string("LF", massive0, 0x1) && srav_string("S", massive1, 0x1))
					{
						strprint_to_global(print_string(*globalx, *globaly, "|", warcolor, 0x0, 0x0));
						strprint_to_global(print_int(*globalx, *globaly, take_file_size(file), warcolor, 0x0, 0x3));
					}

					strprint_to_global(print_string(*globalx, *globaly, ",", warcolor, 0x0, 0x0));
				}
				else if((*(filesys+sdvg)+0x10 == 0xC && *(filesys+sdvg+1)+0x10 == 0xF) && (!take_file_vis(filesys+sdvg) && !(srav_string("LF", massive0, 0x1) && srav_string("H", massive1, 0x1))))
				{
					while(1==1)
					{
						if(*(filesys+sdvg)+0x10 == 0xD && *(filesys+sdvg+1)+0x10 == 0xF)
						{
							break;
				 		}
				 		sdvg++;
				 	}
				}
				sdvg++;
			}
                       	strprint_to_global(print_string(*globalx, *globaly, "\b", attcolor, 0x0, 0x0));
		}
		else if(srav_string("CALL ", massive0, 0x2))
		{
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			char* gfhm = (char*)take_file_adr(find_file(massive1, massive2))+2;
			int* ki = (int*)find_file(massive1, massive2);
			if(srav_string("CUTE", massive2, 0x0) && take_file_size(find_file(massive1, massive2))*0x200 < 0xFFFFF && ki)// && *gfhm != 0x0
			{
				load_num(0xF00000, take_file_size(find_file(massive1, massive2))*0x200, 0x0);
				load(take_file_adr(find_file(massive1, massive2))+2, 0xF00000, take_file_size(find_file(massive1, massive2))*0x200-4);
				asm volatile(
						"movb $0xC3, (0xFFFFFF)\n\t"
						"call $0b0000000000001000, $0xF00000"
					    );
				load_num(0xF00000, take_file_size(find_file(massive1, massive2))*0x200+2, 0x0);
			}
			else if(!srav_string("CUTE", massive2, 0x0) && ki)
			{
				strprint_to_global(print_string(*globalx, *globaly, "This is not an executable", warcolor, 0x0, 0x0));
			}
			else if(ki)
			{
				strprint_to_global(print_string(*globalx, *globaly, "Executable file is very large", warcolor, 0x0, 0x0));
			}
			else if(ki)
			{
				strprint_to_global(print_string(*globalx, *globaly, "Executable file is empty", warcolor, 0x0, 0x0));
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "No such file exists", warcolor, 0x0, 0x0));
			}
		}
		else if(srav_string("ANIM", massive0, 0x0))
		{
			clear(0x0, 0xFFFF);
			short int cadr = 0x0;
			int time = *timer;
			while(1==1)
			{
				if(find_buttn(0x1E))
				{
					break;
				}
				else if(time+animationspeed < *timer)
				{
					cadr = read_rastr_anim(160, 100, alfabet+0xF00, warcolor, cadr);
					time = *timer;
				}
			}
		}
		else if(srav_string("SVIS ", massive0, 0x2))
		{
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			if(find_file(massive1, massive2))
			{
				char in = take_file_vis(find_file(massive1, massive2));
				if(in == 0x0)
				{
					set_file_vis(find_file(massive1, massive2), 0x1);
				}
				else if(in == 0x1)
				{
					set_file_vis(find_file(massive1, massive2), 0x0);
				}
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "No such file", warcolor, 0x0, 0x0));
			}
                        strprint_to_global(print_string(*globalx, *globaly, "\b", attcolor, 0x0, 0x0));
		}
		else
		{
			strprint_to_global(print_string(*globalx, *globaly, "Command not found", warcolor, 0x0, 0x0));
		}

		if(!srav_string("CLEAR", massive0, 0x0) && !srav_string("ANIM", massive0, 0x0) && !srav_string("CALL", massive0, 0x0))
		{
			strprint_to_global(print_string(*globalx, *globaly, "\n", attcolor, 0x0, 0x0));
		}
		else
		{
			clear(0x0, 0xFFFF);
		}
	}
}*/

