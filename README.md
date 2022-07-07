This repository is the result of reading through Discovering Modern C++ 2nd Edition by Peter 
Gottschling.
It contains slightly rewritten examples from the book, together with
additional examples that illustrate concepts described in the book,
as well as solutions to exercsies.

### Declaimer:
This is an exercise in learning/using cmake more than learning C++.
Therefore, many examples / exercises might be "overengineered" in order
to be able to use CMake features. Expect unnecessary splits into 
headers and libraries, as well as useless tests.

### Naming conventions:
using snake_case with first letter capitlized
for public members of class, class names and library functions.

### Build Instructions:
Use cmake. External liberaries, such as `fmt` are not a 
part of the project and need to be installed separately, according
to the instructions on the platform. When invoking cmake commands, 
appropriate flags need to be passed to make the libraries discoverable
using `find_package` comand.

