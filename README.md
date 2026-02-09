# **HT-Bash**

**A programming language that compiles into Bash.**

HT-Bash is a programming language that generates Bash scripts from a high-level source. It is designed for readability, maintainability, and safe automation.

HT-Bash itself is written in **HTVM** and can be converted into **Python or C++**, giving you flexible options to run your scripts.
The original source file is `HT-Bash.htvm`, compiled using **HTVM** with the **author’s custom syntax**.
[HTVM Repository](https://github.com/TheMaster1127/HTVM)

---

## **Installation & Running**

### **Python Version**

1. Ensure Python is installed.
2. Download the HT-Bash repository.
3. Run your `.htsh` file:

```bash
python3 HT-Bash.py my_script.htsh
```

This executes your HT-Bash script and generates Bash output.

---

### **C++ Version**

1. Compile the C++ source:

```bash
g++ -O3 HT-Bash.cpp -o HT-Bash
```

2. Run your `.htsh` file:

```bash
./HT-Bash my_script.htsh
```

This executes the script through the compiled executable.

---

## **Usage**

A minimal HT-Bash script:

```py
print("Hello, World!")
```

Running it through either Python or C++ produces the Bash equivalent.

---

## **Repository & Documentation**

Full documentation and examples are available here:

**[HT-Bash Documentation](https://github.com/TheMaster1127/HT-Bash/blob/main/DOCS.md)**

Download the repository to start compiling and running `.htsh` scripts.

---

## **License**

HT-Bash is licensed under **GPL v3** — free to use, modify, and distribute under the GPL terms.
