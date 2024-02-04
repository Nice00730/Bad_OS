int print_file(int filen, int filee, char y_n);
void start();

void main()
{
	start();
}

char buff[] = "BUFFER";

int masslen = 37;
int stack_size = 0x5;

char can_write = 0x1;

#include "file_redakt_perem.c"
#include "file_redakt_graph.c"
#include "file_redakt_lib.c"

void start()
{
	//clear(0x0, 0xFFFF);

	char massiven[masslen+1];
	char massivee[masslen+1];

	char massive0[masslen+1];
	char massive1[masslen+1];

	//print_int(0x0, 24, massiven, attcolor, 0x1, 0x6);

	load_num(massiven, masslen+1, 0x0);
	load_num(massivee, masslen+1, 0x0);
	load_num(massive0, masslen+1, 0x0);
	load_num(massive1, masslen+1, 0x0);

	plus_string(massive0, tmp, masslen+1, 0x0);

	r_s_f(massivee, masslen, buff, text, r_s_f(massiven, masslen, buff, text, 0x0).sho);

	plus_string(massive0, massiven, masslen+1, 0x0);

	if(!find_file(massiven, massivee))
	{
		exits(0x23);
	}

	if(!(take_file_flg(massiven, massivee) & 0b001))
	{
		exits(0x25);
	}
	else if(!(take_file_flg(massiven, massivee) & 0b010))
	{
		can_write = 0x0;
	}

	clear(0x0, 0xFFFF);

	crt(massive0, massivee, take_file_size(massiven, massivee).sho, 0b011, 0);
	SVIS(massive0, massivee);

	file_to_file(massiven, massive0, text);
	plus_string(massive1, massiven, masslen+1, 0x0);
	load_num(massiven, masslen+1, 0x0);
	plus_string(massiven, massive0, masslen+1, 0x0);
	load_num(massive0, masslen+1, 0x0);

	char texts[] = "ORG F00000\nMOV EAX A0000\nMOV /EAX/ 2\nINC EAX\nCMP EAX A0F00\nJE F00019\nJMP F00005\nRET";
	//char texts[] = "MOV FE6 30\nJMP 10000";

	int cursrtime = *timer;
	char cursron = 0x0;

	int buttime = *timer;
	int clcktimex = *timer;
	int clcktimey = *timer;
	int speedtime = *timer;

	int x = 0x0;
	int y = 0x0;

	char in = 0x0;

	int string_num = print_file(massiven, massivee, 0x1);
	int symb_num = read_str_len(massiven, massivee, 0x0);

	char lc = 0x0;

	char time_to_clc = 0x2;

	strprint_to_global(print_string(0, 24, "Tab plus/nump/ to exit ", attcolor, 0x1, 0x0));
	if(!can_write)
	{
		print_string(*globalx, *globaly, "Only read", warcolor, 0x1, 0x0);
	}
        line(0, 24*8-1, 39*8+1, 1, attcolor);
        line(39*8+1, 0, 24*8-1, 0, attcolor);

	while(1)
	{

		/*if(speedtime+3 < *timer && (find_buttn(0x4D) || find_buttn(0x4B) || find_buttn(0x48) || find_buttn(0x50)))
		{
			time_to_clc = 0x1;
		}
		else if(!find_buttn(0x4D) && !find_buttn(0x4B) && !find_buttn(0x48) && !find_buttn(0x50))
		{
			time_to_clc = 0x3;
			speedtime = *timer;
		}*/

		if(find_buttn(0x4D) && x < symb_num && clcktimex+time_to_clc < *timer)
		{
			cursr(x, y, 0x0);
			x++;
			clcktimex = *timer;
		}
		else if(find_buttn(0x4B) && x > 0x0 && clcktimex+time_to_clc < *timer)
		{
			cursr(x, y, 0x0);
			x--;
			clcktimex = *timer;
		}
		else if(find_buttn(0x4B) && x == 0x0 && clcktimex+time_to_clc < *timer)
		{
			if(y > 0x0)
			{
				cursr(x, y, 0x0);
				y--;
				symb_num = read_str_len(massiven, massivee, y);
                        	x = symb_num;
                        	clcktimex = *timer;
                        }
		}
		else if(find_buttn(0x4D) && x == symb_num && clcktimex+time_to_clc < *timer)
		{
			if(y < string_num)
			{
				cursr(x, y, 0x0);
				y++;
				symb_num = read_str_len(massiven, massivee, y);
                        	x = 0x0;
                        	clcktimex = *timer;
                        }
		}

		if(find_buttn(0x48) && y > 0x0 && clcktimey+time_to_clc < *timer)
		{
			cursr(x, y, 0x0);
			y--;
			symb_num = read_str_len(massiven, massivee, y);
			clcktimey = *timer;
		}
		else if(find_buttn(0x50) && y < string_num && clcktimey+time_to_clc < *timer)
		{
			cursr(x, y, 0x0);
			y++;
			symb_num = read_str_len(massiven, massivee, y);
			clcktimey = *timer;
		}

		if(cursron)
		{
			cursr(x, y, warcolor);
		}

		if(x > symb_num)
		{
			cursr(x, y, 0x0);
			x = symb_num;
		}

		print_int(38, 24, y, warcolor, 0x1, 0x1);
		print_int(35, 24, x, warcolor, 0x1, 0x1);

		in = read_button();

		char probel = 0x0;

		if(in  && can_write && !find_buttn(0x4D) && !find_buttn(0x4B) && !find_buttn(0x48) && !find_buttn(0x50) && ((buttime+time_to_clc-1 < *timer && in != lc) || (buttime+time_to_clc+1 < *timer && in == lc)))
		{
			lc = in;

			clear(0x0, 0xFFFF);

			//fill_square(0, 0, 39*8, 24*8-2, 0x0);
			print_string(0, 24, "Tab plus/nump/ to exit", attcolor, 0x1, 0x0);
			line(0, 24*8-1, 39*8+1, 1, attcolor);
			line(39*8+1, 0, 24*8-1, 0, attcolor);


			if(in != 0x8)
			{
				if(x < 39 && y <= 23)
				{
					plus_null(massiven, massivee, find_chr_num(x, y, massiven, massivee));
		        		if(in != 0x0A)
					{
						w_c(massiven, massivee, find_chr_num(x, y, massiven, massivee), in);
					}
				}

		        	if(x < 39 && in != 0x0A && symb_num < 39)
                                {
                                        x++;
                                }
                                else
                                {
                                        if(y < 23)
                                        {
						if(in != 0x0A)
						{
							probel = 0x1;
						}
                                        	//x++;
                                        	w_c(massiven, massivee, find_chr_num(x, y, massiven, massivee), 0x0A);
                                                y++;
                                                string_num = print_file(massiven, massivee, 0x0);
                                                symb_num = read_str_len(massiven, massivee, y);
                                                x = 0x0;
                                        }
                                }

			}
			else
			{
				if(x > 0x0)
				{
					x--;
				}
				else
				{
					if(y > 0x0)
					{
						y--;
						string_num = print_file(massiven, massivee, 0x0);
						symb_num = read_str_len(massiven, massivee, y);
						x = symb_num;
					}
				}

		        	w_c(massiven, massivee, find_chr_num(x, y, massiven, massivee), 0x0);
		        	kill_all_null(massiven, massivee, find_chr_num(x, y, massiven, massivee));
			}

			if(probel)
			{
				plus_null(massiven, massivee, find_chr_num(x, y, massiven, massivee));
				w_c(massiven, massivee, find_chr_num(x, y, massiven, massivee), in);
				x++;
			}

			string_num = print_file(massiven, massivee, 0x1);
			symb_num = read_str_len(massiven, massivee, y);
			buttime = *timer;
			cursrtime = *timer;
		}

		if(find_buttn(0x4E))
                {
                        break;
                }

		if(clcktimex+4 < *timer && find_buttn(0x52))
		{
			clear(0x0, 0xFFFF);

			char err0 = w_s_f(texts, massiven, massivee, 0x0);
			char err1 = r_c(massiven, massivee, 0x0).err;

			if(err0)
			{
				strprint_to_global(print_string(0, 1, "Writing error: ", warcolor, 0x1, 0x0));
		 	        strprint_to_global(print_int(*globalx, *globaly, err0, attcolor, 0x1, 0x0));
				exits(0x1);
			}
			else if(err1)
			{
				strprint_to_global(print_string(0, 1, "Reading error: ", warcolor, 0x1, 0x0));
		 	        strprint_to_global(print_int(*globalx, *globaly, err1, attcolor, 0x1, 0x0));
				exits(0x2);
			}

			string_num = print_file(massiven, massivee, 0x1);
			symb_num = read_str_len(massiven, massivee, y);
			clcktimex = *timer;
			cursrtime = *timer;
		}

		cursron = 0x1;

		/*if(cursrtime+1 < *timer && cursron)
		{
			cursr(x, y, warcolor);
			cursrtime = *timer;
			cursron = 0x0;
		}
		else if(cursrtime+5 < *timer && !cursron)
		{
			cursr(x, y, 0x0);
			cursrtime = *timer;
			cursron = 0x1;
		}*/
	}

	//w_s_f("inp", massiven, massivee, 0x0);
	buttime = *timer;
	fill_square(0, 24*8, 30*8, 8, 0x0);
	strprint_to_global(print_string(0x0, 24, "To save tab Y/N", attcolor, 0x1, 0x0));
	while(1)
	{
		if(buttime+18 < *timer && find_buttn(0x15))
		{
			file_to_file(massiven, massive1, text);
			break;
		}
		else if((buttime+18 < *timer && find_buttn(0x31)) || !can_write)
		{
			break;
		}
	}
	del(massiven, text);

	exits(0x0);
}

void plus_null(int filen, int filee, int to)
{
	int size = take_file_size(filen, filee).sho*0x200-0x4;

	int start = to;

	struct chr_err o;
        o.chr = 0xFF;

	char save = 0x1;
	char lsave = 0x0;

	while(save)
	{
		o = r_c(filen, filee, to+1);

                if(o.err)
                {
                	return;
                }

		save = r_c(filen, filee, to).chr;
		//w_c(filen, filee, to+1, r_c(filen, filee, to).chr);
		w_c(filen, filee, to, lsave);
		lsave = save;

		//w_c(filen, filee, to+1, r_c(filen, filee, to).chr);

                to++;
	}

	//print_int(0x0, 21, to-start, attcolor, 0x1, 0x6);
}

void kill_all_null(int filen, int filee, int to)
{
	int size = take_file_size(filen, filee).sho*0x200-0x4;
	int start = 0x0;

	struct chr_err o;
	o.chr = 0xFF;

	while(to < size)
	{
		while(o.chr)
		{
			o = r_c(filen, filee, to);

			if(o.err)
			{
				return;
			}

			to++;
		}

		//print_int(0x0, 21, to, attcolor, 0x1, 0x6);

		start = to;

		while(!o.chr)
		{
			o = r_c(filen, filee, to);

			if(o.err)
                        {
                                return;
                        }
			to++;
		}

		int end = to;

		//print_int(0x0, 22, end, attcolor, 0x1, 0x6);

		to--;

		while(to < size)
		{
			//o = r_c(filen, filee, to);

			char err = w_c(filen, filee, to-(end-start), r_c(filen, filee, to).chr);

			if(!o.chr)
                        {
                              	break;
                        }

			if(err)
			{
				return;
			}

			to++;
		}

		//to = start;

		//w_c(filen, filee, to, 0x0);

		//print_int(0x0, 23, to-start, attcolor, 0x1, 0x6);

		break;
	}
}

void exits(char err)
{
	if(err < 0x20 && err)
	{
		clear(0x0, 0xFFFF);
		strprint_to_global(print_string(0x0, 0x0, "Something wrong happend: ", warcolor, 0x1, 0x0));
        	print_int(*globalx, *globaly, err, attcolor, 0x1, 0x0);
		wait(0x18);
		clear(0x0, 0xFFFF);
	}
	else if(err > 0x20 && err)
	{
		strprint_to_global(print_string(*globalx, *globaly, "Something wrong happend: ", warcolor, 0x1, 0x0));
                print_int(*globalx, *globaly, (err-0x20), attcolor, 0x1, 0x0);
		strprint_to_global(print_string(*globalx, *globaly, "\n", warcolor, 0x1, 0x1));
	}
	else if(!err)
	{
		clear(0x0, 0xFFFF);
	}
	del("BUFFER", text);
	exit();
}

int find_chr_num(int x, int y, int filen, int filee)
{
	int to = 0x0;
	int str_now = 0x0;

	struct chr_err o;

        while(str_now < y)
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
	to += x;
	return to;
}

int read_str_len(int filen, int filee, int str_num)
{
	int to = 0x0;
        struct chr_err o;
        o.chr = 0xFF;
        int string_num = 0x0;
	int str_now = 0x0;

        while(str_now < str_num)
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

	o.chr = 0xFF;

        while(o.chr != '\n' && o.chr)
        {
                o = r_c(filen, filee, to);
                string_num++;

                if(o.err)
                {
                        break;
                }

                to++;
        }
	string_num--;
        return string_num;
}

int print_file(int filen, int filee, char y_n)
{
 	int to = 0x0;
	struct chr_err o;
	o.chr = 0xFF;
	char str[2];
	int string_num = 0x0;

	while(o.chr && string_num < 24)
	{
		o = r_c(filen, filee, to);

		if(o.chr == '\n')
		{
			string_num++;
		}

		if(o.err)
		{
			break;
		}

		str[0] = o.chr;
		str[1] = 0x0;
		if(y_n)
		{
			strprint_to_global(print_string(*globalx, *globaly, str, color, 0x0, 0x0));
		}
		to++;
	}
	return string_num;
}
