#include<stdio.h>

//entering the matrix
void readMatrix(int matrix[15][15]) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void findEqualRowsAndColumns(int numbers[15][15]) {
    int row[15] = {0};
    int column[15] = {0};

    //row sum
    for (int i = 0; i < 15; i++) {
        row[i] = 0;
        for (int j = 0; j < 15; j++) {
            row[i] += numbers[i][j];
        }
    }

    //column sum
    for (int j = 0; j < 15; j++) {
        column[j] = 0;
        for (int i = 0; i < 15; i++) {
            column[j] += numbers[i][j];
        }
    }

    //column to row equality
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (row[i] == column[j]) {
                printf("%d %d\n", i , j );
            }
        }
    }

    //row to row equality
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 15; j++) {
            if (row[i] == row[j]) {
                printf("%d %d\n", i, j);
            }
        }
    }

    //column to column equality
    for (int i = 0; i < 15; i++) {
        for (int j = i + 1; j < 15; j++) {
            if (column[i] == column[j]) {
                printf("%d %d\n", i, j);
            }
        }
    }
}


int main(){

    int numbers[15][15], i, j;
    int row[15], column[15];

    readMatrix(numbers);
    findEqualRowsAndColumns(numbers);

}

