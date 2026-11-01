# SPL Lab 3, variant 15

The lexical analyzers recognize the keywords `isalpha` and `isdigit`, and two-digit decimal numbers without a leading zero. Both analyzers write tokens as `<line, type, value>`.

## Build and run

Open `SPL_Lab3.sln` in Rider or Visual Studio and build in `Debug x64`.

The `Cpp` project reads `input.txt` and writes `output_cpp.txt`. The `Flex` project regenerates `Flex/scanner.cpp` from `Flex/scanner.l` before building, then writes `output_flex.txt`.

To check both results, run `build_and_check.ps1` in Developer PowerShell for Visual Studio. It builds and runs both projects, then compares their output files.

## Files

- `input.txt` — lexer test input.
- `output_cpp.txt`, `output_flex.txt` — results from both analyzers.
- `Cpp/main.cpp` — table-driven analyzer.
- `Flex/scanner.l` — Flex rules.
- `automaton/dfa.png` — state diagram.
- `automaton/transition_table.csv` — transition table.
- `tools/win_flex.exe` — scanner generator used by the Flex project.
- `tools/LICENSE_FLEX.txt` — Flex license.
