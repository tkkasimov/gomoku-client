class Board
{
private:
	static const int FIELD_SIZE=11;
	int BoardData[FIELD_SIZE][FIELD_SIZE];
public:
	enum  Sign{X,O,NUL};
	enum Winner{first,second,nikto};
	bool MakeMove(const int x,const int y,const Sign sign);
	int getSize();
	Winner isWin();
	int getCell(const int x,const int y);
};

