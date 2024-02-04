void square(int sdvgx, int sdvgy, int sizex, int sizey, char color);
void draw_pix(int x, int y, char color);
void circle(int sdvgx, int sdvgy, int r, char color);
void fill_square(int sdvgx, int sdvgy, int sizex, int sizey, char color);
void read_rastr(int sdvigx, int sdvigy, int from, char plus, char null);
short int read_rastr_anim(int sdvigx, int sdvigy, int from, char plus, short int time);
void clear(int from, int to);
void read_rastr_0(int sdvigx, int sdvigy, int from, char plus, char null, short int size);

short int read_rastr_anim(int sdvigx, int sdvigy, int from, char plus, short int cadr)
{
	short int cadrnow = 0x0;
	char* point = (char*)from;
	short int minx = 0x0;
	short int miny = 0x0;
	char af = 0x0;
	while(1==1)
	{
		if(*(point)+0x30 == ')' && *(point+1)+0x30 == '/')
                {
                        return;
                }
		else if(*(point)+0x30 == '&')
		{
			if(af == 0x0)
			{
				af++;
				minx /= 2;
			}
			miny++;
		}
                else if(*(point)+0x30 == '#')
                {
                	miny /= 2;
                	sdvigx -= minx;
                	sdvigy -= miny;
                	point = from;
                	break;
                }
		if(af == 0x0)
		{
			minx++;
		}
		point++;
	}
        int x = sdvigx;
        int y = sdvigy;
        while(1==1)
        {
                if(*(point)+0x30 == ')' && *(point+1)+0x30 == '/')
                {
                        cadr = 0x0;
	               	break;
                }
                else if(*(point)+0x30 == '#')
                {
			if(cadrnow < cadr)
			{
				cadrnow++;
			}
			else
			{
                		cadr++;
				break;
                	}
                }
                else if(*(point)+0x30 == '&' && cadrnow == cadr && *(point)+0x30 != '#')
                {
                        y++;
                        x=sdvigx;
                }
                else if(cadrnow == cadr  && *(point)+0x30 != '#')
                {
                        x++;
			if(*point!=0x0)
			{
	                        draw_pix(x, y, *point+plus-1);
                	}
			else
			{
				draw_pix(x, y, *point);
			}
		}
                point++;
        }
        return cadr;
}

void read_rastr(int sdvigx, int sdvigy, int from, char plus, char null)
{
        char* point = (char*)from;
        int x = sdvigx;
        int y = sdvigy;
        point++;
        while(1==1)
        {
                if((*(point)+0x30 == ')' && *(point+1)+0x30 == '/') || plus+0x10 == 0xF)
                {
                        break;
                }
                if(*(point)+0x30 == '&')
                {
                        y++;
                        x=sdvigx;
                }
                else
                {
                        x++;
			if(*point!=0x0)
			{
	                        draw_pix(x, y, *point+plus-1);
                	}
			else if(null == 1)
			{
				draw_pix(x, y, *point);
			}
		}
                point++;
        }
}

void read_rastr_0(int sdvigx, int sdvigy, int from, char plus, char null, short int size)
{
        char* point = (char*)from;
        int x = sdvigx;
        int y = sdvigy;
	short int smil = 0x0;
	short int smhj = 0x0;
        point++;
        while(1==1)
        {
                if((*(point)+0x30 == ')' && *(point+1)+0x30 == '/') || plus+0x10 == 0xF)
                {
                        break;
                }
                if(*(point)+0x30 == '&')
                {
                        y+=size;
                        x=sdvigx;
                }
                else
                {
                        x+=size;

			while(smhj < size)
		        {
				while(smil < size)
				{
					if(*point != 0x0)
					{
	                       			draw_pix(x+smil, y+smhj, *point+plus-1);
					}
					else if(null == 0x1)
					{
						draw_pix(x+smil, y+smhj, *point);
					}
	                       		smil++;
				}
				smil = 0x0;
				smhj++;
			}
			smil = 0x0;
			smhj = 0x0;
		}
                point++;
        }
}

void draw_pix(int x, int y, char color)
{
        /*if(x >= 0 && x <= 40*8 && y >= 0 && y <= 25*8)
        {
                char* point = videostrt;
                point += x+y*320;
                *point = color;
        }*/
	int plus = x+y*320;
	asm volatile(
	"mov %0, %%eax\n\t"
	"mov %1, %%ecx\n\t"
	"int $0x31"
	:
	:"g"(plus), "g"(color)
	:"eax", "ecx"
	);
}

void circle(int sdvgx, int sdvgy, int r, char color)
{
        int x = r;
        int y = 0;
        int rE = 1-x;
        while(x>=y)
        {
                draw_pix(x+sdvgx, y+sdvgy, color);
                draw_pix(y+sdvgx, x+sdvgy, color);
                draw_pix(-x+sdvgx, y+sdvgy, color);
                draw_pix(-y+sdvgx, x+sdvgy, color);
                draw_pix(-x+sdvgx, -y+sdvgy, color);
                draw_pix(-y+sdvgx, -x+sdvgy, color);
                draw_pix(x+sdvgx, -y+sdvgy, color);
                draw_pix(y+sdvgx, -x+sdvgy, color);
                y++;
                if(rE < 0)
                {
                        rE += 2*y+1;
                }
                else
                {
                        x--;
                        rE += 2*(y-x+1);
                }
        }
}

void fill_square(int sdvgx, int sdvgy, int sizex, int sizey, char color)
{
        for(int i = 0; i <= sizey; i++)
        {
                for(int j = 0; j <= sizex; j++)
                {
                        draw_pix(j+sdvgx, i+sdvgy, color);
                }
        }
}

void square(int sdvgx, int sdvgy, int sizex, int sizey, char color)
{
        for(int i = 0; i <= sizex; i++)
        {
                draw_pix(i+sdvgx, sdvgy, color);
        }
        for(int i = 1; i <= sizey; i++)
        {
                draw_pix(sdvgx, i+sdvgy, color);
                draw_pix(sdvgx+sizex, i+sdvgy, color);
        }
        for(int i = 0; i <= sizex; i++)
        {
                draw_pix(i+sdvgx, sdvgy+sizey, color);
        }
}

void clear(int from, int to)
{
	char* point = videostrt+from;
        while(point <= videostrt+to)
        {
                *point = 0x0;
                point++;
        }
	if(clear_on_off)
	{
		// *timer = 0x0;
		*globalx = 0x0;
		*globaly = 0x0;
	}
	return;
}
