# Network Device Registration System

A command-line management system written in C to handle, sort, and analyze network device registration records.

## About
This repository contains a **university course assignment (school project)** designed to practice structured data, file operations, and dynamic memory management in C.

## Features
- **Dynamic Memory Allocation:** Uses `malloc` and `realloc` to dynamically store and expand data entries.
- **File Processing:** Reads existing registration data from a text file and appends new records directly to it.
- **Data Operations:** Features built-in status statistics and sorting options (by Year or Surname).
- **Input Validation:** Validates status inputs and ensures correct MAC address formats during runtime.

## How to Run (Important)
This program requires a text file as a **command-line argument** to load the initial database. 

1. Download or copy the `main.c` file.
2. Create a sample text file in the same directory with space-separated registration data.
3. Compile the code:
   ```bash
   gcc main.c -o registration_system
