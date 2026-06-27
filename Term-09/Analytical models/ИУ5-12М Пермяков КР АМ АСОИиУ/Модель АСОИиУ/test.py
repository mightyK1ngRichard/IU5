class RoasterStack: # на основе указателя
    def __init__(self, size):
        self.__array = [None] * size
        self.__top = 0

    def push(self, elem):
        if self.__top == len(self.__array):
            return
        self.__array[self.__top] = elem
        self.__top += 1

    def pop(self):
        if self.is_empty():
            return
        self.__top -= 1
        result = self.__array[self.__top]
        return result

    def peek(self):
        return self.__array[self.__top - 1]

    def is_empty(self):
        return self.__top == 0
    
def clean_string_from_numbers(s):
    stack = RoasterStack(len(s))
    
    for char in s:
        if char.isdigit():
            if not stack.is_empty() and not stack.peek().isdigit():
                stack.pop()
        else:
            stack.push(char)
    
    result = []
    while not stack.is_empty():
        result.append(stack.pop())
    
    return ''.join(reversed(result))


input_string = input().strip()
result = clean_string_from_numbers(input_string)
print(result)
