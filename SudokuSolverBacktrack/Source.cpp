#include <iostream>
#include <string>

using namespace std;


bool alreadyInRow(const int tab[9][9], const int row, const int val) {
	for (int i = 0; i < 9; i++) {
		if (tab[row][i] == val) {
			return true;
		}
	}
	return false;
}

bool alreadyInCol(const int tab[9][9], const int col, const int val) {
	for (int i = 0; i < 9; i++) {
		if (tab[i][col] == val) {
			return true;
		}
	}
	return false;
}

bool alreadyInSquare(const int tab[9][9], const int row, const int col, const int val) {
	int beginRow = row - row % 3;
	int begincol = col - col % 3;
	for (int i = beginRow; i < beginRow +3; i++) {
		for (int j = begincol; j < begincol +3; j++) {
			if (tab[i][j] == val) {
				return true;
			}
		}
	}
	return false;
}

bool emptyCase(const int tab[9][9], const int row, const int col) {
	return (tab[row][col] == 0);
}

void showGrid(const int tab[9][9]) {
	for (int i = 0; i < 9; i++) {
		cout << "|";
		for (int j = 0; j < 9; j++) {
			if (tab[i][j] == 0) cout << " |";
			else cout << tab[i][j]<<"|";
		}
		cout << endl;
	}
}

bool nextCase(int tab[9][9], int &row, int &col) {
	if (col >= 8 && row >= 8) {
		return true;
	}
	else if (col >= 8 && row < 8) {
		col = 0;
		row++;
	}
	else {
		col++;
	}
	return false;
}

bool previousCase(int tab[9][9], int &row, int &col) {
	if (col <= 0 && row <= 0) {
		return true;
	}
	else if (col <= 0 && row > 0) {
		col = 8;
		row--;
	}
	else {
		col--;
	}
}

bool solver(int tab[9][9], const bool lock[9][9]) {
	int i = 0, j = 0;
	while (i < 9) {
		while (j < 9) {
			if (!lock[i][j]) {
				int val = tab[i][j];
				val++;
				bool assigned = false;
				while (val <= 9 && !assigned) {
					//cout << "Essai : " << val << " dans la case [" << i << "][" << j << "]" << endl;
					if (!alreadyInRow(tab, i, val) && !alreadyInCol(tab, j, val) && !alreadyInSquare(tab, i, j, val)) {
						tab[i][j] = val;
						assigned = true;
					}
					val++;
				}
				if (assigned) {
					if (nextCase(tab, i, j)) {
						return true;
					}
				}
				else {
					tab[i][j] = 0;
					previousCase(tab, i, j);
					while (lock[i][j]) {
						previousCase(tab, i, j);
					}
				}
				//cout << "i = " << i << "j = " << j << "assigned = " << assigned << endl;
			}
			else {
				if (nextCase(tab, i, j)) {
					return true;
				}
			}
		}
	}

	//BACKTRACKING

	//verifie si case vide, si oui tester si on peut mettre un chiffre
	//si on peut => met le chiffre et recommencer check
	//si on peut pas => mettre 0 dedans et revenir a la case d'avant
	//si toutes les cases sont remplies => sudoku solved
}

int main() {
	int grid[9][9] = {
		{4,0,0,0,0,8,0,0,2},
		{0,0,0,7,0,0,0,0,0},
		{0,0,0,0,9,1,0,7,0},
		{0,1,0,5,0,6,0,0,0},
		{6,0,0,0,0,4,0,9,0},
		{0,5,0,0,0,0,8,0,0},
		{3,4,0,0,0,2,0,0,1},
		{8,0,0,0,3,0,0,0,6},
		{0,2,0,8,1,0,0,0,0}
	};
	int grid2[9][9] = {
		{0,7,0,1,0,0,4,0,6},
		{4,0,0,8,5,0,3,0,1},
		{3,0,1,0,0,0,0,0,0},
		{8,9,0,0,1,5,0,0,0},
		{0,0,2,9,7,4,1,0,0},
		{0,0,0,6,8,0,0,9,7},
		{0,0,0,0,0,0,8,0,3},
		{1,0,5,0,9,8,0,0,2},
		{2,0,3,0,0,1,0,6,0}
	};

	int grid3[9][9] = {
		{0,0,0,0,1,0,4,0,0},
		{0,0,0,8,0,4,0,1,0},
		{0,0,0,5,0,7,3,0,9},
		{0,6,5,2,0,0,1,3,0},
		{8,0,0,0,0,0,0,0,4},
		{0,4,1,0,0,8,6,9,0},
		{9,0,2,6,0,3,0,0,0},
		{0,5,0,4,0,1,0,0,0},
		{0,0,3,0,2,0,0,0,0}
	};
	bool lock[9][9] = { 0 };
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			lock[i][j] = (grid3[i][j] !=0);
		}
	}
	if (solver(grid3,lock)) {
		showGrid(grid3);
	}
	else {
		cout << "marche pas";
	}
	return 0;
}