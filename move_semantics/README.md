# Move Semantics in C++
- This is a collection of links, docs, references, tips and tricks related to Move Semantics in C++
- Also see [lvalues and rvalues](https://github.com/nicolcarstens/Nix-Uni-Cpp/tree/master/lvalues_and_rvalues)
- This is a *sandbox* collection. Format will not always be perfect and uniform. 

### A note on `std::move()`

*Remember, `std::move` is nothing more than a cast to an rvalue reference. In itself it doesn't actually move anything. Additionally, the language only states that a moved from object is in a valid/destructible state but apart from that doesn't say anything about its content - it may still be intact, it may not be or (like `std::unique_ptr` it may be defined to have specific content (nullptr)) - it all depends on what the move constructor/move-assignment-operator implements.* - from [Stack Overflow](https://stackoverflow.com/questions/42795683/using-an-object-after-stdmove-doesnt-result-in-a-compilation-error) 

## Links
- [Rule of Five](https://cpppatterns.com/patterns/rule-of-five.html)
- [C++ Core Guidelines - GitHub](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- [Look at Smart Pointers - for Beginners](https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c)
- [Moving Smart Pointers in and out of Functions](https://www.internalpointers.com/post/move-smart-pointers-and-out-functions-modern-c)
- [What is std::move and when should it be used - Stack Overflow](https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used)
- [Rvalue references and move constructors - C++11 Wiki](https://en.wikipedia.org/wiki/C%2B%2B11#Rvalue_references_and_move_constructors)
- [C++ Rvalue References Explained by Thomas Becker](http://thbecker.net/articles/rvalue_references/section_01.html)
- [Rvalue References Explained, by Thomas Becker](http://thbecker.net/articles/rvalue_references/section_02.html)