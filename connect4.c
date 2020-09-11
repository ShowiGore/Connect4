#include <stdio.h>
#include <stdlib.h>


#define H 6
#define W 7



#define RESET   "\x1b[0;0m"
#define BLACK   "\x1b[0;30m"
#define RED     "\x1b[0;31m"
#define GREEN   "\x1b[0;32m"
#define YELLOW  "\x1b[0;33m"
#define BLUE    "\x1b[0;34m"
#define MAGENTA "\x1b[0;35m"
#define CYAN    "\x1b[0;36m"
#define WHITE   "\x1b[0;37m"
#define REDCYAN         "\x1b[1;31;46m"
#define YELLOWCYAN       "\x1b[1;33;46m"


int grid[H][W] = {{}};
int finish = 0;
int turn = 0;
int column, row;

////////////////////////////////////////////////////////////////////////////////

void display() {

        for (int w=1; w<=W; w++) {
                printf(" %d ", w);
        }

        printf("\n");

        for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                        if (grid[h][w] == 0) {
                                printf(BLUE "| |"RESET);
                        } else if (grid[h][w] == 1) {
                                printf(BLUE "|"RED"O"BLUE "|"RESET);
                        } else if (grid[h][w] == 2) {
                                printf(BLUE "|"YELLOW"O"BLUE "|"RESET);
                        } else if (grid[h][w] == 3) {
                                printf(BLUE "|"REDCYAN"O"BLUE "|"RESET);
                        } else if (grid[h][w] == 4) {
                                printf(BLUE "|"YELLOWCYAN"O"BLUE "|"RESET);
                        } else {
                                printf(BLUE "|"GREEN "?"BLUE "|"RESET);
                        }
                }
                printf("\n");
        }
}

////////////////////////////////////////////////////////////////////////////////

void input() {

        column = -1;
        printf("Seleccione una columna: ");
        scanf("%d", &column);
        scanf("%*[^\n]");
        column--;

        while (column<0 || column>=W || grid[0][column]!=0) {
                printf("\033[1A\033[K");
                if (grid[0][column]!=0) printf("Columna llena, seleccione una columna vacía: ");
                else                    printf("Inserte un valor válido: ");

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

        if ((1+down()) >= 4) {
                markdown();
                finish = 1;

        }

        if ((left()+1+right()) >= 4) {
                markleft();
                markright();
                finish = 1;
        }

        if ((upleft()+1+downright()) >= 4) {
                markupleft();
                markdownright();
                finish = 1;
        }

        if ((downleft()+1+upright())>=4) {
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
        printf("turn: %d\n", turn);
        display();

        if (finish == 1) {
                printf("\n\nGana: ");
                if (turn%2 == 0) {
                        printf(YELLOW"O"RESET"\n");
                } else {
                        printf(RED"O"RESET"\n");
                }
        } else if (finish == 2) {
                printf("\n\nEmpate\n");
        }
        printf("\a");//beep

}

////////////////////////////////////////////////////////////////////////////////

int main() {
        printf("\033[2J");//clear

        while (finish == 0) {
                printf("turn: %d\n", turn);
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
