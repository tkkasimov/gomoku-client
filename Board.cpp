#include "Board.h"

int Board::getSize(){
	return FIELD_SIZE;
	}
bool Board::MakeMove(const int x,const int y,const Sign sign){
	if (((x>0)&&(x<11))&&((y>0)&&(y<11))){
		if (Board::BoardData[x][y]<0) {
		Board::BoardData[x][y]=sign;
		return true;}
		else return false;
		}
	else return false;
}
Board::Winner Board::isWin(){
	int countX,countO,i,j;
	for (i=1;i<11;i++){
		countX=0;countO=0;
		for (j=1;j<11;j++){
			if (BoardData[i][j]==1)
				countX++;else countX=0;
			if (BoardData[i][j]==0)
				countO++;else countO=0;
		if (countX>=5) return first;
		else if (countO>=5) return second;}

		for (j=1;j<11;j++){
		countX=0;countO=0;
		for (i=1;i<11;i++){
			if (BoardData[i][j]==1)
				countX++;else countX=0;
			if (BoardData[i][j]==0)
				countO++;else countO=0;
		if (countX>=5) return first;
		else if (countO>=5) return second;}

		countX=0;countO=0;
		for (i=1;i<11;i++){
		if (BoardData[i][i]==1)
			countX++;else countX=0;
		if (BoardData[i][i]==0)
			countO++;else countO=0;
		if (countX>=5) return first;
		else if (countO>=5) return second;}

	countX=0;countO=0;
	for (i=1;i<11;i++){
		if (BoardData[i][11-i]==1)
			countX++;else countX=0;
		if (BoardData[i][11-i]==0)
			countO++;else countO=0;
		if (countX>=5) return first;
		else if (countO>=5) return second;}
		return nikto;}}
}
int Board::getCell(const int x,const int y){
	return Board::BoardData[x][y];
}