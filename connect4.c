#include <stdio.h>
#include <stdlib.h>


#define H 6
#define W 12



#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"


int grid[H][W] = {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
int finish = 0;
int turn = 0;
int column, row;

//------------------------------------------------------------------------------

void display() {
        printf(" 1  2  3  4  5  6  7 \n");
        for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                        if (grid[h][w] == 0) {
                                printf(BLUE "| |"RESET);
                        } else if (grid[h][w] == 1) {
                                printf(BLUE "|"RED "O"BLUE "|"RESET);
                        } else if (grid[h][w] == 2) {
                                printf(BLUE "|"YELLOW "O"BLUE "|"RESET);
                        } else {
                                printf(BLUE "|"GREEN "?"BLUE "|"RESET);
                        }
                }
                printf("\n");
        }
}

//------------------------------------------------------------------------------

void input() {

        column = -1;
        printf("Seleccione una columna: ");
        scanf("%d", &column);
        scanf("%*[^\n]");
        column--;

        while (column<0 || column>=W || grid[0][column]!=0) {
                if (grid[0][column]!=0) printf("Columna llena, seleccione una columna vacía: ");
                else                    printf("Inserte un valor válido: ");

                scanf("%d", &column);
                scanf("%*[^\n]");
                column--;
        }



}

//------------------------------------------------------------------------------

void insert() {
        int i = H-1;

        while (grid[i][column] != 0) {
                i--;
        }
        row = i;

        if (turn%2 == 0) {
                grid[i][column] = 1;
        } else {
                grid[i][column] = 2;
        }

}

//------------------------------------------------------------------------------

void draw() {
        for (int w=0; w<W; w++) {
                if (grid[0][w] == 0) {
                        return;
                }
        }
        finish = 1;
}

//------------------------------------------------------------------------------

int down() {
        int i = row+1, count=0;
        while (i<H && grid[row][column]==grid[i][column]) {
                count++;
                i++;
        }
        return count;
}

int left() {
        int j = column-1, count=0;
        while (j>=0 && grid[row][column]==grid[row][j]) {
                count++;
                j--;
        }
        return count;
}

int right() {
        int j = column+1, count=0;
        while (j<W && grid[row][column]==grid[row][j]) {
                count++;
                j++;
        }
        return count;
}

int upleft() {
        int i = row-1, j = column-1, count=0;
        while (i>=0 && j>=0 && grid[row][column]==grid[i][j]) {
                count++;
                i--;
                j--;
        }
        return count;
}

int downright() {
        int i = row+1, j = column+1, count=0;
        while (i<H && j<W && grid[row][column]==grid[i][j]) {
                count++;
                i++;
                j++;
        }
        return count;
}

int downleft() {
        int i = row+1, j = column-1, count=0;
        while (i<H && j>=0 && grid[row][column]==grid[i][j]) {
                count++;
                i++;
                j--;
        }
        return count;
}

int upright() {
        int i = row-1, j = column+1, count=0;
        while (i>=0 && j<W && grid[row][column]==grid[i][j]) {
                count++;
                i--;
                j++;
        }
        return count;
}

void check() {

        if ( ((1+down()) >= 4) || ((left()+1+right()) >= 4) || ((upleft()+1+downright()) >= 4) || ((downleft()+1+upright())>=4) ) {
                finish = 1;
                return;
        }

        draw();

}

//------------------------------------------------------------------------------

int main() {

        printf("\nSTART\n\n");

        while (finish == 0) {
                printf("\n\n");
                printf("turn: %d\n", turn);
                display();

                input();
                insert();
                check();

                turn++;
        }

        printf("\n\n");
        printf("turn: %d\n", turn);
        display();

        printf("\n\nEND\n");

        return 0;

}
