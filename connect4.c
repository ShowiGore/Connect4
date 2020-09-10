#include <stdio.h>
#include <stdlib.h>


#define H 6
#define W 7


int grid[H][W] = {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
int finish = 0;
int turn = 0;
int column = 0;

//------------------------------------------------------------------------------

void display() {
  printf(" 1  2  3  4  5  6  7 \n");
  for (int h=0; h<H; h++) {
    for (int w=0; w<W; w++) {
      if (grid[h][w] == 0) {
        printf("| |");
      } else if (grid[h][w] == 1) {
        printf("|X|");
      } else if (grid[h][w] == 2) {
        printf("|O|");
      } else {
        printf("|?|");
      }
    }
    printf("\n");
  }
}

//------------------------------------------------------------------------------

void input() {

  printf("Seleccione una columna:");
  fflush(stdin);
  scanf("%d", &column);

  while (column<1 || column>7 || grid[0][column-1]!=0) {
    printf("Inserte un valor válido:");
    fflush(stdin);
    scanf("%d", &column);
  }

}

//------------------------------------------------------------------------------

void insert() {
  int i = H-1;

  while (grid[i][column-1] != 0) {
    i--;
  }

  if (turn%2 == 0) {
    grid[i][column-1] = 1;
  } else {
    grid[i][column-1] = 2;
  }

}

//------------------------------------------------------------------------------

int draw() {
  for (int w=0; w<W; w++) {
    if (grid[0][w] == 0) {
        return 0;
    }
  }
  return 1;
}

//------------------------------------------------------------------------------

int main() {

  printf("\nSTART\n\n");

  while (finish == 0) {
    printf("\n\n");
    printf("Turn: %d\n", turn);
    display();

    input();
    insert();

    finish = draw();
    turn++;
  }

  printf("\n\n");
  printf("Turn: %d\n", turn);
  display();

  printf("\n\nEND\n");

  return 0;

}
