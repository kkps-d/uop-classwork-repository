# COMP 141 Course Project Phase 3.1
# Parser module
# Kaung Khant Pyae Sone
# k_kaung@u.pacific.edu

from copy import deepcopy
from scanner import Token, TokenType

class Node:
    def __init__(self, value, left=None, right=None):
        self.left = left
        self.right = right
        self.value = value

def printTree(node, level=0):
    if node != None:
        printTree(node.right, level + 1)
        print(' ' * 4 * level + f"-> {node.value.value} :{node.value.type}")
        printTree(node.left, level + 1)

# Global variables
tokenList = []
lineNum = 0 # used for error reporting
rawLine = ''

def parser(tokens, n=0, line=''): # n and line are line number and raw line text, used for error reporting
    global lineNum, rawLine, tokenList
    lineNum = n
    rawLine = line
    tokenList = tokens
    return parseExpression()

def parseNumber():
    global tokenList
    num = tokenList[0]
    tokenList = tokenList[1:] # consumes token
    return Node(num)

def parseIdentifier():
    global tokenList
    idf = tokenList[0]
    tokenList = tokenList[1:] # consumes token
    return Node(idf)

def parseElement():
    global tokenList, lineNum, rawLine
    if len(tokenList) > 0 and tokenList[0].value == '(':
        tokenList = tokenList[1:] # consumes token
        tree = parseExpression()
        if len(tokenList) > 0 and tokenList[0].value == ')':
            tokenList = tokenList[1:] # consumes token
            return tree
        else:
            errorString = f'Line {lineNum}: Expected closing \')\' after expression\n -> {rawLine}'
            raise Exception(errorString)
    elif len(tokenList) > 0 and tokenList[0].type == TokenType.NUMBER:
        return parseNumber()
    elif len(tokenList) > 0 and tokenList[0].type == TokenType.IDENTIFIER:
        return parseIdentifier()
    elif len(tokenList) > 0 and tokenList[0].value == ')':
        errorString = f'Line {lineNum}: Invalid starting bracket \')\' \n -> {rawLine}'
        raise Exception(errorString)
    else:
        errorString = f'Line {lineNum}: Expression, number or identifier missing \n -> {rawLine}'
        raise Exception(errorString)

def parsePiece():
    global tokenList
    tree = parseElement()
    while len(tokenList) > 0 and tokenList[0].value == '*':
        token = tokenList[0]
        tokenList = tokenList[1:] # consumes token
        tree = Node(token, tree, parseElement())
    return tree

def parseFactor():
    global tokenList
    tree = parsePiece()
    while len(tokenList) > 0 and tokenList[0].value == '/':
        token = tokenList[0]
        tokenList = tokenList[1:] # consumes token
        tree = Node(token, tree, parsePiece())
    return tree

def parseTerm():
    global tokenList
    tree = parseFactor()
    while len(tokenList) > 0 and tokenList[0].value == '-':
        token = tokenList[0]
        tokenList = tokenList[1:] # consumes token
        tree = Node(token, tree, parseFactor())
    return tree

def parseExpression():
    global tokenList
    tree = parseTerm()
    while len(tokenList) > 0 and tokenList[0].value == '+':
        token = tokenList[0]
        tokenList = tokenList[1:] # consumes token
        tree = Node(token, tree, parseTerm())
    return tree