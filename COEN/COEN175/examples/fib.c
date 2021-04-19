/* fib.c */

int printf(), scanf();

/*
 * return the nth fibonacci number
 */

int fib(int n)
{
    if (n == 0 || n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}


int main(void)
{
    int n;

    scanf("%d", &n);
    printf("%d\n", fib(n));
}
