#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iostream>

using namespace std;


int p=0;

void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console,&lpCursor);
}
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
void draw_ship(int x,int y)
{
    gotoxy(x,y);
    cout << " <-0-> ";
    setcursor(0);
}
void draw_bullet(int x,int y)
{
    gotoxy(x,y);
    cout << "^";
    setcursor(0);
}
void clear_bullet(int x,int y)
{
    gotoxy(x,y);
    cout << " ";
    setcursor(0);
}
void showscore()
{
    int n=0;
    if(n>9) n=1;
    else if(n>99) n=2;
    gotoxy(65-n,0);
    cout << "pt : " << p;
    setcursor(0);
}

void draw_star(int x,int y)
{
    gotoxy(x,y);
    cout << "*";
    setcursor(0);
}

char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2];
    COORD c = {x,y};
    DWORD num_read;

    if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )   return '\0';
    else return buf[0];

}

int main()
{
    char ch='.';
    int x=38,y=20;
    int bx,by,i,sx,sy;
    int bullet = 0;
    setcursor(0);
    draw_ship(x,y);

    //window  w : 70

    for (i=0;i<20;i++)
    {
        sx=abs(rand())%71;
        sy=abs(rand())%6;
        if(sy<2) sy+=2;
        if(sx<10) sx+=10;
        draw_star(sx,sy);
    }

    do
    {
        showscore();

        if (_kbhit())
        {
            ch=_getch();
            if(ch=='a') { draw_ship(--x,y); }
            if(ch=='s') { draw_ship(++x,y); }
            if(bullet!=1 && ch==' ') { bullet=1; bx=x+3; by=y-1; }
            fflush(stdin);
            }

            if (bullet==1)
            {
                clear_bullet(bx,by);
                if (by==2) { bullet=0;}
                else
                {
                    if(cursor(bx,by-1)=='*')
                    {
                        Beep(700,250);
                        p++;
                        sx=abs(rand())%71;
                        sy=abs(rand())%6;
                        if(sy<2) sy+=2;
                        if(sx<10) sx+=10;
                        draw_star(sx,sy);
                    }
                    draw_bullet(bx,--by);
                }
            }
            Sleep(100);
    } while (ch!='x');
    return 0;
}
