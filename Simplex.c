/*
 * 必要なもの
 * fを最大化として表示するための配列
 * 連立方程式を決めるための数式(今回は2元2連立)
 * 表示するのに必要なのはシンプレックス表の3行分
 * 表は上から順に最大化、方程式1、方程式2
 * 
 * 入力
 * 最大化を決めるための係数変数2つ
 * 条件式1つあたり入力係数2つ、2連立分なので4つ
 * 条件式の最大値各1つ、2連立分で2つ
 * 合計8入力
 * 
 * 出力
 * シンプレックス表5行5列
 * x1, x2の解とその時の最大値f
 * 
 * アルゴリズム
 * 最大化と条件式が入力される
 * スラック変数を各式の後ろに代入
 * それぞれを配列に格納する(最大化 = [0][N], 条件式1 = [1][N], 条件式2 = [2][N])
 * x2方向を求めるために、配列の最後をx2で割り、条件式の最大値より小さければ式全体をその数で割る
 * ガウスの消去法を実行
 * x1 = x2 = 1 && x3 = x4 = 0 になったら終了
 * そのときの各配列の最後の値が解となる。
 */

#include<stdio.h>

#define ROW 3 //行
#define COL 5 //列

int Input(void);
int FirstCalc(void);
int ShowSimplexTable(void);

double SimplexMatrix[ROW][COL]={{}};

int main(void){
    Input(); //入力用関数
    ShowSimplexTable(); //初期設定表示
    FirstCalc(); //ピポッド決めるまでの初期計算
}

int Input(void){ //係数入力
    double Input_F[2] = {};
    double Input_A[3] = {};
    double Input_B[3] = {};

    printf("Equation Maximize:\nx1 = "); //最大化の方程式入力
    scanf("%lf", &Input_F[0]);
    printf("x2 = ");
    scanf("%lf", &Input_F[1]); 
    printf("\nEquation A:\nx1 = "); //方程式Aの入力
    scanf("%lf", &Input_A[0]);
    printf("x2 = ");
    scanf("%lf", &Input_A[1]);
    printf("\nEquation B:\nx1 = "); //方程式Bの入力
    scanf("%lf", &Input_B[0]);
    printf("x2 = ");
    scanf("%lf", &Input_B[1]);

    /*
    * 配列の決め事 SimplexMatrix[i][j]
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
    printf("\nEquationA Value = ");
    scanf("%lf", &Input_A[2]);
    printf("EquationB Value = ");
    scanf("%lf", &Input_B[2]);

    printf("\nEquation M: f = %lf x1 + %lf x2\n", Input_F[0], Input_F[1]);
    printf("Equation A: %lf x1 + %lf x2 <= %lf\n", Input_A[0], Input_A[1], Input_A[2]);
    printf("Equation B: %lf x1 + %lf x2 <= %lf\n", Input_B[0], Input_B[1], Input_B[2]);

    SimplexMatrix[1][2] = 1; //スラックス変数 x3
    SimplexMatrix[2][3] = 1; //スラックス変数 x4
    SimplexMatrix[1][4] = Input_A[2]; //方程式Aの値
    SimplexMatrix[2][4] = Input_B[2]; //方程式Bの値

    int i;
    for(i = 0; i < 2; i++){
        SimplexMatrix[0][i] = Input_F[i];
    }
    int j;
    for(i = 1; i < 3; i++){
        for(j = 0; j < 2; j++){
            if (i == 1) { SimplexMatrix[i][j] = Input_A[j]; }
            else if (i == 2) { SimplexMatrix[i][j] = Input_B[j]; } 
            else {}
        }
    }
}

int ShowSimplexTable(void){ //計算過程を見るための表示用関数
    int i, j;
    printf("\n--------------------------Simplex Table----------------------------\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 5; j++)
        {
             printf("%10lf ", SimplexMatrix[i][j]);
        }
        printf("\n");
    }
}

int FirstCalc(void){
    /*
    * 計算ロジック
    * まずx2方向に探索してより値の小さくなるほうの行を選択
    * 選択された行において、x2の係数で式全体（その行）を割って置換
    * あとはガウスの消去法をおこなう
    * 最終的にx1とx2には係数1が、x3とx4には係数0が入っていればよい
    */
   int i = 0; //行選択変数
   int j = 0; //列選択変数
   double comp1 = SimplexMatrix[1][4] / SimplexMatrix[1][1]; //1行目のx2
   double comp2 = SimplexMatrix[2][4] / SimplexMatrix[2][1]; //2行目のx2
   
   if(comp1 < comp2){ //1行目の値のほうが小さい場合は1行目から計算開始
        i = 1;
   }
   else{ //2行目の値のほうが小さい、または等しいならば2行目から計算開始
        i = 2;
   }
    double Val = SimplexMatrix[i][1]; //割る数を保持
   //SimplexMatrix[i][1] はi行のx2の係数なので、これを使って式全体を割る
   for(j; j < 5; j++){
       SimplexMatrix[i][j] = SimplexMatrix[i][j] / Val;
   }
   ShowSimplexTable(); //ちょっと確認
}