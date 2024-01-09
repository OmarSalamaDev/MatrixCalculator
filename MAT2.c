// Main file
// Developed by Omar Abd-Alaziz Salama & Mohammed Adel 


/* >>>> Libraries <<<< */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "matrix.h"

/* >>>> Matrices intializations <<<< */

MATRIX ANS = {1, 1, {0}, {0}}; // #0
MATRIX A = {SIZE, SIZE, {0}, {0}}; // #1
MATRIX B = {SIZE, SIZE, {0}, {0}}; // #2
MATRIX C = {SIZE, SIZE, {0}, {0}}; // #3
MATRIX D = {SIZE, SIZE, {0}, {0}}; // #4
MATRIX E = {SIZE, SIZE, {0}, {0}}; // #5
int number;
int ansFlag = 0;

/* >>>> Functions declaration <<<< */

int main_menu(void);
int run(void);
MATRIX selector(int c);
void matrixSET(int c, MATRIX mat);

/* >>>> Primary functions declaration <<<< */

// main
int main(void)
{
    // starting massege
    printf("\nWelcome to matrix calculator v2.0.\nDeveloped and designed by Omar Abd-Alaziz Salama & Mohammed Adel\n");
    main_menu();
    return 0;
}

// main menu function
int main_menu(void)
{
    printf("\nEnter (run) to start calculator, (exit) to exit the app.\n\n");
    char* start_choice = malloc(5 * sizeof(char));
    printf("> ");
    scanf("%s", start_choice);

    if (strcmp(start_choice, "run") == 0)
    {
        free(start_choice);
        do
        {
            number = input_int("Enter the number of matrices (from 1 to 5): ");
        }
        while (number > 5 || number < 1);

        for (int i = 1; i <= number; i++)
        {
            printf("\nEnter matrix %c:\n", 64 + i);
            matrixSET(i, input_matrix(""));
            print_matrix(selector(i));
        }
        while (run() != 1)
        {
            continue;
        }
        return 0;
    }
    else if (strcmp(start_choice, "exit") == 0)
    {
        free(start_choice);
        return 1;
    }
    else
    {
        free(start_choice);
        printf("Wrong prompt.\n");
        main_menu();
        return 0;
    }
    free(start_choice);
    return 0;
}

// run function
int run()
{
    printf("\n");
    char* opp = malloc(20 * sizeof(char));
    printf("choose the operation:\n");
    printf("addition(add), subtraction(sub), multiplication(mult), transpose(trn),\ndeterminant(det), cofactor(cof), inverse(inv), (show), or (exit).\n\n> ");
    scanf("%s", opp);

    // addtion option
    if (strcmp(opp, "addition") == 0 || strcmp(opp, "add") == 0)
    {
        free(opp);

        char m1,m2;
        do
        {
            printf("Choose two matrices : ");
            m1 = toupper(getche());
            if (m1 == '@') {printf("\bANS");}
            printf(" + ");
            m2 = toupper(getche());
            if (m2 == '@') {printf("\bANS");}
            printf(" =\n");
        }
        while (m1 < '@' || m1 > '@' + number || m2 < '@' || m2 > '@'+ number);
 
        MATRIX mat1 = selector(m1 - 64);
        MATRIX mat2 = selector(m2 - 64);

        if (mat1.row != mat2.row || mat1.col != mat2.col) {printf("\nError!\nMatrices must have the same order.\n"); return 0;} /* Dimensions check */
        ANS = add(mat1, mat2);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // subtraction option
    else if (strcmp(opp, "subtraction") == 0 || strcmp(opp, "sub") == 0)
    {
        free(opp);
        
        char m1,m2;
        do
        {
            printf("Choose two matrices : ");
            m1 = toupper(getche());
            if (m1 == '@') {printf("\bANS");}
            printf(" - ");
            m2 = toupper(getche());
            if (m2 == '@') {printf("\bANS");}
            printf(" =\n");
        }
        while (m1 < '@' || m1 > '@' + number || m2 < '@' || m2 > '@'+ number);
 
        MATRIX mat1 = selector(m1 - 64);
        MATRIX mat2 = selector(m2 - 64);

        if (mat1.row != mat2.row || mat1.col != mat2.col) {printf("\nError!\nMatrices must have the same order.\n"); return 0;} /* Dimensions check */
        ANS = sub(mat1, mat2);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // transpose option
    else if (strcmp(opp, "transpose") == 0 || strcmp(opp, "trn") == 0)
    {
        free(opp);
        
        char m;
        do
        {
            printf("Choose matrix : ");
            m = toupper(getche());
            if (m == '@') {printf("\bANS");}
            printf("\n");
        }
        while (m < '@' || m > '@' + number);
 
        MATRIX mat = selector(m - 64);

        m == '@' ? printf("\ntranspose(ANS) = \n") : printf("\ntranspose(%c) = \n", m);
        ANS = transpose(mat);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // determinant option
    else if (strcmp(opp, "determinant") == 0 || strcmp(opp, "det") == 0)
    {
        free(opp);
        
        char m;
        do
        {
            printf("Choose matrix : ");
            m = toupper(getche());
            if (m == '@') {printf("\bANS");}
            printf("\n");
        }
        while (m < '@' || m > '@' + number);
 
        MATRIX mat = selector(m - 64);

        if (mat.row != mat.col) {printf("\nError!\nMatrix must be square : (rows = columns).\n"); return 0;} /* Dimensions check */
        m == '@' ? printf("\ndeterminant(ANS) = %.6g\n", det(mat)) : printf("\ndeterminant(%c) = %.6g\n", m, det(mat));
        return 0;
    }
    // cofactor option
    else if (strcmp(opp, "cofactor") == 0 || strcmp(opp, "cof") == 0)
    {
        free(opp);
        
        char m;
        do
        {
            printf("Choose matrix : ");
            m = toupper(getche());
            if (m == '@') {printf("\bANS");}
            printf("\n");
        }
        while (m < '@' || m > '@' + number);
 
        MATRIX mat = selector(m - 64);

        if (mat.row != mat.col) {printf("\nError!\nMatrix must be square : (rows = columns).\n"); return 0;} /* Dimensions check */
        if (mat.row == 1) {printf("\nError!\nMatrix size must be at least 2.\n"); return 0;} /* Size check */
        m == '@' ? printf("\ncofactor(ANS) =\n") : printf("\ncofactor(%c) =\n", m);
        ANS = cofactor(mat);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // multiplication option
    else if (strcmp(opp, "multiplication") == 0 || strcmp(opp, "mult") == 0)
    {
        free(opp);
        
        char m1,m2;
        do
        {
            printf("Choose two matrices : ");
            m1 = toupper(getche());
            if (m1 == '@') {printf("\bANS");}
            printf(" * ");
            m2 = toupper(getche());
            if (m2 == '@') {printf("\bANS");}
            printf(" =\n");
        }
        while (m1 < '@' || m1 > '@' + number || m2 < '@' || m2 > '@'+ number);
 
        MATRIX mat1 = selector(m1 - 64);
        MATRIX mat2 = selector(m2 - 64);

        if (mat1.col != mat2.row) {printf("\nError!\nMatrix 1 columns must be equal to matrix 2 rows.\n"); return 0;} /* Dimensions check */
        ANS = mult(mat1, mat2);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // inverse option
    else if (strcmp(opp, "inverse") == 0 || strcmp(opp, "inv") == 0)
    {
        free(opp);
        
        char m;
        do
        {
            printf("Choose matrix : ");
            m = toupper(getche());
            if (m == '@') {printf("\bANS");}
            printf("\n");
        }
        while (m < '@' || m > '@' + number);
 
        MATRIX mat = selector(m - 64);

        if (mat.col != mat.row) {printf("\nError!\nMatrix must be square : (rows = columns).\n"); return 0;} /* Dimensions check */
        if (det(mat) == 0) {printf("\nMatrix has no inverse : (matrix determinant = zero).\n"); return 0;} /* Inverse check */
        m == '@' ? printf("\ninverse(ANS) =\n") : printf("\ninverse(%c) =\n", m);
        ANS = inverse(mat);
        ansFlag = 1;
        print_matrix(ANS);
        return 0;
    }
    // show all matrices
    else if (strcmp(opp, "show") == 0)
    {
        free(opp);
        for (int i = 0; i <= number; i++)
        {
            if (i == 0 && ansFlag == 1) 
            {
                printf("\nANS = \n");
                print_matrix(selector(0));           
            }
            else if (i != 0)
            {
                printf("\nMatrix(%c) = \n", i + 64);
                print_matrix(selector(i));
            }
        }
        return 0;
    }
    // exit option
    else if (strcmp(opp, "exit") == 0)
    {
        free(opp);
        return 1;
    }
    // wrong prompt
    else
    {
        free(opp);
        printf("Wrong prompt.\n");
        return 0;
    }
    free(opp);
    return 1;
}

// Matrix selector function
MATRIX selector(int c)
{
    if (c == 0) return ANS;
    if (c == 1) return A;
    if (c == 2) return B;
    if (c == 3) return C;
    if (c == 4) return D;
    if (c == 5) return E;
    else return ANS;
}

// Matrix intializer function
void matrixSET(int c, MATRIX mat)
{
    if (c == 1) A = mat;
    if (c == 2) B = mat;
    if (c == 3) C = mat;
    if (c == 4) D = mat;
    if (c == 5) E = mat;
}