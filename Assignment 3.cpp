#include<vector>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<iostream>

using namespace std;


int p=0;
vector <int> bullx,bully;

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

void erase_ship(int x,int y)
{
    COORD c={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    cout << "          ";
    setcursor(0);
}


int main()
{
    char ch='.';
    int x=38,y=20;
    int i,sx,sy;
    int bullet = 0;
    int dir=0;
    int c=-1; // count bullets
    int ca=1,cd=1; // direction status

    setcursor(0);
    draw_ship(x,y);
    srand(time(NULL));

    //window  w : 70

    for (i=0;i<20;i++)
    {
        sx=abs(rand())%71;
        sy=abs(rand())%6;
        if(sy<2) sy+=2;
        if(sx<10) sx+=10;
        draw_star(sx,sy);
    }

    showscore();

    do
    {
        if (_kbhit()) // direction
        {
            ch=_getch();
            if(ch=='a') { dir=-1; cd=1; }
            else if(ch=='d') { dir=1; ca=1; }
            else if(ch=='s') { dir=0; }
            else if(ch==' ')
            {
                if(c<4)
                {
                    bullx.push_back(x+3);
                    bully.push_back(y-1);
                    draw_bullet(bullx[i],bully[i]);
                    c++;
                }
            }
            fflush(stdin);
        }
        else
        {
            while(!_kbhit()||!(x>=0&&x<=76)) // move
            {
                if(ch!='s') erase_ship(x,y);
                if(x>=0&&x<=76)
                {
                    if(cd==0||ca==0) dir=0;
                    x+=dir;
                    draw_ship(x,y);
                    Sleep(100);

                    for(i=0;i<=c;i++)
                    {
                        clear_bullet(bullx[i],bully[i]);
                        bully[i]--;
                        if(bully[i]<2)
                        {
                            clear_bullet(bullx[i],bully[i]);
                            bullx.erase(bullx.begin()+i);
                            bully.erase(bully.begin()+i);
                            c--;
                        }
                        else
                        {
                            if(cursor(bullx[i],bully[i]-1)=='*')
                            {
                                Beep(1000,100);
                                p++;
                                showscore();

                                sx=abs(rand())%71;
                                sy=abs(rand())%6;
                                if(sy<2) sy+=2;
                                if(sx<10) sx+=10;
                                draw_star(sx,sy);
                            }
                            else  draw_bullet(bullx[i],bully[i]);
                        }
                    }
                }

                    if(x==5) { ca=0; break; }
                    else if(x==67) { cd=0; break; }
                }
            }
    } while (ch!='x');
    return 0;
}
