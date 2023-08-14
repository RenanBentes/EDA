class Stack:
    def __init__(self):
        self.__stack_list = []

    def push(self, val):
        self.__stack_list.append(val)

    def pop(self):
        val = self.__stack_list[-1]
        del self.__stack_list[-1]
        return val


class AutoPilha(Stack):
    def __init__(self):
        Stack.__init__(self)
        self.__sum = 0

    def get_sum(self):
        return self.__sum

    def get_sum(self):
        return self.__sum


stack_object = AutoPilha()

for i in range(5):
    stack_object.push(i)
    print("Empilhando", i)
    #Pedir entrada
    #j = int(input())
    #stack_object.push(j)
    #print("Empilhando",j)


print("\nSomatorio dos elementos da pilha", stack_object.get_sum(),"\n")

for i in range(5):
    print("Desempilhando", stack_object.pop())
