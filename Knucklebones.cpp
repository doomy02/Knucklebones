#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define CLEAR "clear"

#ifdef _WIN32
#define CLEAR "cls"
#endif

int sumOfColumn(vector<int> matrix, int col);
void printMatrix(vector<int> matrix);
int diceRoll();
int totalSum(vector<int> matrix);
void eliminate(vector<int>& player, vector<int>& computer, int index);
int countVictory(vector<int> matrix);
void printInstructions() {
	cout << "Welcome to Knucklebones!\n\nThe instructions are:\n\n"
			 << "1. You roll a dice, and it can have a value from 1 up to 6. You must place it in\n"
			 << "   one of the free spaces inside your 3x3 board (1 up to 9).\n"
			 << "2. Each die's value is multiplied by the number of dice in that column.\n"
			 << "3. When the player places a die, all dice of the same value in the corresponding\n"
			 << "   column of the opponent's board get destroyed. Use this mechanic to destroy\n"
			 << "   the opponent's high-scoring combos.\n"
			 << "4. The game ends when either of the players has completely filled their board.\n\n"
			 << "Have fun!" << endl;
}

int main() {

	while (1) {
		int countPlayer = 0, countComputer = 0;
		srand(time(NULL));
		vector<int> player(9, 0);
		vector<int> computer(9, 0);

		printInstructions();

		for (int i = 0; i < 9; i++) {
			int diceValue = diceRoll();
			cout << endl << "Player rolled " << diceValue << endl;

			int input;
			cout << "Place " << diceValue << " at: ";
			cin >> input;
			cout << endl;

			if (input >= 1 && input <= player.size() && player[input - 1] == 0) {
				player[input - 1] = diceValue;
				eliminate(player, computer, input);
			}

			cout << "Player's table: " << endl;
			printMatrix(player);

			cout << endl << "Computer's table: " << endl;
			int computerDice = diceRoll();
			for (int i = 0; i < 9; i++) {
				if (computer[i] == 0) {
					computer[i] = computerDice;
					eliminate(computer, player, i);
					break;
				}
			}

			printMatrix(computer);
		}

		countPlayer = countVictory(player);
		countComputer = countVictory(computer);

		if (countPlayer == 9 || countComputer == 9) {
			cout << endl << "Total Player's score: " << totalSum(player) << endl << "Total Computer's score: " << totalSum(computer);
			if (totalSum(player) > totalSum(computer)) {
				cout << endl << "Player WON!" << endl;
			}
			else if (totalSum(player) < totalSum(computer)) {
				cout << endl << "Computer WON!" << endl;
			}
			else {
				cout << endl << "DRAW!" << endl;
			}
		}

		cout << endl << "Press y to restart, press anything else to close: ";
		char decision;
		cin >> decision;
		if (decision == 'y') {
			system(CLEAR);
			main();
		}
		else {
			exit(1);
		}
	}

	return 0;
}

int sumOfColumn(vector<int> matrix, int col) {
	int result = 0;
	bool foundIdentical = false;
	bool foundIdentical2 = false;
	bool foundIdentical3 = false;

	// find identities
	if (matrix.at(col - 1) == matrix.at(col + 2)) {
		foundIdentical = true;
	}
	if (matrix.at(col - 1) == matrix.at(col + 5)) {
		foundIdentical2 = true;
	}
	if (matrix.at(col + 2) == matrix.at(col + 5)) {
		foundIdentical3 = true;
	}

	if (foundIdentical && foundIdentical2 && foundIdentical3) {
		result = matrix.at(col - 1) * 9;
	}
	else if (foundIdentical && !foundIdentical2 && !foundIdentical3) {
		result = matrix.at(col - 1) * 4 + matrix.at(col + 5);
	}
	else if (!foundIdentical && foundIdentical2 && !foundIdentical3) {
		result = matrix.at(col - 1) * 4 + matrix.at(col + 2);
	}
	else if (!foundIdentical && !foundIdentical2 && foundIdentical3) {
		result = matrix.at(col + 2) * 4 + matrix.at(col - 1);
	}
	else {
		result = matrix.at(col - 1) + matrix.at(col + 2) + matrix.at(col + 5);
	}

	return result;
}

void printMatrix(vector<int> matrix) {
	int count = 0;

	for (int x : matrix) {
		cout << " | " << x;
		count++;

		if (count % 3 == 0)
			cout << " | " << endl;
	}

	int col1 = sumOfColumn(matrix, 1);
	int col2 = sumOfColumn(matrix, 2);
	int col3 = sumOfColumn(matrix, 3);

	cout << "   " << col1 << "   " << col2 << "  " << col3 << endl;
}

int diceRoll() {
	return rand() % 6 + 1;
}

int totalSum(vector<int> matrix) {
	int col1 = sumOfColumn(matrix, 1);
	int col2 = sumOfColumn(matrix, 2);
	int col3 = sumOfColumn(matrix, 3);

	return col1 + col2 + col3;
}

void eliminate(vector<int>& player, vector<int>& computer, int index) {
	if (index >= 1 && index <= 3) {
		if (player[index - 1] == computer[index - 1]) {
			computer[index - 1] = 0;
		}

		if (player[index - 1] == computer[index + 2]) {
			computer[index + 2] = 0;
		}

		if (player[index - 1] == computer[index + 5]) {
			computer[index + 5] = 0;
		}
	}
	else if (index >= 4 && index <= 6) {
		if (player[index - 1] == computer[index - 4]) {
			computer[index - 4] = 0;
		}

		if (player[index - 1] == computer[index - 1]) {
			computer[index - 1] = 0;
		}

		if (player[index - 1] == computer[index + 2]) {
			computer[index + 2] = 0;
		}
	}
	else if (index >= 7 && index <= 9) {
		if (player[index - 1] == computer[index - 7]) {
			computer[index - 7] = 0;
		}

		if (player[index - 1] == computer[index - 4]) {
			computer[index - 4] = 0;
		}

		if (player[index - 1] == computer[index - 1]) {
			computer[index - 1] = 0;
		}
	}
}

int countVictory(vector<int> matrix) {
	int count = 0;

	for (int x : matrix) {
		if (x != 0) {
			count++;
		}
	}

	return count;
}
