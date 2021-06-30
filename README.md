# Compiler
This is a C++ implementation of an ANSI-C to MIPS compiler as part of a project for the Electronic and Information Engineering Year 2 course at Imperial College London. The submission also includes a basic ANSI-C to Python translator. Both deliverables were completed in accordance with the following specification: https://github.com/LangProc/langproc-2019-cw

To construct the executable:
`make bin/c_compiler`

To run the Python translator:
`bin/c_compiler --translate [source-file.c] -o [dest-file.py]`

To run the MIPS compiler
`bin/c_compiler -S [source-file.c] -o [dest-file.s]`

To remove all compiled files use command:
`make clean`

# Time Management
There is also a pdf containing our time management logs that were contiually updated during the course of the project 

# Acknowlegdements
Dr John Wickerson for support throughout the duration of the project 
