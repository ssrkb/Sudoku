
#include<stdio.h>
#include<time.h>

int nullcell(int grid[9][9],int *row,int *col){
    for (*row = 0; *row < 9; *row +=1){
        for (*col = 0; *col < 9; *col  +=1){
            //  printf(" %d %d\n",*row,*col);
            if (grid[*row][*col] == 0)
            return 1;

        }
    }
    return 0;
}

int checkrow(int grid[9][9],int row,int num){
    for (int col = 0; col < 9; col++){
        if (grid[row][col] == num)
            return 1;
    }
    return 0;
}

int checkcol(int grid[9][9],int col,int num){
    for (int row = 0; row < 9; row++){
        if (grid[row][col] == num){
            return 1;
            }
    }
    return 0;
}


int checkbox(int grid[9][9], int row,int col,int num){
    row-=row%3;
    col-=col%3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + row][col + j] == num)
                return 1;
    return 0;
}


int is_safe(int grid[9][9], int row,int col, int num){
    return (!checkrow(grid, row, num) && !checkcol(grid, col, num) && !checkbox(grid, row,col, num)&& grid[row][col] == 0);
}


int solve(int grid[9][9]){
    int row,col;

    if(!nullcell(grid,&row,&col))
        return 1;

        //printf("%d",row);
    for (int num = 1; num <= 9; num++) {
        if (is_safe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid))
                return 1;
            //printf("hi");
            grid[row][col] = 0;
        }
    }

    return 0;
}

//sudoku generator


void generate(){
    int arr[9][9]={0};

    srand(time(0));
    //(rand() % (upper - lower + 1)) + lower;
    int i,j,num,row,col;
    int r=30 ;//= ((rand() % 31) + 30);

    for(i=0; i<r; i++){
        row = (rand() % 9);
        col = (rand() % 9);
        num = (rand() % 10);
        if(arr[row][col]==0 && is_safe(arr,row,col,num)){
           arr[row][col] = num;
        }
        else
            continue;
    }
    FILE *f=NULL;
    f=fopen("a.txt","w+");

    if(f==NULL){
        printf("could not open this file\n");
        return;
    }

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            fprintf(f,"%d ",arr[i][j]);
        }
        fprintf(f,"\n",NULL);
    }

    fclose(f);

}
