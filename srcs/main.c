
# include <unistd.h>
# include <sys/mman.h>     
# include <stdlib.h>
# include <sys/time.h> 
# include <sys/resource.h>
# include <sys/mman.h>
static void	ft_putchar(char c)
{
	write(1, &c, 1);
}
static void	ft_putendl(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			i++;
		}
		write(1, s, i);
		ft_putchar('\n');
	}
}
int     main(void)
{
    void *p;
    void *newptr;
    int i;
    int letter;
    char *s;

    i = 0;
    letter =65;
    p = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    s = p;
    while (i < 1024)
    {
        if (letter >= 90)
            letter = 65;
        s[i] = letter;
        i++;
        letter++;
    }
    ft_putendl(s);
    newptr = p + 501;
    s = newptr;
    ft_putendl(s);
}