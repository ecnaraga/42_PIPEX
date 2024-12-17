# 42_PIPEX

Goal

    - Mandatory : Write a program to handle one pipe with an input redirection and an output redirection
    - Bonus : Handle multiple pipes + accept an input redirection with a delimiter
    
Launch

    - Compile with the makefile
    
    - Mandatory : ./pipex <input_redirection> <first_cmd> <second_cmd> <output_redirection>
      => Should behave like : < fileIn cmd1 | cmd2 > fileOut

    - Bonus : ./pipex <input_redirection> <first_cmd> ... <final_cmd> <output_redirection>
      => Should behave like : < fileIn cmd1 | ... | cmdfinal > fileOut 

    - Bonus : to test the redirection with delimiter : ./pipex here_doc <Delimiter> <first_cmd> <second_cmd> <output_redirection>
      => Should behave like : << delimiter cmd1 | cmd2 > fileOut

Authorized functions

    - open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
    - megalibft

What is forbidden

    - Function lseek
    - Global variables
    - for
    - do ... while
    - switch
    - case
    - goto
    - Ternary operators
    - Variable-size tables

The project must be written in accordance with the 42's Norm
