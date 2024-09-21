/*
 * Print Fahrenheit-Celsius table using a function
 */

#include <stdio.h>

/* Fahrenheit-Celsius conversion */
static int ftoc(int ftemp) {
    return 5 * (ftemp - 32) / 9;
}

int main(void) {

    int fahr;
    int lower = 0;   /* lower limit of temperature table */
    int upper = 300; /* upper limit */
    int step  = 20;  /* step size */

    printf("Fahrenheit\tCelsius\n");
    for (fahr = lower; fahr <= upper; fahr += step)
        printf("%d\t\t%d\n", fahr, ftoc(fahr));

    return 0;
}