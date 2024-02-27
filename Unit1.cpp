//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <StdCtrls.hpp >
#include <Controls.hpp >
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TButton *botones[9];
Player *current_player;
Player *PLAYER1;
Player *PLAYER2 ;
int WINNER_MOVES[8][3][2] ={
	{{0,0},{0,1},{0,2}},
	{{1,0},{1,1},{1,2}},
	{{2,0},{2,1},{2,2}},

	{{0,0},{1,0},{2,0}},
	{{0,1},{1,1},{2,1}},
	{{0,2},{1,2},{2,2}},

	{{0,0},{1,1},{2,2}},
	{{0,2},{1,1},{2,0}}
};

int TABLE[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0},
} ;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	PLAYER1 = new Player(1, "Mike", "X");
	PLAYER2 = new Player(2, "Gema", "O");

	current_player= PLAYER1;
	botones[0]  =Form1->Button1;
	botones[1]  =Form1->Button2;
	botones[2]  =Form1->Button3;
	botones[3]  =Form1->Button4;
	botones[4]  =Form1->Button5;
	botones[5]  =Form1->Button6;
	botones[6]  =Form1->Button7;
	botones[7]  =Form1->Button8;
	botones[8]  =Form1->Button9;

	for(int i=0; i< 9; i++){
		TButton *boton = botones[i];
		boton->Tag = i;
		boton->OnClick = BtnClick;
	}
}

void __fastcall TForm1::BtnClick(TObject *Sender){
		TButton *boton = dynamic_cast<TButton *>(Sender);
		if(boton){
			  if(boton->Caption	==""){
				int row = boton->Tag/3;
				int col = boton->Tag%3;
				boton->Caption = current_player->player_shape;
				SetTable(row, col);
				CheckWinner();
				current_player = current_player->player_id == 1?  PLAYER2 : PLAYER1;
			  }
			  
		}
}

void __fastcall TForm1::SetTable(int row, int col){
	TABLE[row][col] = current_player->player_id;
}

void __fastcall TForm1::CheckWinner(){
	for(int i=0; i <8 ; i++){
		bool isWinner =true;

		for(int j=0; j <3 ; j++){
			  int row =  WINNER_MOVES[i][j][0];
			  int col =  WINNER_MOVES[i][j][1];
			  if(TABLE[row][col] != current_player->player_id){
				isWinner=false;
				  break;
			  }
		}
		if(isWinner){
			ShowMessage(AnsiString(current_player->player_name) + " has WON!!");
			ResetTable();
			break;
		}
	}
}
void __fastcall TForm1::ResetTable(){
	for(int i=0; i <3 ; i++){
		for(int j=0; j <3 ; j++){
			TABLE[i][j] = 0;
		}
	}

    for(int i=0; i< 9; i++){
		botones[i]->Caption = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
       ResetTable();
}
//---------------------------------------------------------------------------
