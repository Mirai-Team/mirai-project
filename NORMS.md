## Norms to fulfil.
----------------

________
### Naming :

- File containing only functions : all lower cases with underscore between words. Ex : my_function.hpp
- File containing a class : mixed case starting with upper case. Ex : MyClass.hpp

- Variables names must be mixed case starting with lower case. Ex : myVar

- Classes names must be mixed case starting with upper case. Ex : MyClass
- Classes' private attributes should have underscore suffix. Ex : myPrivateAttribute_

- Methods or functions names must be verbs and written in mixed case starting with lower case. Ex : getBuffValue()

- Namespaces names should be all lowercase. Ex: mynamespace

________
### Documentation:

- Use doxygen comment style in order to describe files, functions, classes, methods.

________
### Other :

- Do not use #define
- No C in C++. Only C++.
- Use ISO/IEC 14882:2011 c++ norm (http://en.wikipedia.org/wiki/C%2B%2B11)
- If possible, one line per comment commit (not too much features in one time).
- Last update at the top of CHANGELOG file.
- No "using namespace" in header files.
- No implicit Else.
