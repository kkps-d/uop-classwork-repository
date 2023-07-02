# COMP 141 Course Project Phase 3.1
# Scanner module
# Kaung Khant Pyae Sone
# k_kaung@u.pacific.edu

from enum import Enum
import re

class TokenType(Enum):
    NUMBER = 0
    SYMBOL = 1
    IDENTIFIER = 2
    ERROR = 3

class Token:
    def __init__(self, type, value, lineNum):
        self.type = type
        self.value = value
        self.lineNum = lineNum

class ScannerReturn:
        def __init__(self):
            self.tokens = []
            self.errors = []

def scanner(line, lineNum):
    scannerReturn = ScannerReturn()

    # Removes newLine
    line = line.strip()
    
    while len(line) > 0:
        # Skip white space
        if line[0] == ' ' or line[0] == '\t':
            line = line[1:]

        # Token is identifier
        elif re.search("[A-Z]|[a-z]", line[0]):
            matchedStr = re.search("([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])*", line).group()
            line = line[len(matchedStr):]
            scannerReturn.tokens.append(Token(TokenType.IDENTIFIER, matchedStr, lineNum))
            # print(f"identifier: {matchedStr}")

        # Token is number
        elif re.search("[0-9]", line[0]):
            matchedStr = re.search("[0-9]+", line).group()
            line = line[len(matchedStr):]
            scannerReturn.tokens.append(Token(TokenType.NUMBER, matchedStr, lineNum))
            # print(f"number: {matchedStr}")

        # Token is symbol
        elif re.search("\\+|\\-|\\*|/|\\(|\\)", line[0]):
            matchedStr = line[0]
            line = line[1:]
            scannerReturn.tokens.append(Token(TokenType.SYMBOL, matchedStr, lineNum))
            # print(f"symbol: {matchedStr}")

        # Token is invalid
        else:
            errChar = line[0]
            line = line[1:]
            scannerReturn.errors.append(Token(TokenType.ERROR, errChar, lineNum))
            break
            # print(f"error: {errChar}")

    return scannerReturn