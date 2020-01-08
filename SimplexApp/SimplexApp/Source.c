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
	Input(); //値の代入(課題の要素)
	Step1(); //ピボット算出 -> ガウスの消去法
	Step2(); //最大化への代入
	return 0;
}

void Step1() { 
	//x2同士の比較
	int i, j;
	int pivot_row, pivot_col;
	//各行の大きさを計算
	double row1val = SimplexTable[1][4] / SimplexTable[1][1]; //1行目の重み
	double row2val = SimplexTable[2][4] / SimplexTable[2][1]; //2行目の重み
	// 1行目のほうが小さい場合
	if (row1val < row2val) {
		i = 1; //1行目でピボットをつくる
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
		i = 2; //2行目でピボットをつくる
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
	//1行目がピボットならば2行目が計算対象
	if (pivot_row == 1) {
		i = 2;
		double tmp = SimplexTable[i][pivot_col] / SimplexTable[pivot_row][pivot_col];//何倍する必要があるか
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
	ShowTable(0); //計算ステップ0
}
