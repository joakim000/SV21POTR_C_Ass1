# Examination Assignment - 1
SV21POTR Continuous Integration (YH3556004-4)

Please note that you need to zip and submit the repository you created for the project and the deadline is 2021-12-07 23:59. The starter of the project has been attached to the assignment. 

In this assignment you are supposed to practice CI in order to develop a module
which has two functions to insert and extract data with a given length in bits and a
given start position to/from a buffer.
An example buffer:
![example buffer](example.png)

For example buffer_insert(array, 12, 6, 24) writes 011000 into bits 4 to 7 of array[1]
and bits 0 and 1 of array[2]. If we call buffer_extract(array, 12, 6) it shall return 24.

## Requirements
1. Make a private repository for the project on github.
2. You need to follow the Github Flow strategy.
3. Use TDD to develop the buffer module. The module shall fully be tested.
4. To build and test your code use make and a Makefile.
5. In Github Actions automate your workflow using
    1. A workflow which only is triggered when you make a pull request from your
feature branch to the mainline ino order to build and test the module.
    2. A workflow which only is triggered when you push to the mainline in order to
build, test and create a release. In the release you shall include the
executable test files.
    3. The workflows shall be run on ubuntu and created by yourself.
6. Don’t change the header file of the module and don’t include any library or
create new functions in the implementation file.
