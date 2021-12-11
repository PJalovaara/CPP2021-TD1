# Test files

It is a common practice to do unit tests of each class before you integrate it into the project to validate its operation.
In this folder, you can create your own unit test files to validate the operation of your components.

> It might be a good idea to also take some notes about the tests since you are required to 
  report these in the final report.

# Unit Tests

## Test of class Game

We start the game with no towers nor enemies to check for memory leaks. We open the window build towers, start enemy waves, and close the window manually.

**Involved Classes:** Game, Tower, Enemy, Bullet

**Test run:** test1

**Results:** We get a fixed amount of memory leaks no matter how many towers or enemies we build.


## Test of class Editor

We open the editor and check for memory leaks when using it manually.

**Involved Classes:** Editor

**Test run:** test2

**Results:** We get the same fixed amount of memory leaks no matter how we build paths.


## Test of class Game

Opens the menu and builds two towers and clears them using CLEAR TOWERS. Addds two new towers. Starts a new enemy wave and closes the window. We check for memory leaks.

**Involved Classes:** Game, Tower, Enemy

**Test run:** test3

**Results:** More possibly lost memory than in tests 1 and 2.




