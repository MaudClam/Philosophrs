#include <stdio.h>
#include <stdlib.h>


void	free_mem(void **a, int counter)
{
	while (a && counter--)
	{
		free(a[counter]);
		if (counter)
			a[counter] = NULL;
	}
}

void	*smart_calloc(void **a, int a_size, int *counter, size_t mem_size)
{
	void	*ptr;
	char	*b;

	ptr = NULL;
	if (*counter < a_size)
	{
		ptr = malloc(mem_size);
		if (!ptr)
			free_mem(a, *counter);
		else
		{
			if (!a)
				a = ptr;
			b = ptr;
			while (mem_size--)
				*(b++) = 0;
			a[*counter] = ptr;
			(*counter)++;
		}
	}
	else
		free_mem(a, *counter);
	return (ptr);
}


int	main ()
{
	int 	i = 0;
	int 	counter = 0;
	int		a_size = 5;
	void	*ptr;
	void	**a;
	
	a = smart_calloc(NULL, a_size, &counter, sizeof(void *) * a_size);
	printf("%p#\n", a);
	while (i < 2)
	{
		ptr = smart_calloc(a, a_size, &counter, 100);
		printf("%p-\n", ptr);
		i++;
	}
	free_mem(a, counter);
	return (0);
}
