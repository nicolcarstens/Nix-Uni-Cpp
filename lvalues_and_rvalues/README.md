# lvalues and rvalues in C++
- This is a collection of links, docs, references, tips and tricks related to lvalues and rvalues in C++
- This is a *sandbox* collection. Format will not always be perfect and uniform. 

### What be these?!
- We all know 'simple' lvalues as variables. Dangerously over simplified definition: it's a variable with an name and memory space we can easily find
- An rvalue can be thought of as a temporary variable/area/space for which we don't have a name ... the results (for example) of a calculation

### lvalue References
- lvalue references are old news...
- `void myFunc(int &foo)`
- `foo` is a lvalue reference. You call `myFunc` with and lvalue and a reference to it is used (call-by-reference implies no time wasted copying)
- And this brings us to rvalue references ...  

### rvalue References
- rvalue references are news... and you can indentify it when you see `&&foo` rather than  `&foo` in the parameter list - for example:
- `void myFunc(int &&foo2)`
- `foo2` is a rvalue reference. You call `myFunc` with an rvalue and a reference to it is used (call-by-reference implies no time wasted copying)

##Related Topics?
- Rule of Five 
- [Move Semantics](https://github.com/nicolcarstens/Nix-Uni-Cpp/tree/master/move_semantics)
- Smart Pointers

## Links
- [Rule of Five](https://cpppatterns.com/patterns/rule-of-five.html)
- [Look at Smart Pointers - for Beginners](https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c)
- [Moving Smart Pointers in and out of Functions](https://www.internalpointers.com/post/move-smart-pointers-and-out-functions-modern-c)
- [How to pass a Unique Pointer to a Constructor or Function - Stack Overflow](https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function/8114913#8114913)
- [Rvalue references and move constructors - C++11 Wiki](https://en.wikipedia.org/wiki/C%2B%2B11#Rvalue_references_and_move_constructors)
- [C++ Rvalue References Explained by Thomas Becker](http://thbecker.net/articles/rvalue_references/section_01.html)