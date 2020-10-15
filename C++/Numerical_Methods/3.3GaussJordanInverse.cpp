#include<iostream>
#include<iomanip>

int const MAX = 10;

void display33(float mat[MAX][MAX], int n) {
    for (int i = 0; i < n / 2; i++) {
        std::cout << "[\t";
        for (int j = 0; j < n; j++) {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << "]" << std::endl;
    }
}
void displayInverse(float mat[MAX][MAX], int n) {
    for (int i = 0; i < n / 2; i++) {
        std::cout << "[\t";
        for (int j = n / 2; j < n; j++) {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << "]" << std::endl;
    }
}
int mainl33() {
    float mat1[MAX][MAX];
    float mat2[MAX][MAX];
    int n;
    std::cout << "Enter the order of square matrix: ";
    std::cin >> n;
    std::cout << "Enter the values of matrix whose inverse is to be calculated: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "mat1[" << i << "][" << j << "]: ";
            std::cin >> mat1[i][j];
            mat2[i][j] = mat1[i][j];
        }
        for (int k = n; k < 2 * n; k++) {
            if (k - i == n)
                mat1[i][k] = mat2[i][k] = 1;
            else
                mat1[i][k] = mat2[i][k] = 0;
        }
    }
    std::cout << "The given matrix is:" << std::endl;
    display33(mat1, 2 * n);
    std::cout << "The augmented form is: " << std::endl;
    display33(mat1, 2 * n);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) 
            if (i != j) 
                for (int k = j; k < 2 * n; k++) 
                    mat2[i][k] = mat1[i][k] - mat1[i][j] / mat1[j][j] * mat1[j][k];
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < 2 * n; j++) 
                mat1[i][j] = mat2[i][j];
        std::cout << std::endl;
        display33(mat2, 2 * n);
    }

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < 2 * n; j++) 
            if (i == j) 
                for (int k = i; k < 2 * n; k++) 
                    mat2[i][k] = mat1[i][k] / mat1[i][j];    
    std::cout << std::endl << "The solution matrix is:" << std::endl;
    display33(mat2, 2 * n);
    std::cout << "The inverse matrix of given matrix is: " << std::endl;
    displayInverse(mat2, 2 * n);
    return 1;
}