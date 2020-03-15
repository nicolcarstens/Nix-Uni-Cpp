# Other Tools 

* This folder contains tools and tricks not specific to C++. 
* It really should not be here but it will be here for the moment as a quick and dirty scratch-pad.

### git command line (CL)

```
>> git pull 

>> git add -A      // stages ALL changes <<-- check
>> git add *       // stages ALL changes <<-- check
>> git add .       // new files and mods, not deletions 
>> git add -u      // mods & deletions, no new files 
>> git add xyx.c   // adds file xyz.c
 
>> git rm -r xyz   // remove/delete directory xyz & content recursively 

>> git diff --name-only --cached 

>> git commit -m "commit message" 

>> git push 
```

### C++ CL compile

```
>> g++ -std=c++14 -pthread myfile.cpp
>> ./a.out 

... or ... 

>> g++ -std=c++14 -pthread myfile.cpp && ./a.out 
```

