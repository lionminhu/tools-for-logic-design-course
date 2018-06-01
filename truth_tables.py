def xnor(a, b):
    return (a and b) or ((not a) and (not b))


def xor(a, b):
    return not xor(a, b)


def LT(vars):
    """LESS THAN function for two-bit comparator"""
    a, b, c, d = vars
    return ((not a) and c) or ((not b) and d and ((not a) or c))


def EQ(vars):
    """EQUAL TO function for two-bit comparator"""
    a, b, c, d = vars
    return (xnor(a, c)) and (xnor(b, d))

    
def truth_table(vars, idx, funcs):
    """
    Parameters:
        vars(list): the size of this list should be the same as
                the number of truth variables. Values of elements do not matter
        idx(int): index to which the Boolean value will be set
        funcs(list of Boolean functions): functions for which truth values will be printed
    Example:
        call with
        truth_table([0]*4, 0, [LT, EQ])
        idx must be input as 0
    """
    if idx == len(vars):
        for var in vars:
            print(int(var), end=" ")
        print(": ", end="")
        for func in funcs:
            print(int(func(vars)), end=" ")
        print()            
        return
    vars[idx] = False
    truth_table(vars, idx + 1, funcs)
    vars[idx] = True
    truth_table(vars, idx + 1, funcs)
