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
	system("CLS");
	cout << "    A   B   C   \n";
	for (int i = 0; i < boardSize; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j] == 'X') {
				cout << "\033[31m X \033[0m";
			}
			else if (board[i][j] == 'O') {
				cout << "\033[34m O \033[0m";
			}
			else {
				cout << " " << board[i][j] << " ";
			}
			if (j < boardSize - 1) {
				cout << "|";
			}
		}
		cout << "\n";
		if (i < boardSize - 1) {
			cout << "   ---|---|---\n";
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

void pcMove(char** board, int boardSize, int difficulty) {
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
	//The commented code below is giving errors in the main section although it works despite it
	//Ashaqidaki dovr ichi kod niyese error verir ve hemchinin dogru shekilde ishleyir
	/*for (int i = 0; i < boardSize; i++)
	{
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == ' ') {
			board[i][2] = 'O';
			return;
		}
		else if (board[i][0] == 'X' && board[i][1] == ' ' && board[i][2] == 'X') {
			board[i][1] = 'O';
			return;
		}
		else if (board[i][0] == ' ' && board[0][1] == 'X' && board[0][2] == 'X') {
			board[i][0] = 'O';
			return;
		}	// Loop through rows
	for (int i = 0; i < boardSize; i++)
	{
		if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == ' ') {
			board[2][i] = 'O';
			return;
		}
		if (board[0][i] == 'X' && board[1][i] == ' ' && board[2][i] == 'X') {
			board[1][i] = 'O';
				return;
		}
		if (board[0][i] == ' ' && board[1][i] == 'X' && board[2][i] == 'X') {
			board[0][i] = 'O';
			return;
		}
	}	// Loop through columns
	*/
	//The conditions below are written due to commented code above causing errors despite working properly
	//Ashaqidaki shertler yuxarida kommente alinmish kodun error vermesine gore yazilmishdir.
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == ' ') {
		board[0][2] = 'O';
	}
	else if (board[0][0] == 'X' && board[0][2] == 'X' && board[0][1] == ' ') {
		board[0][1] = 'O';
	}
	else if (board[0][0] == ' ' && board[0][1] == 'X' && board[0][2] == 'X') {
		board[0][0] = 'O';
	}			//1st row 
	else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == ' ') {
		board[1][2] = 'O';
	}
	else if (board[1][0] == 'X' && board[1][2] == 'X' && board[1][1] == ' ') {
		board[1][1] = 'O';
	}
	else if (board[1][0] == ' ' && board[1][1] == 'X' && board[1][2] == 'X') {
		board[1][0] = 'O';
	}			//2nd row
	else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == ' ') {
		board[2][2] = 'O';
	}
	else if (board[2][0] == 'X' && board[2][2] == 'X' && board[2][1] == ' ') {
		board[2][1] = 'O';
	}
	else if (board[2][0] == ' ' && board[2][1] == 'X' && board[2][2] == 'X') {
		board[2][0] = 'O';
	}			//3rd row
	else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == ' ') {
		board[2][0] = 'O';
	}
	else if (board[0][0] == 'X' && board[1][0] == ' ' && board[2][0] == 'X') {
		board[1][0] = 'O';
	}
	else if (board[0][0] == ' ' && board[1][0] == 'X' && board[2][0] == 'X') {
		board[0][0] = 'O';
	}			//1st column
	else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == ' ') {
		board[2][1] = 'O';
	}
	else if (board[0][1] == 'X' && board[1][1] == ' ' && board[2][1] == 'X') {
		board[1][1] = 'O';
	}
	else if (board[0][1] == ' ' && board[1][1] == 'X' && board[2][1] == 'X') {
		board[0][1] = 'O';
	}			//2nd column
	else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == ' ') {
		board[2][2] = 'O';
	}
	else if (board[0][2] == 'X' && board[1][2] == ' ' && board[2][2] == 'X') {
		board[1][2] = 'O';
	}
	else if (board[0][2] == ' ' && board[0][1] == 'X' && board[2][2] == 'X') {
		board[0][2] = 'O';
	}			//3rd column
	else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == ' ') {
		board[2][2] = 'O';
		return;
	}
	else if (board[0][0] == 'X' && board[1][1] == ' ' && board[2][2] == 'X') {
		board[1][1] = 'O';
		return;
	}
	else if (board[0][0] == ' ' && board[1][1] == 'X' && board[2][2] == 'X') {
		board[0][0] = 'O';
		return;
	}			//1st diagonal
	else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == ' ') {
		board[2][0] = 'O';
		return;
	}
	else if (board[0][2] == 'X' && board[1][1] == ' ' && board[2][0] == 'X') {
		board[1][1] = 'O';
		return;
	}
	else if (board[0][2] == ' ' && board[1][1] == 'X' && board[2][0] == 'X') {
		board[0][2] = 'O';
		return;
	}			//2nd diag
	else {
		int randomIndex = rand() % emptyCount;
		int row = emptyCells[randomIndex][0];
		int col = emptyCells[randomIndex][1];
		board[row][col] = 'O';
	}
}

void main() {
	srand(time(NULL));
	const int boardSize = 3;
	char** board = new char* [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		board[i] = new char[boardSize];
	}
	InitBoard(board, boardSize);

	char winner = ' ';
	bool humanTurn = true;

	cout << "Welcome to the Tic Tac Toe game\n\nPlease choose a difficultyy level:\n";

	while (winner == ' ') {
		PrintBoard(board, boardSize);
		if (humanTurn) {
			char move[3];
			int row;
			int col;

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
			pcMove(board, boardSize, difficulty);
			humanTurn = true;
		}
		winner = winnerCheck(board, boardSize);
	}
	PrintBoard(board, boardSize);

	if (winner == 'X') {
		cout << "\n\033[31mYou win some)\n";
	}
	else if (winner == 'O') {
		cout << "\n\033[34mYou lose some(\n";
	}
	else {
		cout << "\n\033[32mFriendship won\n";
	}

	
}