#include<iostream>
#include<math.h>

int const MAX = 10;

using namespace std;

void display(float mat[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        cout << "[ \t";
        for (int j = 0; j <= n; j++) 
            cout << mat[i][j] << "\t";
        cout << "]" << endl;
    }
}
int main32() {
    int n;
    cout << "Enter the size of square coefficient matrix: ";
    cin >> n;
    float mat1[MAX][MAX], mat2[MAX][MAX];
    cout << "Enter the values of Augmented coefficient Matrix row-wise" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++) {
            cout << "mat[" << i << "][" << j << "]: ";
            cin >> mat1[i][j];
            mat2[i][j] = mat1[i][j];
        }

    cout << "The augmented coefficient matrix is: " << endl;
    display(mat1, n);

    cout << "The procedure in Gauss Elimination method: " << endl;
    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 1; i < n; i++) 
            for (int k = j; k <= n; k++) 
                mat2[i][k] = mat1[i][k] - mat1[i][j] / mat1[j][j] * mat1[j][k];
        for (int a = 0; a < n; a++) 
            for (int b = 0; b <= n; b++) 
                mat1[a][b] = mat2[a][b];
        cout << "STEP " << j + 1 << endl;
        display(mat2, n);
    }

    float ans[MAX];
    for (int i = n - 1; i >= 0; i--) {
        float val = mat2[i][n];
        for (int k = n - 1; k > i; k--) 
            val -= (mat2[i][k] * ans[k]);
        ans[i] = val / mat2[i][i];
    }    
    cout << "The solution matrix is: " << endl;
    for (int i = 0; i < n; i++) 
        cout << "[" << ans[i] << "]" << endl;
    return 1;
}