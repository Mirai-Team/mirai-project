NORMS
=====

+ [Code Style](#code-style)
    + [General](#general)
    + [Integral types](#integral-types)
    + [Indentation](#indentation)
    + [Files extension](#files-extensions)
    + [Header files](#header-files)
    + [Includes](#includes)
    + [Naming](#naming)
    + [Variable and Array Initialization](#variable-and-array-initialization)
    + [Braces](#braces)
    + [Conditionals](#conditionals)
    + [Spaces](#spaces)
    + [Type conversion](#type-conversion)
    + [Namespaces](#namespaces)
    + [Classes](#classes)
    + [Loops](#loops)
+ [Git Workflow](#git-workflow)

# Code style

Most of our code style comes from SFML and Google styleguide. Some excellent extracts are taken from them since that's exactly what we do.
Follow what is necessary in this project, and if it's not in our norms, you may ask us, use common sense to keep a readable code or check the following pages if you need to :
+ http://www.sfml-dev.org/style.php
+ https://google-styleguide.googlecode.com/svn/trunk/cppguide.html

You have to know what you are doing, and resources above explain a lot of intersting stuff in a concise way.

## General

+ C++ source code must be **C++11-compliant.** Use [ISO/IEC 14882:2011 c++ norm](http://en.wikipedia.org/wiki/C%2B%2B11).
+ **No C in C++. _Only C++_.**
+ **If your code contains a warning, please try to fix it.**
+ **Do not use `#define` to create constants.** Prefer enum or an anonymous namespace.
+ For better memory usage :
    + Pass any parameter which **don't need to be modified by the function as _const reference_.**
    + **Use `std::move` to move objects that you no longer need.** [See details about Move constructor and Move Assignement operator here](http://blog.smartbear.com/c-plus-plus/c11-tutorial-introducing-the-move-constructor-and-the-move-assignment-operator/).
+ **All parameters passed by reference must be labeled const.** Use pointers to modify variable from a function / method.
+ Use **smart pointer** (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, …).
+ Prefer **pre-increment** to post-increment.
    ```C++
    ++i; // rather than i++ !
    ```
+ **Surround the return expression with parentheses only if necessary.**
    - yes
    ```C++
    return result;
    ```
    - _no_
    ```C++
    return (result);
    ```
+ **Avoid adding trailing whitespace in the code.**
    - They aren't useful for code understanding and might cause useless conflicts while merging.
    - Remove it in a separate clean-up operation if it's too late (if possible when no one else is working on the related files). To avoid that problem, you may use [.editorconfig](.editorconfig) file along with the [EditorConfig plugin](http://editorconfig.org/).
+ **You can use auto to avoid complicated type names and for _local variables only_**. Continue using manifest type when it **improve readability !**
    - See [that](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#auto) before abusing of it.
+ **Prefer use of [range-based for loop](http://en.cppreference.com/w/cpp/language/range-for) instead of container iterators.**
+ **Use the nullptr type over the macro `NULL`.**
+ One line of code should have a maximum of **100 characters**.

## Integral types

Instead of using `int`, `unsigned int`, `char`, `long long int`, etc. Use type aliases from [Config.hpp](include/MiraiProject/Config.hpp) file :
+ `int8`, `int16`, `int32` and `int64` for signed integers.
+ `uint8`, `uint16`, `uint32` and `uint64` for unsigned ones.

These are standard types that provide fixed, well-defined sizes regardless the architecture.

## Indentation

+ **Do not use tabs** except for files that require them for semantic meaning.
+ Tab indent size is **4 space**.
+ The contents of namespaces are not indented.
+ A case label is indended and the case statement as well.
    - yes
    ```C++
    switch (myVar) {
        case value1:
            // code
        case value2:
            // code
            break;
        default:
            // code
            break;
    }
    ```
    - _no_
    ```C++
    switch (myVar) {
    case value1:
        // code
    case value2:
        // code
        break;
    default:
        // code
        break;
    }
    ```
+ Do not indent `public`, `protected` and `private` labels in classes.
    - yes
    ```C++
    class myClass {
    public:
        myClass();
        void aPublicMethod();

    private:
        int m_aMemberVar;
    };
    ```
    - _no_
    ```C++
    class myClass {
        public:
            myClass();
            void aPublicMethod();

        private:
            int m_aMemberVar;
    };
    ```

## Files extensions

+ C++ source files have the extension _.cpp_.
+ C++ header files have the extension _.hpp_.
+ Templates files have the extension _.tpp_.

## Header files

Like SFML, header files are structured as follow:
+ Licence block
+ Opening include guard.
+ Other headers includes.
+ Opening namespace `mp`.
+ Class definitions or/and global function declarations.
+ Closing namespace `mp`.
+ Closing include guard.
+ Extended comment on the class.

```C++
////////////////////////////////////////////////////////////
//
// License...
//
////////////////////////////////////////////////////////////

#ifndef MP_FILENAME_HPP
#define MP_FILENAME_HPP

#include <...>

namespace mp
{
class ForwardDeclaration;

namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Short description...
///
////////////////////////////////////////////////////////////
class PrivateClass
{
};

} // namespace priv

////////////////////////////////////////////////////////////
/// \brief Short description...
///
////////////////////////////////////////////////////////////
class PublicClass
{
};

////////////////////////////////////////////////////////////
/// \brief Short description...
///
////////////////////////////////////////////////////////////
void doSomething();

} // namespace mp

#endif // MP_FILENAME_HPP

////////////////////////////////////////////////////////////
//
// Extensive Doxygen documentation...
//
////////////////////////////////////////////////////////////
```

**Don't forget the doxygen documentation !**

## Includes

The inclusion order is as follows:
+ Standard library headers, sorted alphabetically.
+ Dependency headers, sorted alphabetically (like SFML, boost, …).
+ Mirai Project headers, sorted alphabetically.

## Naming

+ **Files : mixed case starting with upper case.** Ex : `MyClass.hpp`
+ **Variables names must be mixed case starting with lower case.** Ex : `myVar`
+ **Classes and structs names must be mixed case starting with upper case.** Ex : `MyClass`
+ **Classes' member variables have "m_" prefix.** Ex : `m_myMemberVar`
+ **Global variables have "g_" prefix.** Ex : `g_myGlobalVar`
+ **Static variables have "s_" prefix.** Ex : `s_myStaticVar`
+ **Methods or functions names must be verbs and written in mixed case starting with lower case.** Ex : `getBuffValue`
+ **Namespaces names should be all lower case.** Ex : `mynamespace`

## Variable and Array Initialization

Prefer use a braced initialization list since you can avoid some programming errors.
```C++
int x{3};
int x{ 3 };
```

However, sometimes you may use parentheses... Referring to the Google styleguide :
> Be careful when using a braced initialization list {...} on a type with an std::initializer_list constructor.
> A nonempty braced-init-list prefers the std::initializer_list constructor whenever possible.
> Note that empty braces {} are special, and will call a default constructor if available.
> To force the non-std::initializer_list constructor, use parentheses instead of braces.
```C++
vector<int> v(100, 1);  // A vector of 100 1s.
vector<int> v{100, 1};  // A vector of 100, 1.
```
> Also, the brace form prevents narrowing of integral types.
> This can prevent some types of programming errors.
```C++
int pi(3.14);  // OK -- pi == 3.
int pi{3.14};  // Compile error: narrowing conversion.
```
[Source](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Variable_and_Array_Initialization)

## Braces

+ **Curly braces are placed on _its own line_ for function definitions.**
    - yes
    ```C++
    void myFunction()
    {
        // code
    }
    ```
    - _no_
    ```C++
    void myFunction() {
        // code
    }
    ```

+ **Other opening braces are placed on the line preceding the code block. Closing brace is placed on its own line.**
    - yes
    ```C++
    class MyClass {
        // code
    };

    namespace mp {
        // code
    }

    for (int i = 0; i < 10; ++i) {
        // code
    }
    ```
    - _no_
    ```C++
    for (int i = 0; i < 10; ++i)
    {
        // code
    }
    ```

+ Control clauses without a body should use empty braces.
    - yes
    ```C++
    for (int i = 0; i < 20; i++) {}
    ```
    - _no_
    ```C++
    for (int i = 0; i < 20; i++);
    ```

## Conditionals

**Curly braces** are **not required for single-line statements unless it spans multiple lines, use the else clause or comments are included**.
+ yes
```C++
if (condition)
    Instruction();

if (condition) {
    Instruction();
}

if (condition) {
    // A comment
    Instruction();
}

if (condition) {
    Instruction(arg1,
                arg2,
                arg3);
}

if (condition) {
    Instruction();
}
else {
    Instruction();
}
```
+ _no_
```C++
if (condition)
    // A comment
    Instruction();

if (condition)
    Instruction(arg1,
                arg2,
                arg3);

if (condition)
    Instruction();
else
    Instruction();
```

## Spaces

+ A space precedes an opening parenthesis.
+ A space follows a closing parenthesis.
+ The two first rules are not used for functions calls or final closing parenthesis in conditions.
+ A space follow a comma. `myFunction(arg1, arg2, ...)`
+ No space between a type and its reference `&` or pointer `*` specifier.
+ A space follows the `operator` keyword (`+`, `-`, etc).
+ No trailing spaces.
+ A space before and after a colon. `for (auto i : myVector)`
+ Usually no space inside parentheses. `if (condition) ...`
+ No space precedes a semi-colon.

## Type conversion

**Use modern cast.** No C-style casts (int)value or function-style casts int(value) are used. **Use `static_cast`, `const_cast`, `reinterpret_cast` and `dynamic_cast`**.

Type conversions between signed integers, unsigned integers and floating point types (as well as between different types of the same category) are performed explicitly using `static_cast`.

## Namespaces

The public API is contained in `mp` namespace.
You can use `mp::priv` for private classes or functions.

**The `using` directive is prohibited in headers files** and tolerated for repetitive use of names **in implementation files if you specify what you are using _explicitly_**.
+ yes
```C++
// Header file
#include <string>

std::string myFunction();
```
```C++
// Implementation file.
#include <string>

int main()
{
    std::string myString;
    return 0;
}

// OR //

using std::string;

int main()
{
    string myString;
    return 0;
}

// OR //

int main()
{
    using std::string;

    string myString;
    return 0;
}
```
+ _no_
```C++
// Header file
#include <string>

using namespace std;

string myFunction();

// NOR //

using std::string;

string myFunction();
```
```C++
// Implementation file
#include <string>

using namespace std;

int main()
{
    std::string myString;
    return 0;
}
```

## Classes

If you override a method use override keyword.
```C++
class ParentClass
{
public:
    void update();
};

class ChildClass : ParentClass
{
public:
    void update() override;
};
```

Method or classes that you don't want to be overridden should be marked with final keyword
```C++
class SomeClass final
{
public:
    void update() final;
};
```

Use the C++ keyword `explicit` for __constructors callable with one argument or constructors where every parameter after the first has a default value__.
It avoid undesirable conversions.
This should not be applied to copy or move constructors.
Mark these exceptions with clear comments.
See details [here](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html#Explicit_Constructors) and [here](http://en.cppreference.com/w/cpp/language/explicit).
```C++
class SomeClass
{
public:
    explicit SomeClass(int);
};
```

Moreover, constructors that take only a `std::initializer_list` may not be explicit to permits its construction from a braced initializer list:
```C++
MyClass m = {1, 2};
MyClass FuncThatReturnMyClass() { return {1, 2}; }
FuncThatTakeMyClassAsParameter({1, 2});
```

## Loops

Don't let running loops if it's not required.

+ yes
```C++
bool isInVector(std::vector<int> vect, int element)
{
    for (auto&& value : vect) {
        if (value == element)
            return true;
    }
    return false;
}
```
+ _no_
```C++
bool isInVector(std::vector<int> vect, int element)
{
    bool found = false;
    for (auto&& value : vect) {
        if (value == element)
            found = true;
    }

    return found;
}
```

# Git workflow

**If possible, one line per comment commit (not too much features in one time)**

Mirai Project git workflow is based on [SFML Git Workflow](http://www.sfml-dev.org/workflow.php).
+ Create a branch `feature/feature_name`, `bugfix/name` or `enhancement/name` for every new features, bugfix or enhancement.
+ Create a pull request to merge into master or another branch if necessary.
+ Pull requests are reviewed and tested before being merged.
+ Merged branch can be deleted.
+ Releases receive a tag based on the version number.

