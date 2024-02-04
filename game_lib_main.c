void waitspec(int count);
void wait(short int count);
char find_buttn(char in);
void create_char(int x, int y, char in, char color, char flg);
struct strprint print_string(int x, int y, char* in, char color, char flg, char move);
void strprint_to_global(struct strprint p);
struct strprint print_int(int x, int y, int in, char color, char flg, short int  ogran);
int stepen(int num, short int step);
char razryad(int in, char num);
char del(char* name, char* ext);

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
