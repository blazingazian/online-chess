#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include "clientview.h"
#include "display.h"
#include "instructions.h"

#define EON (char)11

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8
#define DISPLAY_X 2
#define DISPLAY_Y 2
#define SQUARESIZE 3

#define BOARD_HOR '_'
#define BOARD_VERT '|'
#define BOARD_CORN '+'

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BG_BLACK "\x1b[40m"
#define BG_WHITE "\x1b[47m"

static char lastMessage[256];

int drawBoard(char * lastmessage)
{
	clear();
	set_cur_pos(0,0);
	for (int x = 0 ; x < BOARD_WIDTH; x++)
	{
		for(int y = 0 ; y < BOARD_HEIGHT;y++)
		{
			if(y == 0)
			{
				set_cur_pos(y*2-1+DISPLAY_Y,x*SQUARESIZE+DISPLAY_X + 1);
				printf(RESET );
				put((char)('a'+x));
			}
			if(x == (BOARD_WIDTH-1) )
			{
				set_cur_pos(y*2+DISPLAY_Y+1,x*SQUARESIZE+DISPLAY_X + 4);
				printf(RESET );
				printf("%d\n",y+1 );
			}

			char* toPrint;
			if((x+y)%2 == 0)
			{
				printf(BG_BLACK);
			}
			else
			{
				printf(BG_WHITE);
			}
			set_cur_pos(y*2+DISPLAY_Y, x*SQUARESIZE+DISPLAY_X);
			put(' ');
			set_cur_pos(y*2+DISPLAY_Y+1, x*SQUARESIZE+DISPLAY_X);
			put(' ');
			set_cur_pos(y*2+DISPLAY_Y, x*SQUARESIZE+DISPLAY_X+1);
			put(' ');
			set_cur_pos(y*2+DISPLAY_Y+1, x*SQUARESIZE+DISPLAY_X+1);
			put(' ');

			set_cur_pos(y*2+DISPLAY_Y, x*SQUARESIZE+DISPLAY_X+2);
			put(' ');
			set_cur_pos(y*2+DISPLAY_Y+1, x*SQUARESIZE+DISPLAY_X+2);
			put(' ');

		}
	}

	char delims[2];
	delims[0] = EON;
	delims[1] = '\0';

	char * token;
	token = strtok(lobby,delims);
	set_cur_pos(DISPLAY_Y+2*(BOARD_HEIGHT-1)+1 , BOARD_WIDTH*SQUARESIZE+DISPLAY_X+5);
	printf(RESET);
	printf(BLUE);
	printf("%s",token);

	token = strtok(0,delims);
	set_cur_pos(DISPLAY_Y+1 , BOARD_WIDTH*SQUARESIZE+DISPLAY_X+5);
	printf(RED);
	printf("%s",token);

	board = strtok(0,delims);
	int a = 0;

	while(1)
	{
		int x = board[a*4+2] - '0';
		int y = board[a*4+3] - '0';
		int player = board[a*4+1];

		set_cur_pos(y*2+DISPLAY_Y+1,x*3 +DISPLAY_X+1);
		if(player == '0')
			printf(BLUE);
		else
			printf(RED);
		if( (y+x) % 2 == 0)
		{
			printf(BG_BLACK );

		}
		else
		{
			printf(BG_WHITE);
		}
		put(board[a*4]);
		printf(RESET);
		if(board[a*4+4]=='\0')
			break;
		a++;
	}
	printMessage(NULL);
	return 0;
}

int printMessage(char * message)
{
	if(message == NULL)
	{

		message = lastMessage;
	}
	else
	{
		strcpy(lastMessage, message);
	}
	set_cur_pos(19+DISPLAY_Y,0);
	printf(CLEARLINE);
	printf(CLEARLINE);
	set_cur_pos(19+DISPLAY_Y,0);
  printf("%s\n", message);
	return 0;
}
int clearInput()
{
	set_cur_pos(18+DISPLAY_Y,0);
	printf(CLEARLINE);
	set_cur_pos(18+DISPLAY_Y,0);
	put('~');
	return 0;
}

void printHelpMessage(int * inGame)
{
	printMessage("thing");
	if(! * inGame)
	{
		printMessage(man_lobbyHelp);
	}
	else
	{
		printMessage(man_boardHelp);
	}
}

int drawLobby()
{
	clear();
	set_cur_pos(DISPLAY_Y,DISPLAY_X);
	printf("LOBBY:\n");

	char tempS[2];
	tempS[0] = EON;
	tempS[1] = '\0';

	//char * delim = tempS;
	char * token;
	token = strtok(lobby,tempS);
	int a = 0;
	while(token)
	{
		if(token[0] == '0')
			printf(BLUE);
		else
			printf(RED);
		memmove(token, token+1, strlen(token));
		set_cur_pos(a+DISPLAY_Y+1, DISPLAY_X);
		if(strlen(token) !=0)
			printf("%s\n",token);
		token = strtok(0,tempS);
		a++;
	}
	printf(RESET);
	printMessage(NULL);
	return 0;
}

int updateLobby(char * nLobby)
{
  lobby = nLobby;
	return 0;
}
int updateBoard(char * nBoard)
{
	board = nBoard;
	return 0;
}
