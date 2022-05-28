Student Name: Dylan Washburne

Project Name: washburne_cs580_project1

What I implemented: Four pilgrims are making a journey between two towers, through a treacherous desert containing an annoying mosquito.  An angry beast charges wildly, knocking the pilgrims off their path.

Directions (if needed): Just watch

What I liked about the project and framework: 
Simple enough to pick up and generate personal content without much issue.  
Functions were clearly named with obvious calls to components, and these were used in clear ways in the example behavior tree so that I could easily determine how to make my own.

What I disliked about the project and framework: 
Adding new content requires generating 2 new files (cpp and h), linking those 2 filesin 2 locations to be usable in trees, and manually adding the tree I just created.  Further, it is aware of all the trees in the folder but crashes if I'm not explicit about including every single one.  
Interactions between entities are very cumbersome to program when each node is staticly-defined, not allowing inputs like "Collision" with a subinput of  "Tower".
When attempting to add new nodes, or replace existing ones, it becomes a dance of remembering everythings' depth because the new node has to shuffle its way all the way up the tree.

Any difficulties I experienced while doing the project: No real difficulties

Hours spent: 8

New selector node (name): 
C_EternalSequencer

New decorator nodes (names):
D_Repeater
D_RepeatRandomTimes

10 total nodes (names):
L_CollideCommon
L_CollidePredator
L_CollideTower
L_ExponentialToRandomPosition
L_Float
L_Jiggle
L_Knockback
L_MigrateTowers
L_MoveToClosestVictim
L_Ramming
L_Rotate
L_StepBackward

4 Behavior trees (names):
Ease
Predator
Wanderer
Tower_Animation

Extra credit:
nope