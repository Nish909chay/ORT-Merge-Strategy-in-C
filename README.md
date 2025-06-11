# ORT Merge Strategy 

![My Image](ort.png)

This project is a C implementation of Git's **ORT (Optimized Recursive Three-Way)** merge strategy. It simulates how Git handles file merges during a `git merge`, resolving differences between a `base`, `ours`, and `theirs` version of a directory tree.

---

## 🚀 What is ORT Strategy?

ORT (Optimized Recursive Three-way) is Git's default and most efficient strategy for merging changes across three versions of a file/directory:

- `base`: Original common ancestor
- `ours`: Current branch’s version
- `theirs`: Merging branch’s version

It compares content and file existence across all three trees, choosing the most appropriate version or marking conflicts when required.

---

## 🛠️ How This Implementation Works

### ✅ Step-by-step:

1. **Reads the base, ours, and theirs directories** recursively into tree structures.
2. **Compares each file** by name across the three trees.
3. **Applies ORT logic**:
   - If both `ours` and `theirs` match: pick either.
   - If one side changed and the other didn't: pick the changed version.
   - If both changed differently: mark as **conflict**.
4. **Prints merged tree** to console.
5. **Writes merged output** to the `merged_output/` directory.

---

## ⚙️ Building and Running

### ✅ Requirements:
- GCC installed (MinGW or similar for Windows)
- Command Line (PowerShell or CMD)

### 🔧 Compile:
      gcc main.c tree.c file_utils.c -o main.exe
### ▶ Run:
      ./main.exe
