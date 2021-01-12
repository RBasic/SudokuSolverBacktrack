#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

void formatContent(string filename) {
	fstream file;
	file.open(filename);
	string str;
	int i = 0, j = 0;
	vector<string> content;
	while (getline(file, str)) {
		string temp = "";
		for (int i = 0; i < str.size(); i++) {
			if (isdigit(str[i])) {
				temp += str[i];
			}
			else if (str[i] == '.') {
				temp += '0';
			}
		}
		content.push_back(temp);
	}
	file.close();
	file.open(filename, ios::out|ios::trunc);
	for (int i = 0; i < content.size(); i++) {
		if (i == content.size() - 1) {
			file << content[i];
		}
		else {
			file << content[i] << endl;
		}
	}
	file.close();
}

void InitGrid(int tab[9][9],bool lock[9][9],string filename) {
	fstream file;
	file.open(filename);
	string str;
	int i = 0, j = 0;
	while (getline(file, str)) {
		for (char c : str) {
			tab[i][j] = c - '0';
			j++;
		}
		i++;
		j = 0;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			lock[i][j] = (tab[i][j] != 0);
		}
	}
}


int main() {
	int grid[9][9];
	bool lock[9][9] = { 0 };
	string filename = "Sudoku5.txt";
	formatContent(filename);
	InitGrid(grid,lock,filename);
	cout << "GRILLE ENTREE" << endl;
	showGrid(grid);
	cout << "GRILLE SORTIE" << endl;
	if (solver(grid,lock)) {
		showGrid(grid);
	}
	else {
		cout << "marche pas";
	}
	return 0;
}