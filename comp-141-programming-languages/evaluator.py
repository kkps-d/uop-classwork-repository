# COMP 141 Course Project Phase 3.1
# Evaluator module
# Kaung Khant Pyae Sone
# k_kaung@u.pacific.edu

from myParser import Token, TokenType

stack = []

def evalute(ast):
    global stack
    stack = []
    traverse_tree(ast)
    return stack[0]
    
def traverse_tree(ast):
    global stack
    if ast != None:
        stack.append(ast.value)
        try_evalute()
        traverse_tree(ast.left)
        traverse_tree(ast.right)

def try_evalute():
    global stack
    sLen = len(stack)
    while True:
        if sLen < 3:
            break
        else:
            # top elements
            val2 = stack[sLen - 1]
            val1 = stack[sLen - 2]
            sign = stack[sLen - 3]

            if (sign.type == TokenType.SYMBOL 
            and val1.type == TokenType.NUMBER
            and val2.type == TokenType.NUMBER):
                val1Int = int(val1.value)
                val2Int = int(val2.value)
                if sign.value == '+':
                    temp = val1Int + val2Int
                elif sign.value == '-':
                    temp = val1Int - val2Int
                elif sign.value == '*':
                    temp = val1Int * val2Int
                elif sign.value == '/':
                    temp = val1Int // val2Int
                tempToken = Token(TokenType.NUMBER, temp, sign.lineNum)
                stack = stack[:-3]
                stack.append(tempToken)
                sLen = len(stack)
            else:
                break