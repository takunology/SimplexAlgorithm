#include<stdio.h>

#define ROW 3
#define COL 5

double SimplexTable[ROW][COL];

void Step1();
void Step2();
void GaussCalc(int pivot_row, int pivot_col);
void Input();
void ShowTable(short step);

int main() {
	Input(); //�l�̑��(�ۑ�̗v�f)
	Step1(); //�s�{�b�g�Z�o -> �K�E�X�̏����@
	Step2(); //�ő剻�ւ̑��
	return 0;
}

void Step1() { 
	//x2���m�̔�r
	int i, j;
	int pivot_row, pivot_col;
	//�e�s�̑傫�����v�Z
	double row1val = SimplexTable[1][4] / SimplexTable[1][1]; //1�s�ڂ̏d��
	double row2val = SimplexTable[2][4] / SimplexTable[2][1]; //2�s�ڂ̏d��
	// 1�s�ڂ̂ق����������ꍇ
	if (row1val < row2val) {
		i = 1; //1�s�ڂŃs�{�b�g������
		double tmp = SimplexTable[1][1];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = SimplexTable[i][j] / tmp;
		}
		ShowTable(1);
		pivot_row = 1;
		pivot_col = 1;
		GaussCalc(pivot_row, pivot_col);
	}
	else {
		i = 2; //2�s�ڂŃs�{�b�g������
		double tmp = SimplexTable[2][1];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = SimplexTable[i][j] / tmp;
		}
		ShowTable(1);
		pivot_row = 2;
		pivot_col = 1;
		GaussCalc(pivot_row, pivot_col);
	}
	ShowTable(2);
}

void Step2() {
	
}

void GaussCalc(int pivot_row, int pivot_col) {
	int i, j;
	//1�s�ڂ��s�{�b�g�Ȃ��2�s�ڂ��v�Z�Ώ�
	if (pivot_row == 1) {
		i = 2;
		double tmp = SimplexTable[i][pivot_col] / SimplexTable[pivot_row][pivot_col];//���{����K�v�����邩
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] -= (SimplexTable[pivot_row][j] * tmp);
		}
	}
	else {
		i = 1;
		double tmp = SimplexTable[i][pivot_col] / SimplexTable[pivot_row][pivot_col];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] -= (SimplexTable[pivot_row][j] * tmp);
		}
	}
}

void Exchange() {

}

void ShowTable(short step) {
	int i, j;
	printf("\n------------------Simplex Table Step = %d-----------------\n", step);
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf("%10lf ", SimplexTable[i][j]);
		}
		printf("\n");
	}
}

void Input() {
	double sampledata[ROW][COL] = { {29, 45, 0, 0, 0},
								{2, 8, 1, 0, 60},
								{4, 4, 0, 1, 60} };
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = sampledata[i][j];
		}
	}
	ShowTable(0); //�v�Z�X�e�b�v0
}
