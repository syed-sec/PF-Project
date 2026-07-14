// AboutProject.cpp
// This file shows the "About Project" screen.
//
// It explains the whole project to anyone who runs the program: what it is,
// why it was built, how it works, which features it has, and who made it.
//
// It is READ-ONLY. It only prints text on the screen. It never reads, writes,
// encrypts or deletes any file, so it cannot break the rest of the program.
//
// The file is split into one small function per section, and aboutProject()
// at the bottom is the little menu that calls them.
//
// 👉 GROUP MEMBERS: the university details are already filled in. The ONLY
//    placeholders left are the team names and roll numbers, in the
//    showTeamMembers() function near the bottom of this file. Replace those
//    (they look like [Like This]) before you submit.

#include <iostream>
#include <string>
using namespace std;

// These functions are defined in other folders.
void clearScreen();
void waitForUser();
void printHeader(string title);
void printLine();
int readMenuChoice();

// Small helper functions. Each one prints ONE section of the About screen.
// They are only used inside this file.
void showHeroSection();
void showProjectOverview();
void showProjectWorkflow();
void showFeatures();
void showFolderStructure();
void showTechnologies();
void showAdvantages();
void showFutureImprovements();
void showTeamMembers();
void showFeature(string icon, string name, string description, string benefit, string why);

// ---------------------------------------------------------------------------
// Prints the top "hero" section: the project's name card.
// ---------------------------------------------------------------------------
void showHeroSection()
{
    printHeader("🔐  THE DEVELOPER'S TOOLKIT");

    cout << "   A secure, menu-based file encryption tool that gives every user\n";
    cout << "   their own private, password-protected workspace.\n";
    cout << "\n";
    cout << "   📚 Subject           : Programming Fundamentals Theory\n";
    cout << "   🎓 Program           : BS Cyber Security\n";
    cout << "   🏛️  University        : The Superior University, Lahore\n";
    cout << "   👨‍🏫 Instructor        : Prof. Zeeshan Mubeen\n";
    cout << "   📅 Academic Session  : 2025-2029\n";
    cout << "   👥 Project Type      : Group Project\n";
    cout << "\n";
}

// ---------------------------------------------------------------------------
// Explains why the project exists and what it does.
// ---------------------------------------------------------------------------
void showProjectOverview()
{
    clearScreen();
    printHeader("📖  PROJECT OVERVIEW");

    cout << "   WHY WE BUILT IT\n";
    cout << "   ---------------\n";
    cout << "   Text files on a shared computer are open for anyone to read. In a\n";
    cout << "   computer lab, a hostel room, or a family PC, a private file is only\n";
    cout << "   one double-click away from being seen by someone else.\n";
    cout << "\n";
    cout << "   THE PROBLEM IT SOLVES\n";
    cout << "   ---------------------\n";
    cout << "   1. Plain text files can be read by anybody.\n";
    cout << "   2. Files belonging to different people get mixed into one folder.\n";
    cout << "   3. There is no login, so there is no idea of \"my files\".\n";
    cout << "\n";
    cout << "   OUR SOLUTION\n";
    cout << "   ------------\n";
    cout << "   The Toolkit puts a login in front of the files, scrambles the text\n";
    cout << "   so it cannot be read, and gives every single user a private folder\n";
    cout << "   of their own. Two users can even encrypt files with the SAME name\n";
    cout << "   and they will never overwrite or see each other's work.\n";
    cout << "\n";
    cout << "   WHO CAN USE IT\n";
    cout << "   --------------\n";
    cout << "   Students, teachers, or anyone who shares a computer and wants to\n";
    cout << "   keep notes, answers, or personal text private.\n";
    cout << "\n";

    waitForUser();
    clearScreen();
    printHeader("📖  PROJECT OVERVIEW  (continued)");

    cout << "   OUR OBJECTIVES\n";
    cout << "   --------------\n";
    cout << "   1. Practise C++ file handling, functions, loops and conditions.\n";
    cout << "   2. Build a real login system with hashed (scrambled) passwords.\n";
    cout << "   3. Keep every user's data completely separate.\n";
    cout << "   4. Write code that a first-year student can actually read.\n";
    cout << "\n";
    cout << "   WHAT HAPPENS FROM LOGIN UNTIL LOGOUT\n";
    cout << "   ------------------------------------\n";
    cout << "   1. You start the program. It makes the \"Data\" folder if missing.\n";
    cout << "   2. You sign up. Your username must be new, and your password must\n";
    cout << "      be strong. Your password is scrambled before it is saved.\n";
    cout << "   3. Signing up creates your private workspace:\n";
    cout << "         Data/<YourName>/Encrypted/  and  Data/<YourName>/Decrypted/\n";
    cout << "   4. You log in. You get 5 tries. After 5 wrong passwords the\n";
    cout << "      account locks itself for 30 minutes.\n";
    cout << "   5. The Toolkit Menu opens and shows your name at the top.\n";
    cout << "   6. You choose Encrypt or Decrypt, and type a file name.\n";
    cout << "   7. The result is saved inside YOUR folder. Never anyone else's.\n";
    cout << "   8. You log out and return to the Main Menu. Your files stay safe\n";
    cout << "      on the disk, waiting for your next login.\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Draws the step-by-step workflow of the program.
// ---------------------------------------------------------------------------
void showProjectWorkflow()
{
    clearScreen();
    printHeader("🔄  PROJECT WORKFLOW");

    cout << "            ┌──────────────────────────┐\n";
    cout << "            │    Open Application      │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │  \"Data\" folder is ready  │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │      Create Account      │\n";
    cout << "            │  (private folders made)  │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │          Login           │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │     Choose Operation     │\n";
    cout << "            │   (Encrypt or Decrypt)   │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │       Select File        │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │    Encrypt / Decrypt     │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │  Save Output in YOUR     │\n";
    cout << "            │      own folder          │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │          Logout          │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Prints ONE feature in a neat, repeated shape.
// Using this small helper keeps the big features list short and tidy.
// ---------------------------------------------------------------------------
void showFeature(string icon, string name, string description, string benefit, string why)
{
    cout << "   " << icon << "  " << name << "\n";
    cout << "      What    : " << description << "\n";
    cout << "      Benefit : " << benefit << "\n";
    cout << "      Why     : " << why << "\n";
    cout << "\n";
}

// ---------------------------------------------------------------------------
// Shows every feature in the project.
// The list is long, so it is shown a few features at a time.
// ---------------------------------------------------------------------------
void showFeatures()
{
    // ---------------- Page 1: Accounts and security ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (1 of 4)  -  Accounts & Security");

    showFeature("👤", "User Registration",
                "Creates a brand new account with a username and a password.",
                "Every person gets their own identity inside the program.",
                "Without accounts, all files would belong to everybody.");

    showFeature("🔐", "Secure Login",
                "Checks your username and password before letting you in.",
                "Nobody can open your files by simply starting the program.",
                "A lock is useless if there is no door in front of it.");

    showFeature("✏️", "Username Validation",
                "Makes sure the username you choose is not already taken.",
                "Two people can never share one identity or one folder.",
                "Duplicate names would mix two users' files together.");

    showFeature("🛡️", "Password Validation",
                "Requires 8+ characters with upper, lower, digit and symbol.",
                "Weak passwords like \"12345\" are refused straight away.",
                "A short password can be guessed in seconds.");

    showFeature("🔑", "Password Hashing",
                "Scrambles the password before saving it (FNV-1a + salt).",
                "Even if someone opens users.txt, they see nonsense, not your password.",
                "Real passwords must NEVER be stored as plain readable text.");

    waitForUser();

    // ---------------- Page 2: Protection ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (2 of 4)  -  Protection");

    showFeature("🚫", "Duplicate Username Detection",
                "Spots a taken username and asks you for a different one.",
                "You stay on the Sign Up screen instead of starting over.",
                "Being thrown back to the Main Menu would be annoying.");

    showFeature("❌", "Incorrect Password Handling",
                "Counts your wrong tries and shows how many are left (out of 5).",
                "You know exactly where you stand before the lock happens.",
                "Silent failure is confusing and feels broken.");

    showFeature("⏰", "Account Lock (30 minutes)",
                "Locks the account for 30 minutes after 5 wrong passwords.",
                "Stops someone guessing your password again and again.",
                "Unlimited guesses would eventually break any password.");

    showFeature("💾", "Lock Survives Restart",
                "The lock time is saved inside users.txt, not just in memory.",
                "Closing and reopening the program does NOT clear the lock.",
                "Otherwise a guesser could just restart the program to reset it.");

    showFeature("👁️", "Hidden Password Input",
                "Shows a '*' for each key you type instead of the real letter.",
                "Someone standing behind you cannot read your password.",
                "Passwords should never be shown openly on the screen.");

    showFeature("🔒", "Individual User Accounts",
                "Every account is a separate record inside users.txt.",
                "Your account is fully independent from everyone else's.",
                "Shared accounts mean no real privacy at all.");

    waitForUser();

    // ---------------- Page 3: Files and folders ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (3 of 4)  -  Files & Folders");

    showFeature("📁", "Automatic Data Directory",
                "Creates the \"Data\" folder by itself when the program starts.",
                "You never have to make any folder by hand.",
                "A missing folder would make every file operation fail.");

    showFeature("📂", "Separate Folder for Every User",
                "Builds Data/<Username>/ the moment you register.",
                "Your files live in your own private space.",
                "One shared folder would mix everybody's work together.");

    showFeature("🔒", "Encrypted Files Folder",
                "All your encrypted files go into Data/<You>/Encrypted/.",
                "Locked files are always in one predictable place.",
                "Scattered files are easy to lose and hard to find.");

    showFeature("🔓", "Decrypted Files Folder",
                "All your decrypted files go into Data/<You>/Decrypted/.",
                "Readable files never sit next to the locked ones.",
                "Mixing them up risks encrypting an already-encrypted file.");

    showFeature("🚧", "No Mixing Between Users",
                "The logged-in name is used to build every save path.",
                "Two users may encrypt \"notes.txt\" and never clash.",
                "This is the single most important privacy rule of the project.");

    showFeature("🗂️", "Organized Storage",
                "Every file has exactly one correct home folder.",
                "The project stays tidy even after months of use.",
                "Messy storage is the fastest way to lose real work.");

    waitForUser();

    // ---------------- Page 4: Files, input and interface ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (4 of 4)  -  Files, Input & Interface");

    showFeature("🔒", "File Encryption",
                "Shifts every byte of the file by a secret key (Caesar cipher).",
                "The text becomes unreadable to anyone who opens it.",
                "This is the core purpose of the whole project.");

    showFeature("🔓", "File Decryption",
                "Shifts every byte back by the same key to restore the text.",
                "You get your original file back, exactly as it was.",
                "Encryption is worthless if you cannot reverse it.");

    showFeature("📄", "Smart File Selection",
                "If the name is not found, it also looks in YOUR Encrypted folder.",
                "You can type \"notes_encrypted.txt\" instead of a long path.",
                "Typing a full folder path every time is slow and error-prone.");

    showFeature("🏷️", "Automatic File Naming",
                "Adds \"_encrypted\" or \"_decrypted\" and keeps the extension.",
                "Your original file is never overwritten or destroyed.",
                "Overwriting the input would lose the user's real data.");

    showFeature("📥", "Safe File Reading & Writing",
                "Reads and writes the file one character at a time, spaces included.",
                "Nothing in the file is skipped, changed or lost.",
                "A cipher must handle EVERY byte or it cannot be reversed.");

    showFeature("⚠️", "Error Messages",
                "Reports a missing file, an unwritable folder, or an empty file.",
                "You always know exactly what went wrong and why.",
                "Silent failure makes a program impossible to trust.");

    showFeature("✅", "Success Messages",
                "Confirms the action and prints the full path of the saved file.",
                "You know precisely where your new file was placed.",
                "\"It worked\" is useless if you cannot find the result.");

    showFeature("⌨️", "Menu Input Validation",
                "Catches letters typed at a number menu and cleans the buffer.",
                "A typo shows \"Invalid option\" instead of freezing the program.",
                "Without this, one wrong key causes an endless menu loop.");

    showFeature("🖥️", "Console & Screen Management",
                "Clears the screen and pauses so you can read each message.",
                "Every screen stays clean and readable.",
                "Text piling up endlessly looks unprofessional and confusing.");

    showFeature("🧭", "Simple Navigation",
                "Numbered menus with a clear way back at every step.",
                "You can never get stuck or trapped inside a screen.",
                "A user should always be able to go back or leave.");

    showFeature("🌱", "Beginner-Friendly Design",
                "Small functions, plain names, and a comment on every function.",
                "A new group member can understand the code quickly.",
                "Code is read far more often than it is written.");

    waitForUser();
}

// ---------------------------------------------------------------------------
// Shows the folder layout and explains what each folder is for.
// ---------------------------------------------------------------------------
void showFolderStructure()
{
    clearScreen();
    printHeader("🗂️  FOLDER STRUCTURE");

    cout << "   C++ Project V1/\n";
    cout << "   │\n";
    cout << "   ├── Main/                  → holds main(), the program's entry point\n";
    cout << "   │   └── main.cpp           → the Main Menu and the prototype list\n";
    cout << "   │\n";
    cout << "   ├── Functions/             → one folder per function (no .h files)\n";
    cout << "   │   ├── SignUp/            → creating a new account\n";
    cout << "   │   ├── LogIn/             → checking password, attempts, lock\n";
    cout << "   │   ├── EncryptTextFile/   → locking a file\n";
    cout << "   │   ├── DecryptTextFile/   → unlocking a file\n";
    cout << "   │   ├── AboutProject/      → this About screen\n";
    cout << "   │   └── ... and more       → one small job each\n";
    cout << "   │\n";
    cout << "   ├── Complete Code/         → the SAME program in one single file,\n";
    cout << "   │                            for easy reading and submission\n";
    cout << "   │\n";
    cout << "   ├── docs/                  → written documentation\n";
    cout << "   │   ├── Developer_Guide.md → deep guide for us, the group members\n";
    cout << "   │   └── Project_Overview.md→ short summary for the teacher\n";
    cout << "   │\n";
    cout << "   ├── Data/                  → made automatically at startup\n";
    cout << "   │   ├── Ali/               → one folder per registered user\n";
    cout << "   │   │   ├── Encrypted/     → Ali's locked files\n";
    cout << "   │   │   └── Decrypted/     → Ali's unlocked files\n";
    cout << "   │   └── Ahmed/             → completely separate from Ali\n";
    cout << "   │       ├── Encrypted/\n";
    cout << "   │       └── Decrypted/\n";
    cout << "   │\n";
    cout << "   ├── users.txt              → all accounts: name, hash, lock time\n";
    cout << "   └── build.bat              → compiles and runs the program\n";
    cout << "\n";
    cout << "   💡 The golden rule: a user's files NEVER leave their own folder.\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Explains every technology and C++ topic used in the project.
// ---------------------------------------------------------------------------
void showTechnologies()
{
    clearScreen();
    printHeader("🛠️  TECHNOLOGIES USED  (1 of 2)");

    cout << "   ⚙️  C++ (standard C++17)\n";
    cout << "      What  : A fast, compiled programming language.\n";
    cout << "      Why   : It is our course language and it is close to the machine.\n";
    cout << "      Where : Every single file in the project.\n";
    cout << "\n";
    cout << "   📁  File Handling  (<fstream>)\n";
    cout << "      What  : ifstream reads files, ofstream writes files.\n";
    cout << "      Why   : Accounts and encrypted files must survive a restart.\n";
    cout << "      Where : users.txt, and every encrypt/decrypt operation.\n";
    cout << "\n";
    cout << "   🗄️  Filesystem  (<filesystem>)\n";
    cout << "      What  : Creates folders and checks whether a path exists.\n";
    cout << "      Why   : The Data and per-user folders must be made automatically.\n";
    cout << "      Where : ensureDataFolder(), createUserWorkspace(), encrypt, decrypt.\n";
    cout << "\n";
    cout << "   🧩  Functions\n";
    cout << "      What  : Small named blocks of code that do ONE job.\n";
    cout << "      Why   : Small pieces are easy to read, test and fix.\n";
    cout << "      Where : Each one lives in its own folder under Functions/.\n";
    cout << "\n";
    cout << "   🔤  Strings  (<string>)\n";
    cout << "      What  : Text that can grow and shrink.\n";
    cout << "      Why   : Usernames, passwords, file names and paths are all text.\n";
    cout << "      Where : Everywhere. Paths are built by joining strings together.\n";
    cout << "\n";

    waitForUser();

    clearScreen();
    printHeader("🛠️  TECHNOLOGIES USED  (2 of 2)");

    cout << "   🔁  Loops  (while / for)\n";
    cout << "      What  : Repeat a block of code.\n";
    cout << "      Why   : Menus repeat until you exit; files are read byte by byte.\n";
    cout << "      Where : Every menu, the password retry loop, the cipher loop.\n";
    cout << "\n";
    cout << "   ❓  Conditions  (if / else)\n";
    cout << "      What  : Choose between two paths.\n";
    cout << "      Why   : \"Is the password right?\" \"Does this folder exist?\"\n";
    cout << "      Where : Login checks, menu choices, every error check.\n";
    cout << "\n";
    cout << "   📚  Arrays & Vectors  (<vector>)\n";
    cout << "      What  : A list that holds many values of the same type.\n";
    cout << "      Why   : To hold every account in memory while updating one lock.\n";
    cout << "      Where : setUserLock(), which rewrites users.txt safely.\n";
    cout << "\n";
    cout << "   🧮  The Standard Library\n";
    cout << "      What  : Ready-made tools that ship with C++.\n";
    cout << "      Why   : We should not rebuild what already exists and works.\n";
    cout << "      Where : <iostream> screen, <ctime> lock timing, <cctype> letter\n";
    cout << "              checks, <conio.h> hidden password input.\n";
    cout << "\n";
    cout << "   🔐  Caesar Cipher + FNV-1a Hash\n";
    cout << "      What  : A byte-shift cipher, and a one-way password scrambler.\n";
    cout << "      Why   : Simple enough to fully understand, real enough to work.\n";
    cout << "      Where : encryptTextFile(), decryptTextFile(), hashPassword().\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Lists the advantages of the project.
// ---------------------------------------------------------------------------
void showAdvantages()
{
    clearScreen();
    printHeader("✨  ADVANTAGES  (1 of 2)");

    cout << "   🎓 Easy to Learn\n";
    cout << "      No classes, no pointers, no templates. Only the C++ topics from\n";
    cout << "      first year, used the way they are actually taught.\n";
    cout << "\n";
    cout << "   😊 Simple User Experience\n";
    cout << "      Numbered menus only. If you can count to four, you can use it.\n";
    cout << "\n";
    cout << "   🗂️ Organized Data\n";
    cout << "      Every file has exactly one correct home. Nothing is ever loose.\n";
    cout << "\n";
    cout << "   🔐 Secure File Management\n";
    cout << "      Files are unreadable once locked, and passwords are never saved\n";
    cout << "      as plain text anywhere on the disk.\n";
    cout << "\n";
    cout << "   🙋 Individual User Privacy\n";
    cout << "      Your folder is yours. Another user simply cannot reach it through\n";
    cout << "      the program, no matter what they type.\n";
    cout << "\n";
    cout << "   🛠️ Easy Maintenance\n";
    cout << "      One function, one folder, one job. To fix login, you open exactly\n";
    cout << "      one file: LogIn.cpp.\n";
    cout << "\n";

    waitForUser();

    clearScreen();
    printHeader("✨  ADVANTAGES  (2 of 2)");

    cout << "   ♻️ Reusable Code\n";
    cout << "      printHeader(), waitForUser() and readMenuChoice() are written once\n";
    cout << "      and reused by every screen in the program.\n";
    cout << "\n";
    cout << "   🪶 Lightweight\n";
    cout << "      One small .exe. No database, no internet, no installer, no setup.\n";
    cout << "\n";
    cout << "   ⚡ Fast Performance\n";
    cout << "      The cipher is one addition per byte, so files process instantly.\n";
    cout << "\n";
    cout << "   🧱 Clean Structure\n";
    cout << "      You can guess where any piece of code lives just from its name.\n";
    cout << "\n";
    cout << "   🌱 Expandable Design\n";
    cout << "      To add a tool, write one new folder and add one menu line. No\n";
    cout << "      existing code has to be rewritten.\n";
    cout << "\n";
    cout << "   🛡️ Safe by Default\n";
    cout << "      The original file is never overwritten, a bad file name is caught\n";
    cout << "      before anything is written, and a wrong key press cannot crash it.\n";
    cout << "\n";
    cout << "   📖 Fully Documented\n";
    cout << "      Every function has a comment, and the docs/ folder explains the\n";
    cout << "      whole project for both group members and teachers.\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Lists honest, realistic future improvements.
// ---------------------------------------------------------------------------
void showFutureImprovements()
{
    clearScreen();
    printHeader("🚀  FUTURE IMPROVEMENTS");

    cout << "   These are the next steps we would take if the project continued.\n";
    cout << "\n";
    cout << "   🔐 AES Encryption        Replace the Caesar cipher with a real,\n";
    cout << "                            industry-standard algorithm.\n";
    cout << "\n";
    cout << "   🗄️ Database Integration  Store accounts in SQLite instead of a\n";
    cout << "                            plain users.txt file.\n";
    cout << "\n";
    cout << "   ☁️ Cloud Storage         Sync each user's folder online so files\n";
    cout << "                            are safe if the computer is lost.\n";
    cout << "\n";
    cout << "   🔁 Password Recovery     A safe way back in for a user who has\n";
    cout << "                            forgotten their password.\n";
    cout << "\n";
    cout << "   👤 User Profiles         A real name, an email, and a photo for\n";
    cout << "                            each account.\n";
    cout << "\n";
    cout << "   🔍 File Search           Search inside your own folder by file\n";
    cout << "                            name or by date.\n";
    cout << "\n";
    cout << "   👮 Admin Panel           An admin who can unlock a locked account\n";
    cout << "                            or remove an old user.\n";
    cout << "\n";
    cout << "   📝 Activity Logs         Record every login, encryption and error\n";
    cout << "                            with the time it happened.\n";
    cout << "\n";
    cout << "   💾 Backup & Restore      Save and restore a whole workspace as a\n";
    cout << "                            single compressed file.\n";
    cout << "\n";
    cout << "   🌍 Multi-language        Show the menus in Urdu as well as English.\n";
    cout << "\n";
    cout << "   🌙 Dark / Light Themes   Let the user pick the console colours.\n";
    cout << "\n";
    cout << "   💻 Multi-device Support  Build for Linux and macOS too, by replacing\n";
    cout << "                            the Windows-only \"cls\" and _getch().\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// Shows the team.
// 👉 GROUP MEMBERS: replace the placeholders below with your real details.
// ---------------------------------------------------------------------------
void showTeamMembers()
{
    clearScreen();
    printHeader("👥  TEAM MEMBERS");

    cout << "   👑 Group Leader\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 2\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 3\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 4\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 5\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   ℹ️  Members 2-5 currently repeat the leader's details.\n";
    cout << "       Replace them with each member's real name and roll number\n";
    cout << "       in Functions/AboutProject/AboutProject.cpp before submitting.\n";
    cout << "\n";

    waitForUser();
}

// ---------------------------------------------------------------------------
// The About Project menu. It shows the hero card, then lets the user pick a
// section to read. It only prints text, so it can never damage any data.
// ---------------------------------------------------------------------------
void aboutProject()
{
    int choice;

    while (true)
    {
        clearScreen();
        showHeroSection();

        cout << "   📌 Select a section to read\n";
        cout << "\n";
        cout << "      1️⃣   📖 Project Overview\n";
        cout << "      2️⃣   🔄 Project Workflow\n";
        cout << "      3️⃣   ⭐ Complete Features\n";
        cout << "      4️⃣   🗂️  Folder Structure\n";
        cout << "      5️⃣   🛠️  Technologies Used\n";
        cout << "      6️⃣   ✨ Advantages\n";
        cout << "      7️⃣   🚀 Future Improvements\n";
        cout << "      8️⃣   👥 Team Members\n";
        cout << "      9️⃣   🔙 Back to Main Menu\n";
        cout << "\n";
        printLine();
        cout << "👉 Enter your choice: ";
        choice = readMenuChoice();

        if (choice == 1)
        {
            showProjectOverview();
        }
        else if (choice == 2)
        {
            showProjectWorkflow();
        }
        else if (choice == 3)
        {
            showFeatures();
        }
        else if (choice == 4)
        {
            showFolderStructure();
        }
        else if (choice == 5)
        {
            showTechnologies();
        }
        else if (choice == 6)
        {
            showAdvantages();
        }
        else if (choice == 7)
        {
            showFutureImprovements();
        }
        else if (choice == 8)
        {
            showTeamMembers();
        }
        else if (choice == 9)
        {
            break; // leave the About screen and go back to the Main Menu
        }
        else
        {
            cout << "\n❌ Invalid option. Please enter a number from the menu.\n";
            waitForUser();
        }
    }
}
