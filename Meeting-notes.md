# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any

# Meeting 06.12.2021 10:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Worked on multiple features over the weekend with Perttu.

2. Anna Huttunen

   Implemented a beta version of PooperGoose.

3. Perttu Jalovaara

   Worked on multiple features over the weekend with Antti.

4. Atte Tommiska

   Improved the code to fit the Google C++ style standards.

## Challenges

1. Documenting the code rigorously.
2. Fixing the final memory leaks.
3. Writing the project documentation.

## Actions (Code)
1. Antti is going to improve and unify the tick/frame rate of the game.
2. Anna is going to document (Doxygen) the source code with Atte.
3. Perttu is going to change deletes to sells. And improve wave generation logic.
4. Atte is going to document (Doxygen) the source code and improve code quality.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Short summary of current project status. 

### TODOs (Writing)
1. Antti: Project overview
2. Anna: How to use the software and Work Log
3. Perttu: Software structure
4. Atte: Testing

# Meeting 2.12.2021 09:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Added the money earning principle. Added also Cruiseship to enemies. Made upgrading towers possible.

2. Anna Huttunen

   Did enemygraphics and started PooperGoose.

3. Perttu Jalovaara

   Made the alpha version of level editor.

4. Atte Tommiska

   Has worked hard on the main menu and brainstormed options for implementation. Valgrind memcheck.

## Challenges

1. Memory leaks and testing.
2. Making levels.

## Actions
1. Antti is going to make enemy abstract. Adds parameter paths to game (QList(QList(QPointF))). Sound effects. Update LIBS directory.
2. Anna is going to finish PooperGoose and study Doxygen to be able to do documentation on atleast enemies and towers.
3. Perttu is going to make the enemies choose a path randomly or with some intelligence i.e. virtual function ChoosePath for enemies. Enemywave functionality. Sound effects. Abstract Projectiles class. 
4. Atte is going to finish the main menu. Tests (memory leaks).

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
The biggest challenges are the main menu, running different levels and finding and fixing all memory leaks. The game is working, and now we are adding more functionalities to get more points and a more entertaining game. 

### TODOs
1. Antti: Enemy abstract. Parameter paths to game (QList(QList(QPointF))). Sound effects. LIBS directory.
2. Anna: Finish PooperGoose (only hits some enemies, dynamic cast). Doxygen for enemy and tower classes.
3. Perttu: Virtual function ChoosePath. Enemywaves. Sound effects. Abstract Projectiles class.
4. Atte: Main menu. Tests.


# Meeting 22.11.2021 10:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Added startRound, clearTowers and healtBars to the game. 

2. Anna Huttunen

   Nothing.

3. Perttu Jalovaara

   Centered all graphical elements. Fixed aiming.

4. Atte Tommiska

   Studied Doxygen and talked with other students that have taken this course.

## Challenges

1. Implementing level editor.
2. Time management. 

## Actions
1. Antti is going to add the money earning principle. Add Cruiseship to enemies. Upgrade towers.
2. Anna is going to add different enemies and Pooper goose to Towers.
3. Perttu is going to do the level-editor with path exportation.
4. Atte is going to implement the main menu.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
We have three weeks left, but effectively two weeks, because we want to get the game ready by Monday 6.12. to have enough time for final testing and documentation. Now we have the base classes and some functions for them. We also have subclasses for some towers already. Coding continues.

### TODOs
1. Antti: money earning principle. Cruiseship to enemies. Upgrade towers.
2. Anna: different enemies and Pooper goose to Towers.
3. Perttu: level-editor with path exportation.
4. Atte: main menu.


# Meeting 18.11.2021 09:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen (NOT PRESENT)
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Coded the demo version of the game according to the tutorial ("C++ Qt Game Tutorial" by Abdullah).

2. Anna Huttunen

   Brainstormed visuals for the game.

3. Perttu Jalovaara

   Acted as a rubber duck while Antti did the coding. 

4. Atte Tommiska

   Fixed goose. Generated the first version of Docs for the game.

## Challenges

1. Level editor and text encoding for levels.
2. Main menu and reset/start buttons for the game.

## Actions
1. Antti is going to develop the vital parts of the game.
2. Anna is going to draw graphics with her newly-obtained drawing pad.
3. Perttu is going to work on the level-editor with path exportation.
4. Atte is going to code the tentative main menu.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
We have a working demo as planned. Coding continues.

### TODOs
1. Antti: Enemy destructability, player HP, start and reset buttons.
2. Anna: Draw geese and teekkaris, teekkari class inheritance and comments.
3. Perttu: Level editor: path creation (saved to .txt, input as param to Game)
4. Atte: Create a tentative main menu with buttons to game and level editor.

# Meeting 08.11.2021 09:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen (NOT PRESENT)
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Studied the Qt library extensively and implemented a small graphical test.

2. Anna Huttunen

   Did the majority of the work on the Project Plan.

3. Perttu Jalovaara

   Sketched concept art for geese and finished the Project Plan.

4. Atte Tommiska

   Resolved challenges that appeared in compiling the graphical test.

## Challenges

1. Figuring out how to render an arbitrary goose with Qt.
2. Implementing a simple test level with one enemy.

## Actions
1. Antti is going to code some basic functionalities for the classes.
2. Anna is going to work on art for the game.
3. Perttu is going to work on representing enemy paths in the game.
4. Atte is going to solve the goose render issue.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
We have a clear plan and we will now attempt to implement it. Issues will be faced courageously.

### TODOs
1. Antti: Code some classes!
2. Anna: Draw geese and teekkaris!
3. Perttu: Create paths!
4. Atte: Fix goose!

# Meeting 01.11.2021 09:15

**Participants**: 
1. Antti Haavikko
2. Anna Huttunen
3. Perttu Jalovaara
4. Atte Tommiska 

## Summary of works
1. Antti Haavikko 
   
   Studied the A+ project materials. Tested CMake in combination with the Qt library.

2. Anna Huttunen

   Studied the A+ project materials.

3. Perttu Jalovaara

   Studied the A+ project materials. Studied Google's C++ Style Guide. Brainstormed some game ideas.

4. Atte Tommiska

   Studied the A+ project materials. Studied Google's C++ Style Guide.

## Challenges

1. Finishing the project plan due Friday.
2. Figuring out a way to create a working "sandbox" prototype of the game for testing purposes.

## Actions
1. Antti Haavikko is going to study some Qt tower defense tutorials.
2. Anna Huttunen is going to work on the project plan, including the object diagram.
3. Perttu Jalovaara is going to work with Anna on the project plan and study Git and Qt.
4. Atte Tommiska is going to study some Qt tower defense tutorials.

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
We have decided on the topic of the game and designed a tentative class hierarchy for the essential objects of the game.

### TODOs
1. Antti: Study Qt!
2. Anna: Finish the project plan!
3. Perttu: Help Anna finish the project plan!
4. Atte: Study Qt!
