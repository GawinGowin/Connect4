/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _s_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:43 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 19:39:49 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	s_print_str(int fd, va_list args)
{
	char	*value;
	int		digits;

	value = va_arg(args, char *);
	digits = 0;
	if (value == NULL)
		value = "(null)";
	while (*value != '\0')
	{
		if (write(fd, value, 1) != -1)
			digits ++;
		value ++;
	}
	return (digits);
}

// void	test_helper(const char *fmt, ...)
// {
// 	va_list		args;

// 	va_start(args, fmt);
// 	s_print_str(args);
// 	va_end(args);
// }

// int	main(void)
// {
// 	test_helper("", "Hello");
// }
