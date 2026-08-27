# MyShell

## Requirements

- GCC or Clang
- GNU Make

## Building

### Build

```bash
make
```

Output binary: `bin/myshell`.

### Run

```bash
make run
```

Builds and runs the binary.

### Debug with GDB

```bash
make gdb
```

Builds the binary and launches it under `gdb`.

### Clean

```bash
make clean
```

Removes all generated build artifacts (`build/` and `bin/`).

## Embedded Projects

MyShell embeds several of my own projects as built-in commands.

| Command | Project | Repository | Description |
| --- | --- | --- | --- |
| `vip` [filename] | vip | [GitHub](https://github.com/alexpapagrigoriou/vip) | A modal, terminal-based text editor. |
| `bf` <filename> | brainfuck_compiler | [GitHub](https://github.com/alexpapagrigoriou/brainfuck_compiler) | A Brainfuck Compiler. |
| `bfi` [filename] | brainfuck_interpreter | [GitHub](https://github.com/alexpapagrigoriou/brainfuck_interpreter) | A Brainfuck Interpreter. |
| `minesweeper` | minesweeper | [GitHub](https://github.com/alexpapagrigoriou/minesweeper) | A terminal-based Minesweeper implementation. |

## Third-Party Libraries

| Library | Repository | License |
| --- | --- | --- |
| incbin | [GitHub](https://github.com/graphitemaster/incbin) | [Unlicense](third_party/incbin/UNLICENSE) |

## License

MIT. See [LICENSE](LICENSE).
