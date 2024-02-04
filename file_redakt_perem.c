char animationspeed = 0x1;
int* globalx = (int*)0xE00;
int* globaly = (int*)0xE04;
char* buttonread = (char*)0xFEB;
int* timer = (int*)0xFE7;
char* alfabet = (char*)0x30000;
char* videostrt = (char*)0xA0000;
char* videofin = (char*)0xA0000+0xFFFF;
char jircolor = 0x1;
char color = 0x2;
char warcolor = 0x4;
char attcolor = 0x6;
char clear_on_off = 0x1;
char* IRQ = (char*)0xFE6;
int* arg0 = (int*)0xFE1;
int* arg1 = (int*)0xFDD;
int* arg2 = (int*)0xFD9;
int* arg3 = (int*)0xFD5;
int* arg4 = (int*)0xFD1;
int* arg5 = (int*)0xFCD;
char text[] = "TEXT";
char cute[] = "CUTE";
char tmp[] = "TMP";
typedef void (*fs)(void);
fs OS = (fs) 0x10000;

struct tstring
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

struct sho_err
{
        short int sho;
        char err;
};

struct chr_err
{
        char chr;
        char err;
};
