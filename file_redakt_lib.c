void waitspec(int count);
void wait(short int count);
char find_buttn(char in);
void create_char(int x, int y, char in, char color, char flg);
struct strprint print_string(int x, int y, char* in, char color, char flg, char move);
void strprint_to_global(struct strprint p);
struct strprint print_int(int x, int y, int in, char color, char flg, short int ogran);
int stepen(int num, short int step);
char razryad(int in, char num);
char del(char* name, char* ext);
struct chr_err r_c(int _0, int _1, int _2);
struct sho_err r_s_f(char* to, int msln, char* n, char* e, int from);
char w_c(int _0, int _1, int _2, char _3);
char w_s_f(char* from, char* n, char* e, int to);
char read_button();
char crt(char* name, char* ext, short int size, char ref, char root);
char SVIS(char* name, char* ext);
void load_num(int to, int size, char num);
char* plus_string(char* in0, char* in1, short int lenin0, char num);
struct sho_err take_file_size(char* name, char* ext);
char file_to_file(char* name0, char* name1, char* ext);
char find_file(char* fn, char* fe);
char srav_string(char* in0, char* in1, char num);
int str_to_int(char* str);
struct tstring redakt_string(char* in0, char* in1, char del, char num);
char take_file_flg(char* name, char* ext);
char set_file_flags(char* fir, char* sec, char in);

char set_file_flags(char* fir, char* sec, char in)
{
        *IRQ = 0xC;
        *arg0 = fir;
        *arg1 = sec;
        *arg2 = in;
        OS();
        return *arg2;
}


char take_file_flg(char* name, char* ext)
{
	*IRQ = 0xB;
        *arg0 = name;
        *arg1 = ext;
        OS();
	return *arg3;
}

struct tstring redakt_string(char* in0, char* in1, char del, char num)//in0 начальная строка, in1 - пустая, в неё кладётся результат; 0x0 - передаёт две строки, делённые по del
{//                                     ТОЛЬКО БОЛЬШИЕ БУКВЫ В del
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

char find_file(char* fn, char* fe)
{
	*IRQ = 0xA;
        *arg0 = fn;
        *arg1 = fe;
        OS();
	return *arg2;
}

char file_to_file(char* name0, char* name1, char* ext)
{
	int size = take_file_size(name0, ext).sho*0x200-0x4;
	//print_int(0, 23, size, attcolor, 0x1, 0x6);
	int to = 0x0;

	while(to < size)
	{
		char err = w_c(name1, ext, to, r_c(name0, ext, to).chr);
		if(err)
		{
			return err;
		}
		to++;
	}
	return 0x0;
}

char* plus_string(char* in0, char* in1, short int lenin0, char num)
{
        short int len0 = 0x0;
        short int len1 = 0x0;

        while(*(in0+len0))
        {
                len0++;
        }

        while(*(in1+len1) && len0 < lenin0)
        {
		*(in0+len0) = *(in1+len1);
                if(num)
                {
			*(in1+len1) = 0x0;
                }
                len0++;
                len1++;
        }

        return in0;
}

void load_num(int to, int size, char num)
{
        char* go = (char*)to;
        for(int i = 0; i < size; i++)
        {
                *(go+i) = num;
        }
}

struct sho_err take_file_size(char* name, char* ext)
{
        *IRQ = 0x9;
        *arg0 = name;
        *arg1 = ext;
        OS();
	struct sho_err p;
	p.sho = *arg3;
	p.err = *arg2;
	return p;
}

char SVIS(char* name, char* ext)
{
        *IRQ = 0x7;
        *arg0 = name;
        *arg1 = ext;
        *arg2 = 0x0;
	OS();
	return *arg2;
}

char crt(char* name, char* ext, short int size, char ref, char root)
{
	*IRQ = 0x1;
        *arg0 = name;
        *arg1 = ext;
        *arg2 = size;
        *arg3 = ref;//0b011
	*arg4 = root;
        OS();
	return *arg2;
}

struct sho_err r_s_f(char* to, int msln, char* n, char* e, int from)
{
	char in = 0x1;
	short int sdvg = 0x0;
	struct chr_err o;
	while(in)
	{
		o = r_c(n, e, sdvg+from);
		in = o.chr;
		if(o.err || sdvg >= msln)
		{
			break;
		}
		*(to+sdvg) = o.chr;
		sdvg++;
	}
	struct sho_err p;
	p.err = o.err;
	p.sho = sdvg;
	return p;
}

char w_s_f(char* from, char* n, char* e, int to)
{
	short int sdvg = 0x0;
	char err = 0x0;
	while(*(from+sdvg))
	{
		err = w_c(n, e, sdvg+to, *(from+sdvg));
		if(err)
		{
			return err;
		}
		sdvg++;
	}
}

struct chr_err r_c(int _0, int _1, int _2)
{
	*IRQ = 0x5;
	*arg0 = _0;
	*arg1 = _1;
	*arg2 = _2;
	OS();
	struct chr_err p;
	p.err = *arg2;
	p.chr = *arg3;
	return p;
}

char w_c(int _0, int _1, int _2, char _3)
{
	*IRQ = 0x3;
	*arg0 = _0;
	*arg1 = _1;
	*arg2 = _2;
	*arg3 = _3;
	OS();
	return *arg2;
}

char del(char* name, char* ext)
{
        *IRQ = 0x2;
        *arg0 = name;
        *arg1 = ext;
        OS();
        return *arg2;
}

void exit()
{
	*IRQ = 0x30;
	OS();
}

void strprint_to_global(struct strprint p)
{
        *globalx = p.x;
        *globaly = p.y;
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
		/*else
		{
			fill_square(x+3, y+3, 1, 1, attcolor);
		}*/
        }
        return;
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

/*struct strprint read_string(char* mass, int len, int x, int y, char flg, short int stack_len)
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
		if(find_buttn(0x53))
		{
			x = 240;
			y = 240;
			nlen = 240;
			break;
		}

                char in = read_button();
                if(nlen >= 0 && (nlen < len || in == 0x08 || in == 0x0A) && (ltime+5 <= *timer || lchar != in || (llchar == lchar && lchar == in && ltime+3 <= *timer)) && ((in >= 0x41 && in <= 0x5A) || (in >= 0x61 && in <= 0x7A) || (in >= 0x30 && in <= 0x3A) || in == 0x20 || in == 0x08 || in == 0x27 || in == 0x2E || in == 0x3A || in == 0x2F || in == 0x0A || in == 0x2C || in == 0x7C))
                {
                        if(in == 0x0A)
                        {
                                break;
                        }

			punkt = -0x1;

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
                else if(time1+3 < *timer && (in == 0x2B || (in == 0x2D && r_c(stack, text, (punkt+1)*(len+1)).chr))) // *(stack+(punkt+1)*(len+1))
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
                                        // *(mass+i) = *(stack+punkt*(len+1)+i);
                                        *(mass+i) = r_c(stack, text, punkt*(len+1)+i).chr;
                                }
                                //fill_square(sx*8, (sy+1)*8, len*8, 8, 0x0);
                                //strprint_to_global(print_string(sx, sy+1, mass, attcolor, 0x0, 0x0));
                                fill_square(sx*8, sy*8, len*8, 8, 0x0);

				x = sx;
				y = sy;
				nlen = 0x0;
				int i = 0x0;
				while(r_c(stack, text, punkt*(len+1)+i).chr)
				{
					create_char(x*8, y*8, r_c(stack, text, punkt*(len+1)+i).chr, color, flg);
					x++;
					nlen++;
					i++;
				}
                                //struct strprint srt = print_string(sx, sy, stack+punkt*(len+1), color, 0x0, 0x0);
                                //x = srt.x;
                                //y = srt.y;
                                //nlen = srt.len;
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
