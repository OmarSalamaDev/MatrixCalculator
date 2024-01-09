#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    double real;
    double img;
}
complex;

complex Zadd(complex z1, complex z2);
complex Zsub(complex z1, complex z2);
complex Zmult(complex z1, complex z2);
void input_complex(void);

int main(void)
{
    
    //complex z3 = input_complex();
    input_complex();


    //printf("\n>> %.6g %c %.6gi\n", z3.real, (z3.img > 0)? '+': '-' , fabs(z3.img));


}

complex Zadd(complex z1, complex z2)
{
    complex z3;
    z3.real = z1.real + z2.real;
    z3.img = z1.img + z2.img;
    return z3;
}

complex Zsub(complex z1, complex z2)
{
    complex z3;
    z3.real = z1.real - z2.real;
    z3.img = z1.img - z2.img;
    return z3;
}

complex Zmult(complex z1, complex z2)
{
    complex z3;
    z3.real = z1.real * z2.real - (z1.img * z2.img);
    z3.img = z1.real * z2.img + z1.img * z2.real;
    return z3;
}

void input_complex(void)
{
    complex z;
    char realBuffer[20];
    char imgBuffer[20];
    char sign = '+';
    char input[50];
    printf(">> ");
    gets(input);
    int i;
    for(i = 0; isdigit(input[i]) == 1; i++)
    {
        realBuffer[i] = input[i];    
    }

    printf("\n%d\n", i);

    printf("\n>%c<\n", input[i-1]);
    printf(">%c<\n", input[i]);
    printf(">%c<\n", input[i+1]);
    printf(">%c<\n", input[i+2]);
    printf(">%c<\n", input[i+3]);

    /*while (1)
    {
        if (isdigit(input[i])) break;
        else if (isspace(input[i])) i++;
        else if (input[i] == '-') sign = '-';
        else continue; 
    }*/
    

    printf("\ninput >> %s\n", input);
    printf("real >> %s\n", realBuffer);
    printf("sign >> %c\n", sign);
    //printf("img >> %s\n", imgBuffer);

}