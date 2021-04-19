/* sum.c */

int printf();

int main(void)
{
    int i, n, sum;

    i = 0;
    sum = 0;
    n = 10;

    for (i = 1; i <= n; i = i + 1)
	sum = sum + i;

    printf("%d %d\n", sum, n * (n + 1) / 2);
}
