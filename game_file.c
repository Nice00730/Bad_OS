char* IRQ = (char*)0xFE6;
int* arg0 = (int*)0xFE1;
int* arg1 = (int*)0xFDD;
int* arg2 = (int*)0xFD9;
int* arg3 = (int*)0xFD5;
int* arg4 = (int*)0xFD1;
typedef void (*fs)(void);
fs OS = (fs) 0x10000;

void main()
{
	game();
}

char text[] = "TEXT";
char cute[] = "CUTE";
char _0[] = "SCORE";

#include "game_perem.c"
#include "game_lib_graph.c"
#include "game_lib_main.c"

char white = 0x7;

int bscore = 0x0;
short int sdvgx = 9;
short int sdvgy = 9;
short int scalex = 300;
short int scaley = 180;
short int R = 6;
short int X = 0x0;
short int Y = 0x0;
short int lX = 0x0;
short int lY = 0x0;
short int sX = 0x0;
short int sY = 0x0;
short int slX = 0x0;
short int slY = 0x0;
short int maxspeedx = 10;
short int maxspeedy = 10;
short int maxsspeedx = 6;
short int maxsspeedy = 6;
short int sspeedx = 0;
short int sspeedy = 0;
short int speedx = 0;
short int speedy = 0;
short int speedpl = 2;
short int sspeedpl = 2;
int time = 0x0;
int timef = 0x0;
int timed = 0x0;
short int fuel = 18;
int score = 0x0;
char SHIFT = 0x0;
char main_menu_num = 0x0;
char main_menu_org = 0x3;
char main_menu_sm = 0x8;
char phantom = 0x1;

char end_menu_sm = 0xD;
char end_menu_num = 0x0;
char end_menu_org = 0x2;

void game()
{
	*arg0 = 0x0;
	*arg1 = 0x0;
	*arg2 = 0x0;
	*arg3 = 0x0;
	*arg4 = 0x0;

	//wait(6);

	clear(0x0, 0xFFFF);

	*IRQ = 0x1;
	*arg0 = _0;
	*arg1 = text;
	*arg2 = 0x1;
	*arg3 = 0b011;
	*arg4 = 0x0;
	OS();

	if(!*arg2)
	{
		*IRQ = 0x7;
        	*arg0 = _0;
        	*arg1 = text;
        	OS();
	}

	print_string(12, main_menu_sm, ">", attcolor, 0x0, 0x0);
	print_string(13, 8, "Phantom", attcolor, 0x0, 0x0);
	fill_square(21*8, 8*8+2, 2, 2, warcolor);
        print_string(13, 9, "Clear score", attcolor, 0x0, 0x0);
	print_string(13, 10, "Start", attcolor, 0x0, 0x0);
	print_string(13, 11, "Exit", attcolor, 0x0, 0x0);
	square(160-R/2-1-64-64/2, 100-R/2-1-64, R+2+64*3, R+2+64*2, warcolor);

	while(1)
	{
		if(find_buttn(0x1C) && timed+3 < *timer)
		{
			if(main_menu_num == 0x2)
			{
				break;
			}
			else if(main_menu_num == 0x1)
                        {
                                *IRQ = 0x4;
                                *arg0 = _0;
                                *arg1 = text;
                                if(phantom)
                                {
                                        *arg2 = 0x4;
                                }
                                else
                                {
                                        *arg2 = 0x0;
                                }
                                *arg3 = 0x0;
                                OS();
                                if(*arg2)
                                {
                                        fill_square(25*8, 9*8+2, 2, 2, warcolor);
                                }
                                fill_square(25*8, 9*8+2, 2, 2, color);
                        }
			else if(main_menu_num == 0x0)
			{
				if(!phantom)
				{
					fill_square(21*8, 8*8+2, 2, 2, color);
					phantom = 0x1;
				}
				else
				{
					fill_square(21*8, 8*8+2, 2, 2, warcolor);
					phantom = 0x0;
				}
			}
			else if(main_menu_num == 0x3)
			{
				clear(0x0, 0xFFFF);
				exit();
			}
			timed = *timer;
		}

		if(find_buttn(0x50) && main_menu_num < main_menu_org && timed+2 < *timer)
		{
			print_string(13, main_menu_sm+main_menu_num, "\b", attcolor, 0x0, 0x0);
			main_menu_num++;
			print_string(12, main_menu_sm+main_menu_num, ">", attcolor, 0x0, 0x0);
			timed = *timer;
		}
		else if(find_buttn(0x48) && main_menu_num > 0x0 && timed+2 < *timer)
		{
			print_string(13, main_menu_sm+main_menu_num, "\b", attcolor, 0x0, 0x0);
			main_menu_num--;
			print_string(12, main_menu_sm+main_menu_num, ">", attcolor, 0x0, 0x0);
			timed = *timer;
		}
	}

	while(1)
	{

	/*sX = 160;
	sY = 100;
	slX = 160;
	slY = 100;*/

	short int r = 0x0;

	while(1)
        {
	        if(r == 64)
                {
	                break;
                }
		if(r*3 < 160)
                {
                	fill_square(r*3, 0x0, 3, 200, 0x0);
                        fill_square(315-r*3, 0x0, 3, 200, 0x0);
                }
                /*square(slX, slY, R+2+(r-1)*3, R+2+(r-1)*2, 0x0);
                square(sX-R/2-1-r-r/2, sY-R/2-1-r, R+2+r*3, R+2+r*2, warcolor);
                slX = sX-R/2-1-r-r/2;
                slY = sY-R/2-1-r;*/
                r++;
                waitspec(0x50000);
        }

	clear(0x0, 0xFFFF);

	*IRQ = 0x6;
	*arg0 = _0;
        *arg1 = text;
        if(phantom)
        {
        	*arg2 = 0x4;
        }
        else
        {
        	*arg2 = 0x0;
        }
        OS();

	if(*arg2)
        {
        	strprint_to_global(print_string(0x10, 0, "Can't read: ", warcolor, 0x0, 0x0));
        	print_int(*globalx, *globaly, *arg2, color, 0x0, 0x0);
        	bscore = 0x0;
        	*arg3 = 0x0;
	}
	else
	{
		bscore = *arg3;
	}

        square(sdvgx, sdvgy, scalex, scaley, attcolor);
        //wait(0x2);
        char change = 0;

	time = *timer;
	timef = *timer;
	timed = *timer;
	fuel = 18;
	X = 159-R;
	Y = 99-R;
	lX = X;
	lY = Y;
	sX = 10+R;
	sY = 10+R;
	slX = sX;
	slY = sY;
	score = 0x0;
	sspeedx = 0x0;
	sspeedy = 0x0;
	speedx = 0x0;
	speedy = 0x0;
	SHIFT = 0x0;
	char brk = 0x0;
	char spfl = 0x0;
	char spfe = 0x0;

	if(phantom)
	{
      		fill_square(314, 73, 2, 54, jircolor);
      		square(313, 72, 4, 56, attcolor);
      	}

	/*strprint_to_global(print_string(0x0, 24, "BestScore:", attcolor, 0x0, 0x0));
	strprint_to_global(print_int(*globalx, *globaly, bscore, color, 0x0, 0x6));
	strprint_to_global(print_string(*globalx, *globaly, " | ", warcolor, 0x0, 0x0));*/
	strprint_to_global(print_string(0x0, 24, "Score:", attcolor, 0x0, 0x0));
	strprint_to_global(print_int(7, 24, score/2, color, 0x0, 0x6));

        square(sX-R/2-1, sY-R/2-1, R+2, R+2, warcolor);
        circle(X, Y, R, color);

	int time1 = *timer;
	char timing = 0x3;
	strprint_to_global(print_string(0x0, 0x0, "Unpausing: ", attcolor, 0x0, 0x0));
	strprint_to_global(print_int(*globalx, *globaly, timing, color, 0x0, 0x1));
	while(1)
	{
		if(timing == -0x1)
		{
			fill_square(0x0, 0x0, 30*8, 0x8, 0x0);
			break;
		}
		else if(time1+6 < *timer)
		{
			strprint_to_global(print_string(*globalx, *globaly, "\b\b", attcolor, 0x0, 0x0));
			strprint_to_global(print_int(*globalx, *globaly, timing, color, 0x0, 0x1));
			timing--;
			time1 = *timer;
		}
	}

	print_string(0x0, 0x0, "SPACE to pause", attcolor, 0x0, 0x0);

	while(1)
        {
           	if(find_buttn(0x39))
           	{
			//wait(0x6);
			fill_square(0x0, 0x0, 25*8, 0x8, 0x0);
			print_string(0x0, 0x0, "ESC to main menu/E to unpause", attcolor, 0x0, 0x0);

        		while(1)
			{
				if(find_buttn(0x01))
				{
					//clear(0x0, 0xFFFF);
					//exit();
					brk = 0x1;
					break;
				}
				else if(find_buttn(0x12))
				{
					fill_square(0x0, 0x0, 30*8, 0x8, 0x0);
					break;
				}
			}
			if(!brk)
			{
			int time1 = *timer;
			char timing = 0x3;
			strprint_to_global(print_string(0x0, 0x0, "Unpausing: ", attcolor, 0x0, 0x0));
			strprint_to_global(print_int(*globalx, *globaly, timing, color, 0x0, 0x1));
			while(1)
			{
				if(timing == -0x1)
				{
					fill_square(0x0, 0x0, 30*8, 0x8, 0x0);
					break;
				}
				else if(time1+6 < *timer)
				{
					strprint_to_global(print_string(*globalx, *globaly, "\b\b", attcolor, 0x0, 0x0));
					strprint_to_global(print_int(*globalx, *globaly, timing, color, 0x0, 0x1));
					timing--;
					time1 = *timer;
				}
			}
			print_string(0x0, 0x0, "SPACE to pause", attcolor, 0x0, 0x0);
			}
           	}


                if(SHIFT && fuel > 0x0 && !spfl && phantom)
                {
                        spfl = 0x1;
                }
		else if((!SHIFT || fuel == 0x0) && spfl && phantom)
		{
			if(fuel == 0x0)
			{
				spfe = 0x0;
				SHIFT = 0x0;
			}
			spfl = 0x0;
		}

	     	if(find_buttn(0x11))
                {
                        speedy -= speedpl;
                }
                else if(find_buttn(0x1F))
                {
                        speedy += speedpl;
                }

                if(find_buttn(0x1E))
                {
                        speedx -= speedpl;
                }
                else if(find_buttn(0x20))
                {
                        speedx += speedpl;
                }

                if(find_buttn(0x39))
                {
                        speedx /= 0x2;
                        speedy /= 0x2;
                }

		if(find_buttn(0x2A) && phantom)
		{
			SHIFT = 0x1;
		}
		else if(!find_buttn(0x2A) && phantom)
		{
			SHIFT = 0x0;
		}

                if(timef+1 < *timer && SHIFT && fuel > 0x0 && phantom)
                {
                	fuel--;
                	timef = *timer;
                	fill_square(314, 127-(18-fuel)*3, 2, (18-fuel)*3, 0x0);
                }
                else if(timef+3 < *timer && fuel < 18 && !SHIFT && phantom)
                {
                	fuel++;
                	timef = *timer;
                	fill_square(314, 73, 2, fuel*3, jircolor);
                }

                if((X-R+speedx <= sdvgx || X+R+speedx >= sdvgx+scalex) && speedx != 0)
                {
                        speedx *= -1;
                        speedx /= 2;
                }
                if((Y-R+speedy <= sdvgy || Y+R+speedy >= sdvgy+scaley) && speedy != 0)
                {
                        speedy *= -1;
                        speedy /= 2;
                }
		if(speedx-1 > 0)
                {
                        speedx -= speedpl-1;
                }
                else if(speedx+1 < 0)
                {
                        speedx += speedpl-1;
                }
                else
                {
                        speedx = 0;
                }
                if(speedy-1 > 0)
                {
                        speedy -= speedpl-1;
                }
                else if(speedy+1 < 0)
                {
                        speedy += speedpl-1;
                }
                else
                {
                        speedy = 0;
                }
                if(speedx > maxspeedx)
                {
                        speedx = maxspeedx;
                }
                else if(speedx < -maxspeedx)
                {
                        speedx = -maxspeedx;
                }
                if(speedy > maxspeedy)
                {
                        speedy = maxspeedy;
                }
		else if(speedy < -maxspeedy)
                {
                        speedy = -maxspeedy;
                }

                if(!change)
                {
                        X+=speedx;
                        Y+=speedy;
                }

		//square

		if((Y+R > sY-R && Y-R < sY+R) && (X+R > sX-R && X-R < sX+R) && !spfl || brk)
		{
			//clear(0x0, 0xFFFF);
			circle(lX, lY, R, 0x0);
			line(0xA, slY, slX-0x9-R, 0x1, 0x0);
			line(slX, 0xA, slY-0x9-R, 0x0, 0x0);
			line(slX+R-1, slY, 300-slX+R/2, 0x1, 0x0);
			line(slX, slY+R-1, 180-slY+R/2, 0x0, 0x0);
                	square(sX-R/2-1, sY-R/2-1, R+2, R+2, warcolor);
                	while(1)
                	{
				if(sX == 160 && sY == 99)
                		{
                			break;
                		}

                		if(sX < 160)
                		{
                			sX++;
                		}
                		else if(sX > 160)
                		{
                			sX--;
                		}

                		if(sY < 99)
                		{
                			sY++;
                		}
                		else if(sY > 99)
                		{
                			sY--;
                		}

				fill_square(slX-R/2-1, slY-R/2-1, R+2, R+2, 0x0);
		                square(sX-R/2-1, sY-R/2-1, R+2, R+2, warcolor);

                		slX = sX;
                		slY = sY;

               			waitspec(0xE0000);
                	}

			wait(2);

                	short int r = 0x0;

                	while(1)
                	{
                		if(r == 64)
                		{
                			break;
                		}
                		if(r*3 < 160)
                		{
					fill_square(r*3, 0x0, 3, 200, 0x0);
					fill_square(315-r*3, 0x0, 3, 200, 0x0);
				}
				square(slX, slY, R+2+(r-1)*3, R+2+(r-1)*2, 0x0);
		                square(sX-R/2-1-r-r/2, sY-R/2-1-r, R+2+r*3, R+2+r*2, warcolor);
				slX = sX-R/2-1-r-r/2;
				slY = sY-R/2-1-r;
               			r++;
               			waitspec(0x50000);
                	}
			break;
		}

		if(Y+R < sY)
                {
                        sspeedy -= sspeedpl;
                }
                else if(Y > sY)
                {
                        sspeedy += sspeedpl;
                }

                if(X+R < sX)
                {
                        sspeedx -= sspeedpl;
                }
                else if(X > sX)
                {
                        sspeedx += sspeedpl;
                }

                if((sX-R+sspeedx <= sdvgx || sX+R+sspeedx >= sdvgx+scalex) && sspeedx != 0)
                {
                        sspeedx *= -1;
                        sspeedx /= 2;
                }

                if((sY-R+sspeedy <= sdvgy || sY+R+sspeedy >= sdvgy+scaley) && sspeedy != 0)
                {
                        sspeedy *= -1;
                        sspeedy /= 2;
                }

		if(sspeedx-1 > 0)
                {
                        sspeedx -= sspeedpl-1;
                }
                else if(sspeedx+1 < 0)
                {
                        sspeedx += sspeedpl-1;
                }
                else
                {
                        sspeedx = 0;
                }

                if(sspeedy-1 > 0)
                {
                        sspeedy -= sspeedpl-1;
                }
                else if(sspeedy+1 < 0)
                {
                        sspeedy += sspeedpl-1;
                }
                else
                {
                        sspeedy = 0;
                }

                if(sspeedx > maxsspeedx)
                {
                        sspeedx = maxsspeedx;
                }
                else if(sspeedx < -maxsspeedx)
                {
                        sspeedx = -maxsspeedx;
                }

                if(sspeedy > maxsspeedy)
                {
                        sspeedy = maxsspeedy;
                }
		else if(sspeedy < -maxsspeedy)
                {
                        sspeedy = -maxsspeedy;
                }

                if(!change)
                {
                        sX+=sspeedx;
                        sY+=sspeedy;
                }

		if(time+6 < *timer)
		{
			score++;
			time = *timer;
	        	fill_square(7*8, 24*8, 9*8, 0x8, 0x0);
			strprint_to_global(print_int(7, 24, score/2, color, 0x0, 0x6));
		}

		fill_square(slX-R/2-1, slY-R/2-1, R+2, R+2, 0x0);
                circle(lX, lY, R, 0x0);
		/*line(0xA, slY, slX-0x9-R, 0x1, 0x0);
		line(slX, 0xA, slY-0x9-R, 0x0, 0x0);
		line(slX+R-1, slY, 300-slX+R/2, 0x1, 0x0);
		line(slX, slY+R-1, 180-slY+R/2, 0x0, 0x0);*/
                lX=X;
                lY=Y;
                slX=sX;
                slY=sY;
		/*line(slX, sY+R-1, 180-sY+R/2, 0x0, white);
		line(sX+R-1, sY, 300-sX+R/2, 0x1, white);
		line(0xA, sY, sX-0x9-R, 0x1, white);
		line(sX, 0xA, sY-0x9-R, 0x0, white);*/
                square(sX-R/2-1, sY-R/2-1, R+2, R+2, warcolor);
		char nc = 0x0;
		if(fuel <= 0x6)
		{
			nc = warcolor;
		}
		else if(fuel <= 0xC)
		{
			nc = attcolor;
		}
		else
		{
			nc = color;
		}
                circle(X, Y, R, nc);
                waitspec(0x15FFFF);
                change = 0;
        }
	//clear(0x0, 0xFFFF);
	score /= 2;
	char nfg = *arg0;

	if(score > bscore)
	{
		*IRQ = 0x4;
		*arg0 = _0;
		*arg1 = text;
		if(phantom)
		{
			*arg2 = 0x4;
		}
		else
		{
			*arg2 = 0x0;
		}
		*arg3 = score;
		OS();
		if(*arg2)
		{
			print_string(0x0, 0x0, "Can't write", warcolor, 0x0, 0x0);
		}
		print_string(28, 12, "NR", jircolor, 0x0, 0x0);
		bscore = score;
	}

	print_string(19-4, 6, "Game Over", warcolor, 0x0, 0x0);

	strprint_to_global(print_string(9, 10, "Phantom mode/", attcolor, 0x0, 0x0));
	if(phantom)
	{
		print_string(*globalx, *globaly, "On", color, 0x0, 0x0);
	}
	else
	{
		print_string(*globalx, *globaly, "Off", warcolor, 0x0, 0x0);
	}
	strprint_to_global(print_string(9, 11, "Score: ", attcolor, 0x0, 0x0));
	strprint_to_global(print_int(*globalx, *globaly, score, color, 0x0, 0x6));
	strprint_to_global(print_string(9, 12, "BestScore: ", attcolor, 0x0, 0x0));
	strprint_to_global(print_int(*globalx, *globaly, bscore, color, 0x0, 0x6));
	print_string(8, end_menu_sm, ">", attcolor, 0x0, 0x0);
	print_string(9, 13, "Retry", attcolor, 0x0, 0x0);
	print_string(9, 14, "Clear score", attcolor, 0x0, 0x0);
	print_string(9, 15, "Exit", attcolor, 0x0, 0x0);

	while(1)
	{
		if(find_buttn(0x1C) && timed+3 < *timer)
		{
			if(!end_menu_num)
			{
				break;
			}
			else if(end_menu_num == 0x1)
			{
				*IRQ = 0x4;
				*arg0 = _0;
				*arg1 = text;
				if(phantom)
				{
					*arg2 = 0x4;
				}
				else
				{
					*arg2 = 0x0;
				}
				*arg3 = 0x0;
				OS();
				if(*arg2)
				{
					fill_square(21*8, 14*8+2, 2, 2, warcolor);
				}
				fill_square(21*8, 14*8+2, 2, 2, color);
			}
			else if(end_menu_num == end_menu_org)
			{
				//brk = 0x1;
				//break;
				clear(0x0, 0xFFFF);
				exit();
			}
			timed = *timer;
		}

		if(find_buttn(0x50) && end_menu_num < end_menu_org && timed+2 < *timer)
		{
			print_string(9, end_menu_sm+end_menu_num, "\b", attcolor, 0x0, 0x0);
			end_menu_num++;
			print_string(8, end_menu_sm+end_menu_num, ">", attcolor, 0x0, 0x0);
			timed = *timer;
		}
		else if(find_buttn(0x48) && end_menu_num > 0x0 && timed+2 < *timer)
		{
			print_string(9, end_menu_sm+end_menu_num, "\b", attcolor, 0x0, 0x0);
			end_menu_num--;
			print_string(8, end_menu_sm+end_menu_num, ">", attcolor, 0x0, 0x0);
			timed = *timer;
		}
	}
	}

	//return;
}
