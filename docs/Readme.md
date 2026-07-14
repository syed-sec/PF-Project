# The Developer's Toolkit — Project Overview

> **A secure, menu-driven file encryption tool that gives every user their own private, password-protected workspace.**

| | |
|---|---|
| **Subject** | *Programming Fundamentals Theory* |
| **Program** | *BS Cyber Security* |
| **University** | *The Superior University, Lahore* |
| **Instructor** | *Prof. Zeeshan Mubeen* |
| **Academic Session** | *2025-2029* |
| **Project Type** | Group Project |
| **Language** | C++ |

## 1. Introduction

The Developer's Toolkit is a Windows console application written in C++. It lets a user create an account, log in securely, and then encrypt or decrypt text files. Every registered user is given a private folder of their own, so no two users can ever see or overwrite each other's files.

The whole project is written in first-year C++ — functions, loops, conditions, strings, arrays and file handling. It uses no classes, no pointers and no external libraries.

---

## 2. Problem Statement

On a shared computer — a university lab, a hostel room, a family PC — a plain text file offers no protection at all:

1. **Anyone can read it.** A `.txt` file opens instantly in Notepad.
2. **Files get mixed together.** Without accounts, everybody's work lands in the same folder.
3. **There is no concept of "my files".** With no login, ownership does not exist.

---

## 3. Objectives

- Practise C++ file handling, functions, loops and conditions on a real problem.
- Build a genuine login system where passwords are never stored in readable form.
- Guarantee that each user's data stays completely separate from everyone else's.
- Keep the code simple enough that any first-year student can read and maintain it.

---

## 4. The Solution

The Toolkit places a **login in front of the files**, **scrambles the file contents** so they cannot be read, and gives each user a **private workspace**:

```
Data/
├── Ali/
│   ├── Encrypted/     ← Ali's locked files
│   └── Decrypted/     ← Ali's unlocked files
└── Ahmed/
    ├── Encrypted/     ← completely separate from Ali
    └── Decrypted/
```

Because the save path is built from the **logged-in username**, Ali and Ahmed can both encrypt a file called `notes.txt` and the two results never collide.

---

## 5. Features

| Feature | What it does |
|---|---|
| **User Registration** | Creates an account with a unique username and a strong password. |
| **Secure Login** | Verifies credentials before granting any access. |
| **Password Hashing** | Scrambles passwords (FNV-1a + salt) so `users.txt` never holds a real password. |
| **Hidden Password Input** | Shows `*` instead of the typed characters. |
| **Password Strength Rules** | Requires 8+ chars with upper, lower, digit and symbol. |
| **Duplicate Username Detection** | Rejects a taken name and re-asks, without leaving the Sign Up screen. |
| **Attempt Limiting** | Allows 5 password attempts and shows how many remain. |
| **Account Lock** | Locks an account for 30 minutes after 5 failures. The lock is saved to disk, so restarting the program does not clear it. |
| **Automatic Data Folder** | Creates `Data/` on startup if it is missing. |
| **Per-User Workspace** | Creates `Data/<User>/Encrypted/` and `Decrypted/` on registration. |
| **File Encryption** | Shifts every byte by a secret key (Caesar cipher). |
| **File Decryption** | Reverses the shift to restore the original file exactly. |
| **Smart File Lookup** | If a filename is not found, also searches the user's own `Encrypted/` folder. |
| **Automatic File Naming** | Appends `_encrypted` / `_decrypted` and preserves the extension, so the original is never overwritten. |
| **Input Validation** | Catches letters typed at a number menu instead of looping forever. |
| **Clear Error & Success Messages** | Always reports what happened and where the output was saved. |
| **About Project Screen** | A built-in screen documenting the entire project. |

---

## 6. Technologies Used

| Technology | Why it is used | Where |
|---|---|---|
| **C++17** | The course language; fast and compiled. | Everywhere |
| **`<fstream>`** | Accounts and files must survive a restart. | `users.txt`, encrypt, decrypt |
| **`<filesystem>`** | Creates folders and checks whether a path exists. | `ensureDataFolder`, `createUserWorkspace` |
| **`<string>`** | Usernames, passwords, file names and paths are all text. | Everywhere |
| **`<vector>`** | Holds every account in memory while one lock value is updated. | `setUserLock` |
| **`<ctime>`** | Reads the clock to time the 30-minute lock. | `logIn` |
| **`<cctype>`** | Checks letters, digits and symbols. | `isStrongPassword` |
| **`<conio.h>`** | `_getch()` reads a key without showing it. | `readPassword` |
| **Functions** | One small function per job, each in its own folder. | The whole design |
| **Loops & Conditions** | Menus repeat; files are read byte by byte; every check is an `if`. | Everywhere |

---

## 7. Folder Structure

```
C++ Project V1/
├── Main/
│   └── main.cpp                      ← main(), Main Menu, prototype list
├── Functions/                        ← one folder per function (no .h files)
│   ├── SignUp/  LogIn/  AboutProject/
│   ├── EncryptTextFile/  DecryptTextFile/
│   ├── EnsureDataFolder/  CreateUserWorkspace/
│   └── ... (20 functions in total)
├── Complete Code/
│   └── CPP_Project_V1_Complete.cpp   ← the same program in ONE file
├── docs/
│   ├── Developer_Guide.md            ← deep guide for group members
│   └── Project_Overview.md           ← this file, for the teacher
├── Data/                             ← created automatically at startup
│   └── <Username>/Encrypted/, Decrypted/
├── users.txt                         ← username, password hash, lock time
└── build.bat                         ← compiles and runs the program
```

---

## 8. Project Workflow

```
Open Application
      ↓
"Data" folder created if missing
      ↓
Create Account  →  private workspace folders created
      ↓
Login  (5 attempts, then a 30-minute lock)
      ↓
Choose Operation  (Encrypt or Decrypt)
      ↓
Select File
      ↓
Encrypt / Decrypt  (byte-by-byte Caesar shift)
      ↓
Save Output into the user's OWN folder
      ↓
Logout
```

---

## 9. Important Functions

| Function | Purpose |
|---|---|
| `main()` | Shows the Main Menu and routes the user to Sign Up, Log In, About or Exit. |
| `signUp()` | Registers a new account, then builds its private workspace. |
| `logIn()` | Verifies the password, counts attempts, and applies the lock. |
| `hashPassword()` | Turns a password into an irreversible 16-character hash. |
| `isStrongPassword()` | Enforces the password strength rules. |
| `ensureDataFolder()` | Creates `Data/` at startup if it does not exist. |
| `createUserWorkspace()` | Creates `Data/<User>/Encrypted/` and `Decrypted/`. |
| `encryptTextFile()` | Shifts each byte forward by the key and saves to the user's folder. |
| `decryptTextFile()` | Shifts each byte back by the key and saves to the user's folder. |
| `toolkitMenu()` | The menu shown after a successful login. |
| `aboutProject()` | The built-in About Project screen. |
| `readMenuChoice()` | Reads a menu number safely, even if the user types a letter. |

---

## 10. Input and Output Process

**Input**
1. Menu numbers, read through `readMenuChoice()`, which rejects non-numbers safely.
2. Username, read with `cin >>`, then the input buffer is cleaned.
3. Password, read one key at a time by `_getch()` and displayed as `*`.
4. A file name, read with `cin >>`.

**Output**
1. Screen messages: headers, menus, success (`✅`), errors (`❌`), information (`ℹ️`).
2. `users.txt` — one line per account: `username  passwordHash  lockUntil`.
3. Encrypted files → `Data/<User>/Encrypted/<name>_encrypted.txt`
4. Decrypted files → `Data/<User>/Decrypted/<name>_decrypted.txt`

---

## 11. Advantages

- **Privacy by design** — the save path is built from the logged-in username, so users physically cannot reach each other's folders through the program.
- **Passwords are never stored** — only a salted, one-way hash is written to disk.
- **The lock survives a restart** — it is saved in `users.txt`, not just held in memory.
- **The original file is never destroyed** — output always gets a new name.
- **Lightweight** — a single `.exe`, with no database, installer or internet connection.
- **Fast** — the cipher costs one addition per byte.
- **Easy to maintain** — one function, one folder, one job.
- **Expandable** — a new tool needs one new folder and one new menu line.
- **Beginner-friendly** — no classes, no pointers, and a comment on every function.

---

## 12. Limitations

We state these honestly rather than overclaim:

- **The Caesar cipher is not real security.** A fixed byte shift can be broken by frequency analysis in minutes. It is chosen for *teaching value*, not strength. AES would be the real answer.
- **The secret key is hard-coded** (`5`) and identical for every user.
- **FNV-1a is not a password hash.** Real systems use bcrypt or Argon2, which are deliberately slow to resist brute force.
- **`users.txt` is plain text.** The hashes are safe-ish, but the usernames are visible.
- **Windows only.** `system("cls")` and `_getch()` are Windows-specific.
- **No password recovery.** A forgotten password means the account is unreachable.
- **File-level protection only.** Anyone with access to the disk can still delete or copy a `Data/` folder from outside the program.

---

## 13. Future Scope

Database integration (SQLite) · Cloud storage · **AES encryption** · Password recovery · User profiles · File search · Admin panel · Activity logs · Backup & restore · Multi-language (Urdu/English) · Dark/light console themes · Cross-platform support for Linux and macOS.

---

## 14. Team Members

| Role | Name | Roll Number |
|---|---|---|
| **Group Leader** | Syed Muhammad Shah | SU92-BSCBM-F25 |
| Member 2 | Syed Muhammad Shah | SU92-BSCBM-F25 |
| Member 3 | Syed Muhammad Shah | SU92-BSCBM-F25 |
| Member 4 | Syed Muhammad Shah | SU92-BSCBM-F25 |
| Member 5 | Syed Muhammad Shah | SU92-BSCBM-F25 |

> ℹ️ Members 2–5 currently repeat the leader's details. Replace them with each member's real name and roll number before submitting.

---

## 15. Conclusion

The Developer's Toolkit shows that the core ideas behind real security software — authentication, hashing, attempt limiting, account lockout, and per-user data isolation — can be built entirely from first-year C++.

The cipher itself is deliberately simple, and we are clear about that. What the project demonstrates is the *architecture* around it: a login that cannot be bypassed, passwords that are never stored in readable form, a lock that survives a restart, and a folder layout in which one user's files can never reach another user's hands. Swapping the Caesar cipher for AES would not require redesigning any of that — which is exactly the point.

---

## How to Build and Run

```
Double-click build.bat
```

It compiles every `.cpp` under `Main/` and `Functions/` and launches the program. Or compile the single-file version by hand:

```bash
g++ -std=c++17 -Wall "Complete Code/CPP_Project_V1_Complete.cpp" -o Toolkit.exe
```

`-std=c++17` is **required** — the project uses `<filesystem>`.
