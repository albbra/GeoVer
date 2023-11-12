# Add a new submodule
## Clone the submodule
Get the submodule:
```
git submodule add https://github.com/01org/tbb.git
```

Output:
```Cloning into 'D:/code/Lecture/ParPro/libcogra/contrib/submodules/tbb'...
remote: Enumerating objects: 43, done.
remote: Counting objects: 100% (43/43), done.
remote: Compressing objects: 100% (41/41), done.
remote: Total 12159 (delta 3), reused 39 (delta 2), pack-reused 12116
Receiving objects: 100% (12159/12159), 34.11 MiB | 1.52 MiB/s, done.
Resolving deltas: 100% (9734/9734), done.
warning: LF will be replaced by CRLF in .gitmodules.
The file will have its original line endings in your working directory.
```

Update and init the submodule:
```
git submodule update --init --recursive
```

Checkout a specific version:
```
git checkout 8ff3697f544c5a8728146b70ae3a978025be1f3e
```

Commit.

## Integrate into build pipeline
In case the project you include supports CMake, open `libcogra/contrib/submodules/CMakeLists.txt`