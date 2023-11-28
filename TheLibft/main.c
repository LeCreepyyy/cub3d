#include "base/libft.h"
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h> /* open() */
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define CYAN "\x1b[36m"

int	main(void)
{
	printf(CYAN "#Testing: Libft\n\n");

	char ft_atoi_test[] = "  -42";
		printf(YELLOW "ft_atoi: %d\n", ft_atoi(ft_atoi_test));
		printf(GREEN "atoi: %d\n\n", atoi(ft_atoi_test));
	char ft_atol_test[] = "  -2147483647";
		printf(YELLOW "ft_atol: %d\n", ft_atol(ft_atol_test));
		printf(GREEN "atol: %d\n\n", atol(ft_atol_test));
	char ft_bzero_test[] = "bzero";
		ft_bzero(ft_bzero_test, 2);
		printf(YELLOW "ft_bzero: %s\n", ft_bzero_test);
	char bzero_test[] = "bzero";
		bzero(bzero_test, 2);
		printf(GREEN "bzero: %s\n\n", bzero_test);
	// Calloc outputs nothing, beacause its memory was cleared by bzero.
		printf(YELLOW "ft_calloc: %s\n", ft_calloc(4242, sizeof(int)));
		printf(GREEN "calloc: %s\n\n", calloc(4242, sizeof(int)));
	// ft_isalnum should output 011
		printf(YELLOW "ft_isalnum(#): %i\n", ft_isalpha("#"));
		printf(YELLOW "ft_isalnum(Z): %i\n", ft_isalpha("Z"));
		printf(YELLOW "ft_isalnum(5): %i\n\n", ft_isalpha("5"));
	// ft_isalpha should output 010
		printf(YELLOW "ft_isalpha(#): %i\n", ft_isalpha("#"));
		printf(YELLOW "ft_isalpha(Z): %i\n", ft_isalpha("Z"));
		printf(YELLOW "ft_isalpha(5): %i\n\n", ft_isalpha("5"));
	// ft_isascii should ouput 110
		printf(YELLOW "ft_isascii(#): %i\n", ft_isascii("#"));
		printf(YELLOW "ft_isascii(Z): %i\n", ft_isascii("Z"));
		printf(YELLOW "ft_isascii(的): %i\n\n", ft_isascii("的"));
	// ft_isdigit should ouput 001
		printf(YELLOW "ft_isdigit(#): %i\n", ft_isdigit("#"));
		printf(YELLOW "ft_isdigit(Z): %i\n", ft_isdigit("Z"));
		printf(YELLOW "ft_isdigit(5): %i\n\n", ft_isdigit("5"));
	// ft_isprint should output 10
		printf(YELLOW "ft_isdigit(#): %i\n", ft_isdigit("#"));
		printf(YELLOW "ft_isdigit(5): %i\n\n", ft_isdigit(127));
	int ft_itoa_test = -2147483648;
		printf(YELLOW "ft_itoa: %s\n", ft_itoa(ft_itoa_test));
		printf(YELLOW "itoa: -2147483648\n\n");

	ft_printf(CYAN "#Testing: ft_printf\n");

	char *ptr = "lol";
	ft_printf("ft_printf percent:	%%%%\n");
		printf("printf percent:	%%%%\n\n");
	ft_printf("ft_printf char:	%c, %c, %c\n", 'a', 'b', 'c');
		printf("printf  char:	%c, %c, %c\n\n", 'a', 'b', 'c');
	ft_printf("ft_printf str:	%s, %s\n", "Bonjour", "424242");
		printf("printf str:	%s, %s\n\n", "Bonjour", "424242");
	ft_printf("ft_printf nbr:	%d, %i\n", 42, -4368);
		printf("printf nbr:	%d, %i\n\n", 42, -4368);
	ft_printf("ft_printf uint:	%u, %u\n", 42, 4368);
		printf("printf uint:	%u, %u\n\n", 42, 4368);
	ft_printf("ft_printf hex:	%x, %X\n", 555, 4242);
		printf("printf hex:	%x, %X\n\n", 555, 4242);
	ft_printf("ft_printf ptr:	%p\n", ptr);
		printf("printf ptr:	%p\n\n", ptr);



	ft_printf(CYAN "#Testing: GNL\n");

	int fd = open("./get_next_line/GNLtest.txt", O_RDONLY);
	char *line;
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
			free (line);
		}
		ft_printf("%s", line);
		free (line);
	}
	ft_printf("\n\n");
	return (0);
}