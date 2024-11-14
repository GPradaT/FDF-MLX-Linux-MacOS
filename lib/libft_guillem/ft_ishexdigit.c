#include "libft.h"

int	ft_ishexdigit(char c)
{
	return ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}
