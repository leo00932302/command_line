# Shell 基本設計理念

## 目前可用命令

- `help`
- `exit`

## 實現方式

### Global Variables

```c
char *shell_str[];
int (*shell_func[])(char **);
```

### Main Function

```text
loop
  ↓
read_line
  ↓
split_line
  ↓
execute
  ↓
loop
```

## read_line

讀取使用者輸入的一整行字串。

## split_line

將輸入依空白切割成 `char **args`。

## execute

判斷是否為內建命令，若是則呼叫對應函式，否則輸出錯誤訊息。
