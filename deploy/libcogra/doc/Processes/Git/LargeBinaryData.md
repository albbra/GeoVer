# Binary Data
If you have your own repository, you will put in source code and documentation, but you might also want put in large binary data.

Adding binary data in git is problematic, because it cannot track changes easily and therefore versioning binary data in git uses a lot of disk memory.

Therefore, we use **git lfs** which provides a memory efficent way of managing large binary files in a git repository.

# Use Existing Binary Data

In libcogra (that you are probably use as a submodule), there is already some data in the folder `libcogra/data`.

CMake copies that once you click "Configure" in the CMake GUI to your build directory.
For many people, that data will be sufficient. 


# Create a Subfolder for Your Own Binary Data
However, you might feel the need to add your own data to your own repository.

Support your repository is called `ComputerGraphics`.
You have libcogra as a submodule in `ComputerGraphics/libcogra`.

Now we add our own folder for binary data:

1. Open git bash.

1. Create a folder where you want to store your binary data, e.g., `data`
1. `git lfs track "data/**"`
This will make sure, that all files in the folder data and subfolders therein wil be tracked by git lfs. 

1. `git add .gitattributes`
Effectively, the last command has created a file `.gitattributes`.
That file contains information about what files will be tracked with git lfs.
Now You have to add that file to your repository.

1. Eventually, you can add files as usally
e.g., `git add data/LargeFile.zip`.
Remember all files in folder data will be tracked by git lfs.
