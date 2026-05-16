#include "connect4.h"
#include "libft.h"

#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  t_args args = {};
  t_parse_err err = parse_args(argc, argv, &args);
  if (err) {
    print_usage(argv[0], err);
    return 1;
  }

  srand(time(NULL));
  t_cell next_player = rand() % 2 ? CELL_P1 : CELL_P2;
  ft_printf("First player: %s\n", next_player == CELL_P1 ? "You (Human)" : "AI");

  t_board board = {.cols = 7, .rows = 6, .grid = {}, .stack_top = {}, .moves_count = 0};
  board_init(&board, &args);

  while (1) {
    draw_board(&board);
    int col = -1;
    while (next_player == CELL_P1 && col < 0) {
      ft_printf("Your move (column 0-%d): ", board.cols - 1);
      col = input_terminal(&board);
      if (col == -1) {
        ft_dprintf(STDERR_FILENO, "\nGame Exited\n");
        return 0;
      } else if (col == -2) {
        continue;
      }
    }
    if (next_player == CELL_P2) {
      col = ai_choose_move(&board, CELL_P2);
      if (col < 0) {
        ft_dprintf(STDERR_FILENO, "something wrong\n");
        return 1;
      }
      ft_printf("AI plays column: %d\n", col);
    }
    int row = board_drop(&board, col, next_player);
    if (board_check_win(&board, row, col) > 0) {
      draw_board(&board);
      ft_printf("%s won!\n", next_player == CELL_P1 ? "You" : "AI");
      break;
    }
    if (board_is_full(&board)) {
      draw_board(&board);
      ft_printf("It's a draw!\n");
      return (0);
    }

    if (next_player == CELL_P1) {
      next_player = CELL_P2;
    } else if (next_player == CELL_P2) {
      next_player = CELL_P1;
    }
  }
  return (0);
}
