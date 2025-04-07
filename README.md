# 📚 Antique Collection Sorting and Rarity Analysis – BLG335E Project 2

A C++ project that organizes a large collection of historical artifacts by age and rarity using Counting Sort, Heap Sort, and a custom rarity score based on local similarity and global diversity. Designed for efficient data processing and insightful analysis in exhibition planning.

---

## 📋 Project Overview

Eleanor, a passionate antique collector, needs help organizing her massive and diverse artifact collection for an upcoming international exhibition. The collection must be sorted based on both **age** and **rarity**, highlighting ancient and unique items.

This project involves:

- **Sorting by Age**: Using Counting Sort to efficiently organize artifacts from oldest to newest.
- **Rarity Score Calculation**: Based on the item's similarity in type and origin within an age window.
- **Sorting by Rarity**: Using Heap Sort to emphasize unique and rare items in the display.

---

## 🚀 Features

- 🕰️ **Counting Sort** – Fast sorting by age (`O(n + k)`)
- 🎯 **Heap Sort** – Reliable sorting by rarity score (`O(n log n)`)
- 🔍 **Rarity Scoring** – Calculates a rarity score per item using age-based windows
- 📈 **Performance Benchmarking** – Execution time analysis for multiple dataset sizes
- 🧪 **Testing Support** – Includes test files and validation I/O binary
- ⚙️ **Makefile-based Build System**

---

## 📁 Folder Structure

## 📁 Folder Structure

- `bin/` – Compiled executables
- `data/` – Input and output CSV files
- `include/` – Header files
- `lib/` – Optional libraries (e.g., io_op)
- `src/` – C++ source files (main.cpp, sort.cpp, etc.)
- `tests/` – Unit tests and sample test datasets
- `LICENSE` – License information
- `Makefile` – Compilation and run automation
- `README.md` – This file
