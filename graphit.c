void main()
{
	st();
}

char* IRQ = (char*)0xFE6;
int* arg0 = (int*)0xFE1;
int* arg1 = (int*)0xFDD;
int* arg2 = (int*)0xFD9;
int* arg3 = (int*)0xFD5;
int* arg4 = (int*)0xFD1;
int* arg5 = (int*)0xFCD;

typedef void (*fs)(void);
fs OS = (fs) 0x10000;

char* ex_file_root = (char*)0xFD4;
int* ex_file = (int*)0xFD0;

int* globalx = (int*)0xE00;
int* globaly = (int*)0xE04;

char color = 0x2;
char warcolor = 0x4;
char attcolor = 0x6;

char* buttonread = (char*)0xFEB;
int* timer = (int*)0xFE7;

char* alfabet = (char*)0x30000;

char* start = (char*)0xFE6;
char* start0 = (char*)0xF90;

char animationspeed = 0x1;

int masslen = 37;

char* videostrt = (char*)0xA0000;
char* videofin = (char*)0xA0000+0xFFFF;

char stack[] = "STACK";
char text[] = "TEXT";


#include "graphit_lib.c"
#include "graphit_lib_graph.c"

void st()
{

	if(*arg3 == 0xFE)
	{
		strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
		strprint_to_global(print_int(*globalx, *globaly, *arg2, attcolor, 0x0, 0x1));
		strprint_to_global(print_string(*globalx, *globaly, "\n", warcolor, 0x0, 0x0));
	}

	char massive0[masslen+1];
	char massive1[masslen+1];
	char massive2[masslen+1];

	short int stack_size = 0x5;
	//char stack[stack_size*(masslen+1)];
	if(crt(stack, text, 1, 0x0) && !*start0)
	{
		strprint_to_global(print_string(*globalx, *globaly, "Can't create stack file\n", warcolor, 0x0, 0x0));
	}

	if(!*start0)
	{
		SVIS(stack, text, 0x0);
	}

	if(!*start0)
	{
		*start0 = 0x1;
	}

	while(1)
	{
	 	wait(0x6);

		load_num(massive0, masslen, 0x0);
		load_num(massive1, masslen, 0x0);
		load_num(massive2, masslen, 0x0);

	        strprint_to_global(print_string(*globalx, *globaly, ">>", attcolor, 0x0, 0x0));
	        strprint_to_global(read_string(massive0, masslen, *globalx, *globaly, 0x0, stack_size));
	        strprint_to_global(print_string(*globalx, *globaly, "\n", attcolor, 0x0, 0x0));

	        stack_mandge(massive0, stack_size, masslen);

		char _n = 0x0;

		if(*globaly >= 24)
                {
			_n = 0x1;
                        clear(0x0, 0xFFFF);
                }
                else if(srav_string("CRT ", massive0, 0x2))
                {
                        redakt_string(redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, ' ', 0x0).str0, massive0, '.', 0x0);
			if(!srav_string(massive0, "CUTE", 0x0))
			{
				char out = crt(massive1, massive0, str_to_int(massive2), 0x3);
                        	if(!out)
                        	{
					strprint_to_global(print_string(*globalx, *globaly, "File create...", attcolor, 0x0, 0x0));
					strprint_to_global(print_string(*globalx, *globaly, "Ok", color, 0x0, 0x0));
				}
                		else
                		{
					strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
                			strprint_to_global(print_int(*globalx, *globaly, out, attcolor, 0x0, 0x1));
                		}
                	}
			else
                        {
                        	strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
                        	strprint_to_global(print_string(*globalx, *globaly, "7", attcolor, 0x0, 0x0));
                        }
		}
		else if(srav_string("DEL ", massive0, 0x2))
                {
                        redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			char out = del(massive1, massive2);
                        if(!out)
			{
				strprint_to_global(print_string(*globalx, *globaly, "File delete...", attcolor, 0x0, 0x0));
				strprint_to_global(print_string(*globalx, *globaly, "Ok", color, 0x0, 0x0));
                	}
                	else
                	{
				strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
                		strprint_to_global(print_int(*globalx, *globaly, out, attcolor, 0x0, 0x1));
                	}
		}
                else if(srav_string("LF ", massive0, 0x2) || srav_string("LF", massive0, 0x0))
                {
                	char _H = 0x0;
			char _S = 0x0;
			if(srav_string("LF ", massive0, 0x2))
			{
                        	redakt_string(massive0, massive1, ' ', 0x0);
				if(srav_string("H", massive1, 0x1))
                        	{
                        		_H = 0x1;
                        	}
                        	if(srav_string("S", massive1, 0x1))
                        	{
                        		_S = 0x1;
                        	}
			}
                        LF(_H, _S);
                }
		else if(srav_string("CALL ", massive0, 0x2))
                {
			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			if(srav_string("RETEXT", massive1, 0x0) && srav_string("CUTE", massive2, 0x0))
			{
				strprint_to_global(print_string(*globalx, *globaly, "Please start this with: ", attcolor, 0x0, 0x0));
				strprint_to_global(print_string(*globalx, *globaly, "RED", color, 0x0, 0x0));
			}
			else
			{
				*arg0 = massive1;
				*arg1 = massive2;
				*arg3 = 0x7F;
                		exit();
			}
                }
		else if(srav_string("RED ", massive0, 0x2))
                {
                	char _0[] = "RETEXT";
                	char _1[] = "CUTE";

			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);

			crt("BUFFER", "TEXT", 0x1, 0x2);
			copy_str_file(massive2, "BUFFER", "TEXT", copy_str_file(massive1, "BUFFER", "TEXT", 0x0));
			SVIS("BUFFER", "TEXT", 0x0);

			*arg3 = 0x7F;
			*arg0 = _0;
			*arg1 = _1;
                	exit();
                }
		else if(srav_string("COM ", massive0, 0x2))
                {
                	char _0[] = "COMPILER";
                	char _1[] = "CUTE";

			redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);

			crt("BUFFER", "TEXT", 0x1, 0x2);
			copy_str_file(massive2, "BUFFER", "TEXT", copy_str_file(massive1, "BUFFER", "TEXT", 0x0));
			SVIS("BUFFER", "TEXT", 0x0);

			*arg3 = 0x7F;
			*arg0 = _0;
			*arg1 = _1;
                	exit();
                }
                else if(srav_string("SVIS ", massive0, 0x2))
                {
                        redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0);
			char err = SVIS(massive1, massive2, 0x45);
			if(!err)
			{
				strprint_to_global(print_string(*globalx, *globaly, "\b", warcolor, 0x0, 0x0));
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
                                strprint_to_global(print_int(*globalx, *globaly, err, attcolor, 0x0, 0x1));
			}
		}
		else if(srav_string("SFF ", massive0, 0x2))
                {
                        redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, '.', 0x0).str1;
			load_num(massive0, masslen, 0x0);
			redakt_string(massive2, massive0, ' ', 0x0);
			char err = set_file_flags(massive1, massive2, str_to_int(massive0));
			if(!err)
			{
				strprint_to_global(print_string(*globalx, *globaly, "\b", warcolor, 0x0, 0x0));
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "Error code: ", warcolor, 0x0, 0x0));
                                strprint_to_global(print_int(*globalx, *globaly, err, attcolor, 0x0, 0x1));
			}
		}
                else if(srav_string("LOG ", massive0, 0x2))
                {
                        redakt_string(redakt_string(massive0, massive1, ' ', 0x0).str1, massive2, ' ', 0x0);
                        log(massive1, massive2);
                }
		/*else if(srav_string("FLG", massive0, 0x0))
                {
			fs Obs = (fs) 0x4600;
			Obs();
                }*/
                else if(srav_string("CLEAR", massive0, 0x0))
                {
                        clear(0x0, 0xFFFF);
                }
		else
		{
			strprint_to_global(print_string(*globalx, *globaly, "Undefind command", color, 0x0, 0x0));
		}

		if(!srav_string("CLEAR", massive0, 0x0) && !_n)
		{
			strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
		}
	}
	exit();
}
