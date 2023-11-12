# Release A Version

This documents guides you as developer through the process of creating a new version.

A new version is neccessary, if you upload a new Base-Framework for student lab assignments.
Every version that goes into moodle must have a version.
The Base-Framework shall remain stable throughout the semster, whenver possible.

## Deploy Base-Framework using CMake

In CMake, enable the flag COGRA_DEPLOY. 

This will copy only the required resource files from cogra and its contribution libraries to build a version to your build directory into the folder ``deploy``.

That what is in the ``depoly`` folder is called the Base-Framework.

## Test

Make sure to test the new and the old assignments of this semester with the version that you wish to release

## Changelog

Put the most important changes into the ChangeLog.md file located in libcogra's root directory.

## Decide for Version number

We use a versioning scheme that consists of three integer values prefixed with a "v", e.g., "v1.2.3".

We use the following versioning scheme:
- The first number ("1" in this example) is the major version (starting at 1), 
- the second number ("2" in this example) is the minor version (starting at 0), and the
- third number ("3" in this example) is the patch version (starting at 0).

Increase the numbers as follows:
- Increase the first number only upon large changes preferably during summer break.
- Increase the second number in case you add important new feature. Try to add features during semester only when they are absolutely neccessary.
- Increase the third number for fixes that are required during the semester.

# Git

Commit and push your changes. Add a version tag

``git tag -a v1.2.3 -m "Release new version"``

Communicate the tags to rest of origin.

``git push origin --tags``

## Upload to Moodle

Zip the ``deploy`` folder in your build directory and upload it to moodle.