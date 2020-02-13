/* Knight's tour 
 *
 * with Warnsdorff's heuristic rule
 */

#include <stdio.h>

#define CHESS_DIM 8
#define MAX_VARIANT 8

const unsigned char gc_chMark = CHESS_DIM * CHESS_DIM * 2;
const char g_acX[MAX_VARIANT] = { -1, +1, +2, +2, +1, -1, -2, -2 };
const char g_acY[MAX_VARIANT] = { +2, +2, +1, -1, -2, -2, -1, +1 };

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

  for (int i = 0; i < MAX_VARIANT; i ++) {

    unsigned char ucX = nPos / 10 + g_acX[i];
    unsigned char ucY = nPos % 10 + g_acY[i];
    if (ucX < CHESS_DIM && ucY < CHESS_DIM) {
      acVariant[i] = (nPos / 10 + g_acX[i]) * 10 + (nPos % 10 + g_acY[i]);
    } else {
      acVariant[i] = gc_chMark;
    }
  }
}

/* Warnsdorff's a heuristic rule */
void prioVariant(unsigned char acVariant[MAX_VARIANT], unsigned char acChess [ CHESS_DIM ] [ CHESS_DIM ]) {

  unsigned char acPrio[MAX_VARIANT] = { 0 };

  for (int i = 0; i < MAX_VARIANT; i ++) {
    unsigned char acV[MAX_VARIANT] = { 0 };
    getVariant(acVariant[i], acV);
    for (int j = 0; j < MAX_VARIANT; j ++) {
      if ( ! isMarked(acV[j], acChess) ) acPrio[i] ++;
    }
  }

  unsigned char ucMin = MAX_VARIANT;
  for (int i = 0; i < MAX_VARIANT; i ++) {
    if (acPrio[i] > 0 && acPrio[i] < ucMin) ucMin = acPrio[i];
  }

  unsigned char ucPos = 0;
  for (int i = 0; i < MAX_VARIANT; i ++) {
    if (acPrio[i] == ucMin) {
      if (i != ucPos) {
        unsigned char ucTmp = acVariant[i];
        acVariant[i] = acVariant[ucPos];
        acVariant[ucPos] = ucTmp;
        ucPos ++;
      }
    }
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
  prioVariant(acVar, acChess);
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
