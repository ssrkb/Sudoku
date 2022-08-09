#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include"sudoku.c"

int grid[9][9];

int main(){

    int gm, gd=DETECT;
    initgraph(&gd,&gm,"");
    closegraph();

    system("COLOR 0B");
    //making sudoku board
    initwindow(1400,700,"Sudoku",100,10);
    setbkcolor(2);
    setcolor(9);

    int j=0;
    //generating sudoku
    generate();

    //textwidth("100");
    settextstyle(10,0,5);
    outtextxy(50,50,"enter SOLUTION:");

    j=0;

    for(int i=100; i<500; i+=50){
        line(50,i+50,500,i+50);
        if(i%3==2)  {
            i+=2;
            line(50,i+50,500,i+50);
            i--;
            line(50,i+50,500,i+50);
            i--;
        }
        j++;
    }
    j=0;

    for(int i=50; i<450; i+=50){
        line(50+i,100,50+i,550);
        if(i%3==0)  {
            i+=2;
            line(50+i,100,50+i,550);
            i--;
            line(50+i,100,50+i,550);
            i--;
        }
        j++;
    }
    rectangle(50,100,500,550);
    rectangle(51,101,501,551);
    rectangle(52,102,502,552);
    setbkcolor(16);

    //instructions
    settextstyle(10,0,5);
    setcolor(YELLOW);
    rectangle(595,165,1350,300);
    outtextxy(600,170,"INSTRUCTIONS : ");
    outtextxy(600,420,"RULE : ");

    setcolor(WHITE);
    settextstyle(10,0,4);
    outtextxy(600,220,"ENTER");
    outtextxy(600,260,"1-9 : numbers in sudoku");
    //outtextxy(600,300,"100 : if you done with solving sudoku");
    //outtextxy(600,340,"10  : one cell back");


    setcolor(15);
    settextstyle(10,0,5);


    //setcolor(YELLOW);
    //outtextxy(600,30,"time remaining:");

    //RULE
    settextstyle(10,0,4);
    setcolor(WHITE);
    outtextxy(600,460,"no similar number in same row,column");
    outtextxy(600,500,"and in 3*3 cells");


    //displaying sudoku on screen
    settextstyle(10,0,5);
    int i=0,key;
    char str[3];

    //displaying sudoku on screen

    int p,q,valid=0;
    int user[9][9];

    FILE *f=fopen("a.txt","r");

    if(f==NULL){
        printf("could not open this file\n");
        return 0;
    }

    for(q=0,i=0; i<9; i++,q+=50){
        for(p=0,j=0; j<9; j++,p+=50){
            fscanf(f,"%d",&key);
            user[i][j] = grid[i][j] = key;
            if(grid[i][j]==0)
                continue;
            sprintf(str,"%d",grid[i][j]);
            outtextxy(55+p,105+q,str);
        }
    }

    fclose(f);

    //user solver the sudoku now
    valid=solve(grid);
    if(valid == 0) {
        readimagefile("oop.jpg",50,50,550,550);
        getch();
        closegraph();
        return 0;
    }
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ",grid[i][j]);
        }
        printf("\n");
    }

    for(i=0,q=0; i<9; i++,q+=50){
        for(j=0,p=0; j<9; j++,p+=50){
            if(user[i][j]==0){
                scanf("%d",&key);
            }
            else
                continue;
            if(key<1 || key>9){
                cleardevice();
                readimagefile("oops.jpg",50,50,550,550);
                outtextxy(100,600,"NOT AN VALID INPUT");
                getch();
                return 0;
            }
            user[i][j] = key;
            sprintf(str,"%d",key);
            outtextxy(55+p,105+q,str);
            if(key != grid[i][j]){
                valid = 0;
                cleardevice();

                //image
                readimagefile("wrong.jpg",550,100,1050,600);

                int j=0;
                outtextxy(50,50,"--RIGHT-SOLUTION-- ");
                rectangle(50,100,500,550);
                rectangle(51,101,501,551);
                rectangle(52,102,502,552);
                for(int i=100; i<500; i+=50){
                    line(50,i+50,500,i+50);
                    if(i%3==2){
                        i+=2;
                        line(50,i+50,500,i+50);
                        i--;
                        line(50,i+50,500,i+50);
                        i--;
                    }
                    j++;
                }
                j=0;

                for(int i=50; i<450; i+=50){
                    line(50+i,100,50+i,550);
                    if(i%3==0){
                        i+=2;
                        line(50+i,100,50+i,550);
                        i--;
                        line(50+i,100,50+i,550);
                        i--;
                    }
                    j++;
                }
                setcolor(WHITE);
                for(i=0,q=0; i<9; i++,q+=50){
                    p=0;
                    for(j=0; j<9; j++,p+=50){
                        sprintf(str,"%d",grid[i][j]);
                        outtextxy(55+p,105+q,str);
                    }
                }

            }
        }
    }

    if(valid == 1){
        readimagefile("right.jpg",50,50,550,550);
    }
    //image of congratulations

    getch();
    closegraph();
	return 0;

}
