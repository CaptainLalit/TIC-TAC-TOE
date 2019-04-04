#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#include<stdio.h>
#include<time.h>
using namespace std;
int check(int,int,int);
void gotoxy(int,int);
int possibility(int);
int moves(int,int,int);
void AI(int);
void display(void);
int a[3][3]={0};
int air,aic,steps;
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void delay(unsigned int msec)
{
    clock_t goal=msec+clock();
    while(goal>clock());
}

int possibility(int kount)
{
    int n,maxmarks=-1000,minmarks=1000,score,i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++){
            if(a[i][j]==0)
            {
                //steps++;
                n=kount%2+1;
                score=moves(i,j,n);
                    if(score==100||score==-100||score==0){
                        a[i][j]=0;
                        return score;
                    }
                if(score==5)
                    score=possibility(n);
                if(n==2){
                    if(maxmarks<=score)
                        maxmarks=score;
                    if(maxmarks==100){
                        a[i][j]=0;
                        goto hell;
                    }
                }
                else if(minmarks>=score){
                    minmarks=score;
                    if(minmarks==-100){
                        a[i][j]=0;
                        goto hell;
                    }
                }
                a[i][j]=0;
            }
        }

    hell :
    if(n==2)
        return (maxmarks);
    else if(n==1)
        return (minmarks);

}

int moves(int r,int c,int player)
{
    a[r][c]=player;
    return (check(r,c,player));
}

void AI(int player)
{
    int i,j,maxscore=-1000,score;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            if(a[i][j]==0)
            {
                //steps++;
                a[i][j]=player;
                score=check(i,j,2);
                if(score==100||score==0)
                {
                    air=i;
                    aic=j;
                    a[i][j]=0;
                    goto hell;
                }
                score=possibility(player);
                a[i][j]=0;
                if(maxscore<=score){
                    maxscore=score;
                    air=i;
                    aic=j;
                }
            }
        }
    hell : cout<<"";
}


int check(int r,int c,int player)
{
     int i,j,kount=0,kount1=0;
     int check=a[r][c];
     for(i=0;i<3;i++)
         if(a[r][i]==player)
             kount++;
     if(kount!=3){
         kount=0;
         for(i=0;i<3;i++)
             if(a[i][c]==player)
                 kount++;
     }
     if(kount!=3)
     {
         kount=0;
         if((r==0&&c==0)||(r==2&&c==2)||(r==1&&c==1)||(r==2&&c==0)||(r==0&&c==2))
         {
              j=i=0;
              while(i!=3)
              {
                  if(a[i][j]==player)
                    kount++;
                  i++;
                  j++;
              }
              if(kount!=3){
                  kount=0;
                  i=0;
                  j=2;
                  while(i!=3)
                  {
                      if(a[i][j]==player)
                        kount++;
                      i++;
                      j--;
                  }
              }
         }

     }
     if(kount==3&&player==1)
        return -100;
     else if(kount==3&&player==2)
        return 100;
     else if(kount!=3){
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                if(a[i][j]!=0)
                 kount1++;
        if(kount1==9)
            return 0;
        else
            return 5;
     }
}


void display(void)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        gotoxy(46,2*i);
        for(j=0;j<3;j++)
            if(a[i][j]==0)
                cout<<"-"<<"   ";
            else if(a[i][j]==1)
                cout<<"X"<<"   ";
            else
                cout<<"O"<<"   ";
            cout<<"\n\n\n";
    }
}


int main(void)
{

    int i,j;
    int position,c,r,kount=0,result=1,choice1,play;
    system("color 20");
    gotoxy(44,14);
    cout<<"WELCOME TO TIC TAC TOE";
    delay(1500);
    system("cls");
    start :
    cout<<"1. 1 Player\n2. 2 Players\n3. Exit\n\nNOTE : If you press other key then you play with computer\n\nEnter your choice : ";
    cin>>choice1;
    PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
    if(choice1==3)
        exit(0);
    system("cls");
    if(choice1==2)
    {
        cout<<"NOTE : FIRST PLAYER IS PLAYING WITH 'X'\n       SECOND PLAYER IS PLAYING WITH 'O'.\n\nPRESS ANY KEY TO CONTINUE : ";
        getch();
        PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
    }
    else
    {
        cout<<"NOTE : YOU ARE PLAYING WITH 'X'.\n\nAt which position do you want to play\n'1' or '2' : ";
        cin>>play;
        PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
        system("cls");
        for(i=0;i<3;i++){
            gotoxy(46,2*i);
            for(j=0;j<3;j++)
                cout<<"-"<<"   ";
                cout<<"\n\n\n";
        }
        if(play==1)
            goto start1;
        else
            goto start2;
    }
    system("cls");
    for(i=0;i<3;i++){
            gotoxy(46,2*i);
            for(j=0;j<3;j++)
                cout<<"-"<<"   ";
                cout<<"\n\n\n";
        }
    while(kount!=9)
    {
        start1 :
        system("cls");
        display();
        cout<<"Player 1\nEnter position :";
        cin>>position;
        if(position<1||position>9){
            gotoxy(44,14);
            cout<<"\aInvalid move";
            delay(1000);
            goto start1;
        }
        if(position%3!=0){
        r=position/3+1;
        c=position%3;
        }
        else
        {
            r=position/3;
            c=3;
        }
        if(a[r-1][c-1]!=0){
            gotoxy(44,14);
            cout<<"\aInvalid move";
            delay(1000);
            goto start1;
        }
        kount++;
        PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
        a[r-1][c-1]=1;
        result=check(r-1,c-1,1);
        system("cls");
        display();
        if(result==-100){
            gotoxy(44,14);
            cout<<"Player 1 wins";
            PlaySound(TEXT("2.wav"),NULL,SND_SYNC);
            break;
        }
        if(result==0)
        {
            gotoxy(44,14);
            cout<<"No player wins";
            gotoxy(44,15);
            cout<<"Game draw";
            break;
        }
        start2 :
        system("cls");
        display();
        if(choice1==2){
        cout<<"Player 2\nEnter position :";
        cin>>position;
        if(position<1||position>9){
            gotoxy(44,14);
            cout<<"\aInvalid move";
            delay(1000);
            goto start2;
        }
        if(position%3!=0){
        r=position/3+1;
        c=position%3;
        }
        else
        {
            r=position/3;
            c=3;
        }
        if(a[r-1][c-1]!=0){
            gotoxy(44,14);
            cout<<"\aInvalid move";
            delay(1000);
            goto start2;
        }
        PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
        a[r-1][c-1]=2;
        }
        else {
            start3 :
            if(kount==0)
            {
                air=rand()%3;
                aic=rand()%3;
                if(a[air][aic]!=0)
                    goto start3;
            }
            else
                AI(2);
            a[air][aic]=2;
            result=check(air,aic,2);
        }
        kount++;
        if(choice1==2)
            result=check(r-1,c-1,2);
        system("cls");
        display();
        if(result==100){
            gotoxy(44,14);
            if(choice1==1)
                cout<<"Computer wins";
            else
                cout<<"Player 2 wins";
            PlaySound(TEXT("2.wav"),NULL,SND_SYNC);
            break;
        }
        if(result==0)
        {
            gotoxy(44,14);
            cout<<"No player wins";
            gotoxy(44,15);
            cout<<"Game draw";
            break;
        }
    }
    gotoxy(44,16);
    cout<<"Press any key to continue : ";
    getch();
    PlaySound(TEXT("CLICK.wav"),NULL,SND_SYNC);
    system("cls");
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            a[i][j]=0;
    kount=0;
    result=1;
    goto start;
}
