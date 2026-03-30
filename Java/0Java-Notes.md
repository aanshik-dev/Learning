<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **JAVA NOTES** 🔥🐦‍🔥

- By [Aanshik-dev](https://aanshik-dev.vercel.app/)
  <br>

Java is a statically-typed, object-oriented, platform-independent language. It runs on the JVM (Java Virtual Machine), enabling "Write Once, Run Anywhere" (WORA).

- History & Evolution
  - Created by: James Gosling at Sun Microsystems (now Oracle) in 1995.
  - Original Name: Oak.
  - Goal: "Write Once, Run Anywhere" (WORA) - platform independence.
- Key Features
  - Platform Independent
  - Object-Oriented (except primitives)
  - Robust: Strong memory management, exception handling, and type-checking.
  - Secure: No explicit pointers; bytecode verification; security manager.
  - Multithreaded: Built-in support for concurrent programming.
  - Portable: Same bytecode works on any platform with a JVM.
  - High Performance: Just-In-Time (JIT) compilation optimizes bytecode to native machine code at runtime.

<br>
  
## 🐦‍🔥 Components of Java
```bash
JDK (Java Development Kit)
├── JRE (Java Runtime Environment)
│   ├── JVM (Java Virtual Machine)
│   │   ├── Interpreter
│   │   ├── JIT Compiler
│   │   └── Garbage Collector
│   └── Core Libraries (rt.jar, etc.)
├── Development Tools
│   ├── javac (Compiler)
│   ├── jar (Archiver)
│   ├── javadoc (Documentation)
│   ├── jdb (Debugger)
│   └── jconsole (Monitoring)
└── Additional Libraries
```

```bash
Source Code (.java) → Compiler (javac) → Bytecode (.class) → JVM → Machine Code
```

<br>

## 🐦‍🔥 VARIABLES

A variable is a container that holds a value. Java is statically typed, meaning you must declare the variable's type before using it. The type is checked at compile-time.

```java
// Declaration and Initialization
String name = "Aanshik";
int age = 20;
double height = 5.6;

Primitive Types (8):
System.out.println(name.getClass().getSimpleName()); // String
// Primitives don't have methods, but we can use wrapper classes
```

### 🔥 Primitive Datatypes

```java
byte b = 127;    // 1 byte
short s = 32767; // 2 bytes
int i = 2_147_483_647;  // 4 bytes
long l = 9_223_372_036_854_775_807L;  // 8 bytes
float f = 3.14f; // 4 bytes
double d = 3.14159265359; // 8 bytes
char c = 'A';    // 2 bytes (Unicode)
boolean flag = true; // size depends on JVM (1 byte)
```

### 🔥 Reference Data Type

Reference types store the address (reference) of an object in memory.
Reference Types: Objects, arrays, interfaces, enums.

```java
String text = "Hello";              // String is a reference type
int[] numbers = {1, 2, 3};          // Array is a reference type
Object obj = new Object();          // Any class instance
```

### 🔥 Type Conversion vs Type Casting

⚡ `Widening (Implicit/Automatic)` : Converting a smaller type to a larger type. Done automatically by compiler.

⚡ `Narrowing (Explicit/Manual)` : Converting a larger type to a smaller type. Requires explicit casting.

```java
// Widening (Implicit)
int price = 75;
double percent = price + 5;          // int → double (automatic)
System.out.println(percent);         // Output: 80.0

// Narrowing (Explicit Casting)
double priceDouble = 75.56;
int priceInt = (int) priceDouble;    // double → int (manual cast)
System.out.println(priceInt);        // Output: 75 (truncated, not rounded)
```

<br>

## 🐦‍🔥 COMMENTS

```java
// Single Line Comment

/*
 * Multi-line Comment
 * Can span multiple lines
 */

/**
 * Documentation Comment (Javadoc)
 * Used to generate API documentation
 * @param param description
 * @return description
 */
```

<br>

## 🐦‍🔥 PRINT STATEMENT

```java
System.out.print("Hello");           // Prints without newline
System.out.println("Hello World");   // Prints with newline
System.out.printf("Format: %d %s", 10, "Java");  // Formatted printing
```

<br>

## 🐦‍🔥 String Formatting

```java
String name = "coffee";
double price = 3.50;

// Concatenation
System.out.println("The " + name + " costs " + price);

// printf / format
System.out.printf("The %s costs $%.2f.%n", name, price);

// String.format() - returns formatted string
String message = String.format("The %s costs $%.2f.", name, price);
System.out.println(message);
```

## 🐦‍🔥 FILE HANDLING

♦️ **FILE CLASS**
File represents names of the files/directories, not their contents.

```java
File f1 = new File("data.txt");                       // relative path
File f2 = new File("C:/Users/abc/Desktop/data.txt"); // absolute path
File f3 = new File("folder", "data.txt");            // parent + child
```

IMPORTENT CHECKS :
`f.exists();`
`f.isFile();`
`f.isDirectory();`
`f.canRead();`
`f.canWrite();`
`f.canExecute();`

METADATA
`f.length();` // in bytes
`f.getName();`
`f.getParent();`
`f.getAbsolutePath();`
`f.lastModified();`

OPERATIONS
`f.createNewFile();`
`f.mkdir();` // one directory
`f.mkdirs();` // nested directories
`f.delete();`

> 📝 NOTE : File class cannot read/write data, only handles metadata & paths.

</div>
</div>
