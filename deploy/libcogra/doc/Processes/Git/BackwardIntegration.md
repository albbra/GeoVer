# Backward integrate changes from one branch into another
This document describes, how to backward integrate changes from one branch to another.

This is useful for
- Incorperate changes from any other branch into the master branch

## Backward Integration

1. Make sure you are on the newest version of your source branch
	- git-bash
		- `git checkout [source]`
		- `git pull`
		- [source] is the name of your source branch
		
1. Make sure you are on the newest version of your target branch
	- git-bash
		- `git checkout [target]`
		- `git pull`
		- [target] is the name of your source branch (`master` most of the time)
		
1. Backward integrate changes from target to source branch 
	- git-bash
		- `git checkout [target]`
		- `git merge [source]`
		- [target] is the name of your source branch (`master` most of the time)
		- [source] is the name of your source branch
		
1. Optional: Push updated branch to remote location
	- git-bash
		- `git push`
		
1. Optional: Delete source branch local
	- git-bash
		- `git branch -d [source]`
		
1. Optional: Delete source branch remote location
	- git-bash
		- `git push origin --delete [source]`