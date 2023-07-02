# COMP 141 Course Project Phase 3.1
# Test driver module
# Kaung Khant Pyae Sone
# k_kaung@u.pacific.edu

import sys
from scanner import scanner
from myParser import parser, printTree
from evaluator import evalute

if __name__ == "__main__":
    if len(sys.argv) < 3:
        raise Exception("ERROR: Incorrect usage, main.py input.txt output.txt")

    inputF = sys.argv[1];
    outputF = sys.argv[2];

    fout = open(outputF, 'w+')

    print(f"\nInput: {inputF}, Output: {outputF}\n")
    with open(inputF) as file:
        lines = file.readlines()

    currLine = 1
    for line in lines:
        # Strip endline
        outStr = f"Line {currLine}: {line.strip()}"
        print(outStr)
        fout.write(outStr + '\n')

        # Run scanner on input line
        result = scanner(line, currLine)

        # Prints tokens obtained from scanner
        for token in result.tokens:
            outStr = f"{token.type}, {token.value}"
            print(outStr)
            fout.write(outStr + '\n')
        for error in result.errors:
            outStr = f"Error on line {error.lineNum}: {error.value}"
            print(outStr)
            fout.write(outStr + '\n')

        # Checks if there are any errors
        # If none, parse line
        if len(result.errors) == 0:
            ast = parser(result.tokens, currLine, line)
            print("\n AST (tilt head left): \n")
            printTree(ast)
            evalResult = evalute(ast)
            print(f"Output: {evalResult.value}")

        print()
        fout.write('\n')
        currLine += 1