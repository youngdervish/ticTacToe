#include <iostream>
using namespace std;

void inputUpperCase(char& ch) {
	if (ch >= 'a' && ch <= 'z') {
		ch = ch - ('a' - 'A');
	}
}

void InitBoard(char** board, int boardSize) {
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void PrintBoard(char** board, int boardSize) {
	cout << "   A   B   C   \n";
	for (int i = 0; i < boardSize; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < boardSize; j++)
		{
			cout << board[i][j];
			if (j < boardSize - 1) {
				cout << " | ";
			}
		}
		cout << "\n";
		if (i < boardSize - 1) {
			cout << "  ---|---|---\n";
		}
	}
	cout << "\n";
}

char winnerCheck(char** board, int boardSize) {
	for (int i = 0; i < boardSize; i++)
	{
		bool rowWin = true;
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] != board[i][0] || board[i][0] == ' ') {
				rowWin = false;
				break;
			}
		}
		if (rowWin) {
			return board[i][0];
		}

		bool colWin = true;
		for (int j = 0; j < boardSize; j++)
		{
			if (board[j][i] != board[0][i] || board[0][i] == ' ') {
				colWin = false;
				break;
			}
		}
		if (colWin) {
			return board[0][i];
		}
	}

	bool diag1Win = true, diag2Win = true;
	for (int i = 1; i < boardSize; i++)
	{
		if (board[i][i] != board[0][0] || board[0][0] == ' ') {
			diag1Win = false;
		}
		if (board[i][boardSize - i - 1] != board[0][boardSize - 1] || board[0][boardSize - 1] == ' ') {
			diag2Win = false;
		}
	}

	if (diag1Win) {
		return board[0][0];
	}
	if (diag2Win) {
		return board[0][boardSize - 1];
	}

	bool draw = true;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] == ' ') {
				draw = false;
				return ' ';
			}
		}
	}

	if (draw) { return 'D'; }
}

bool checkInput(char* input, int& row, int& col, int boardSize) {
	if (input[0] == '\0' || input[1] == '\0' || input[2] != '\0') {
		return false;
	}

	inputUpperCase(input[1]);

	row = input[0] - '1';
	col = input[1] - 'A';

	if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
		return false;
	}
	return true;
}

void pcMove(char** board, int boardSize) {
	int emptyCells[9][2];							//Storage for empty cells
	int emptyCount = 0;

	for (int i = 0; i < boardSize; i++)				// Loop for finding empty cells
	{
		for (int j = 0; j < boardSize; j++)			// Another loop for finding empty cells since it's a 2d array
		{
			if (board[i][j] == ' ') {
				emptyCells[emptyCount][0] = i;		//store row if empty
				emptyCells[emptyCount][1] = j;		//store column if empty
				emptyCount++;						//iterating through the storage
			}
		}
	}												//This keeps updating after every turn
	
	if (emptyCount == 0) return;

	int randomIndex = rand() % emptyCount;
	int row = emptyCells[randomIndex][0];
	int col = emptyCells[randomIndex][1];
	board[row][col] = 'O';
}


void main() {
	srand(time(NULL));
	const int boardSize = 3;
	char** board = new char*[boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		board[i] = new char[boardSize];
	}

	InitBoard(board, boardSize);
	char winner = ' ';
	bool humanTurn = true;

	while (winner == ' ') {
		PrintBoard(board, boardSize);
		if (humanTurn) {
			char move[3];
			int row, col;

			cout << "Enter your move (i.e. 1A, 1B or 3C): \n";
			cin >> move;

			if (checkInput(move, row, col, boardSize) && board[row][col] == ' ') {
				board[row][col] = 'X';
				humanTurn = false;
			}
			else {
				cout << "Incorrect move. Try again\n";
			}
		}
		else {
			cout << "The PC is making its move. Please wait a moment:\n";
			pcMove(board, boardSize);
			humanTurn = true;
		}
		winner = winnerCheck(board, boardSize);
	}
	PrintBoard(board, boardSize);

	if (winner == 'X') {
		cout << "\nYou win some)\n";
	}
	else if (winner == 'O') {
		cout << "\nYou lose some(\n";
	}
	else {
		cout << "\nFriendship won\n";
	}
}