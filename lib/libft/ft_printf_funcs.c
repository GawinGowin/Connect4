/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saraki <saraki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:31:21 by saraki            #+#    #+#             */
/*   Updated: 2023/10/01 05:29:21 by saraki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"
#include "libft_int.h"

int dec_to_nbase(uintptr_t n, char *base, int fd) {
  uintptr_t base_num;
  uintptr_t residual;
  int cnt;

  base_num = (uintptr_t)ft_strlen(base);
  if (n < base_num) {
    if (write(fd, &base[n], 1) == -1)
      return (0);
    return (1);
  }
  residual = n % base_num;
  cnt = dec_to_nbase(n / base_num, base, fd);
  if (write(fd, &base[residual], 1) == -1)
    return (cnt);
  return (cnt + 1);
}
