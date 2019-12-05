#include<stdio.h>

#define ROW 3
#define COL 5

int Input(void);
int Calc(void);

double SimplexTable[ROW][COL] = {{}};

int main(void){
    Input();
    Calc();
}

int Input(void){ //係数入力
    double Input_F[2] = {};
    double Input_A[3] = {};
    double Input_B[3] = {};
/*
    printf("Equation Maximize:\nx1 = "); //最大化の方程式入力
    scanf("%lf", &Input_F[0]);
    printf("x2 = ");
    scanf("%lf", &Input_F[1]); 
    printf("Equation A:\nx1 = "); //方程式Aの入力
    scanf("%lf", &Input_A[0]);
    printf("x2 = ");
    scanf("%lf", &Input_A[1]);
    printf("Equation B:\nx1 = "); //方程式Bの入力
    scanf("%lf", &Input_B[0]);
    printf("x2 = ");
    scanf("%lf", &Input_B[1]);
    printf("EquationA Value = ");
    scanf("%lf", &Input_A[2]);
    printf("EquationB Value = ");
    scanf("%lf", &Input_B[2]);
*/
//デバッグ用
    Input_F[0] = 29;
    Input_F[1] = 45;
    Input_A[0] = 2;
    Input_A[1] = 8;
    Input_B[0] = 4;
    Input_B[1] = 4;
    Input_A[2] = 60;
    Input_B[2] = 60;

    printf("\nEquation M: f = %lf x1 + %lf x2\n", Input_F[0], Input_F[1]);
    printf("Equation A: %lf x1 + %lf x2 <= %lf\n", Input_A[0], Input_A[1], Input_A[2]);
    printf("Equation B: %lf x1 + %lf x2 <= %lf\n", Input_B[0], Input_B[1], Input_B[2]);
    /*
    * 配列の決め事 SimplexTable[i][j]
    * ------------ i -------------
    * [0] 最大化の式
    * [1] 条件式A
    * [2] 条件式B
    * ------------ j -------------
    * [0] = x1の係数
    * [1] = x2の係数
    * [2] = スラック変数 x3 の係数
    * [3] = スラック変数 x4 の係数
    * [4] = 方程式の値(右辺)
    */

    /*
    * 配列の決め事 Input[i]
    * [0] x1の係数
    * [1] x2の係数
    * [2] 右辺の値
    */

    SimplexTable[1][2] = 1; //スラックス変数 x3
    SimplexTable[2][3] = 1; //スラックス変数 x4
    SimplexTable[1][4] = Input_A[2]; //方程式Aの値
    SimplexTable[2][4] = Input_B[2]; //方程式Bの値

    int i;
    for(i = 0; i < 2; i++){
        SimplexTable[0][i] = Input_F[i];
    }
    int j;
    for(i = 1; i < 3; i++){
        for(j = 0; j < 2; j++){
            if (i == 1) { SimplexTable[i][j] = Input_A[j]; }
            else if (i == 2) { SimplexTable[i][j] = Input_B[j]; } 
        }
    }
}

int ShowSimplexTable(void){ //計算過程を見るための表示用関数
    int i, j;
    printf("\n---------------------Simplex Table------------------------\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 5; j++)
        {
             printf("%10lf ", SimplexTable[i][j]);
        }
        printf("\n");
    }
}

int Calc(void){
    int CalcFlag = 0;
    while(1){
        //１行目のx1, x2の係数が0 かつ 2行目のx2の係数が1 かつ 3行目のx1の係数が1 ならば終了
        if((SimplexTable[0][0] == 0) && (SimplexTable[0][1] == 0)){
            if((SimplexTable[1][0] == 0) && (SimplexTable[1][1] == 1)){
                if((SimplexTable[2][0] == 1) && (SimplexTable[2][1] == 0)){ break; }
            }
        }
        
        if(CalcFlag == 0){ //最初の計算のとき
            int i, j;
            //まずはx2同士を比較
            double compA = SimplexTable[1][4] / SimplexTable[1][1];
            double compB = SimplexTable[2][4] / SimplexTable[2][1];
            //条件式Aのほうが小さかったらこちらを採用
            if(compA < compB) {
                double tmp = SimplexTable[1][1];
                //compAで1行目全体を割る
                i = 1;
                for(j = 0; j < COL; j++){
                    SimplexTable[i][j] = SimplexTable[i][j] / tmp;
                }
            }
            //条件式Bのほうが大きい、または同等の場合はこちらを採用
            else {
                double tmp = SimplexTable[2][1];
                //compBで2行目全体を割る
                i = 2;
                for(j = 0; j < COL; j++){
                    SimplexTable[i][j] = SimplexTable[i][j] / tmp;
                }
            }
            CalcFlag++; //最初の計算が終了したフラグ
            ShowSimplexTable();
        }
        //2回目以降の計算
        else if(CalcFlag == 1){
            int i, j;
            int PivotX = 0, PivotY = 0;
            //ピボットを探す
            for(i = 1; i < 3; i++){
                for(j = 0; j < 2; j++){
                    if(SimplexTable[i][j] == 1){
                        PivotX = i;
                        PivotY = j;
                    }
                }   
            }
            //次の行と比較
            double tmp = 0;
            if(PivotX == 1){
                //１行目にピボットがあるとき次の行はピボットの何倍かを計算  
                tmp = SimplexTable[PivotX + 1][PivotY] / SimplexTable[PivotX][PivotY];
                i = 2;
            }
            else if(PivotX == 2){
                // 2行目にピボットがあるとき前の行はピボットの何倍かを計算
                tmp = SimplexTable[PivotX - 1][PivotY] / SimplexTable[PivotX][PivotY];
                i = 1;
            }
            //もう一方のx2の係数を0にする
            for(j = 0; j < COL; j++){
                SimplexTable[i][j] = SimplexTable[i][j] - (SimplexTable[PivotX][j] * tmp);
            }
            //ピボットを使った計算が終わったのでフラグ加算
            CalcFlag++;
            ShowSimplexTable();
        }
        else if(CalcFlag == 2){
            if((SimplexTable[1][1] == 1) && (SimplexTable[2][1] == 0)){
                
            }
            break;
        }
    }
    ShowSimplexTable();
    printf("flag = %d\n", CalcFlag);
}