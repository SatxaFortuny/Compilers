As a way to practice, I've created this repository to make sort of a tutorial and document the way I learned how to create compilers. The way I learned follows the following workflow:
1. I create an agent that contains the manuals of all the tools I use in this project. 
2. Then I instruct it to make sort of a tutorial in which I begin with one archive and with some of the project's goals, not all just at once.
3. Then I move to the next archive and I keep iterating until I finally have done everything the project says.

** First iteration: calc.l **
We will implement the following rules:
    1. Spaces and tabs are ignored
    2. Single line comments such as # or // are ignored
    3. Integers are recognized
    4. \n are recognized as EOL
    5. The rest of the characters are marked as incorrect
Testing:
    1. Single number. OK
    2. Single number with comment. OK
    3. Single line comment. OK
    4. Random characters. NOT OK
    5. All of the above with blank spaces and tabs. OK