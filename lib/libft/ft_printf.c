/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:05:57 by saraki            #+#    #+#             */
/*   Updated: 2023/09/30 16:12:20 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

static t_func_pt	switch_fmt_render(char specifier);

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		cnt;

	va_start(args, fmt);
	i = 0;
	cnt = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			cnt += switch_fmt_render(fmt[i + 1])(args, fmt[i + 1]);
			i ++;
		}
		else if (write(STDOUT_FILENO, &fmt[i], 1) != -1)
			cnt ++;
		i ++;
	}
	va_end(args);
	return (cnt);
}

static t_func_pt	switch_fmt_render(char specifier)
{
	if (specifier == 'c')
		return ((t_func_pt) c_print_char);
	else if (specifier == 's')
		return ((t_func_pt) s_print_str);
	else if (specifier == 'p')
		return ((t_func_pt) p_print_pt);
	else if (specifier == 'd')
		return ((t_func_pt) d_print_dec);
	else if (specifier == 'i')
		return ((t_func_pt) i_print_dec);
	else if (specifier == 'u')
		return ((t_func_pt) u_print_dec);
	else if (specifier == 'x')
		return ((t_func_pt) x_print_dec_lower);
	else if (specifier == 'X')
		return ((t_func_pt) x_print_dec_upper);
	else if (specifier == '%')
		return ((t_func_pt) _print_percent);
	else
		return ((t_func_pt) _other_format);
}
