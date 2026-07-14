# Developer Guide — The Developer's Toolkit

**Audience: our group members only.** This is the deep guide. If a new member joins tomorrow, this document should be enough for them to understand, run, and safely change the project without breaking it.

For the short version to hand to the teacher, read `Project_Overview.md` instead.

---

## Table of Contents

1. [Project Architecture](#1-project-architecture)
2. [Folder Purpose](#2-folder-purpose)
3. [Every File and What It Does](#3-every-file-and-what-it-does)
4. [Every Function Explained](#4-every-function-explained)
5. [Every Important Variable](#5-every-important-variable)
6. [Every Menu](#6-every-menu)
7. [Every Loop](#7-every-loop)
8. [Every Important Condition](#8-every-important-condition)
9. [Data Structures](#9-data-structures)
10. [The Two Algorithms](#10-the-two-algorithms)
11. [Complete Project Flow](#11-complete-project-flow)
12. [Data Flow](#12-data-flow)
13. [The users.txt File Format](#13-the-userstxt-file-format)
14. [Input and Output](#14-input-and-output)
15. [Error Handling](#15-error-handling)
16. [Validation](#16-validation)
17. [Naming Convention](#17-naming-convention)
18. [Coding Style](#18-coding-style)
19. [Future Maintenance](#19-future-maintenance)
20. [Possible Improvements](#20-possible-improvements)
21. [Frequently Asked Questions](#21-frequently-asked-questions)

---

## 1. Project Architecture

The project is deliberately built with **no header (`.h`) files**. This is unusual for professional C++, but it is a conscious teaching choice, and you need to understand how it works before you change anything.

Normally you would write a `.h` file to tell the compiler that a function exists. Instead, we write a **prototype** — a one-line preview of the function — directly at the top of any `.cpp` file that calls it.

```cpp
// At the top of SignUp.cpp:
bool usernameExists(string username);   // ← a prototype, not the real code

void signUp()
{
    ...
    if (!usernameExists(username))      // ← now the compiler allows this call
    ...
}
```

The real body of `usernameExists()` lives in `Functions/UsernameExists/UsernameExists.cpp`. At **compile time** the compiler only needs the prototype. At **link time**, the linker finds the real function in the other file and connects them.

**This is the single most important thing to understand about the project.**

### ⚠️ The rule this creates

> If you change a function's **signature** (its name, its return type, or its parameters), you must update the prototype **everywhere** it appears — in `Main/main.cpp` and in every `.cpp` file that calls it.

If you forget, you get an "undefined reference" error from the linker. That error means: *"you promised me this function exists, but I cannot find it."*

Example: when we added the `currentUser` parameter to `encryptTextFile()`, we had to update the prototype in **two** places (`main.cpp` and `ToolkitMenu.cpp`), not just the definition.

### The two copies of the program ⚠️

The exact same program exists **twice**:

1. **`Main/` + `Functions/`** — the multi-file version. **This is the real one.** Edit this.
2. **`Complete Code/CPP_Project_V1_Complete.cpp`** — the same program merged into one file, for easy reading and submission.

**Nothing keeps them in sync automatically.** If you change one, you must make the same change in the other, or they will drift apart. Always change the `Functions/` version first, then mirror it.

---

## 2. Folder Purpose

| Folder | Why it exists | What is inside |
|---|---|---|
| `Main/` | Holds the program's entry point. | `main.cpp` — the Main Menu, and the master prototype list. |
| `Functions/` | One folder per function. Keeping each function alone makes it easy to find and safe to change. | 20 sub-folders, each with one `.cpp` file. |
| `Complete Code/` | The whole program in one file, so it can be read top-to-bottom or submitted as a single listing. | `CPP_Project_V1_Complete.cpp` |
| `docs/` | Written documentation. | This guide, and `Project_Overview.md`. |
| `Data/` | **Created automatically at runtime.** The root of all user data. | One sub-folder per registered user. |
| `Data/<User>/Encrypted/` | Keeps a user's locked files in one predictable place. | `*_encrypted.txt` |
| `Data/<User>/Decrypted/` | Keeps unlocked files away from the locked ones, so you never accidentally re-encrypt an encrypted file. | `*_decrypted.txt` |
| `.vscode/` | Editor settings. Not part of the program. | IntelliSense config. |

`users.txt` and `Data/` are created **at runtime**, next to the `.exe`. They are not in the repository until someone runs the program.

---

## 3. Every File and What It Does

### `Main/main.cpp`
Holds `main()` and the **master prototype list** of every function in the project. Treat this list as the project's index — when you add a function, add its prototype here too, even if `main()` does not call it.

`main()` does two things:
1. Calls `ensureDataFolder()` **once**, before the menu loop.
2. Runs the Main Menu loop forever until the user picks Exit.

### The 20 files in `Functions/`

| File | Function it defines | Job |
|---|---|---|
| `ClearScreen.cpp` | `clearScreen()` | Wipes the console. |
| `WaitForUser.cpp` | `waitForUser()` | Pauses until Enter is pressed. |
| `ClearInputLine.cpp` | `clearInputLine()` | Removes leftovers from the input buffer. |
| `PrintHeader.cpp` | `printHeader()` | Prints the title bar on every screen. |
| `PrintLine.cpp` | `printLine()` | Prints the thin divider above a menu prompt. |
| `ReadMenuChoice.cpp` | `readMenuChoice()` | Reads a menu number safely. |
| `ReadPassword.cpp` | `readPassword()` | Reads a password, showing `*`. |
| `IsStrongPassword.cpp` | `isStrongPassword()` | Enforces the strength rules. |
| `HashPassword.cpp` | `hashPassword()` | Scrambles a password (one-way). |
| `UsernameExists.cpp` | `usernameExists()` | Checks whether a name is taken. |
| `IsValidUsername.cpp` | `isValidUsername()` | Checks a name is **safe as a folder name**. |
| `GetSecretKey.cpp` | `getSecretKey()` | The one shared cipher key. |
| `GetUserRecord.cpp` | `getUserRecord()` | Loads one account from `users.txt`. |
| `SetUserLock.cpp` | `setUserLock()` | Saves a new lock time for one account. |
| `EnsureDataFolder.cpp` | `ensureDataFolder()` | Creates `Data/` at startup. |
| `CreateUserWorkspace.cpp` | `createUserWorkspace()` | Creates a new user's two folders. |
| `SignUp.cpp` | `signUp()` | The whole registration screen. |
| `LogIn.cpp` | `logIn()` | The whole login screen, attempts and lock. |
| `MakeEncryptedFileName.cpp` | `makeEncryptedFileName()` | `notes.txt` → `notes_encrypted.txt` |
| `MakeDecryptedFileName.cpp` | `makeDecryptedFileName()` | `notes_encrypted.txt` → `notes_decrypted.txt` |
| `EncryptTextFile.cpp` | `encryptTextFile()` | The encryption screen. |
| `DecryptTextFile.cpp` | `decryptTextFile()` | The decryption screen. |
| `ToolkitMenu.cpp` | `toolkitMenu()` | The menu shown after login. |
| `AboutProject.cpp` | `aboutProject()` + 9 helpers | The About Project screen. |

---

## 4. Every Function Explained

### `main()` — *Main/main.cpp*
- **Takes:** nothing. **Returns:** `0`.
- Calls `ensureDataFolder()` once, then loops the Main Menu until Exit.
- Routes: `1` → `signUp()`, `2` → `logIn()`, `3` → `aboutProject()`, `4` → break.
- If login succeeds, it calls `toolkitMenu(loggedInUser)`. When that returns, the user has logged out and lands back on the Main Menu.

### `clearScreen()`
Runs `system("cls")`. **Windows only** — on Linux the screen simply will not clear, but nothing breaks.

### `waitForUser()`
Prints "Press Enter to continue" and calls `getline(cin, dummyLine)`.

> ⚠️ This only works because **every** `cin >> x` in the project is followed by `clearInputLine()`. If you add a `cin >>` and forget that call, the leftover Enter key will be swallowed by the next `getline()`, and the pause will be **skipped**. This is the classic bug in this project — do not cause it.

### `clearInputLine()`
`cin.ignore(numeric_limits<streamsize>::max(), '\n')` — throws away everything up to and including the next newline.

### `printHeader(title)` / `printLine()`
Looks-only helpers. Every screen calls them so all screens look identical. To restyle the whole app, change these two functions and nothing else.

### `readMenuChoice()` → `int`
The guard against infinite menu loops.

If the user types a letter, `cin >> choice` **fails** and the bad text stays stuck in the buffer. Without a fix, the menu would re-read the same bad text forever — an infinite loop that pegs the CPU.

```cpp
if (!(cin >> choice))
{
    cin.clear();        // 1. clear the error flag so cin works again
    clearInputLine();   // 2. throw away the bad text
    return -1;          // 3. -1 means "invalid choice"
}
```

**Both `cin.clear()` and `clearInputLine()` are required.** Removing either one reintroduces the infinite loop.

### `readPassword()` → `string`
Reads keys one at a time with `_getch()` (from `<conio.h>`), which does **not** echo them. Prints `*` instead.
- `13` = Enter → finish. `8` = Backspace → remove last char and erase the `*` with `"\b \b"`.
- `0` or `224` = an arrow/function key, which sends **two** codes; we read and discard the second so it does not become a `*`.

> ⚠️ `_getch()` reads the console **directly** and ignores piped input. This means the login screen **cannot be tested with a script**. To test the rest of the program automatically, compile `Functions/**` with a temporary `main()` that calls the functions directly.

### `isStrongPassword(password)` → `bool`
Requires length ≥ 8 **and** an uppercase, a lowercase, a digit, and a special character. "Special" is defined as *anything that is not a letter, not a digit, and not whitespace*.

Note the `else if` chain: a character is counted as exactly one category. And note `size_t i` — using `int` here would produce a signed/unsigned warning against `password.length()`.

### `hashPassword(username, password)` → `string`
A **one-way** scramble. You can turn a password into a hash, but you cannot turn a hash back into a password. That is why we can safely store it.

1. **Salt:** `saltedText = username + "$" + password`. Mixing the username in means two users with the same password get *different* hashes.
2. **FNV-1a:** start at `1469598103934665603`, then for each byte: XOR it in, multiply by the prime `1099511628211`. Overflow is *expected and fine* — that is the scrambling.
3. **Hex:** convert the 64-bit number into 16 hex characters, so it stores neatly as text.

> Not production-grade. Real systems use bcrypt/Argon2, which are deliberately **slow** to resist brute force. Ours is fast, which is a weakness. We are honest about this in `Project_Overview.md`.

### `usernameExists(username)` → `bool`
Reads `users.txt` line by line looking for a match. Returns `false` if the file does not exist yet (an unopened `ifstream` simply reads nothing) — which is exactly what we want for the very first user.

### `getUserRecord(username, &hashOut, &lockUntilOut)` → `bool`
Finds one account and hands back **two** values through **reference parameters** (the `&`). A function can only `return` one thing, so `bool` reports "found or not", and the `&` parameters carry the data back to the caller.

### `setUserLock(username, lockUntil)`
You cannot easily edit one line in the middle of a text file. So we do it the simple, beginner way:
1. Read **all** accounts into three `vector`s.
2. While reading, swap in the new lock time for the matching user.
3. Write **all** accounts back out, overwriting the file.

> ⚠️ Step 3 opens `ofstream("users.txt")` **without** `ios::app`, so it **truncates the file**. That is intentional — we are rewriting it completely. If the program were killed between step 2 and step 3, `users.txt` would be lost. A safer version would write to a temp file and rename it. Worth knowing.

### `ensureDataFolder()`
If `Data` does not exist: print the messages, create it, and pause. If it *does* exist: **do nothing and print nothing**, so the user is not nagged on every launch.

### `createUserWorkspace(username)`
Called by `signUp()` **only after** the account has been successfully written.
- If `Data/<user>` already exists → print `ℹ️ Existing workspace found.` and **return without touching it** (it may hold real files).
- Otherwise → `create_directories()` builds the whole path in one call, including any missing parent folders.

### `signUp()`
1. **Username loop** — repeats until the name is free, or the user types `cancel`. It deliberately does **not** return to the Main Menu on a taken name.
2. **Password loop** — repeats until `isStrongPassword()` passes.
3. Opens `users.txt` with `ios::app` (**append** — this is what stops existing accounts being erased) and checks `is_open()` before claiming success.
4. Writes `username hash 0`. The `0` is the lock time, meaning "not locked".
5. Calls `createUserWorkspace(username)`.

### `logIn(&loggedInUser)` → `bool`
1. Reads the username, and calls `getUserRecord()`. If not found → generic error. **The message is deliberately vague** ("Incorrect username or password") so an attacker cannot discover which usernames exist.
2. Reads the clock: `now = time(nullptr)`.
3. **Lock check comes first.** If `lockUntil > now`, login is refused *even if the password is correct*.
4. Loops up to 5 attempts, showing how many remain.
5. On success: sets `loggedInUser` (a reference parameter) and returns `true`.
6. After 5 failures: `setUserLock(username, now + 30*60)` and returns `false`.

### `makeEncryptedFileName(name)` → `string`
Finds the **last** `.` (searching backwards), splits into base + extension, returns `base + "_encrypted" + ext`. With no dot, it just appends.

### `makeDecryptedFileName(name)` → `string`
Searches for the literal text `"_encrypted"` with a manual character-by-character loop, and replaces it with `"_decrypted"`, keeping the extension. If `"_encrypted"` is not found, it appends `"_decrypted"` to the end.

### `encryptTextFile(currentUser)` / `decryptTextFile(currentUser)`
Both follow the same careful sequence:
1. Read the file name.
2. Build `outputFolder = "Data/" + currentUser + "/Encrypted"` (or `Decrypted`). **This is what guarantees users never mix.**
3. `create_directories(outputFolder)` — silently makes the folder if missing, so old accounts created before this feature existed still work.
4. `filesystem::path(name).filename()` — strips any folder the user typed, so `C:\docs\a.txt` still saves as `a_encrypted.txt` **inside the user's own folder**.
5. **Open the input file FIRST and check it.** ⚠️ This ordering is deliberate: creating an `ofstream` immediately makes an empty file on disk. If we opened the output first and *then* found the input was missing, we would leave a stray empty file behind.
6. Loop `inputFile.get(currentChar)` — reads **every** byte, including spaces and newlines.
7. Shift the byte and write it.

`decryptTextFile()` has one extra step: if the typed name is not found as-is, it also looks in `Data/<user>/Encrypted/`, so the user can type just `notes_encrypted.txt`.

### `toolkitMenu(currentUser)`
The post-login menu. Passes `currentUser` down into encrypt/decrypt. Option `3` breaks the loop — and *returning from this function is what "logging out" actually means*.

### `aboutProject()` and its 9 helpers
A read-only screen with its own sub-menu. It only ever prints text — it never opens, writes or deletes a file — so it **cannot corrupt any data**. Safe to edit freely.

---

## 5. Every Important Variable

| Variable | Where | Type | Purpose |
|---|---|---|---|
| `choice` | every menu | `int` | The number the user picked. `-1` = invalid. |
| `loggedInUser` | `main()` | `string` | The name of whoever is logged in. **The most important variable in the project** — every save path is built from it. |
| `currentUser` | toolkit/encrypt/decrypt | `string` | The same name, passed down the call chain. |
| `secretKey` | encrypt/decrypt | `int` = `5` | The Caesar shift. ⚠️ **Must be identical in both files** or decryption produces garbage. |
| `lockUntil` | `logIn` | `long long` | Unix time when the lock expires. `0` = not locked. |
| `now` | `logIn` | `long long` | The current time in seconds. |
| `attempts` / `maxAttempts` | `logIn` | `int` | Failed tries, and the limit of `5`. |
| `hashValue` | `hashPassword` | `unsigned long long` | The rolling FNV-1a hash. **Unsigned on purpose** — overflow is defined behaviour for unsigned types, but is *undefined* for signed. |
| `hasData` | encrypt/decrypt | `bool` | Whether the input file had any content. |
| `outputFolder` | encrypt/decrypt | `string` | The user's private destination folder. |
| `strongEnough` | `signUp` | `bool` | Controls the password retry loop. |

---

## 6. Every Menu

| Menu | Where | Options | Exit condition |
|---|---|---|---|
| **Main Menu** | `main()` | 1 Sign Up · 2 Log In · 3 About · 4 Exit | `4` → `break` → `return 0` |
| **Toolkit Menu** | `toolkitMenu()` | 1 Encrypt · 2 Decrypt · 3 Log Out | `3` → `break` → return to Main Menu |
| **About Menu** | `aboutProject()` | 1–8 sections · 9 Back | `9` → `break` → return to Main Menu |

Every menu follows the identical safe pattern:

```cpp
while (true)
{
    clearScreen();
    printHeader("...");
    // ... print options ...
    printLine();
    choice = readMenuChoice();

    if (choice == 1) { ... }
    else if (choice == 2) { ... }
    else if (choice == N) { break; }        // ← the ONLY way out
    else { /* invalid */ waitForUser(); }   // ← invalid never loops silently
}
```

**Never write a menu without a `break` branch and an `else` branch.** The `break` is the exit; the `else` stops a bad key press from spinning silently.

---

## 7. Every Loop

| Loop | File | Type | How it ends |
|---|---|---|---|
| Main Menu | `main.cpp` | `while (true)` | `break` on Exit |
| Toolkit Menu | `ToolkitMenu.cpp` | `while (true)` | `break` on Log Out |
| About Menu | `AboutProject.cpp` | `while (true)` | `break` on Back |
| Username retry | `SignUp.cpp` | `while (true)` | `break` when free, or `return` on `cancel` |
| Password retry | `SignUp.cpp` | `while (!strongEnough)` | ends when the password passes |
| Login attempts | `LogIn.cpp` | `while (attempts < maxAttempts)` | `return true`, or 5 failures |
| Password keys | `ReadPassword.cpp` | `while (true)` | `break` on Enter (key 13) |
| Read file bytes | encrypt/decrypt | `while (inputFile.get(c))` | ends at end-of-file |
| Read accounts | users files | `while (file >> a >> b >> c)` | ends at end-of-file |
| Hash bytes | `HashPassword.cpp` | `for` | fixed length |
| Find the dot | `MakeEncryptedFileName.cpp` | `for` (backwards) | fixed length |

**Every `while (true)` in this project has exactly one `break`.** If you add a loop, make sure you can point to the line that ends it.

The three loops that could hang if mishandled are the menus — and `readMenuChoice()` is the single thing protecting all three. Do not "simplify" it away.

---

## 8. Every Important Condition

| Condition | Where | Why it matters |
|---|---|---|
| `if (!(cin >> choice))` | `readMenuChoice` | Catches a letter typed at a number menu. **Prevents an infinite loop.** |
| `if (!file.is_open())` | `signUp`, encrypt, decrypt | Never claim success when the write actually failed. |
| `if (lockUntil > now)` | `logIn` | Refuses login **even with the right password**. Checked *before* the password. |
| `if (!usernameExists(...))` | `signUp` | The only thing preventing two users from sharing a folder. |
| `if (filesystem::exists(userFolder))` | `createUserWorkspace` | Protects an existing workspace from being touched. |
| `if (!filesystem::exists(inputFileName))` | `decryptTextFile` | Triggers the fallback search in the user's own folder. |
| `if (password.length() < 8)` | `isStrongPassword` | The fast reject before the character scan. |
| `if (hasData)` | encrypt/decrypt | Distinguishes "worked" from "the file was empty". |
| `if (dotPosition != -1)` | `makeEncryptedFileName` | Handles a file name with no extension. |
| `if (ch == 0 \|\| ch == 224)` | `readPassword` | Swallows the 2nd byte of an arrow key. |

---

## 9. Data Structures

The project is deliberately simple. There are only three:

1. **`string`** — every username, password, hash, file name and path. Paths are built by plain string concatenation: `"Data/" + currentUser + "/Encrypted"`.
2. **`vector<string>` / `vector<long long>`** — used **only** in `setUserLock()`, as three parallel vectors (`usernames`, `hashes`, `locks`). Index `i` in all three refers to the same account. This is the simplest way to rewrite one line of a text file.
3. **The text file itself** (`users.txt`) — our "database". One line = one record, three fields separated by spaces.

There are no classes, no structs, no pointers, no maps. That is on purpose.

---

## 10. The Two Algorithms

### A. The Caesar Cipher (encryption)

**Encrypt:** `shifted = (original + 5) % 256`
**Decrypt:** `original = (shifted - 5 + 256) % 256`

Two details that matter:

- **Why `unsigned char`?** A plain `char` is *signed* on most compilers, so bytes above 127 become negative and the arithmetic breaks. Casting to `unsigned char` guarantees a clean 0–255 range.
- **Why `+ 256` when decrypting?** If the byte is smaller than the key (say `2 - 5`), the result is negative, and in C++ `-3 % 256` is `-3`, not `253`. Adding 256 first keeps it positive so the shift reverses **exactly**.

Because we shift **every byte** — including spaces and newlines — the round trip is lossless. We verified this: encrypting and then decrypting returns a byte-identical file.

**Security reality:** a fixed shift is broken by frequency analysis in minutes. This is a *teaching* cipher.

### B. FNV-1a (password hashing)

```
hash = 14695981039346656037           (the offset basis)
for each byte b:
    hash = hash XOR b
    hash = hash * 1099511628211       (the FNV prime)
```

One-way: easy forward, effectively impossible backwards. Overflow is intentional and is where the scrambling comes from.

---

## 11. Complete Project Flow

```
main()
 │
 ├── ensureDataFolder()          creates Data/ if missing (once, at startup)
 │
 └── Main Menu loop ─────────────────────────────────────────┐
      │                                                      │
      ├─ 1 → signUp()                                        │
      │      ├── loop until username is free (or 'cancel')   │
      │      ├── loop until password is strong               │
      │      ├── hashPassword()  →  append to users.txt      │
      │      └── createUserWorkspace()  → Data/<u>/Enc,Dec   │
      │                                                      │
      ├─ 2 → logIn(loggedInUser)                             │
      │      ├── getUserRecord()                             │
      │      ├── if locked → refuse                          │
      │      ├── up to 5 attempts                            │
      │      ├── FAIL x5 → setUserLock(now + 30 min)         │
      │      └── SUCCESS ↓                                   │
      │          toolkitMenu(loggedInUser) ─────────┐        │
      │           ├─ 1 → encryptTextFile(user)      │        │
      │           ├─ 2 → decryptTextFile(user)      │        │
      │           └─ 3 → break  ("log out") ────────┘        │
      │                                                      │
      ├─ 3 → aboutProject()   (read-only, no file access)    │
      │                                                      │
      └─ 4 → break  → return 0 ─────────────────────────────┘
```

---

## 12. Data Flow

**How a username becomes a folder path — the core of the whole design:**

```
User types "Ali" at the Log In screen
        ↓
logIn() writes it into loggedInUser   (a reference parameter, &)
        ↓
main() passes it to toolkitMenu(loggedInUser)
        ↓
toolkitMenu() passes it to encryptTextFile(currentUser)
        ↓
encryptTextFile() builds:  "Data/" + currentUser + "/Encrypted"
        ↓
The file is written to:    Data/Ali/Encrypted/notes_encrypted.txt
```

**This chain is the privacy guarantee.** The path is *derived from the logged-in name*, never from anything the user types at the file prompt. Even if Ali types `../Ahmed/secret.txt`, `filesystem::path(...).filename()` strips the folder part and only `secret.txt` survives — so it still lands in Ali's own folder.

> ⚠️ **If you break this chain, you break the entire project.** Never let the destination folder come from user input.

---

## 13. The users.txt File Format

One line per account, three fields separated by spaces:

```
username   passwordHash        lockUntil
Ali        a1b2c3d4e5f60718    0
Ahmed      99aa88bb77cc66dd    1789456123
```

| Field | Type | Meaning |
|---|---|---|
| `username` | text, **no spaces** | The account name. |
| `passwordHash` | 16 hex chars | The FNV-1a salted hash. The real password is never here. |
| `lockUntil` | `long long` | Unix time when the lock expires. `0` = not locked. |

Reading always uses `file >> a >> b >> c`, which splits on whitespace. **This is why a username must never contain a space** — it would be read back as two separate fields and corrupt the record.

> ✅ **Protected by `isValidUsername()`.** A username may only contain letters, digits and underscores, so a space can never reach the file. `cin >> username` also stops at the first space anyway, and `clearInputLine()` discards the rest of the line — so `Ali Khan` used to be *silently truncated* to `Ali`. Now it is rejected with a clear message instead of silently becoming a different name.

---

## 14. Input and Output

**Input**

| What | How | Note |
|---|---|---|
| Menu numbers | `readMenuChoice()` | Safe against letters. |
| Username | `cin >> username` + `clearInputLine()` | Stops at the first space. |
| Password | `readPassword()` / `_getch()` | Hidden. **Cannot be scripted.** |
| File name | `cin >> inputFileName` + `clearInputLine()` | |
| "Press Enter" | `getline(cin, dummy)` | Only works because of `clearInputLine()`. |

**Output**

| What | Where |
|---|---|
| Screens | `cout` |
| Accounts | `users.txt` (append on signup; full rewrite on lock) |
| Encrypted files | `Data/<User>/Encrypted/` |
| Decrypted files | `Data/<User>/Decrypted/` |

---

## 15. Error Handling

There are **no exceptions and no try/catch** in this project. Errors are handled by checking a return value and printing a message. That is deliberate — it is simple and it is enough here.

| Error | Detected by | What the user sees |
|---|---|---|
| Non-number at a menu | `!(cin >> choice)` | `❌ Invalid option.` |
| Username taken | `usernameExists()` | `❌ Username already exists.` + re-ask |
| Weak password | `isStrongPassword()` | The 5 rules, then re-ask |
| `users.txt` unwritable | `!file.is_open()` | `❌ Could not save the account.` |
| Wrong password | hash mismatch | `❌ Incorrect password.` + attempts left |
| Account locked | `lockUntil > now` | `🔒 Locked. Try again in N minutes.` |
| Input file missing | `!inputFile.is_open()` | `❌ Input file could not be opened.` |
| Output not creatable | `!outputFile.is_open()` | `❌ Output file could not be created.` |
| Empty file | `hasData == false` | `⚠️ The file was empty.` |

**The rule:** every function that touches a file checks `is_open()` before it claims success. Keep it that way.

---

## 16. Validation

| Rule | Enforced by | If it fails |
|---|---|---|
| Menu input is a number | `readMenuChoice()` | Returns `-1`, menu re-shows |
| Username is unique | `usernameExists()` | Re-ask, stay on Sign Up |
| Password ≥ 8 chars, upper + lower + digit + symbol | `isStrongPassword()` | Re-ask |
| Attempts ≤ 5 | `logIn()` | Lock for 30 minutes |
| Account not locked | `logIn()` | Refuse, even with the right password |
| Input file exists | `is_open()` | Error, return safely |
| Output folder exists | `create_directories()` | Created silently |

---

## 17. Naming Convention

| Thing | Convention | Example |
|---|---|---|
| Functions | `camelCase`, a **verb** | `createUserWorkspace()` |
| Variables | `camelCase`, a **noun** | `outputFolder` |
| Booleans | read as a question | `hasData`, `strongEnough` |
| Folders | `PascalCase`, matching the function | `Functions/SignUp/` |
| Files | exactly the folder name + `.cpp` | `SignUp/SignUp.cpp` |
| Runtime folders | Exactly `Data`, `Encrypted`, `Decrypted` | ⚠️ **do not rename** |

**The folder rule:** `Functions/<Name>/<Name>.cpp` defines `<name>()`. If you follow this, anyone can find any function in two seconds. Both build scripts scan `Functions/` recursively, so a new folder compiles automatically — **you never edit `build.bat`.**

---

## 18. Coding Style

The house rules. Follow them or the project stops being readable by first-years:

- **No classes, no pointers, no templates, no `auto`.** Only first-year C++.
- **`using namespace std;`** at the top of every file. (Bad practice in real projects — fine here, and it keeps the code short.)
- **A comment above every function** saying what it does and *why it exists*.
- **Allman braces** — the `{` goes on its own line.
- **4 spaces** for indentation, never tabs.
- **Small functions.** One function, one job.
- **Explain the *why*, not the *what*.** `i++` needs no comment. `+ 256` does.

---

## 19. Future Maintenance

### To add a new tool to the Toolkit Menu
1. Create `Functions/MyTool/MyTool.cpp` with one function `myTool(string currentUser)`.
2. Add its prototype to `Main/main.cpp` (the master index).
3. Add its prototype to `ToolkitMenu.cpp`, plus a menu line and an `else if` branch.
4. **Mirror all of it into `Complete Code/CPP_Project_V1_Complete.cpp`.**
5. Run `build.bat`. The new folder is picked up automatically.

### To change how every screen looks
Edit `printHeader()` and `printLine()`. That is all. Every screen updates at once.

### Before you commit any change
- [ ] It compiles: `g++ -std=c++17 -Wall <all .cpp> -o test.exe` — **fix warnings, do not ignore them.**
- [ ] Sign up a new user → the two folders appear.
- [ ] Encrypt a file → it lands in `Encrypted/`.
- [ ] Decrypt it → the result matches the original **exactly**.
- [ ] Two different users cannot see each other's files.
- [ ] Every menu still exits.
- [ ] **`Complete Code/` mirrors `Functions/`.**

### The traps that will bite you
1. **Forgetting `-std=c++17`** → hundreds of `<filesystem>` errors.
2. **Changing a signature but not every prototype** → "undefined reference" at link time.
3. **Adding `cin >>` without `clearInputLine()`** → the next "Press Enter" is silently skipped.
4. **Weakening `isValidUsername()`** → the username is used to build folder paths, so allowing `.` or `/` reopens the path-escape bug where `..` writes outside `Data/`. **Never let the destination folder come from unchecked user input.**
5. **Letting `Complete Code/` drift** out of sync with `Functions/`.

---

## 20. Possible Improvements

**✅ Already fixed** (these were real bugs — they are done, do not "re-fix" them):

1. ~~Unsafe usernames~~ → `isValidUsername()` now enforces 3–20 characters, letters/digits/underscore only, and rejects Windows reserved names (`CON`, `NUL`, `PRN`, `COM1`…). **This was a genuine path-escape bug:** a user named `..` produced the path `Data/../Encrypted`, which created folders *outside* `Data/` entirely.
2. ~~`setUserLock()` could destroy every account~~ → it now writes `users_temp.txt` in full and only then `rename()`s it over `users.txt`, so a crash mid-write leaves the original intact.
3. ~~`secretKey` was duplicated in two files~~ → both encrypt and decrypt now call `getSecretKey()`. They can no longer drift apart.

**Still open — the real remaining work:**

- **AES instead of the Caesar cipher.** This is the honest weakness of the project.
- **The key is hard-coded and shared by all users.** A per-user key derived from the password would be the proper design.
- **FNV-1a is not a password hash.** bcrypt/Argon2 are deliberately slow; ours is fast, which is exactly what an attacker wants.
- **No password recovery**, so a forgotten password means a dead account.
- **Windows only** — `system("cls")` and `_getch()` would both need replacing.

**Then the features:** SQLite · cloud storage · admin panel · activity logs · file search · backup/restore · Urdu translation.

---

## 21. Frequently Asked Questions

**Q: Why are there no `.h` files? Is that wrong?**
For a real project, yes — you would use headers. Here it is a teaching choice: it removes an entire concept the reader would otherwise have to learn first. The trade-off is §1's rule: change a signature, update every prototype.

**Q: I changed a function and now I get "undefined reference to ...".**
The linker cannot find the function body. Either you changed the signature in the definition but not in a prototype (they must match **exactly**), or you spelled the name differently, or the `.cpp` file was not compiled.

**Q: Hundreds of errors about `filesystem`.**
You forgot `-std=c++17`. Both build scripts already include it.

**Q: My decrypted file is garbage.**
This used to happen when `secretKey` differed between the encrypt and decrypt files, and it failed **silently**. Both now call `getSecretKey()`, so they cannot disagree. If you still see garbage, you are decrypting a file that was never encrypted by this program.

**Q: The "Press Enter to continue" is being skipped.**
Somewhere a `cin >> x` is missing its `clearInputLine()` call. The leftover Enter is being eaten by the next `getline()`.

**Q: Can I test the login screen with a script?**
No. `_getch()` reads the console directly and ignores piped input. Test everything else by compiling `Functions/**` against a temporary `main()` that calls the functions directly.

**Q: Where do `Data/` and `users.txt` come from? They are not in the repo.**
They are created at runtime, next to the `.exe`, the first time you run the program and register a user.

**Q: If I delete a user's folder, is their account gone?**
No — the account still lives in `users.txt`, so they can still log in. Their folders will be silently recreated (empty) by `create_directories()` in encrypt/decrypt. Deleting an account properly would mean removing its line from `users.txt` too.

**Q: Is this actually secure?**
The *architecture* is sound — hashed passwords, attempt limiting, lockout, per-user isolation. The *cipher* is not: a Caesar shift is trivially broken. We say so plainly in `Project_Overview.md`. Swapping in AES would not require redesigning anything else, which is the real lesson of the project.
