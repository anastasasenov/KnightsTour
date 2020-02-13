/* Knight's tour 
 *
 * Brute-force algorithm
 */

#include <stdio.h>

#define CHESS_DIM 7 /* 8 */
#define MAX_VARIANT 8

const unsigned char gc_chMark = CHESS_DIM * CHESS_DIM * 2;
unsigned char g_ucMoveNo = 0;

void initChess(unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  for (int i = 0; i < CHESS_DIM; i ++) {
    for (int j = 0; j < CHESS_DIM; j ++) {
      acChess [ i ][ j ] = i * 10 + j;
    }
  }
}

void printChess(unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  for (int i = 0; i < CHESS_DIM; i ++) {
    printf("\n\n");
    for (int j = 0; j < CHESS_DIM; j ++) {
      printf(" %02d ", acChess [ i ][ j ] - gc_chMark);
    }
  }
  printf("\n");
}

int isMarked(unsigned char cValue, unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  unsigned char cX = cValue / 10;
  unsigned char cY = cValue % 10;
  return (cX >= CHESS_DIM || cY >= CHESS_DIM) ? !0 : (gc_chMark <= acChess [ cX ] [ cY ]);
}

int markItem(unsigned char cValue, unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  g_ucMoveNo ++;
  acChess [ cValue / 10 ] [ cValue % 10 ] = gc_chMark + g_ucMoveNo;
}

int unmarkItem(unsigned char cValue, unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  g_ucMoveNo --;
  acChess [ cValue / 10 ] [ cValue % 10 ] = cValue;
}

int isFinish(unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  for (int i = 0; i < CHESS_DIM; i ++) {
    for (int j = 0; j < CHESS_DIM; j ++) {
      if ( ! isMarked(acChess [ i ][ j ], acChess)) return 0;
    }
  }

  return !0;
}

void getVariant(unsigned char nPos, unsigned char acVariant[MAX_VARIANT]) {

  const char acX[MAX_VARIANT] = { -1, +1, +2, +2, +1, -1, -2, -2 };
  const char acY[MAX_VARIANT] = { +2, +2, +1, -1, -2, -2, -1, +1 };
  for (int i = 0; i < MAX_VARIANT; i ++) {

    acVariant[i] = (nPos / 10 + acX[i]) * 10 + (nPos % 10 + acY[i]);
  }
}

void processMove(unsigned char ucValue, unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  markItem(ucValue, acChess);
  //printf(" %c%d ", 'A' + ucValue / 10, 1 + ucValue % 10);
}

int doMove(unsigned char ucPos, unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  int nRet = 0;
  char acVar[MAX_VARIANT] = { 0 };
  getVariant(ucPos, acVar);
  processMove(ucPos, acChess);
  for (int i = 0; i < MAX_VARIANT; i ++) {

    if ( ! isMarked(acVar[i], acChess) ) {
       nRet = !nRet;
       if ( ! doMove(acVar[i], acChess) ) {
         if ( ! isFinish(acChess) ) {
           unmarkItem(acVar[i], acChess);
           nRet = !nRet;
         }
       } else if (CHESS_DIM * CHESS_DIM <= g_ucMoveNo) {
         nRet = !nRet;
       }
    }
  }

  return nRet;
}

int main() {

  unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ];

  initChess(acChess);
  printf("\nKnight's tour: ");
  doMove(0 /*A1*/, acChess);
  printChess(acChess);
  return 0;
}
