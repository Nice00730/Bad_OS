char read_string(int from, char* filen, char* filee, char* massive);
void exite(char err);
char name_str(char* in, char* arg0, char* arg1, int to);
void WC(char err);

void main()
{
	start();
}

#include "file_redakt_perem.c"
#include "file_redakt_graph.c"
#include "file_redakt_lib.c"

//Ошибки в компиляторе *обнаруживать

char buff[] = "BUFFER";
char bye[] = "COMPILATION COMPLETE: ";

int masslen = 37;

int startpo = 0x0;

char start_file_name[37+1];

start()
{
        //clear(0x0, 0xFFFF);

	char start_file_extention[masslen+1];

	char massive0[masslen+1];
	char massive1[masslen+1];
	char massive2[masslen+1];

        load_num(start_file_name, masslen+1, 0x0);
        load_num(start_file_extention, masslen+1, 0x0);
        load_num(massive0, masslen+1, 0x0);
        load_num(massive1, masslen+1, 0x0);
        load_num(massive2, masslen+1, 0x0);

        //plus_string(massive0, tmp, masslen+1, 0x0);

        r_s_f(start_file_extention, masslen, buff, text, r_s_f(start_file_name, masslen, buff, text, 0x0).sho);

        //plus_string(massive0, start_file_name, masslen+1, 0x0);

        if(!find_file(start_file_name, start_file_extention))
        {
                exite(0x3);
        }
	else if(!srav_string(start_file_extention, text, 0x0))
	{
		exite(0x5);
	}

	del(start_file_name, cute);

        crt(start_file_name, cute, take_file_size(start_file_name, start_file_extention).sho, 0b111, 0x3);

	int str_now = 0x0;
	char off = 0x0;

	int to = 0x0;
	char len = 0x0;

	while(!off)
	{
        	load_num(massive0, masslen+1, 0x0);
        	load_num(massive1, masslen+1, 0x0);

		off = read_string(str_now, start_file_name, start_file_extention, massive0);
		//strprint_to_global(print_string(*globalx, *globaly, massive0, color, 0x0, 0x0));
		//strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
		len = name_str(massive0, massive1, massive2, to);

		if(len == 0x7D)
		{
			del(start_file_name, cute);
			WC(str_now+1);
		}

		for(int i = 0; i < len; i++)
		{
			w_c(start_file_name, cute, to, *(massive0+i));
			to++;
		}
		//strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
		str_now += 1;
	}

        //SVIS(start_file_name, cute);

        //file_to_file(start_file_name, massive0, text);
        //plus_string(massive1, start_file_name, masslen+1, 0x0);
        //load_num(start_file_name, masslen+1, 0x0);
        //plus_string(start_file_name, massive0, masslen+1, 0x0);
        //load_num(massive0, masslen+1, 0x0);

	strprint_to_global(print_string(*globalx, *globaly, bye, attcolor, 0x0, 0x0));
	strprint_to_global(print_string(*globalx, *globaly, start_file_name, color, 0x0, 0x0));
	strprint_to_global(print_string(*globalx, *globaly, ".", color, 0x0, 0x0));
	strprint_to_global(print_string(*globalx, *globaly, cute, color, 0x0, 0x0));
	strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
	exite(0x0);
}

char name_str(char* in, char* arg0, char* arg1, int to)
{
	char je[] = "JE ";
	char jge[] = "JGE ";
	char jle[] = "JLE ";
	char jne[] = "JNE ";

	load_num(arg0, masslen+1, 0x0);
        load_num(arg1, masslen+1, 0x0);

	if(srav_string("MOV ", in, 0x2))
	{
		if(srav_string("MOV EAX ", in, 0x2))
	        {
	        	redakt_string(redakt_string(in, arg0, ' ', 0x0).str1, arg1, ' ', 0x0);
	        	load_num(in, masslen+1, 0x0);
			*in = 0xB8;
			int* ui = (int*)(in+1);
                        *ui = str_to_int(arg1);
                        return 0x5;
	        }
		else if(srav_string("MOV /EAX/ ", in, 0x2))
	        {
	        	redakt_string(redakt_string(in, arg0, ' ', 0x0).str1, arg1, ' ', 0x0);
	        	load_num(in, masslen+1, 0x0);
			*in = 0xC6;
			*(in+1) = 0x00;
			*(in+2) = str_to_int(arg1);
                        return 0x3;
	        }
	        else
	        {
	                redakt_string(redakt_string(in, arg0, ' ', 0x0).str1, arg1, ' ', 0x0);
			load_num(in, masslen+1, 0x0);
			*in = 0xC7;
			*(in+1) = 0x05;
			int* ui = (int*)(in+2);
			*ui = str_to_int(arg0);
			ui = (int*)(in+2+4);
			*ui = str_to_int(arg1);
			//strprint_to_global(print_string(*globalx, *globaly, arg0, color, 0x0, 0x0));
	                //strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
			/*for(int i = 0; i < 10; i++)
			{
				strprint_to_global(print_int(*globalx, *globaly, *(in+i), color, 0x0, 0x1));
			}*/
			//str_to_int(arg0);
			return 0xA;
		}
		//strprint_to_global(print_string(*globalx, *globaly, "1", color, 0x0, 0x0));
	}
	else if(srav_string("ORG ", in, 0x2))
	{
	      	redakt_string(in, arg0, ' ', 0x0);
	       	//load_num(in, masslen+1, 0x0);
		startpo = str_to_int(arg0);
                return 0x0;
	}
	else if(srav_string("INC ", in, 0x2))
	{
		if(srav_string("INC EAX", in, 0x2))
	        {
	        	load_num(in, masslen+1, 0x0);
			*in = 0x40;
                        return 0x1;
	        }
	}
	else if(srav_string("RET", in, 0x2))
	{
		load_num(in, masslen+1, 0x0);
		*in = 0xC3;
                return 0x1;
	}
	else if(srav_string("CMP ", in, 0x2))
	{
		if(srav_string("CMP EAX ", in, 0x2))
	        {
	        	redakt_string(redakt_string(in, arg0, ' ', 0x0).str1, arg1, ' ', 0x0);
	        	load_num(in, masslen+1, 0x0);
			*in = 0x3D;
			int* ui = (int*)(in+1);
                        *ui = str_to_int(arg1);
                        return 0x5;
	        }
	}
	else if(srav_string(je, in, 0x2) || srav_string(jge, in, 0x2) || srav_string(jle, in, 0x2) || srav_string(jne, in, 0x2))
	{
		char ghy = 0x0;
		if(srav_string(je, in, 0x2))
		{
               		ghy = 0x84;
		}
		else if(srav_string(jge, in, 0x2))
		{
                	ghy = 0x8D;
		}
		else if(srav_string(jle, in, 0x2))
		{
                	ghy = 0x8E;
		}
		else if(srav_string(jne, in, 0x2))
		{
                	ghy = 0x85;
		}

		redakt_string(in, arg0, ' ', 0x0);
	        load_num(in, masslen+1, 0x0);
		*in = 0x0F;
		*(in+1) = ghy;
                int* ui = (int*)(in+2);
                int scht = str_to_int(arg0);
                scht -= startpo;
                int prov = str_to_int(arg0);
                prov -= startpo;
                if(prov < to+0x4)
                {
                        scht = to-scht+0x5;
                        scht = 0xFFFFFFFF-scht;
                }
                else
                {
                        scht = scht-to-0x6;
                }
                *ui = scht;
                return 0x6;
	}
	else if(srav_string("JMP ", in, 0x2))
	{
                redakt_string(in, arg0, ' ', 0x0);
		load_num(in, masslen+1, 0x0);
		*in = 0xE9;
		int* ui = (int*)(in+1);
		int scht = str_to_int(arg0);
		scht -= startpo;
		int prov = str_to_int(arg0);
		prov -= startpo;
		if(prov < to+0x4)
		{
			scht = to-scht+0x4;
			scht = 0xFFFFFFFF-scht;
		}
		else
		{
			scht = scht-to-0x5;
		}
		*ui = scht;
		//strprint_to_global(print_int(*globalx, *globaly, scht, color, 0x0, 0x6));
		/*for(int i = 0; i < 5; i++)
		{
			strprint_to_global(print_int(*globalx, *globaly, *(in+i), color, 0x0, 0x1));
		}*/
		//str_to_int(arg0);
		return 0x5;
	}
	else if(!srav_string("", in, 0x0))
	{
		return 0x7D;
	}
	else if(srav_string("", in, 0x0))
	{
		return 0x0;
	}
}

void exite(char err)
{
	if(err)
	{
		strprint_to_global(print_string(*globalx, *globaly, "SOMETHING WRONG HAPPEND: ", warcolor, 0x0, 0x0));
		strprint_to_global(print_int(*globalx, *globaly, err, color, 0x0, 0x1));
		strprint_to_global(print_string(*globalx, *globaly, "\n", warcolor, 0x0, 0x0));
	}
	else
	{
		set_file_flags(start_file_name, cute, 0b100);
	}

	del(buff, text);
	exit();
}

void WC(char err)
{
	if(err)
	{
		strprint_to_global(print_string(*globalx, *globaly, "WRONG COMMAND: ", warcolor, 0x0, 0x0));
		strprint_to_global(print_string(*globalx, *globaly, "LINE ", color, 0x0, 0x0));
		strprint_to_global(print_int(*globalx, *globaly, err, color, 0x0, 0x1));
		strprint_to_global(print_string(*globalx, *globaly, "\n", warcolor, 0x0, 0x0));
	}
	del(buff, text);
	exit();
}

char read_string(int from, char* filen, char* filee, char* massive)
{
	struct chr_err o;

	int str_now = 0x0;
	int to = 0x0;

	while(str_now < from)
        {
                o = r_c(filen, filee, to);

                if(o.err)
                {
                        break;
                }

                if(o.chr == '\n')
                {
                        str_now++;
                }

                to++;
        }

	int nlen = 0x0;
	char off = 0x0;

	while(nlen < masslen)
        {
                o = r_c(filen, filee, to);

                if(o.err)
                {
                        break;
                }

                if(o.chr == '\n')
                {
                        break;
                }
		else if(o.chr == 0x0)
		{
			off--;
			break;
		}

		*(massive+nlen) = o.chr;

		nlen++;
                to++;
        }

	return off;
}

