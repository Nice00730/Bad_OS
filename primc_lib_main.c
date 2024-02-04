void wait(short int count);
void waitspec(int count);
int module(int in);
char read_button();
char find_buttn(char in);
void setup_keyboard(char setup);
void create_char(int x, int y, char in, char color, char flg);
//struct strprint read_string(char* mass, int len, int x, int y, char flg, char* stack, short int stack_len);
struct tstring redakt_string(char* in0, char* in1, char del, char num);
void load(int from, int to, int size);
struct strprint print_string(int x, int y, char* in, char color, char flg, char move);
char srav_string(char* in0, char* in1, char num);
void strprint_to_global(struct strprint p);
char create_filesys(char* addr, int size, char filemode);
int stepen(int num, short int step);
char razryad(int in, char num);
struct strprint print_int(int x, int y, int in, char color, char flg, short int  ogran);
char* plus_string(char* in0, char* in1, short int lenin0, char plus, char num);
char create_file(char* name, char* extention, short int size, char* sysadr, char root);
int take_file_adr(int file);
int find_file(char* name, char* ext);
int create_file_place(short int ssize, int from, int to);
int str_to_int(char* str);
short int take_file_size(int file);
char podtasovka(char* fsys);
void set_file_vis(int file, char in);
char take_file_vis(int file);
void set_file_root(int file, char in);
char take_file_root(int file);
void load_num(int to, int size, char num);
//void stack_mandge(int in, int stack, short int stack_size, short int in_size);
char* take_file_name(int file);
char* take_file_ext(int file);
void set_file_priv(int file, char in);
char take_file_priv(int file);

//--------------------------------------------------------------------------------------------------

struct tstring//Функции использующие должны подавать два равных массива, один с данными другой пустой
{
	char* str0;
	char* str1;
};

struct strprint
{
	short int x;
	short int y;
	short int len;
};

//---------------------------------------------------------------------------------------------------

/*void stack_mandge(int in, int stack, short int stack_size, short int in_size)
{
	char* to = (char*)stack;
	char* ab = (char*)in;
	stack_size--;
	if(*ab != 0x0 || *ab != 0x0A)
	{
		for(int i = stack_size-1; i >= 0x0; i--)
		{
			for(int j = 0; j < in_size; j++)
			{
				 *(to+(i+1)*(in_size+1)+j) = *(to+i*(in_size+1)+j);
			}
		}
		for(int l = 0; l < in_size; l++)
		{
			*(to+l) = *(ab+l);
		}
	}
}*/

void strprint_to_global(struct strprint p)
{
	*globalx = p.x;
	*globaly = p.y;
}

int take_file_adr(int file)
{
	file+=0xA;
	int* adr = (int*)file;
	return *adr;
}

char take_file_vis(int file)
{
	file+=0x2;
	char* adr = (char*)file;
	return *adr;
}

void set_file_vis(int file, char in)
{
	file+=0x2;
	char* adr = (char*)file;
	*adr = in;
}

char take_file_root(int file)
{
	file+=0x3;
	char* adr = (char*)file;
	return *adr;
}

char* take_file_name(int file)
{
	file+=0xE;
	char* name = (char*)file;
	return name;
}

char* take_file_ext(int file)
{
	file+=0xE;
	char* ext = (char*)file;
	return ext;
}

void set_file_root(int file, char in)
{
	if(in <= 0b111 && in >= 0x0)
	{
		file+=0x3;
		char* adr = (char*)file;
		*adr = in;
	}
}

void set_file_priv(int file, char in)
{
	file+=0x4;
	char* adr = (char*)file;
	*adr = in;
}

char take_file_priv(int file)
{
	file+=0x4;
	char* adr = (char*)file;
	return *adr;
}

short int take_file_size(int file)
{
	file+=0x8;
	short int* adr = (short int*)file;
	return *adr;
}

int str_to_int(char* str)
{
	int out = 0x0;
	short int step = 0x0;
	short int esle = 0x0;
	while(*(str+step) != 0x0)
	{
		if((*(str+step) >= 0x30 && *(str+step) <= 0x39) || (*(str+step) >= 0x41 && *(str+step) <= 0x46))
		{
			step++;
		}
		else
		{
			return out;
		}
	}
	step--;
	while(*(str+esle) != 0x0)
	{
		if(*(str+esle) >= 0x30 && *(str+esle) <= 0x39)
		{
			out+=stepen(0x10, step)*(*(str+esle)-0x30);
		}
		else if(*(str+esle) >= 0x41 && *(str+esle) <= 0x46)
		{
			out+=stepen(0x10, step)*(*(str+esle)-0x41+0xA);
		}
		esle++;
		step--;
	}
	return out;
}

char podtasovka(char* fsys)
{
	int sdvig = 0x1;
	int space = 0x0;
	int len;
	while(1==1)
	{
		if(*(fsys+sdvig)+0x10 == 0xE && *(fsys+sdvig+1)+0x10 == 0xF)
		{
			break;
		}
		else if(*(fsys+sdvig)+0x10 == 0xC && *(fsys+sdvig+1)+0x10 == 0xF && space == 0x1)
		{
			while(1==1)
			{
				if(*(fsys+sdvig)+0x10 == 0xD && *(fsys+sdvig+1)+0x10 == 0xF)
				{
					break;
				}
				sdvig++;
			}
			sdvig++;
			space = 0x0;
		}
		else if(*(fsys+sdvig)+0x10 == 0xC && *(fsys+sdvig+1)+0x10 == 0xF && space > 0x2)
		{
			space--;
			int spsdvig = sdvig-space;
			while(1==1)
			{
				if(*(fsys+sdvig)+0x10 == 0xD && *(fsys+sdvig+1)+0x10 == 0xF)
				{
					break;
				}
				*(fsys+spsdvig) = *(fsys+sdvig);
				*(fsys+sdvig) = 0x0;
				sdvig++;
				spsdvig++;
			}
			*(fsys+spsdvig) = *(fsys+sdvig);
			*(fsys+sdvig) = 0x0;
			sdvig++;
			spsdvig++;
			*(fsys+spsdvig) = *(fsys+sdvig);
			*(fsys+sdvig) = 0x0;
			sdvig -= space;
			space = 0x0;
		}
		space++;
		sdvig++;
	}
	return 0x0;
}

char delete_file(char* name, char* ext, char* fsys)
{
	char* ladr = (char*)find_file(name, ext);
	if(ladr != 0x0)
        {
		char* fadr = (char*)take_file_adr(ladr);
		int sdvig = 0x0;
		short int fsize = take_file_size(ladr);
		short int lsize = 0x0;

		fsize*=0x200;

		//strprint_to_global(print_string(*globalx, *globaly, "Deleting file...", attcolor, 0x0, 0x0));

		if(*fadr+0x60 == 0x8 && *(fadr+1) == 0x55 && *(fadr+fsize-2)+0x60 == 0x9 && *(fadr+fsize-1) == 0x55 && *ladr+0x10 == 0xC && *(ladr+1)+0x10 == 0xF)
		{
			while(1==1)
			{
				if(*(fadr+sdvig)+0x60 == 0x9 && *(fadr+sdvig+1) == 0x55)
				{
					break;
				}

				*(fadr+sdvig) = 0x0;

				sdvig++;
			}

			*(fadr+sdvig) = 0x0;
			sdvig++;
			*(fadr+sdvig) = 0x0;

			sdvig = 0x0;

			while(1==1)
			{
				if(*(ladr+sdvig)+0x10 == 0xD && *(ladr+sdvig+1)+0x10 == 0xF)
				{
					break;
				}
				else if(lsize >= 50)
				{
					//strprint_to_global(print_string(*globalx, *globaly, "Error/File corrupted|1", color, 0x0, 0x0));
					return 0x2;
				}

				*(ladr+sdvig) = 0x0;

				lsize++;
				sdvig++;
			}

			*(ladr+sdvig) = 0x0;
			sdvig++;
			*(ladr+sdvig) = 0x0;

			if(*fadr == 0x0 && *(fadr+1) == 0x0 && *(fadr+fsize-2) == 0x0 && *(fadr+fsize-1) == 0x0 && *(ladr) == 0x0 && *(ladr+1) == 0x0 && *(ladr+lsize-1) == 0x0 && *(ladr+lsize) == 0x0)
			{
				//strprint_to_global(print_string(*globalx, *globaly, "Ok", color, 0x0, 0x0));
				//break;
			}
			else
			{
				//strprint_to_global(print_string(*globalx, *globaly, "Error/Can't delete file", warcolor, 0x0, 0x0));
				return 0x3;
			}
		}
		else
		{
			//strprint_to_global(print_string(*globalx, *globaly, "Error/File corrupted|0", warcolor, 0x0, 0x0));
			return 0x2;
		}
	}
	else
	{
		//strprint_to_global(print_string(*globalx, *globaly, "No such file", warcolor, 0x0, 0x0));
		return 0x1;
	}
	podtasovka(fsys);
	return 0x0;
}

int find_file(char* name, char* ext)
{
	int sdvig = 0x2;
	int start = 0x0;
	while(1==1)
	{
		if(*(filesys+sdvig)+0x10 == 0xE && *(filesys+sdvig+1)+0x10 == 0xF)
		{
			return 0x0;//no file
		}
		else if(*(filesys+sdvig)+0x10 == 0xC && *(filesys+sdvig+1)+0x10 == 0xF)
		{
			start = filesys+sdvig;
			sdvig+=0xE;
			if(srav_string(filesys+sdvig, name, 0x0))
			{
				while(*(filesys+sdvig) != 0x0)
				{
					sdvig++;
				}
				sdvig++;
				if(srav_string(filesys+sdvig, ext, 0x0))
				{
					return start;
				}
				else
				{
					sdvig++;
					while(*(filesys+sdvig) != 0x0)
					{
						sdvig++;
					}
					sdvig+=0x2;
				}
			}
		}
		else
		{
			sdvig++;
		}
	}
}

int create_file_place(short int ssize, int from, int to)
{
	char* fromc = from;
	//fromc++;
	int sdvig = 0x0;

	int size = 0x200*ssize;

	int start = sdvig+fromc;
	int ssze = 0x0;
	while(1==1)
	{
		if(sdvig+from >= to)
		{
			return 0x0;
		}
		else if(*(sdvig+fromc)+0x60 == 0x8 && *(sdvig+fromc+1) == 0x55)
		{
			while(1==1)
			{
				if(*(sdvig+fromc)+0x60 == 0x9 && *(sdvig+fromc+1) == 0x55)
				{
					break;
				}
				sdvig++;
			}
			start=sdvig+from+2;
			sdvig++;
			ssze = 0x0;
		}
		else if(ssze >= size)
		{
			if(start+size > file_to)
			{
				return 0x0;
			}
			char* jku = start;
			*(jku) = 0xA8;
			*(jku+1) = 0x55;
			*(jku+size-2) = 0xA9;
			*(jku+size-1) = 0x55;
			break;
		}
		ssze++;
		sdvig++;
	}
	char* kl = (char*)start;
	if(*(kl)+0x60 == 0x8 && *(kl+1) == 0x55 && *(kl+size-2)+0x60 == 0x9 && *(kl+size-1) == 0x55)
	{
		return start;
	}
	else
	{
		return 0x0;
	}
}

char create_file(char* name, char* ext, short int size, char* sysadr, char root)
{
	//strprint_to_global(print_string(*globalx, *globaly, "Creating file...", attcolor, 0x0, 0x0));

	char flg0 = 0x0;
	char* pack = name;

	while(*pack != 0x0)
	{
		if(*pack == '.')
		{
			flg0 = 0x1;
			break;
		}
		pack++;
	}

	if(!print_string(*globalx, *globaly, name, 0x0, 0x0, 0x0).len || flg0)
	{
		//strprint_to_global(print_string(*globalx, *globaly, "Error/Bad name", warcolor, 0x0, 0x0));
		return 0x6;//null name
	}

	pack = ext;
	flg0 = 0x0;

	while(*pack != 0x0)
	{
		if(*pack == '.')
		{
			flg0 = 0x1;
			break;
		}
		pack++;
	}

	if(((!srav_string(ext, "TEXT", 0x0) && !srav_string(ext, "CUTE", 0x0))) || flg0)
	{
		//strprint_to_global(print_string(*globalx, *globaly, "Error/Bad extension\nAllowable: TEXT, CUTE", warcolor, 0x0, 0x0));
		return 0x7;//unpinned ext
	}

	if(!find_file(name, ext))
	{
		if(!size)
		{
			//strprint_to_global(print_string(*globalx, *globaly, "Error/Null size", warcolor, 0x0, 0x0));
			return 0x5;//can't create file place
		}

		int adress = create_file_place(size, file_from, file_to);

		if(adress == 0x0)
		{
			//strprint_to_global(print_string(*globalx, *globaly, "Error/No place to file", warcolor, 0x0, 0x0));
			return 0x4;//can't create file place
		}

		char* startf = 0x0;
		int sdvig = 0x0;
		short int space = 0x0;
		sdvig += 0x2;
		short int namelen = print_string(0x0, 0x0, name, 0xFF, 0x0, 0x0).len;
		short int extlen = print_string(0x0, 0x0, ext, 0xFF, 0x0, 0x0).len;

		while(1==1)
		{
			if(*(sysadr+sdvig)+0x10 == 0xE && *(sysadr+sdvig+1)+0x10 == 0xF)
			{
				//strprint_to_global(print_string(*globalx, *globaly, "Error/No place to log", warcolor, 0x0, 0x0));
				return 0x1;//filesys full
			}
			else if(*(sysadr+sdvig)+0x10 == 0xC && *(sysadr+sdvig+1)+0xF)
			{
				short int plus = 0x0;
				while(1==1)
				{
					if(*(sysadr+sdvig)+0x10 == 0xD && *(sysadr+sdvig+1)+0xF)
					{
						break;
					}
					else if(plus > 0xFF)
					{
						//strprint_to_global(print_string(*globalx, *globaly, "Error/filesys corrupted", warcolor, 0x0, 0x0));
						return 0x2;//filesys corrupted
					}
					sdvig++;
					plus++;
				}
				sdvig += 0x2;
			}
			else if(space >= extlen+namelen+0x10)//visible, folder + 4 empty(0x6) && start+end(0x4) && adress(0x4) && scale(0x2)
			{
				startf = sysadr+sdvig;
				*(sysadr+sdvig) = 0xFC;
				sdvig++;
				*(sysadr+sdvig) = 0xFF;
				sdvig++;

				sdvig+=0x6;//flags
				short int* siz = (short int*)(sysadr+sdvig);
				*siz = size;
				sdvig+=0x2;//scale
				int* adr = (int*)(sysadr+sdvig);
				*adr = adress;
				sdvig+=0x4;//adress

				short int jkl = 0x0;
				while(*(name+jkl))
				{
					*(sysadr+sdvig+jkl) = *(name+jkl);
					jkl++;
				}
				sdvig+=jkl;
				*(sysadr+sdvig) = 0x0;
				sdvig++;

				jkl = 0x0;
				while(*(ext+jkl))
				{
					*(sysadr+sdvig+jkl) = *(ext+jkl);
					jkl++;
				}
				sdvig+=jkl;
				*(sysadr+sdvig) = 0x0;
				sdvig++;

				*(sysadr+sdvig) = 0xFD;
				sdvig++;
				*(sysadr+sdvig) = 0xFF;
				sdvig++;

				set_file_vis(startf, 0x1);
				set_file_root(startf, root);

				if(find_file(name, ext))
				{
					//strprint_to_global(print_string(*globalx, *globaly, "Ok", color, 0x0, 0x0));
					return 0x0;
				}
				else
				{
					//strprint_to_global(print_string(*globalx, *globaly, "Error/Can't find create file", warcolor, 0x0, 0x0));
					return 0x3;//can't create file
				}

				break;
			}
			else if(*(sysadr+sdvig) == 0x0)
			{
				space++;
			}
		}
	}
	else
	{
		//strprint_to_global(print_string(*globalx, *globaly, "Such file already exists", warcolor, 0x0, 0x0));
		return 0x8;
	}
}

char create_filesys(char* addr, int size, char filemode)//size по 0x100
{
	int smesh = 0x0;
	char p = 0x0;
	char tryn = 0x1;
	strprint_to_global(print_string(*globalx, *globaly, "Filesystem...", attcolor, 0x0, 0x0));
	while(p == 0x0)
	{

		if(tryn >= 0x4)
		{
			strprint_to_global(print_string(*globalx, *globaly, "Error\n", warcolor, 0x0, 0x0));
			return 0x1;
		}

		if(*addr+0x10 == 0xB && *(addr+1)+0x10 == 0xF && *(addr+size-2)+0x10 == 0xE && *(addr+size-1)+0x10 == 0xF)
		{
			strprint_to_global(print_string(*globalx, *globaly, "Ok\n", color, 0x0, 0x0));
			p = 0x1;
		}
		else
		{
			if(tryn == 0x1)
			{
				strprint_to_global(print_string(*globalx, *globaly, "No\n", warcolor, 0x0, 0x0));
			}
			else
			{
				strprint_to_global(print_string(*globalx, *globaly, "Error\n", warcolor, 0x0, 0x0));
			}
			strprint_to_global(print_string(*globalx, *globaly, "Create try number: ", attcolor, 0x0, 0x0));
			strprint_to_global(print_int(*globalx, *globaly, tryn, attcolor, 0x0, 0x1));
			strprint_to_global(print_string(*globalx, *globaly, "\n", color, 0x0, 0x0));
			strprint_to_global(print_string(*globalx, *globaly, "Creating...", attcolor, 0x0, 0x0));

			int spec = 0x0;
			while(1==1)
			{
				if(spec >= size+1)
				{
					break;
				}
				else
				{
					*(addr+spec) = 0x0;
				}
				spec++;
			}

			*addr = 0xFB;
			*(addr+1) = 0xFF;
			*(addr+size-2) = 0xFE;
			*(addr+size-1) = 0xFF;
		}
		tryn++;
	}
	return 0x0;
}

void load(int from, int to, int size)
{
	asm volatile(
        "mov %0, %%edx\n\t"
        "mov %1, %%ecx\n\t"
        "mov %2, %%esi\n\t"
        "int $0x30"
        :
        :"g"(from), "g"(to), "g"(size)
        :"edx", "ecx", "esi"
        );
}

void load_num(int to, int size, char num)
{
	char* go = (char*)to;
	for(int i = 0; i < size; i++)
	{
		*(go+i) = num;
	}
}

char srav_string(char* in0, char* in1, char num)//0x0-абсолютное равенство, 0x1 - первое во втором, 0x2 - первое во втором в начале
{
	short int nlen = 0x0;
	short int nlen1 = 0x0;
	char out = 0x0;
	while(1==1)
	{
		if(num == 0x0 && *(in0+nlen) != *(in1+nlen) && (*(in0+nlen) != 0x0 && *(in1+nlen) != 0x0))
		{
			break;
		}
		else if(num == 0x0 && (*(in0+nlen) == 0x0 && *(in1+nlen) == 0x0))
		{
			out = 0x1;
			break;
		}
		else if(num == 0x0 && (*(in0+nlen) == 0x0 || *(in1+nlen) == 0x0))
		{
			break;
		}

		if(num == 0x1 && *(in0+nlen1) == *(in1+nlen) && (*(in0+nlen1) != 0x0 && *(in1+nlen) != 0x0))
		{
			nlen1++;
		}
		else if(num == 0x1 && *(in0+nlen1) != *(in1+nlen) && (*(in0+nlen1) != 0x0 && *(in1+nlen) != 0x0))
		{
			nlen1 = 0x0;
		}
		else if(num == 0x1 && *(in0+nlen1) == 0x0)
		{
			out = 0x1;
			break;
		}
		else if(num == 0x1 && *(in1+nlen) == 0x0)
		{
			break;
		}

		if(num == 0x2 && *(in0+nlen) != *(in1+nlen) && *(in0+nlen) != 0x0)
		{
			break;
		}
		else if(num == 0x2 && *(in0+nlen) == 0x0)
		{
			out = 0x1;
			break;
		}

		nlen++;
	}
	return out;
}

char* plus_string(char* in0, char* in1, short int lenin0, char plus, char num)
{
	short int len0 = 0x0;
	short int len1 = 0x0;
	while(*(in0+len0) != 0x0)
	{
		len0++;
	}
	*(in0+len0) = plus;
	len0++;
	while(*(in1+len1) != 0x0 && len0 < lenin0)
	{
		if(num == 0x0)
		{
			*(in0+len0) = *(in1+len1);
		}
		len0++;
		len1++;
	}
	len1 = 0x0;
	while(*(in1+len1) != 0x0)
	{
		*(in1+len1) = 0x0;
		len1++;
	}
	return in0;
}

struct tstring redakt_string(char* in0, char* in1, char del, char num)//in0 начальная строка, in1 - пустая, в неё кладётся результат; 0x0 - передаёт две строки, делённые по del
{//					ТОЛЬКО БОЛЬШИЕ БУКВЫ В del
	char* start0 = in0;
	char* start1 = in1;
	short int len0 = 0x0;
	short int len1 = 0x0;
	char flag0 = 0x0;
	while(*in1 != 0x0)
	{
		*in1 = 0x0;
		in1++;
	}
	in1 = start1;
	while(1==1)
	{
		if(*(in0+len0) == 0x0)
		{
			break;
		}
		else if(flag0 == 0x0 && num == 0x0 && *(in0+len0) == del)
		{
			flag0 = 0x1;
			*(in0+len0) = 0x0;
			len0++;
		}

		if(flag0 == 0x1)
		{
			*(in1+len1) = *(in0+len0);
			*(in0+len0) = 0x0;
			len1++;
		}

		len0++;
	}
	struct tstring ret;
	ret.str0 = start0;
	ret.str1 = start1;
	return ret;
}

/*struct strprint read_string(char* mass, int len, int x, int y, char flg, char* stack, short int stack_len)
{
        int ltime = 0x0;
        char lchar = 0x0;
	char llchar = 0x0;
	int nlen = 0x0;
	int lx = x;
	int ly = y;
	int list = 0x0;
	int time = *timer;
	int time1 = *timer;
	int time2 = *timer;
	char cursr = 0x1;
	char punkt = 0xFF;
	int sx = x;
	int sy = y;

	for(int i = 0; i < len;  i++)
	{
		*(mass+i) = 0x0;
	}

        for(int i = 0; i < 7; i++)
        {
        	*(videostrt+x*8+y*8*320+i*320) = warcolor;
	}

	while(1==1)
	{
		char in = read_button();
                if(nlen >= 0 && (nlen < len || in == 0x08 || in == 0x0A) && (ltime+5 <= *timer || lchar != in || (llchar == lchar && lchar == in && ltime+3 <= *timer)) && ((in >= 0x41 && in <= 0x5A) || (in >= 0x61 && in <= 0x7A) || (in >= 0x30 && in <= 0x3A) || in == 0x20 || in == 0x08 || in == 0x27 || in == 0x2E || in == 0x3A || in == 0x2F || in == 0x0A || in == 0x2C || in == 0x7C))
                {
			if(in == 0x0A)
			{
				break;
			}

                        ltime = *timer;
                        llchar = lchar;
                        lchar = in;

                        if(x<40 && in != 0x08)
                        {
                        	if(x-sx < nlen && in)
                        	{
                        		//lx = x;
                        		//ly = y;

                        		char* massln = (char*)(mass+(x-sx));
                        		char _0 = 0x0;
                        		char _1 = in;

                        		while(*(massln-1) || massln == mass)
                        		{
                        			_0 = *massln;
                        			*massln = _1;
                        			_1 = _0;
                        			massln++;
                        		}

					fill_square(x*8, y*8, (nlen-(x-sx))*8, 8, 0x0);

                                	struct strprint srt = print_string(x, y, mass+(x-sx), color, 0x0, 0x0);
                                	//x = srt.x;
                                	//y = srt.y;
					x++;
                                	nlen++;
                        	}
                        	else if(in)
                        	{
                        		create_char(x*8, y*8, in, color, flg);
                                        *(mass+nlen) = in;
                                        nlen++;
                                        x++;
                                }
                        }
                        else if(in != 0x08)
                        {
                                if(y<24)
                                {
                                        x=0x0;
                                        y++;
                                        if(in)
                        		{
                        	        	create_char(x*8, y*8, in, color, flg);
                                                *(mass+nlen) = in;
                                                nlen++;
                        		}
                        		x++;
                                }
				else
				{
					clear(0x0, 0xFFFF);
					list++;
					x = 0x0;
					y = 0x0;
                        		if(in)
                        		{
                        	        	create_char(x*8, y*8, in, color, flg);
                                                *(mass+nlen) = in;
                                                nlen++;
                        		}
					x++;
				}
                        }

                        if(x>0x1 && in == 0x08 && nlen > 0x0 && x-sx > 0x0)
                        {
                        	x--;
                        	nlen--;
				if(x-sx < nlen && in)
                                {
                                        //lx = x;
                                        //ly = y;
                                        //x--;
                                        //nlen--;

                                        char* massln = (char*)(mass+(x-sx));

                                        while(*(massln))
                                        {
                                                *massln = *(massln+1);
                                                massln++;
                                        }

                                        fill_square(x*8, y*8, (nlen-(x-sx)+1)*8, 8, 0x0);

                                        struct strprint srt = print_string(x, y, mass+(x-sx), color, 0x0, 0x0);
                                        //x = srt.x;
                                        //y = srt.y;
                                }
                                else if(in)
                                {
                                	//x--;
                                	create_char(x*8, y*8, 0x8, color, flg);
                                	//nlen--;
                               		*(mass+nlen) = 0x0;
                                }
                        }
                        else if(in == 0x08 && nlen > 0x0 && x-sx > 0x0)
                        {
                                if(y>0)
                                {
                                	x--;
					create_char(x*8, y*8, 0x08, color, flg);
                                        x=40;
                                        y--;
                                        nlen--;
                                	*(mass+nlen) = 0x0;
                                }
                                else
                                {
					clear(0x0, 0xFFFF);
					list--;
					if(!list)
					{
						strprint_to_global(print_string(*globalx, *globaly, ">>", attcolor, 0x0, 0x0));
					}
					nlen--;
                                	*(mass+nlen) = 0x0;
					strprint_to_global(print_string(*globalx, *globaly, mass+list*39*24, color, 0x0, 0x0));
					x = *globalx;
					y = *globaly;
                                }
                                create_char(x*8, y*8, 0x8, color, flg);
                        }

                        for(int i = 0; i < 7; i++)
                	{
                		*(videostrt+lx*8+ly*8*320+i*320) = 0x0;
                		cursr = 0x1;
			}
                }
		else if(time2+3 < *timer && (in == 0x5B || in == 0x5D))
		{
			lx = x;
			ly = y;

			if(in == 0x5B && x < nlen+sx)
			{
				x++;
			}
			else if(x > sx && in == 0x5D)
			{
				x--;
			}

			for(int i = 0; i < 7; i++)
                	{
                		*(videostrt+lx*8+ly*8*320+i*320) = 0x0;
                		cursr = 0x1;
			}

			time2 = *timer;
		}
		else if(time1+3 < *timer && (in == 0x2B || (in == 0x2D && *(stack+(punkt+1)*(len+1)))))
		{
			if(in == 0x2D && punkt < stack_len-1 && punkt != 0xFF)
			{
				punkt++;
			}
			else if(in == 0x2B && punkt >= 0x0 && punkt != 0xFF)
			{
				punkt--;
			}
			else if(punkt == 0xFF && in == 0x2D)
			{
				punkt = 0x0;
			}

			lx = x;
			ly = y;

			if(punkt == -0x1 && in == 0x2B)
			{
				nlen = 0x0;
				x = sx;
				y = sy;
				fill_square(sx*8, sy*8, len*8, 8, 0x0);
				for(int i = 0; i < len; i++)
				{
					*(mass+i) = 0x0;
				}
			}
			else
			{
				for(int i = 0; i < len; i++)
				{
					*(mass+i) = 0x0;
				}
				for(int i = 0; i < len; i++)
				{
					*(mass+i) = *(stack+punkt*(len+1)+i);
				}
				//fill_square(sx*8, (sy+1)*8, len*8, 8, 0x0);
				//strprint_to_global(print_string(sx, sy+1, mass, attcolor, 0x0, 0x0));
				fill_square(sx*8, sy*8, len*8, 8, 0x0);
				struct strprint srt = print_string(sx, sy, stack+punkt*(len+1), color, 0x0, 0x0);
				x = srt.x;
				y = srt.y;
				nlen = srt.len;
			}
			time1 = *timer;
		}

		if(time + animationspeed+3 < *timer && x != 40)
		{
			if(cursr == 0x0)
			{
                        	for(int i = 0; i < 7; i++)
                		{
                			*(videostrt+lx*8+ly*8*320+i*320) = 0x0;
                			cursr = 0x1;
				}
			}
			else
			{
                		for(int i = 0; i < 7; i++)
                		{
                			*(videostrt+x*8+y*8*320+i*320) = warcolor;
					cursr = 0x0;
				}
			}
			time = *timer;
		}
		else if(x == 40)
		{
			for(int i = 0; i < 7; i++)
                	{
                		*(videostrt+lx*8+ly*8*320+i*320) = 0x0;
                		cursr = 0x1;
			}
		}

		lx = x;
		ly = y;
	}
	for(int i = 0; i < 7; i++)
        {
                *(videostrt+lx*8+ly*8*320+i*320) = 0x0;
        }
	struct strprint p;
	p.x = x;
	p.y = y;
	p.len = nlen;
	return p;
}*/

void create_char(int x, int y, char in, char color, char flg)
{
	if((in >= 0x41 && in <= 0x5A) || (in >= 0x61 && in <= 0x7A) || (in >= 0x30 && in <= 0x3A) || in == 0x20 || in == 0x08 || in == 0x2E || in == 0x3A || in == 0x2F || in == 0x0A || in == 0x3E || in == 0x27 || in == 0x2C || in == 0x7C)
	{
		if(in >= 0x41 && in <= 0x5A)
                {
                	read_rastr(x, y, alfabet+0x4B*(in-0x40), color, flg);
                }
		else if(in >= 0x61 && in <= 0x7A)
                {
                	read_rastr(x, y, alfabet+0x4B*(in-0x60), color, flg);
                }
                else if(in >= 0x30 && in <= 0x3A)
                {
                      	read_rastr(x, y, alfabet+0x4B*(in-0x30+27), color, flg);
                }
                else if(in == 0x20)
                {
                      	read_rastr(x, y, alfabet+0x4B*(0), color, 0x1);
                }
                else if(in == 0x08)
                {
                      	read_rastr(x, y, alfabet+0x4B*(0), color, 0x1);
                }
                else if(in == 0x2E)
                {
                      	read_rastr(x, y, alfabet+0x4B*(39), color, flg);
                }
                else if(in == 0x3A)
                {
                      	read_rastr(x, y, alfabet+0x4B*(37), color, flg);
                }
                else if(in == 0x2F)
                {
                      	read_rastr(x, y, alfabet+0x4B*(41), color, flg);
                }
                /*else if(in == 0x0A)
                {
                      	read_rastr(x, y, alfabet+0x4B*(0), color, 0x1);
                }*/
                else if(in == 0x3E)
                {
                      	read_rastr(x, y, alfabet+0x4B*(40), color, flg);
                }
                else if(in == 0x27)
                {
                      	read_rastr(x, y, alfabet+0x4B*(38), color, flg);
                }
                else if(in == 0x2C)
                {
                      	read_rastr(x, y, alfabet+0x4B*(43), color, flg);
                }
                else if(in == 0x7C)
                {
                      	read_rastr(x, y, alfabet+0x4B*(42), color, flg);
                }
        }
        return;
}

struct strprint print_int(int x, int y, int in, char color, char flg, short int ogran)
{
	short int len = 0x0;
	short int nlen = 0x0;
	char inp = 0x0;
	int sx = x;
        int sy = y;
        int time = *timer;
        while(len < ogran)
        {
        	len++;
        }
        while(len >= 0x0)
        {
		inp = razryad(in, len);
		if(inp >= 0x0 && inp <= 0x9)
		{
			create_char(x*8, y*8, inp+0x30, color, flg);
		}
		else if(inp >= 0xA && inp <= 0xF)
	 	{
			create_char(x*8, y*8, inp-0xA+0x41, color, flg);
		}
		else
		{
			create_char(x*8, y*8, 0x3A, color, flg);
		}

		if(x<39)
		{
			x+=1;
		}
		else
		{
			if(y<25)
			{
				x=0;
				y+=1;
			}
			else
			{
				break;
			}
		}

		len--;
	}
	struct strprint p;
        p.len = len;
        p.x = x;
        p.y = y;
        return p;
}

struct strprint print_string(int x, int y, char* in, char color, char flg, char move)
{
	short int len = 0x0;
	short int nlen = 0x0;
	char* start = in;
	int sx = x;
	int sy = y;
	int time = *timer;
	if(x <= 39 && x >= 0x0 && y <= 24 && y >= 0x0)
	{
		while(*in != 0x0)
		{
			if(len > nlen && move > 0x0)
			{
				while(time+animationspeed >= *timer && move != 0x3){}
				time = *timer;
				if(move == 0x2 || move == 0x3)
				{
					for(int i = 0; i < len; i++)
					{
						create_char((sx+i)*8, sy*8, 0x20, color, flg);
					}
				}
				nlen = len;
				len = 0;
				in = start;
				/*if(sx<39 && move == 0x1)
				{
					sx+=1;
				}
				else if(move == 0x1)
				{
					if(sy<25)
					{
						sx=0;
						sy+=1;
					}
					else
					{
						break;
					}
				}*/
				if(sx>0 && (move == 0x2 || move == 0x3))
				{
					sx--;
				}
				else if(move == 0x2 || move == 0x3)
				{
					if(sy>0)
					{
						sx=39;
						sy--;
					}
					else
					{
						break;
					}
				}
				x = sx;
				y = sy;
			}

			if(*in != 0x08)
			{
				create_char(x*8, y*8, *in, color, flg);
				if(x<39 && *in != 0x0A)
				{
					x++;
				}
				else
				{
					if(y<24 || *in == 0x0A)
					{
						x=0;
						y++;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				if(x>0)
				{
					x--;
				}
				else
				{
					if(y>0)
					{
						x=39;
						y--;
					}
					else
					{
						break;
					}
				}
				create_char(x*8, y*8, 0x20, color, flg);
			}

			in++;
			len++;
		}
	}

	struct strprint p;
	p.len = len;
	p.x = x;
	p.y = y;

	return p;
}

char read_button()
{
	char out = 0x0;
        for(int i = 0; i < 20; i++)
        {
                if(*(buttonread+i) >= 0x2 && *(buttonread+i) <= 0x57)
                {
                        for(int j = 0; j < 49; j++)
                        {
                                if(*(alfabet+0xD00+j*2) == *(buttonread+i))
                                {
                                        out = *(alfabet+0xD00+j*2+1);
                                        break;
                                }
                        }
			break;
                }
        }
        return out;
}

char find_buttn(char in)
{
        for(int i = 0; i < 20; i++)
        {
                if(*(buttonread+i) == in)
                {
                        return 0x1;
                }
        }
        return 0x0;
}

char razryad(int in, char num)
{
	char min = 0x0;
	if(num > 0x0 && in > 0x0)
	{
        	return (in-in/stepen(0x10, num+1)*stepen(0x10, num+1)-in%stepen(0x10, num))/stepen(0x10, num);
	}
	else if(num == 0x0 && in > 0x0)
	{
		return in%0x10;
	}
	else if(in < 0x0)
	{
		while(in < 0x0)
		{
			in+=0x10000000;
			min++;
		}
		min--;
		if(num != 0x7)
		{
        		return (in-in/stepen(0x10, num+1)*stepen(0x10, num+1)-in%stepen(0x10, num))/stepen(0x10, num);
		}
		else
		{
			return 0xF-min;
		}
	}
	else if(in == 0x0)
	{
		return 0x0;
	}
}

int stepen(int num, short int step)
{
	int newnum = num;
	short int st = 0x1;
	if(step > 0x1)
	{
		while(st < step)
		{
			newnum *= num;
			st++;
		}
	}
	else if(step == 0x0)
	{
		newnum = 0x1;
	}
	return newnum;
}

void setup_keyboard(char setup)
{
        asm volatile
        (
        "movb $0xED, %%al\n\t"
        "outb %%al, $0x60"
        :
        :
        :"eax"
        );
        wait(0x1);
        asm volatile
        (
        "movb $0b00000001, %%al\n\t"
        "outb %%al, $0x60\n\t"
        "movb $0x60, %%al\n\t"
        "outb %%al, $0x64\n\t"
        "mov %0, %%al\n\t"
        "outb %%al, $0x60\n\t"
        "movb 0x20, %%al\n\t"
        "outb %%al, $0x20\n\t"
        :
        :"g"(setup)
        :"eax"
        );
}

int module(int in)
{
	if(in < 0)
	{
		in*=-1;
	}
	return in;
}

void wait(short int count)
{
        int time = *timer;
        while(time+count >= *timer){}
}


void waitspec(int count)
{
        int time = 0x0;
        while(time <= count)
	{
		time++;
	}
}
