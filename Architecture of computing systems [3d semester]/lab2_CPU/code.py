# Variant 9:
#   Addressing mode: 1 adress (accumulator)
#   Word size: 28 bit
#   Commands:
#       1) MOV `what`   (copy constant to accum, or accum to register)
#       2) OR `x`       (set accum as bitwise OR `x` and accum)

import random

class Processor:
    tick_count = 2
    register_count = 4
    word_size = 28
    commands = ["MOV", "OR"]

    def parse_num(x):
        p = 2**word_size;
        if not(p <= x < p):
            return p

        if x >= 0:
            return x
        else:
            return ((-x) ^ (p-1))+1
        # x = -x
        # x = (p-1) ^ x
        # x = x + 1
        # return x


class PState(Processor):
        # Registers:
    R = list(0 for x in range(Processor.register_count))
    R_comm = ""     # text literal of now command
    R_acc = 0       # accumulator
    R_state = 0     # `0` if current value is positive, `1` in other case
    R_tick = 0      # from `0` to tick_count-1
    R_cTick = 0     # sequence number of current command


    def write(self):        
        def bit(x):
            s = bin(x)[2:];
            pref = "0" * (Processor.word_size - len(s))
            return pref + s

        def w(name, val):
            if isinstance(val, int):
                val = bit(val)
            print("{:>8} : {}".format(name, val))


        w("R_comm", self.R_comm)
        w("R_acc", self.R_acc)
        for i in range(Processor.register_count):
            w("R"+str(i), self.R[i])

        w("R_state", self.R_state)
        w("R_tick", self.R_tick)
        w("R_cTick", self.R_cTick)


    def init_random(self):
        def get():
            return random.randint(0, 2**Processor.word_size-1)
        
        self.R_acc = get()
        for i in range(Processor.register_count):
            self.R[i] = get();


    def __init__(self):
        self.init_random()
        self.write()




def read_instructions(filename = "commands.com"):
    commands = []

    file = open(filename, "r")
    for line in file:
        commands.append(line.split())
    file.close()

    return commands;



def main():
    state = PState()
    program = read_instructions()

main()
