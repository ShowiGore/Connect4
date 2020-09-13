#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define C 4
#define H 6
#define W 7



#define RESET   "\e[0m"
#define BLACK   "\e[0;30m"
#define RED     "\e[0;31m"
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define BLUE    "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN    "\e[0;36m"
#define WHITE   "\e[0;37m"
#define RED_M     "\e[0;31;7;5m"
#define YELLOW_M  "\e[0;33;7;5m"


int grid[H][W] = {{}};
int finish = 0;
int turn = 0;
int column, row;

////////////////////////////////////////////////////////////////////////////////

int digits(int number) {
        return (number==0) ? 1 : ((int) log10((double) number)+1);
}

int digit(int number, int digit) {
        return (number / (int) pow(10, (double) (digit-1)) ) % 10;
}

////////////////////////////////////////////////////////////////////////////////

void display() {

        for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                        if (grid[h][w] == 0) {
                                printf(BLUE"| |"RESET);
                        } else if (grid[h][w] == 1) {
                                printf(BLUE"|"RED"O"BLUE"|"RESET);
                        } else if (grid[h][w] == 2) {
                                printf(BLUE"|"YELLOW"O"BLUE"|"RESET);
                        } else if (grid[h][w] == 3) {
                                printf(BLUE"|"RED_M"O"BLUE"|"RESET);
                        } else if (grid[h][w] == 4) {
                                printf(BLUE"|"YELLOW_M"O"BLUE"|"RESET);
                        } else {
                                printf(BLUE"|"GREEN"?"BLUE"|"RESET);
                        }
                }
                printf("\n");
        }

        //enumeration string should be constructed only once
        for (int d=0; d<digits(W); d++) {
                for (int w=1; w<=W; w++) {
                        if (digits(w)>=d+1) {
                                printf(" %d ", digit(w,digits(w)-d));
                        } else {
                                printf("   ");
                        }

                }
                printf("\n");
        }
}

////////////////////////////////////////////////////////////////////////////////

void input() {

        column = -1;
        printf("Select a column: ");
        scanf("%d", &column);
        scanf("%*[^\n]");
        column--;

        while (column<0 || column>=W || grid[0][column]!=0) {
                printf("\033[1A\033[K");
                if (grid[0][column]!=0) printf("Full column, select an empry tile: ");
                else                    printf("Insert a valid value: ");

                scanf("%d", &column);
                scanf("%*[^\n]");
                column--;
        }

}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void draw() {
        for (int w=0; w<W; w++) {
                if (grid[0][w] == 0) {
                        return;
                }
        }
        finish = 2;
}

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

void markdown() {
        int i = row+1;
        while (i<H && grid[row][column]==grid[i][column]) {
                grid[i][column] = grid[i][column]+2;
                i++;
        }
}

void markleft() {
        int j = column-1;
        while (j>=0 && grid[row][column]==grid[row][j]) {
                grid[row][j] = grid[row][j]+2;
                j--;
        }
}

void markright() {
        int j = column+1;
        while (j<W && grid[row][column]==grid[row][j]) {
                grid[row][j] = grid[row][j]+2;
                j++;
        }
}

void markupleft() {
        int i = row-1, j = column-1;
        while (i>=0 && j>=0 && grid[row][column]==grid[i][j]) {
                grid[i][j] = grid[i][j]+2;
                i--;
                j--;
        }
}

void markdownright() {
        int i = row+1, j = column+1;
        while (i<H && j<W && grid[row][column]==grid[i][j]) {
                grid[i][j] = grid[i][j]+2;
                i++;
                j++;
        }
}

void markdownleft() {
        int i = row+1, j = column-1;
        while (i<H && j>=0 && grid[row][column]==grid[i][j]) {
                grid[i][j] = grid[i][j]+2;
                i++;
                j--;
        }
}

void markupright() {
        int i = row-1, j = column+1;
        while (i>=0 && j<W && grid[row][column]==grid[i][j]) {
                grid[i][j] = grid[i][j]+2;
                i--;
                j++;
        }
}

////////////////////////////////////////////////////////////////////////////////

void check() {

        if ((1+down()) >= C) {
                markdown();
                finish = 1;

        }

        if ((left()+1+right()) >= C) {
                markleft();
                markright();
                finish = 1;
        }

        if ((upleft()+1+downright()) >= C) {
                markupleft();
                markdownright();
                finish = 1;
        }

        if ((downleft()+1+upright()) >= C) {
                markdownleft();
                markupright();
                finish = 1;
        }

        if (finish == 1) {
                grid[row][column] = grid[row][column]+2;
                return;
        } else {
                draw();
        }

}

////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////

void end() {
        printf("Round: %d\n", turn);
        display();
        printf("\n\n");
        if (finish == 1) {
                if (turn%2 == 0) {
                        printf(YELLOW"O"RESET);
                } else {
                        printf(RED"O"RESET);
                }
                printf(" WINS\n");
        } else if (finish == 2) {
                printf("DRAW\n");
        }
        printf("\a");//beep

}

////////////////////////////////////////////////////////////////////////////////

int main() {
        printf("\033[2J");//clear

        while (finish == 0) {
                printf("Round: %d\n", turn);
                display();

                input();
                insert();
                check();

                printf("\033[2J");//clear

                turn++;
        }

        end();

        return 0;

}

//gcc connect4.c -o connect4; ./connect4
//gcc connect4.c -o connect4; .\connect4.exe
