# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Goal

Implement a terminal Connect Four game in C where a human plays against an AI.
The AI must play on every turn without hanging, and must try to win.

## Commands

```bash
make              # Build release binary: ./connect4
make debug        # Build debug binary with -g3 -fsanitize=address: ./connect4_debug
make re           # Full rebuild (fclean + all)
make fmt          # Format all C sources with clang-format
make clean        # Remove object/dep files
make fclean       # Remove objects + binaries
```

The binary is invoked as: `./connect4 <rows> <cols>` (minimum 6 rows, 7 cols).

## Architecture

### Current state
- `include/connect4.h` — empty; all types and prototypes go here
- `src/main.c` — stub returning 0
- `lib/libft/` — fully implemented (atoi, split, putstr_fd, calloc, strtol, ft_printf, get_next_line, etc.); linked as `libft.a` / `libft_debug.a`
- `Makefile SRCS` — only contains `src/main.c`; add new `.c` files here

### Target file structure
```
src/
├── main.c               # arg parse → select t_io backend → srand → game_loop
├── args.c               # validate argc/argv, row/col minimums, non-digit rejection
├── board.c              # board_create / board_destroy / board_drop / board_is_full
├── display.c            # board_print terminal backend (ft_printf; row=0 is bottom)
├── display_ncurses.c    # board_print_ncurses bonus backend (mvprintw)
├── win_check.c          # board_check_win(board, last_row, last_col) — 4-dir check
├── input.c              # input_terminal: get_next_line + ft_atoi, EOF / range / full-col
├── input_ncurses.c      # input_ncurses bonus backend (wgetch)
├── io.c                 # t_io vtable instances: g_terminal_io, g_ncurses_io
├── game_loop.c          # turn loop: io->draw_board → move → check_win/draw
└── ai/
    ├── ai.c             # public: ai_choose_move(board, player_mark)
    ├── ai_heuristic.c   # Phase 1: instant-win → block → safe → center
    ├── ai_negamax.c     # Phase 2: negamax + alpha-beta + iterative deepening
    └── ai_evaluate.c   # leaf evaluation: center weight + threat count + parity
```

### Core data model

```c
typedef enum e_cell  { CELL_EMPTY = 0, CELL_P1 = 1, CELL_P2 = 2 }  t_cell;

typedef struct s_board {
    t_cell **grid;      // grid[row][col], row=0 is the bottom row
    int      rows;
    int      cols;
    int     *heights;   // heights[col] = next empty row index in that column
    int      moves_count;
} t_board;

typedef struct s_player {
    t_cell mark;   // CELL_P1 or CELL_P2
    int    is_ai;  // 0 = human, 1 = AI
} t_player;

// I/O vtable — game_loop only knows this; backend is selected in main
typedef struct s_io {
    void (*draw_board)(t_board *board);
    int  (*get_input)(t_board *board);   // returns col (0-indexed), -1 on EOF
    void (*show_result)(const char *msg);
} t_io;

// vtable instances defined in io.c
extern t_io g_terminal_io;   // ft_printf / get_next_line
extern t_io g_ncurses_io;    // mvprintw / wgetch  (bonus)
```

**Critical layout rule**: `row=0` is the bottom (gravity side). `heights[col]` is the row where the next piece lands. Display iterates `rows-1` down to `0`. Win-check uses only the last-dropped (row, col) as the origin — no full-board scan.

### Subject constraints
- Language: C, compiler: `cc -Wall -Wextra -Werror`
- Allowed: libft, `malloc`, `free`, `rand`, `srand`, `time`
- First player chosen randomly via `rand()` after `srand(time(NULL))`
- AI must always move and must not block for a long time — use iterative deepening with a ~1 s time cap
- Argument order: `./connect4 <rows> <cols>`, minimum 6 rows × 7 cols

### AI implementation priority (36 h budget)
1. **Heuristic AI** (ship-critical): instant-win → block → avoid gifting win → center-biased walk
2. **Negamax + α-β** (quality): move order = center outward; dynamic board size means the order array must be built at runtime (`build_move_order`)
3. **Iterative deepening**: mandatory for large boards; use `clock()` to cut off at ~900 ms

Move ordering for arbitrary `cols`:
```c
void build_move_order(int *order, int cols) {
    int center = cols / 2, idx = 0;
    order[idx++] = center;
    for (int d = 1; d <= cols; d++) {
        if (center - d >= 0)   order[idx++] = center - d;
        if (center + d < cols) order[idx++] = center + d;
    }
}
```

### Bonus (only evaluated if mandatory is perfect)
- A single binary handles both modes; ncurses is always linked.
- Pass `--gui` as a 3rd runtime argument to activate: `./connect4 <rows> <cols> --gui`
  — no `make bonus` target, no compile flags.
- `main` selects `&g_ncurses_io` or `&g_terminal_io` and passes the pointer to `game_loop`.
- `game_loop` calls only through the vtable (`io->draw_board`, `io->get_input`,
  `io->show_result`) — zero if/else for backend switching inside the loop.
- Terminal output (grid + winner/draw message) remains mandatory in both modes;
  ncurses replaces draw + input interaction.

### Submission checklist
- `./connect4` with no args, non-digits, negative numbers, below-minimum dimensions → error + exit
- EOF (Ctrl-D) during input → no infinite loop
- Full column input → prompt again
- Draw (all cells filled) → correct end message
- Grid display skipped (or truncated) when too large for a standard terminal
- `valgrind` or `-fsanitize=address` shows zero leaks
- `make re`, `make fclean`, `make clean` all work
- `-Wall -Wextra -Werror` zero warnings

## Code style
`.clang-format` is configured (100-column limit, `AlwaysBreak` after open bracket). Run `make fmt` before committing.

### Include rules
- Each `.c` file includes only the headers it directly uses ("include what you use").
- Add a standard header to `connect4.h` **only** when a type or prototype defined
  there requires it (e.g., `<time.h>` if a prototype returns `time_t`).
- `connect4.h` and `libft.h` are the project-wide headers every `.c` includes;
  standard library headers are pulled in per-file.

Typical mapping:
| File | Standard headers |
|---|---|
| `main.c` | `<stdlib.h>` `<time.h>` |
| `display.c` | none (ft_printf via libft) |
| `display_ncurses.c` | `<ncurses.h>` |
| `args.c` | `<stdlib.h>` |
| `input.c` | none (get_next_line + ft_atoi via libft) |
| `input_ncurses.c` | `<ncurses.h>` |
| `game_loop.c` | `<stdlib.h>` (clock) |
