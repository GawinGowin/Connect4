# Connect4

ターミナルで動作するコネクトフォーゲームの C 言語実装。人間 vs Negamax AI で対戦できます。

---

## 機能

- 任意ボードサイズ対応（最小 6 行 × 7 列、最大 128 × 128）
- 先攻プレイヤーをランダム決定（`srand(time(NULL))`）
- 3 段階の AI 実装：即勝ち手/ブロック → Negamax + α-β 枝刈り → 反復深化（最大 1 秒）
- 入力バリデーション（範囲外・満杯列・EOF/Ctrl-D 対応）
- 4 方向（水平・垂直・斜め）の勝利判定、引き分け判定

---

## 動作環境

| 項目 | 要件 |
|---|---|
| OS | Linux / macOS |
| コンパイラ | `cc`（GCC または Clang） |
| ビルドツール | `make` |

---

## ビルド

```bash
git clone <リポジトリURL>
cd Connect4
make
```

| コマンド | 説明 |
|---|---|
| `make` | リリースバイナリ `./connect4` をビルド（`-O3`） |
| `make debug` | デバッグバイナリ `./connect4_debug` をビルド（`-g3 -fsanitize=address`） |
| `make re` | フルリビルド（`fclean` + `all`） |
| `make fmt` | `clang-format` でコードを整形 |
| `make clean` | オブジェクト・依存ファイルを削除 |
| `make fclean` | バイナリも含めて削除 |

---

## 実行方法

```bash
./connect4 <rows> <cols>
```

```bash
# 標準サイズ（6行7列）
./connect4 6 7

# 大きめのボード
./connect4 10 12
```

### 引数エラーの例（エラー終了）

```bash
./connect4          # 引数なし
./connect4 abc 7    # 非数値
./connect4 -1 7     # 負数
./connect4 5 7      # 行数が最小値（6）未満
./connect4 6 6      # 列数が最小値（7）未満
```

---

## ゲームの流れ

ゲーム開始時はランダムで先攻が決まります。プレイヤーは `X`、AI は `O` で表示されます。

### 初期盤面（6 × 7）

```
. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
. . . . . . .
1 2 3 4 5 6 7
列を入力してください (1-7): 
```

### 中盤の盤面例

```
. . . . . . .
. . . . . . .
. . . . . . .
. . . X . . .
. . X O . . .
. X O O . . .
1 2 3 4 5 6 7
列を入力してください (1-7): 
```

| 記号 | 説明 |
|---|---|
| `X` | プレイヤー（P1・人間） |
| `O` | AI（P2） |
| `.` | 空きセル |

4 つ縦・横・斜めに並べると勝利。全セルが埋まると引き分け。

---

## AI の仕組み

### フェーズ 1: グリーディ（即時判断）

1. 次の 1 手で自分が勝てる列があれば選ぶ
2. 相手が次の 1 手で勝つ列があればブロックする
3. 自分の着手後に相手が即勝ちできない列を選ぶ
4. 上記に該当しない場合は中心列を優先

### フェーズ 2: Negamax + α-β 枝刈り

- 中心列を優先した着手順序で探索木を効率的に枝刈り
- 評価関数：
  - 中心列に近いほど高スコア
  - 4 セルウィンドウの脅威カウント（3 連: +100点、2 連: +10点）
  - 相手の脅威は逆符号で評価

### フェーズ 3: 反復深化（イテラティブ ディープニング）

- depth=1 から始め、1 秒以内に探索深度を最大化
- 大きなボードでも必ず時間内に応答
- 勝利確定手（スコア ≥ WIN_SCORE）が見つかれば即座に返す

---

## ファイル構成

```
Connect4/
├── src/
│   ├── main.c           # 引数パース → srand → ゲームループ
│   ├── args.c           # 引数バリデーション（範囲・型チェック）
│   ├── board.c          # board_drop / board_undo / board_is_full
│   ├── display.c        # ボード表示（ft_printf）
│   ├── input.c          # ユーザー入力処理（get_next_line + バリデーション）
│   ├── win_check.c      # 4方向勝利判定
│   └── ai/
│       ├── ai.c         # ai_choose_move（公開 API）
│       ├── ai_utils.c   # 中心優先の着手順序配列を構築
│       ├── ai_greedy.c  # グリーディ AI（即勝ち・ブロック・2手先読み）
│       ├── ai_negamax.c # Negamax + α-β 枝刈り + 反復深化
│       └── ai_evaluate.c# 評価関数（中心ボーナス・脅威カウント）
├── include/
│   └── connect4.h       # 全型定義とプロトタイプ
├── lib/
│   └── libft/           # 自作 C 標準ライブラリ（ft_printf, get_next_line 等）
└── Makefile
```

---

## 主要な型定義

```c
typedef enum e_cell { CELL_EMPTY = 0, CELL_P1 = 1, CELL_P2 = 2 } t_cell;

typedef struct s_board {
    t_cell grid[MAX_ROWS][MAX_COLS]; // grid[row][col]、row=0 が底（重力側）
    int    rows;
    int    cols;
    int    stack_top[MAX_COLS];      // 各列の次の空き行インデックス
    int    moves_count;
} t_board;
```

---

## 開発

### コードスタイル

`.clang-format` で 100 列制限・開き括弧後改行を統一。

```bash
make fmt    # フォーマット実行
```

### メモリチェック

```bash
make debug
valgrind ./connect4_debug 6 7
# または
./connect4_debug 6 7   # -fsanitize=address が有効
```
