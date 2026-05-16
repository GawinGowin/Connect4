#include "connect4.h"
#include "libft.h"

int input_terminal(t_board *b) {
  char *line = NULL;

  line = get_next_line(STDIN_FILENO);
  if (line == NULL) {
    return (-1);
  }

  char *endptr = NULL;
  long col = ft_strtol(line, &endptr, 10);
  while ((*endptr == ' ') || (*endptr == '\t') || (*endptr == '\r'))
    endptr++;
  if (endptr != NULL && ft_strcmp(endptr, "\n") != 0) {
    if (line[0] != '\n')
      ft_printf("Please enter a number.\n");
    free(line);
    return (-2);
  }
  free(line);
  if (col < 0 || col >= b->cols) {
    ft_printf("Enter a column between 0 and %d.\n", b->cols - 1);
    return (-2);
  }
  if (b->stack_top[col] >= b->rows) {
    ft_printf("Column %d is full. Choose another.\n", col);
    return (-2);
  }
  return (col);
}
