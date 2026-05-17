---
name: create-pr
description: 現在のブランチからmainブランチへのPull Requestを作成する。コミット履歴を解析してタイトルと概要を自動生成し、gh CLIでPRを作成する。
allowed-tools: Bash(git *), Bash(gh *)
---

# Pull Request 作成

現在のブランチからmainブランチへのPull Requestを作成します。

## 手順

1. 現在のブランチ名を確認し、mainでないことを検証する
2. mainとの差分コミットを取得する
3. コミット内容からPRタイトルと本文を生成する
4. `gh pr create` でPRを作成する
5. 作成されたPRのURLを表示する

## 実行ルール

- 現在のブランチがmainの場合はエラーを表示して終了する
- mainとの差分コミットがない場合はエラーを表示して終了する
- リモートにブランチが存在しない場合は `git push -u origin <branch>` でpushしてからPRを作成する
- PRタイトル: 最新のコミットメッセージの1行目を使用する
- PR本文: 以下の形式で生成する

```
## Summary
<コミット一覧を箇条書き>

## Test plan
- [ ] 動作確認済み

🤖 Generated with [Claude Code](https://claude.com/claude-code)
```

- PRのbaseブランチは `main` とする
- `$ARGUMENTS` が指定された場合はそれをPRタイトルとして使用する

## gh コマンドの使い方

`gh pr edit` は Projects (classic) の非推奨警告により exit code 1 で失敗することがある。
そのため **PR の作成・更新には必ず `gh api` を使う**:

### PR作成
```bash
# まずリポジトリの owner/repo を取得
REPO=$(gh repo view --json nameWithOwner -q .nameWithOwner)

gh api repos/$REPO/pulls -X POST \
  -f title="<タイトル>" \
  -f body="<本文>" \
  -f head="<ブランチ名>" \
  -f base="main" \
  --jq .html_url
```

### PR更新
```bash
REPO=$(gh repo view --json nameWithOwner -q .nameWithOwner)
PR_NUMBER=<番号>

gh api repos/$REPO/pulls/$PR_NUMBER -X PATCH \
  -f title="<タイトル>" \
  -f body="<本文>" \
  --jq .html_url
```

`gh pr create` / `gh pr edit` は使わない。

## 注意

- `gh auth login` が完了していることを前提とする
- エラーが発生した場合はその内容をユーザーに伝える
