/* malloc.c */

int *malloc(unsigned long n);

int main(void)
{
    int n;
    int *p;

    n = 10;
    p = malloc(sizeof(int) * n);

    while (-- n)
	*p ++ = 0;
}
