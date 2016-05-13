#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "display.h"
#include "piece.h"

#define BOARD_LENGTH 8
#define BOARD_WIDTH 8
#define DISPLAY_X 10
#define DISPLAY_Y 35

#define BOARD_HOR '_'
#define BOARD_VERT '|'
#define BOARD_CORN '+'



int simCheck(struct board * b, struct piece * p,struct pos * move, struct piece * k);

int drawBoard(struct board *);
int initBoard(struct board *);
int occupied(struct board *, int, int);

int main(int argc, char * argv[])
{
	clear();
	struct board *boardy =  malloc(sizeof(struct board));
	initBoard(boardy);
//	initBoard(board
	//printf("%d\n", boardy->s_pieces);
//	addPiece(boardy,KING,1,1,0);
//	addPiece(boardy,ROOK,1,2,0);

//	addPiece(boardy,ROOK,1,5,1);
//	addPiece(boardy,KING,1,3,1);
//	addPiece(boardy,ROOK,4,2,1);
//	addPiece(boardy,KING,5,2,1);

	updateAllMoves(boardy);

//	tryMove(boardy,4,2,3,2);
//	tryMove(boardy,3,2,3,4);
//	struct board * b = copyBoard(boardy);
//	deleteBoard(b);

//	addPiece(boardy,BISHOP,1,0,1);
//	addPiece(PAWN,3,1,0,boardy);
//	addPiece(PAWN,4,1,0,boardy);
//	addPiece(PAWN,2,0,1,boardy);

//	removePiece(boardy->pieces[1], boardy);
//	removePiece(boardy->pieces[1], boardy);

//	updateMoves(boardy->pieces[0],boardy);

//	removeMove(boardy->pieces[0],0);

//	updateAllMoves(boardy);
//	updateAllMoves(b);


//	printMoves(b->pieces[1]);
	while(1)
	{
		int quit = 0;
		drawBoard(boardy);
		set_cur_pos(55,0);
		char * input;
		char *end;
		while(1)
		{
			gets(input);
			printf("%s\n",input );
			if(strcmp(input,&"quit")==0)
			{
				quit = 1;
				break;
			}
			int x1 = strtol(input ,&end,10);
			int y1 = strtol(end ,&end,10);
			int x2 = strtol(end ,&end,10);
			int y2 = strtol(end ,&end,10);
			int t = tryMove (boardy,x1,y1,x2,y2);
			printf("%d %d %d %d %d\n", x1,y1,x2,y2,t);
			if(t == 1)
			{
				printf("sucess\n");
				break;
			}
		}
		if (quit)
		{
			break;
		}
	}
	deleteBoard(boardy);
}

int printAllMoves(struct board * b)
{
	set_cur_pos(0,0);
	printf("player : %d" ,b->currentPlayer);
	for (int a = 0 ; a< b->s_pieces;a++)
	{
		printMoves(b->pieces[a]);
	}
}

/* returns 1 if valid
 * returns -1 if invalid m1
 * returns -2 if invalid m2
 */

int tryMove(struct board* b,int x1,int y1,int x2,int y2)
{
	struct pos * m1 = makeLoc(x1,y1);
	struct pos * m2 = makeLoc(x2,y2);

	struct piece * mover = getSpace(b,x1,y1);
	if(mover == NULL)
	{
				return -1;
	}
	if(mover->player != b->currentPlayer)
		return -1;

	struct pos * m3 = validMoveForPiece(mover,m2);

	if(m3 != NULL)
	{
		movePiece(b, mover, m3);
		updateAllMoves(b);
		return 1;
	}
	else
	{
		return -2;
	}


}


//
int drawBoard(struct board *b)
{
	clear();
	set_cur_pos(0,0);
	printAllMoves(b);

	for (int x = 0 ; x < BOARD_WIDTH; x++)
	{
		for(int y = 0 ; y < BOARD_LENGTH;y++)
		{

			set_cur_pos(y*2+DISPLAY_Y+2, 4*x+DISPLAY_X);
			put(BOARD_VERT);
			set_cur_pos(y*2+DISPLAY_Y+1, 4*x+DISPLAY_X);
			put(BOARD_VERT);
			set_cur_pos(y*2+DISPLAY_Y, 4*x+DISPLAY_X);
			put(BOARD_VERT);
			set_cur_pos(y*2+DISPLAY_Y, 4*x+DISPLAY_X+1);
			put(BOARD_HOR);
			set_cur_pos(y*2+DISPLAY_Y, 4*x+DISPLAY_X+2);
			put(BOARD_HOR);
			set_cur_pos(y*2+DISPLAY_Y, 4*x+DISPLAY_X+3);
			put(BOARD_HOR);

		}
		set_cur_pos(BOARD_LENGTH*2+DISPLAY_Y,4*x+DISPLAY_X);
		put(BOARD_HOR);
		set_cur_pos(BOARD_LENGTH*2+DISPLAY_Y,4*x+DISPLAY_X+1);
		put(BOARD_HOR);
		set_cur_pos(BOARD_LENGTH*2+DISPLAY_Y,4*x+DISPLAY_X+2);
		put(BOARD_HOR);
		set_cur_pos(BOARD_LENGTH*2+DISPLAY_Y,4*x+DISPLAY_X+3);
		put(BOARD_HOR);
		set_cur_pos(DISPLAY_Y,4*x+DISPLAY_X);
		put(BOARD_HOR);

		set_cur_pos(x*2+DISPLAY_Y,BOARD_WIDTH*4+DISPLAY_X);
		put(BOARD_VERT);
		set_cur_pos(x*2+1+DISPLAY_Y,BOARD_WIDTH*4+DISPLAY_X);
		put(BOARD_VERT);

		set_cur_pos(DISPLAY_Y-1,4*x+DISPLAY_X+2);
		put(x+'0');
		set_cur_pos(x*2+1+DISPLAY_Y,DISPLAY_X+1+BOARD_WIDTH*4);
		put(x+'0');


		set_cur_pos(DISPLAY_Y,DISPLAY_X);
		put(BOARD_CORN);
		set_cur_pos(DISPLAY_Y+BOARD_LENGTH*2,DISPLAY_X);
		put(BOARD_CORN);
		set_cur_pos(DISPLAY_Y,DISPLAY_X+BOARD_WIDTH*4);
		put(BOARD_CORN);
		set_cur_pos(DISPLAY_Y+BOARD_LENGTH*2,DISPLAY_X+BOARD_WIDTH*4);
		put(BOARD_CORN);
	}
	for(int a = 0; a < b->s_pieces;a++)
	{
		set_cur_pos(b->pieces[a]->loc->y*2+DISPLAY_Y+1,
			b->pieces[a]->loc->x*4 +DISPLAY_X+1);
		if(b->pieces[a]->player == 0)
			printf(BLUE);
		else
			printf(RED);
		put(b->pieces[a]->p);
		printf(RESET);
	}

}

struct board * copyBoard(struct board * b)
{
	struct board * nBoard = malloc(sizeof(struct board));
	nBoard->s_pieces = 0;

	for(int a = 0; a < b->s_pieces;a++)
	{
		int x = b->pieces[a]->loc->x;
		int y = b->pieces[a]->loc->y;

		addPiece(nBoard,b->pieces[a]->p,x,
			y,b->pieces[a]->player);

		int notM = b->pieces[a]->notMoved;

		nBoard->pieces[a]->notMoved = notM;
	}
	return nBoard;
}

int deleteBoard(struct board * b)
{
	while(b->s_pieces != 0)
		removePiece(b,b->pieces[0]);
	free(b);
	return 0;
}

int initBoard(struct board *b)
{
	b->s_pieces = 0;
	b->currentPlayer = 0;
	for(int a = 0; a < BOARD_WIDTH;a++)
	{
		printf("%d\n",a);
		addPiece(b,PAWN,a,6,0);
		addPiece(b,PAWN,a,1,1);
	}
	addPiece(b,ROOK,0,0,1);
	addPiece(b,ROOK,7,0,1);
	addPiece(b,ROOK,7,7,0);
	addPiece(b,ROOK,0,7,0);

/*
	addPiece(b,KNIGHT,1,0,1);
	addPiece(b,KNIGHT,6,0,1);
	addPiece(b,KNIGHT,1,7,0);
	addPiece(b,KNIGHT,6,7,0);

	addPiece(b,BISHOP,2,0,1);
	addPiece(b,BISHOP,5,0,1);
	addPiece(b,BISHOP,2,7,0);
	addPiece(b,BISHOP,5,7,0);

	addPiece(b,QUEEN,4,7,0);
	addPiece(b,QUEEN,4,0,1);
*/

	addPiece(b,KING,3,7,0);
	addPiece(b,KING,3,0,1);
	return 0;
}


/* returns number of player of the piece at the position x,y
 * returns -1 if no piece is at the position
 * returns -2 if coordinate is not on the board
 * return 2 if valid enzzZ
 */
int checkSpace(struct board * b, int x , int y, int g, int player)
{
	if(x < 0 || x >= BOARD_WIDTH)
		return -2;
	if(y < 0 || y >= BOARD_LENGTH)
		return -2;

	for(int a = 0; a < b->s_pieces;a++)
	{
		if(b->pieces[a]->loc->x == x && b->pieces[a]->loc->y ==y)
			return b->pieces[a]->player;
		if(g && b->pieces[a]->ghostLoc != NULL && b->pieces[a]->ghostLoc->x == x
			 && b->pieces[a]->ghostLoc->y ==y && b->pieces[a]->player != player)
			 return 2;
	}
	return -1;
}

struct piece * getSpace(struct board * b, int x , int y)
{
	for(int a = 0; a < b->s_pieces;a++)
	{
		if(b->pieces[a]->loc->x == x && b->pieces[a]->loc->y == y)
		{
			return b->pieces[a];
		}

	}
	return NULL;
}

int getOrder(struct board * b, struct piece * p)
{
	for(int a = 0; a < b->s_pieces;a++)
	{
		if(b->pieces[a] == p)
		{
			return a;
		}

	}
	return 0;
}


int updateAllMovesSim(struct board * b)
{
	struct piece * k1 = NULL;
	struct piece * k2 = NULL;
	for(int a = 0 ; a< b->s_pieces; a++)
	{
		// saves kings for later, all other pieces must
		// be updated BEFORE the king
		if(b->pieces[a]->p == KING)
		{
			continue;
		}
		updateMoves(b,b->pieces[a]);
	}
}

int updateAllMoves(struct board * b)
{
	struct piece * k0 = NULL;
	struct piece * k1 = NULL;
	for(int a = 0 ; a< b->s_pieces; a++)
	{
		// saves kings for later, all other pieces must
		// be updated BEFORE the king
		if(b->pieces[a]->p == KING)
		{
			if(b->pieces[a]->player == 0)
				k0 = b->pieces[a];
			else
				k1 = b->pieces[a];
			continue;
		}
		updateMoves(b,b->pieces[a]);
	}

	for(int a = 0 ; a< b->s_pieces; a++)
	{
		if(b->pieces[a]->p == ROOK)
		{
			addCastleing(b,b->pieces[a]);
		}
	}

	if(k0 != NULL)
	{
		for(int a = 0 ; a< b->s_pieces; a++)
		{
			if(b->pieces[a]->player == 1)
				continue;
			for(int c = 0 ; c < b->pieces[a]->s_moves;c++)
			{
				if(b->pieces[a]->moves[c]-> type == 2)
				{
					continue;
				}
				if(simCheck(b,b->pieces[a],b->pieces[a]->moves[c],k0) == 1)
				{
					removeMove(b->pieces[a],c);
				}
			}
		}
	}

	if(k1 != NULL)
	{
		for(int a = 0 ; a< b->s_pieces; a++)
		{
			if(b->pieces[a]->player == 0)
				continue;
			for(int c = 0 ; c < b->pieces[a]->s_moves;c++)
			{
				if(simCheck(b,b->pieces[a],b->pieces[a]->moves[c],k1) == 1)
				{
					removeMove(b->pieces[a],c);
				}
			}
		}
	}

	if(k0 != NULL)
	{
		updateMoves(b,k0);
	}
	if(k1 != NULL)
	{
		updateMoves(b,k1);
	}
	//specialKingMoveCheck(b,k1,k2);

}

int movePiece(struct board * b, struct piece * p, struct pos* move)
{
	//if(move->type == 2 || move->type == 3)
		//return 0;


	for(int a = 0 ; a < b->s_pieces; a++)
	{
		clearGhost(b->pieces[a]);
	}

	if(move->taken != NULL)
	{
		removePiece(b,move->taken);
	}
	p->notMoved = 0;

	free(p->loc);
	p->loc = makeLoc(move->x,move->y);
	if(move->type == 6)
	{
		if(p->player ==0)
		{
			p->ghostLoc= makeLoc(move->x, move->y +1);
			printf("made ghosty at %d,%d ",move->x, move->y +1);
		}
		else
		{
			p->ghostLoc= makeLoc(move->x, move->y -1);
			printf("made ghosty at %d,%d ",move->x, move->y +1);
		}
	}
	else
	{
		p->ghostLoc = NULL;
	}
	if(b->currentPlayer == 0)
	{
		b->currentPlayer = 1;
	}
	else
		b->currentPlayer = 0;
}

// returns 0 if NOT in check after the move
// return 1 if in check after the move
int simCheck(struct board * b, struct piece * p, struct pos * move, struct piece * k )
{
	struct piece * inactivePiece = NULL;
	struct pos * tempLoc;
	struct board * nBoard = copyBoard(b);

 	int temp = getOrder(b, p);

	movePiece(nBoard,nBoard->pieces[temp],move);
	updateAllMovesSim(nBoard);
	if(incheckCheck(nBoard,k,k->loc) == 1)
	{
		deleteBoard(nBoard);
		return 1;
	}
	deleteBoard(nBoard);
	return 0;
}
