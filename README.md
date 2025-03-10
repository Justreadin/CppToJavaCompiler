# C++ to Java Compiler

![C++ to Java Compiler](https://via.placeholder.com/1000x300?text=C%2B%2B+to+Java+Compiler)

## 🚀 Overview
This C++ to Java Compiler is a sophisticated source-to-source compiler that translates C++ code into equivalent Java code. It replicates essential features of the C++ language and generates syntactically correct Java output. The compiler is built with a structured pipeline, including lexical analysis, parsing, semantic checks, and code generation.

## 📂 Project Structure
```
CppToJavaCompiler/
│
├── src/                     # Source code for the compiler
│   ├── lexer/               # Tokenization module
│   ├── parser/              # Syntax and semantic analysis module
│   ├── codegen/             # Java code generation module
│   ├── utils/               # Utility functions
│   ├── main.cpp             # Main entry point of the compiler
│
├── tests/                   # Unit tests for different components
├── examples/                # Sample C++ programs for testing
├── build/                   # Compiled binaries (after compilation)
├── CMakeLists.txt           # CMake build configuration
├── README.md                # Project documentation
└── .gitignore               # Git ignore file
```

## 🛠️ How the Compiler Works
The compiler processes C++ code through four main stages:

### 1️⃣ Lexical Analysis (Tokenization)
The lexer scans C++ source code and converts it into a stream of tokens.

**Example:**
```cpp
int x = 5;
```
**Tokens:** `[int, IDENTIFIER(x), =, NUMBER(5), ;]`

**🔹 Key Files:**
- `Token.h / Token.cpp` - Defines different token types.
- `Lexer.h / Lexer.cpp` - Implements the lexer.

---
### 2️⃣ Parsing & AST Generation
The parser organizes tokens into an Abstract Syntax Tree (AST) to understand program structure.

**Example AST Representation:**
```
VariableDeclaration
 ├── Type: int
 ├── Name: x
 └── Value: 5
```

**🔹 Key Files:**
- `ASTNode.h / ASTNode.cpp` - Defines AST nodes.
- `Parser.h / Parser.cpp` - Constructs the AST.
- `SymbolTable.h / SymbolTable.cpp` - Manages variable and function symbols.

---
### 3️⃣ Java Code Generation
Transforms the AST into equivalent Java code.

**Example:**
```cpp
class Test {
    int x = 5;
};
```
Converts to:
```java
public class Test {
    int x = 5;
}
```

**🔹 Key Files:**
- `CodeGenerator.h / CodeGenerator.cpp` - Converts AST into Java code.
- `JavaEmitter.h / JavaEmitter.cpp` - Handles Java code emission.

---
### 4️⃣ Writing Output to Java Files
Generates a `.java` file containing the translated code.

**🔹 Key File:**
- `OutputWriter.h / OutputWriter.cpp` - Manages file writing.

## 🎯 CLI Interface
The compiler includes a command-line interface for easy usage:
```sh
cpp2java myfile.cpp -o myfile.java
```
Supported flags:
- `-o <output>`: Specify the output Java file.
- `--debug`: Enable verbose logging.
- `--optimize`: Apply optimizations.

## ⚡ Setup & Compilation

### 🏗️ Build Instructions
```sh
rm -r build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

### 🌍 Set Up as an Executable
To run the compiler globally, set the generated binary as an environmental variable.

## 🔬 Testing
Unit tests are included for each module using Google Test:
```sh
./tests/lexer_tests
./tests/parser_tests
./tests/codegen_tests
```

## 📌 Features
✅ Translates C++ code to Java with high accuracy  
✅ Supports variable declarations, expressions, and class structures  
✅ Provides detailed error messages for syntax and type checking  
✅ Includes a CLI for user-friendly compilation  
✅ Built with modular and scalable architecture  

## 🤖 Technologies Used
- **Language:** C++
- **Build System:** CMake
- **Testing Framework:** Google Test (gtest)
- **Version Control:** Git

## 🚀 Future Improvements
🔹 Support for more complex C++ features (inheritance, templates, etc.)  
🔹 Optimizations for performance improvement  
🔹 Web-based UI for compiling code online  

## 🏆 Why This Project Stands Out
This project showcases advanced compiler development skills, including:
- **Lexical & syntax analysis** using AST representation.
- **Efficient memory handling** with symbol tables.
- **Cross-language transformation** using structured parsing techniques.

## ✨ Connect With Me
📧 Email: dave.400g@gmail.com
💼 LinkedIn: https://linkedin.com/in/favour-akintoye-285847278
📂 GitHub: https://github.com/Justreadin
