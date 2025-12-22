# Code Formatting

ArachneOS uses **clang-format** for consistent code style.

## Quick Commands

```bash
# Check formatting
make format-check

# Fix formatting
make format

# Format single file
clang-format -i src/path/to/file.cpp
```

## Rules

- **Style**: Google with 4-space indent
- **Line length**: 120 chars
- **Pointers**: `int* ptr` (left-aligned)
- **Braces**: Linux style (attached for functions/classes, new line for control structures)

## Editor Setup

**VS Code**: Install C/C++ extension, enable format-on-save  
**Vim**: `:setlocal formatprg=clang-format\ -style=file`  
**CLion**: Settings → Code Style → Set from clang-format

See `.clang-format` in project root for full configuration.
