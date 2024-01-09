// Matrix.h library
// Designed by Omar Abd-Alaziz Salama 


/* >>>> Constants <<<< */

#define SIZE 10
#define zeroApproxi 1.0E-010

/* >>>> Libraries <<<< */
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/* >>>> Matrix structure <<<< */

typedef struct
{
    int row;
    int col;
    double data[SIZE][SIZE];
    bool lock[SIZE][SIZE];
}
MATRIX;

/* >>>> Functions declaration <<<< */

MATRIX add(MATRIX mat1, MATRIX mat2);
MATRIX sub(MATRIX mat1, MATRIX mat2);
MATRIX mult(MATRIX mat1, MATRIX mat2);
MATRIX mult_byNum(MATRIX mat, double x);
MATRIX transpose(MATRIX mat);
MATRIX unlockALL(MATRIX mat);
void reset(MATRIX mat);
double minor(MATRIX mat, int R, int C);
double det(MATRIX mat);
MATRIX cofactor(MATRIX mat);
MATRIX inverse(MATRIX mat);
MATRIX input_matrix(char text[50]);
void print_matrix(MATRIX matrix);

int input_int(char text[50]);
double input_double(char text[50]);
void printRepeated(int ch, int N);

/* >>>> Primary functions definition <<<< */

// addition function
MATRIX add(MATRIX mat1, MATRIX mat2)
{
    MATRIX mat3;
    mat3.row = mat1.row;
    mat3.col = mat1.col;
    for (int r = 0; r < mat1.row; r++)
    {
        for (int c = 0; c < mat1.col; c++)
        {
            mat3.data[r][c] = mat1.data[r][c] + mat2.data[r][c];
        }
    }
    return mat3;
}

// substarcion function
MATRIX sub(MATRIX mat1, MATRIX mat2)
{
    MATRIX mat3;
    mat3.row = mat1.row;
    mat3.col = mat1.col;
    for (int r = 0; r < mat1.row; r++)
    {
        for (int c = 0; c < mat1.col; c++)
        {
            mat3.data[r][c] = mat1.data[r][c] - mat2.data[r][c];
        }
    }
    return mat3;
}

// cofactor matrix function
MATRIX cofactor(MATRIX mat)
{
    MATRIX ans;
    ans.row = mat.row;
    ans.col = mat.col;
    if (mat.row == 2)
    {
        ans.data[0][0] = mat.data[1][1];
        ans.data[1][1] = mat.data[0][0];
        ans.data[0][1] = -mat.data[1][0];
        ans.data[1][0] = -mat.data[0][1];
    }
    else
    {
        for (int r = 0; r < ans.row; r++)
        {
            for (int c = 0; c < ans.col; c++)
            {
                ans.data[r][c] = minor(mat, r, c) * pow(-1, r+c+2);
            }
        }
    }
    reset(mat);
    return ans;
}

// matrix determinant function
double det(MATRIX mat)
{
    if (mat.row == 1) {return mat.data[0][0];}
    else if (mat.row == 2)
    {
        return (mat.data[0][0] * mat.data[1][1]) - (mat.data[0][1] * mat.data[1][0]);
    }
    else
    {
        double det = 0;
        for (int c = 0; c < mat.row; c++)
        {
            det += minor(mat, 0, c) * pow(-1, c+2) * mat.data[0][c];
        }
        reset(mat);
        return det;
    }
    return 0;
}

// matrices multiplication function
MATRIX mult(MATRIX mat1, MATRIX mat2)
{
    MATRIX ans;
    ans.row = mat1.row;
    ans.col = mat2.col;
    mat1 = transpose(mat1);
    double dot = 0;
    for (int c1 = 0; c1 < mat1.col; c1++)
    {
        for (int c2 = 0; c2 < mat2.col; c2++)
        {
            for (int r = 0; r < mat1.row; r++)
            {
                dot += mat1.data[r][c1] * mat2.data[r][c2];
            }
            ans.data[c1][c2] = dot;
            dot = 0;
        }
    }
    return ans;
}

// matrix inverse function
MATRIX inverse(MATRIX mat)
{
    MATRIX ans;
    ans.col = mat.col;
    ans.row = mat.row;
    if (mat.row == 1)
    {
        ans.data[0][0] = 1 / mat.data[0][0];
        return ans;
    }
    else
    {
        double C = 1 / det(mat);
        MATRIX adj = transpose(cofactor(mat));
        ans = mult_byNum(adj, C);
        reset(mat);
        return ans;
    }
}

// matrix transpose function
MATRIX transpose(MATRIX mat)
{
    MATRIX ans;
    ans.row = mat.col;
    ans.col = mat.row;

    for (int c = 0; c < mat.col; c++)
        {
            for (int r = 0; r < mat.row; r++)
            {
                ans.data[c][r] = mat.data[r][c];
            }
        }
    return ans;
}

// unlock function
MATRIX unlockALL(MATRIX mat)
{
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            mat.lock[r][c] = false;
        }
    }
    return mat;
}

// matrix reset
void reset(MATRIX mat)
{
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            mat.data[r][c] = 0;
        }
    }
}

// lock row and column function
double minor(MATRIX mat, int R, int C)
{
    MATRIX ans;
    for (int r = 0; r < mat.row; r++)
    {
        for (int c = 0; c < mat.col; c++)
        {
            if (r == R || c == C)
            {
                mat.lock[r][c] = true;
            }
        }
    }
    ans.row = mat.row - 1;
    ans.col = mat.row - 1;
    int rd = 0, cd = 0;
    for (int r = 0; r < mat.row; r++)
    {
        for (int c = 0; c < mat.col; c++)
        {
            if (mat.lock[r][c] == false)
            {
                ans.data[rd][cd] = mat.data[r][c];
                if (cd == ans.col - 1)
                {
                    cd = 0;
                    rd++;
                }
                else {cd++;}
            }
        }
    }
    reset(mat);
    return det(ans);
}

// multiply by a number function
MATRIX mult_byNum(MATRIX mat, double x)
{
    for (int r = 0; r < mat.row; r++)
    {
        for (int c = 0; c < mat.col; c++)
        {
            mat.data[r][c] *= x;
        }
    }
    return mat;
}

// make matrix function
MATRIX input_matrix(char text[50])
{
    MATRIX matrix;
    printf("%s", text);

    while (true)
    {
        matrix.row = input_int("rows> ");
        if (matrix.row < 1 || matrix.row > SIZE)
        {
            printf("Enter an integer between 1 and %d:\n", SIZE);
            continue;
        }
        else {break;}
    }

    while (true)
    {
        matrix.col = input_int("columns> ");
        if (matrix.col < 1 || matrix.col > SIZE)
        {
            printf("Enter an integer between 1 and %d:\n", SIZE);
            continue;
        }
        else {break;}
    }

    char msg[10];
    printf("Enter the matrix:\n");
    for (int i = 0; i < matrix.row; i++)
    {
        for(int j = 0; j < matrix.col; j++)
        {
            sprintf(msg, "[%i,%i]> ", i+1, j+1);
            matrix.data[i][j] = input_double(msg);
        }
    }
    matrix = unlockALL(matrix);
    return matrix;
}

// ptint matrix funcion
void print_matrix(MATRIX matrix)
{
    char* str = malloc(20*sizeof(char));
    int max = 1;
    int maxes[matrix.col];
    int len[matrix.row][matrix.col];

    for (int c = 0; c < matrix.col; c++)
    {
        max = 0;
        for (int r = 0; r < matrix.row; r++)
        {
            if (fabs(matrix.data[r][c]) < zeroApproxi) {matrix.data[r][c] = 0;}
            if (matrix.data[r][c] == -0) {matrix.data[r][c] = 0;}
            sprintf(str, "%.6g", matrix.data[r][c]);
            int L = strlen(str);
            len[r][c] = L;
            if (L > max) {max = L;}
        }
        maxes[c] = max;
    }
    printf("\n\n");
    for (int i = 0; i < matrix.row; i++)
    { 
        printf("%c  ", 179);
        for (int j = 0; j < matrix.col; j++)
        {
            printf("%.6g  ", matrix.data[i][j]);
            printRepeated(32, maxes[j] - len[i][j]);
        }
        printf("%c\n", 179);
    }
    free(str);
}

/* >>>> Secondary functions declaration <<<< */

// integer input check function
int input_int(char text[50])
{
    char* input = malloc(50 * sizeof(char));
    int L = strlen(input);
    printf("%s", text);
    scanf("%s", input);

    for (int j = 0; input[j] != '\0'; j++)
    {
        if (input[0] == '-' && j == 0 && input[1] != '\0') {continue;} 
        else if (input[j] == '.' || !isdigit(input[j]))
        {
            printf("Enter an integer between 1 and 10:\n");
            printf("%s", text);
            scanf("%s", input);
            j = -1;
        }
    }
    int integer = atoi(input);
    free(input);
    return integer;
}

// double input check function
double input_double(char text[50])
{
    char* input = malloc(50 * sizeof(char));
    int L = strlen(input);
    printf("%s", text);
    scanf("%s", input);
    int n = 1;
    for (int j = 0; input[j] != '\0'; j++)
    {
        if (input[0] == '-' && j == 0 && input[1] != '\0') {continue;}
        else if (input[j] == '.' && n == 1 && input[1] != '\0') {n++; continue;}
        else if (!isdigit(input[j])) 
        {
            printf("Wrong input : (must enter a number).\n");
            printf("%s", text);
            scanf("%s", input);
            j = -1;
            n = 1;
        }
    }
    double d;
    char* endptr;
    d = strtod(input, &endptr); 
    free(input);
    return d;
}

// print spaces function
void printRepeated(int ch,int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%c", ch);
    }
}