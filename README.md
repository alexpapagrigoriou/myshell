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

## Third-Party Libraries

| Library | Repository | License |
| --- | --- | --- |
| incbin | [GitHub](https://github.com/graphitemaster/incbin) | [Unlicense](third_party/incbin/UNLICENSE) |

## License

MIT. See [LICENSE](LICENSE).
