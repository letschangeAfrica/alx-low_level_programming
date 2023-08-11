#include <stdio.h>
/**
 * main - A program to print all the numbers in base 16
 * with putchar function three times
 *
 * Return: Always 0
 */
int main(void)
{
int i;
for (i = 48; i < 58; i++)
putchar(i);
for (i = 97; i < 103; i++)
putchar(i);
putchar('\n');
return (0);
}
