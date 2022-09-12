#include <iostream>
#include <vector>
using namespace std;


void printSudoku9x9(int arr[9][9]) {
	cout << "-------------------------" << endl;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++)
			cout << arr[y][x] << " ";
		cout << endl;
	}
	cout << "-------------------------" << endl;

}

bool canPlace9x9(int arr[9][9], int row, int col, int n)
{
	if (arr[row][col] != 0) return false;
	bool status = true;
	int gridx = (col / 3) * 3;
	int gridy = (row / 3) * 3;
	for (int i = 0; i < 9; i++) {
		if (arr[row][i] == n) { status = false; break; }
		if (arr[i][col] == n) { status = false; break; }
		if (arr[gridy + i / 3][gridx + i % 3] == n) { status = false; break; }
	}
	return status;
}

void nextEmpty(int arr[9][9], int row, int col, int& rowNext, int& colNext)
{

	int indexNext = 9 * 9 + 1;
	for (int i = row * 9 + col + 1; i < 9 * 9; i++) {
		if (arr[i / 9][i % 9] == 0) {

			indexNext = i;
			break;
		}
	}
	rowNext = indexNext / 9;
	colNext = indexNext % 9;
	//cout << row << "," << col << "|" << rowNext << "," << colNext << endl;
}

void copyArray(int arr[9][9], int arrCpy[9][9]) {
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arrCpy[y][x] = arr[y][x];
}
std::vector<int> findPlaceables(int arr[9][9], int row, int col) {
	vector<int> placebles = {};
	for (int n = 1; n <= 9; n++)
		if (canPlace9x9(arr, row, col, n)) placebles.push_back(n);
	return placebles;
}


bool solveSudoku9x9(int arr[9][9], int row, int col)
{
	//system("cls");
	//printSudoku9x9(arr);

	if (row > 8) return true;
	if (arr[row][col] != 0) {
		int rowNext, colNext;
		nextEmpty(arr, row, col, rowNext, colNext);
		return solveSudoku9x9(arr, rowNext, colNext);
	}

	std::vector<int> placebles = findPlaceables(arr, row, col);

	if (placebles.size() == 0) {
		
		return false; 
	
	};

	bool status = false;
	for (int i = 0; i < placebles.size(); i++) {
		int n = placebles[i];
		int arrCpy[9][9];
		copyArray(arr, arrCpy);
		//cout << "(" << row << "," << col << ") =>" << n << endl;
		arrCpy[row][col] = n;
		int rowNext = row;
		int colNext = col;
		nextEmpty(arrCpy, row, col, rowNext, colNext);
		if (solveSudoku9x9(arrCpy, rowNext, colNext)) {
			copyArray(arrCpy, arr);
			status = true;
			break;
		}
	}
	return status;
}


int main(int argc, char** argv)
{
	int board[9][9] = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
	};
	int board2[9][9] = {
		{8,0,0,0,0,0,0,0,0},
		{0,0,3,6,0,0,0,0,0},
		{0,7,0,0,9,0,2,0,0},
		{0,5,0,0,0,7,0,0,0},
		{0,0,0,0,4,5,7,0,0},
		{0,0,0,1,0,0,0,3,0},
		{0,0,1,0,0,0,0,6,8},
		{0,0,8,5,0,0,0,1,0},
		{0,9,0,0,0,0,4,0,0}
	};
	
	if (solveSudoku9x9(board, 0, 0)) cout << "successfully solved board!" << std::endl;
	printSudoku9x9(board);
	if (solveSudoku9x9(board2, 0, 0)) cout << "successfully solved board 2!" << std::endl;
	printSudoku9x9(board2);

	return 0;
}