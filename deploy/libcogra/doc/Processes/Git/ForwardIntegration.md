# Forward integrate changes from one branch into another
This document describes, how to forward integrate changes from one branch to another.

This is useful for
- Incorperate changes from master branch into other branch

## Forward Integration


1. Make sure you are on the newest version of your source branch
	- git-bash
		- `git checkout [source]`
		- `git pull`
		- [source] is the name of your source branch (`master` most of the time)


1. Optional: Create target branch local and push to remote location
	- git-bash
		- `git checkout -b [target]`
		- `git push origin -b [target]`
		

1. Make sure you are on the newest version of your target branch
	- git-bash
		- `git checkout [target]`
		- `git pull`
		- [target] is the name of your source branch
		
1. Forward integrate changes from target to source branch 
	- git-bash
		- `git rebase [source]`
		- or `git merge [source]` if `git rebase [source]` does not work
		- [source] is the name of your source branch (`master` most of the time)
		