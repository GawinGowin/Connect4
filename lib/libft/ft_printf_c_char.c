/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _c_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:36:33 by saraki            #+#    #+#             */
/*   Updated: 2023/08/19 18:27:41 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

int	c_print_char(va_list args)
{
	char	value;

	value = (char) va_arg(args, int);
	if (write(STDOUT_FILENO, &value, 1) == -1)
		return (0);
	return (1);
}

// void	test_helper(const char *fmt, ...)
// {
// 	va_list		args;
// 	int			a;

// 	va_start(args, fmt);
// 	a = c_print_char(args);
// 	va_end(args);
// }

// int	main(void)
// {
// 	test_helper("", 'a');
// 	write(1,"\n",1);
// 	test_helper("", ' ');
// }
