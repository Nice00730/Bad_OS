void square(int sdvgx, int sdvgy, int sizex, int sizey, char color);
void draw_pix(int x, int y, char color);
void circle(int sdvgx, int sdvgy, int r, char color);
void read_rastr(int sdvigx, int sdvigy, int from, char plus, char null);
void clear(int from, int to);
void fill_square(int sdvgx, int sdvgy, int sizex, int sizey, char color);

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

void draw_pix(int x, int y, char color)
{
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

/*void circle(int sdvgx, int sdvgy, int r, char color)
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
}*/

void clear(int from, int to)
{
        *IRQ = 0x20;
        *arg0 = from;
        *arg1 = to;
        OS();
        return;
}
