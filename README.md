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
PascalCase is used for user defined type names and functions
and public fields.

Private fields and function parameters use camelCase.

Namespaces begin with lower case and with words_seperated_with_underscores.


### Build Instructions:
Use cmake. External liberaries, such as `fmt` are not a 
part of the project and need to be installed separately, according
to the instructions on the platform. When invoking cmake commands, 
appropriate flags need to be passed to make the libraries discoverable
using `find_package` comand.

In addition the project uses `ranges-v3` instead of standard ranges due
to clang bugs at the moment of writing. 

