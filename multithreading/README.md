# Multithreading in C++
- This is a collection of links, docs, references, tips and tricks related to multithreading in C++
- This is a *sandbox* collection. Format will not always be perfect and uniform. 

Quick little example from [cppreference.com](https://en.cppreference.com/w/cpp/thread/thread/thread):

```
int main()
{
    int n = 0;
    foo f;
    baz b;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    std::thread t5(&foo::bar, &f); // t5 runs foo::bar() on object f
    std::thread t6(b); // t6 runs baz::operator() on object b
    t2.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of foo::n is " << f.n << '\n';
}
```


## Links
- [Top 20 C++ multithreading mistakes and how to avoid them](https://www.acodersjourney.com/top-20-cplusplus-multithreading-mistakes/)