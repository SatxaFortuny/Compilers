As a way to practice, I've created this repository to make sort of a tutorial and document the way I learned how to create compilers. The way I learned follows the following workflow:
1. I create an agent that contains the manuals of all the tools I use in this project. 
2. Then I instruct it to make sort of a tutorial in which I begin with one archive and with some of the project's goals, not all just at once.
3. Then I move to the next archive and I keep iterating until I finally have done everything the project says.

## First iteration: calc.l 

This file consist of a scanner that detects the input given by the user and transforms those characters into tokens.

We will implement the following rules:
    1. Spaces and tabs are ignored.
    2. Single line comments such as # or // are ignored.
    3. Integers are recognized.
    4. '\n' are recognized as EOL.
    5. The rest of the characters are marked as incorrect.

### Testing:
    1. Single number. **OK**
    2. Single number with comment. **OK**
    3. Single line comment. **OK**
    4. Random characters. **NOT OK**
    5. All of the above with blank spaces and tabs. **OK**

## First iteration: calc.y
Now that we have the flex scanner, we can analyze those tokens and convert them into meaningful sentences.
What we will do basically is define the tokens that we will receive and then try to put it all into a rule "program".
This program rule will contain lines which will contain rules.
We also should save in the scanner the value into the variable "yylval.ival" so later Bison can access it.

### Testing:
We should now see if Bison has only tokens and not rubbish. Also if it can access the values.
```text
--- Starting Parser (Bison + Flex) ---
123
(1) TRACKED: NUMBER (123)
(2) TRACKED: EOL
BISON: NUMBER (123) + EOL
123 //comment
(2) TRACKED: NUMBER (123)        
(2) IGNORED: SPACE OR TAB        
(2) IGNORED: SINGLE LINE COMMENT.
(3) TRACKED: EOL
BISON: NUMBER (123) + EOL
wake up
(3) TRACKED: LEXICAL ERROR
(3) TRACKED: LEXICAL ERROR
(3) TRACKED: LEXICAL ERROR
(3) TRACKED: LEXICAL ERROR
(3) IGNORED: SPACE OR TAB
(3) TRACKED: LEXICAL ERROR
(3) TRACKED: LEXICAL ERROR
(4) TRACKED: EOL
BISON: EOL
text ```