# Copy-elision and Return Value Optimization (RVO)
- This is a collection of links, docs, references, tips and tricks related to Move Semantics in C++
- Also see [lvalues and rvalues](https://github.com/nicolcarstens/Nix-Uni-Cpp/tree/master/lvalues_and_rvalues)
- This is a *sandbox* collection. Format will not always be perfect and uniform. 

### from Copy-elision and RVO Wiki

In C++ computer programming, copy elision refers to a compiler optimization technique that eliminates unnecessary copying of objects. The C++ language standard generally allows implementations to perform any optimization, provided the resulting program's observable behavior is the same as if, i.e. pretending, the program were executed exactly as mandated by the standard.

The standard also describes a few situations where copying can be eliminated even if this would alter the program's behavior, the most common being the return value optimization. Another widely implemented optimization, described in the C++ standard, is when a temporary object of class type is copied to an object of the same type. As a result, copy-initialization is usually equivalent to direct-initialization in terms of performance, but not in semantics; copy-initialization still requires an accessible copy constructor. The optimization can not be applied to a temporary object that has been bound to a reference.

## Links
- [C++ Core Guidelines - GitHub](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
- [Copy-elision - Wiki](https://en.wikipedia.org/wiki/Copy_elision)