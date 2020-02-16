# Smart Pointers in C++
- This is a collection of links, docs, references, tips and tricks related to Smart Pointers in C++
- This is a *sandbox* collection. Format will not always be perfect and uniform. 

### A note on `make_unique` and `make_shared`

From [C++ Core Guidelines:](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)

- **Rule 22 : Use `make_shared()` to make `std::shared_ptr`**
- **Rule 23 : Use `make_unique()` to make `std::unique_ptr`** 

The increased management overhead compared to raw pointers becomes in particular true if a `shared_ptr` is used. Creating a `shared_ptr` requires (1) the allocation of the resource using new and (2) the allocation and management of the reference counter. Using the factory function make_shared is a one-step operation with lower overhead and should thus always be preferred. (R22). This also holds for `unique_ptr` (R23), although the performance gain in this case is minimal (if existent at all).

But there is an additional reason for using the `make_...` factory functions: Creating a smart pointer in a single step removes the risk of a memory leak. Imagine a scenario where an exception happens in the constructor of the resource. In such a case, the object would not be handled properly and its destructor would never be called - even if the managing object goes out of scope. Therefore, make_shared and `make_unique` should always be preferred. Note that `make_unique` is only available with compilers that support at least the C++14 standard.

## Links
- [Rule of Five](https://cpppatterns.com/patterns/rule-of-five.html)
- [Look at Smart Pointers - for Beginners](https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c)
- [Moving Smart Pointers in and out of Functions](https://www.internalpointers.com/post/move-smart-pointers-and-out-functions-modern-c)