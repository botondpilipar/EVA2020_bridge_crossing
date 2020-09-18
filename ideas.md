# Visual plan

                     /
                    /
         *         /      *
         *        /       * 
         *       /        *
         *      /         *

- Players will form a table or single row
- Each player is a rectangle which has a number and a corresponding colour
- User chooses three players to pass over the bridge
  - Slowest player will determine the speed of the whole pass
- User chooses one player to pass to the original side
  - Player speed will determine the pass speed


# Implementation ideas
1. State machine transition will determine the animation
    a, Transitions will be QAbstractTransition
        - this approach will enable me to set conditions on transitions
    b, States will include the following
        - CrossSelection
          - User is selecting 3 players to cross
        - CrossAnimationOnGoing
          - User cannot click any more buttons, until animation is finished
        - ReturnSelection
          - User is selecting one player to return with the lamp
        - ReturnAnimationOnGoing
          - User cannot click any more buttons, until animation is finished
        - GameFinished
          - Game is won, a message is displayed, high score displayed
          - Possibilty is displayed for player to start a new game