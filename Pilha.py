class Stack:
    def __init__(self):
        self.__stack_list = []

    def push(self, val):
        self.__stack_list.append(val)

    def pop(self):
        val = self.__stack_list[-1]
        del self.__stack_list[-1]
        return val

pilha1 = Stack()

pilha1.push(3)
pilha1.push(2)
pilha1.push(1)

pilha2 = Stack()
pilha2.push(1)
pilha2.push(3)
pilha2.push(5)

print(pilha1.pop())
print(pilha1.pop())
print(pilha1.pop())

print(pilha2.pop())
print(pilha2.pop())
print(pilha2.pop())
