# ORT Merge Strategy in C

## Project Overview
This project implements a simplified version of Git’s ORT (Optimized Recursive Three-way) merge strategy in C. It simulates how Git recursively merges directory trees, handling both auto-merges and conflicts, using custom tree-based data structures and file I/O routines.

- **Directory Trees:** Builds in-memory trees from three directories: `base/`, `ours/`, and `theirs/`, each representing a different version of a project.
- **Merging:** Merges these trees into a unified `merged` tree, applying the ORT strategy to resolve changes and conflicts.
- **Output:** Prints the merged tree and writes the result to `merged_output/` on disk, including conflict markers when necessary.

## Features
- **Recursive Directory Parsing:** Reads entire directory structures and constructs a tree of files and folders.
- **TreeNode Structure:** Each node represents either a file or directory, supporting arbitrary nesting.
- **Custom Merge Logic:**
  - If `ours` and `theirs` match, the file is auto-merged.
  - If only `ours` changed, the merged result uses `ours`.
  - If both changed, a conflict is detected and conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`) are written, along with `AUTO-MERGE FAILED`.
- **File I/O:** The merged tree is written to disk under `merged_output/`, recreating the directory structure and file contents.
- **Verbose Debugging:** Prints detailed logs for directory traversal, file reading/writing, and merge operations.

## Project Structure
```
C-implementation/
├── main.c            # Builds and merges trees, handles output
├── tree.c            # Tree creation, merging, helpers
├── tree.h            # Structs and function declarations
├── file_utils.c      # File reading and writing logic
├── file_utils.h
├── base/             # Base version of files
│   ├── a.txt
│   └── b.txt
├── ours/             # Our version (simulates current dev)
│   └── a.txt
├── theirs/           # Their version (simulates incoming change)
│   └── b.txt
└── merged_output/    # Auto-created, stores final merged result
```

## Implementation Notes
- Written and tested on **Windows** using PowerShell and GCC (MinGW).
- Uses `_mkdir` for directory creation (with cross-platform macro for portability).
- Avoids name conflicts with system macros like `MAX_PATH`.
- Includes verbose debug logs: "Opening dir", "Found entry", "Wrote file", etc.
- Ensures conflict markers are cleanly formatted in merged files for easy manual resolution.

## Build & Run
```bash
gcc main.c tree.c file_utils.c -o main.exe
./main.exe
```

### Sample Output
```
Dir : merged
  File: a.txt | Content: AUTO-MERGE FAILED
<<<<<<< OURS
edited by us
=======
edited by them
>>>>>>> THEIRS
```

## How to Simulate Merge Scenarios
To test different merge outcomes:
1. **Edit files in `base/`, `ours/`, and `theirs/`**:
   - Change file contents to simulate different changes by you and others.
   - For example, edit `ours/a.txt` and `theirs/a.txt` differently to trigger a conflict.
2. **Rebuild and rerun:**
   - Run the build and execute the program again to see the new merged result in `merged_output/`.

## Attribution
Inspired by Git’s recursive and ORT merge strategies. This project was built step-by-step, emphasizing tree construction, clean logic separation (`tree.c`, `file_utils.c`), and extensive debugging/testing.

---
