#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"

struct poly_t
{
    int *exponents;
    int *coefficients;
    int length;
};

struct poly_t *new_poly_from_string(const char *str)
{
    struct poly_t *p = malloc(sizeof(struct poly_t));
    p->exponents = malloc(sizeof(int));
    p->coefficients = calloc(1, sizeof(int));
    int negative = 0;
    int exponent = 0;
    volatile int index = 1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
        {
            int num = 0;
            while (isdigit(str[i]))
            {
                num *= 10;
                num += str[i] - '0';
                i++;
            }
            i--;

            if (exponent == 1)
            {
                if (negative == 1)
                {
                    p->exponents[index - 1] = -(num);
                }
                else
                {
                    p->exponents[index - 1] = (num);
                }
                negative = 0;
                exponent = 0;
                if (p->coefficients[index - 1] == 0)
                {
                    p->coefficients[index - 1] = 1;
                }
            }
            else
            {

                if (negative == 1)
                {
                    p->coefficients[index - 1] = -(num);
                }
                else
                {
                    p->coefficients[index - 1] = num;
                }
                p->exponents[index - 1] = 0;
                negative = 0;
            }
        }
        else if (str[i] == '-' || str[i] == '+')
        {
            if (str[i] == '-')
            {
                negative = 1;
            }
            if (i != 0)
            {
                index++;
                p->exponents = realloc(p->exponents, index * sizeof(int));
                p->coefficients = realloc(p->coefficients, index * sizeof(int));
            }
        }
        else if (str[i] == 'x')
        {
            exponent = 1;
            negative = 0;
        }
        else if (str[i] == ' ' && exponent == 1)
        {
            p->exponents[index - 1] = 1;
            exponent = 0;
            negative = 0;
        }
    }
    p->length = index;
    return p;
}
void free_poly(struct poly_t *p)
{
    free(p->exponents);
    free(p->coefficients);
    free(p);
}

struct poly_t *mul(struct poly_t *a, struct poly_t *b)
{
    struct poly_t *p = malloc(sizeof(struct poly_t));
    p->exponents = calloc(1, sizeof(int));
    p->coefficients = calloc(1, sizeof(int));
    p->length = 0;

    for (int i = 0; i < a->length; i++)
    {
        for (int j = 0; j < b->length; j++)
        {
            int exp = a->exponents[i] + b->exponents[j];
            int coeff = a->coefficients[i] * b->coefficients[j];
            for (int k = 0; k < p->length; k++)
            {
                if (p->exponents[k] == exp)
                {
                    p->coefficients[k] = p->coefficients[k] + coeff;
                    goto next_x;
                }
            }
            p->length++;
            p->exponents = realloc(p->exponents, p->length * sizeof(int));
            p->coefficients = realloc(p->coefficients, p->length * sizeof(int));
            p->exponents[p->length - 1] = exp;
            p->coefficients[p->length - 1] = coeff;
        next_x:;
        }
    }
    return p;
}

void print_poly(struct poly_t *p)
{
    for (int i = 0; i < p->length; i++)
    {
        int coeff = p->coefficients[i];
        int exp = p->exponents[i];
        if (coeff != 0)
        {
            if (i != 0)
            {
                coeff > 0 ? printf(" + ") : printf(" - ");
            }
            if (coeff != 1 || exp == 0)
                printf("%d", abs(coeff));
            if (exp == 1)
            {
                printf("x");
            }
            else if (exp > 1)
            {
                printf("x^%d", exp);
            }
        }
    }
    printf("\n");
}