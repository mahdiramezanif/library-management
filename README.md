# Library Management System (C++)

A console-based C++ library-management exercise using **text files for storage**. The source contains separate flows for library managers and registered members.

## Features found in the code
- Manager login and book addition/editing
- Member signup and login
- Book listing and searching by title or author
- Borrowed-book records
- Membership renewal and fine calculations
- Local persistence through `.txt` files

## Files

```text
library-management.cpp   # Main application source
books.txt                # Local catalog data
number_of_members.txt    # Member count
1.txt, 2.txt, 3.txt      # Example/persistent text records
```

## Build and run

The code uses **Windows-specific** APIs (`conio.h` and `system("cls")`), so a Windows C++ toolchain is the most natural environment. From the directory containing the text files:

```bash
g++ -std=c++11 library-management.cpp -o library-management.exe
.\library-management.exe
```

The command assumes a Windows compiler with `conio.h` available. Cross-platform support requires code changes.

## Security and limitations
- The sample manager credentials are hard-coded in the C++ source; they are for demonstration only.
- Local plaintext files are used instead of a database and may contain user input; do not use the program for real personal data.
- Back up `.txt` files before experimenting because program actions may rewrite them.
- This is an educational console app, not a multiuser library service.
