# Variant 9:
# f(a, b) = (a+b) / (b-a)
# Command:
#   PUSH val
#   POP 
#   ADD
#   SUB
#   DIV

# push a
# push b
# sub
# push a
# push b
# add
# div

# 𓆏


import random

class Processor:
    def c_MOV(state, reg, val):
        if val != None:
            state.R_acc = val
            state.R_state |= val & 1
        if reg != None:
            state.R[reg] = state.R_acc
            state.R_state |= state.R_acc & 1

    def c_OR(state, reg, val):
        if val != None:
            state.R_acc |= val
        if reg != None:
            state.R_acc |= state.R[reg]
        state.R_state |= state.R_acc & 1


    tick_count = 2
    register_count = 4
    word_size = 28
    commands = {"MOV":c_MOV, "OR":c_OR}


    def parse_num(x:int) -> (int, bool):
        p = 2**Processor.word_size;
        if not(-p <= x < p):
            return None, True

        if x >= 0:
            return x, None
        else:
            return ((-x) ^ (p-1))+1, None


    def parse_reg(s:str) -> (int, bool):
        if not len(s) or s[0] != "R":
            return None, True
        x = int(s[1:])
        if not(0 <= x < Processor.register_count):
            return None, True
        return x, None


    def bits(x:int) -> str:
        if x < 0:
            x, _ = Processor.parse_num(x)
        s = bin(x)[2:];
        pref = "0" * (Processor.word_size - len(s))
        return pref + s



class PState(Processor):
        # Registers:
    R = [0] * Processor.register_count
    R_comm = ""     # text literal of current command
    R_acc = 0       # accumulator
    R_state = 0     # last bit for sign, pre-last for invalid command 
    R_tick = 0      # from `0` to tick_count-1
    R_cTick = 0     # sequence number of current command


    def __init__(self):
        self.init_random()


    def write(self):        
        def w(name, val):
            num = ""
            if isinstance(val, int):
                num = f" ({val})"
                val = Processor.bits(val)

            print(" {:<7} : {}{}".format(name, val, num))

        w("R_comm", self.R_comm)
        w("R_acc", self.R_acc)
        for i in range(Processor.register_count):
            w("R"+str(i), self.R[i])

        w("R_state", self.R_state)
        w("R_tick", self.R_tick)
        w("R_cTick", self.R_cTick)
        
        input("Press Enter for next step ")
        print()


    def init_random(self):
        def get_rand():
            return random.randint(0, 2**Processor.word_size-1)
        
        self.R_acc = get_rand()
        for i in range(Processor.register_count):
            self.R[i] = get_rand();


    def do(self, oper, arg):
        def command_parse():
            val, reg, handler, err = None, None, None, None
            
            is_const = arg[0] != 'R'
            if is_const:
                val, err = Processor.parse_num(int(arg))
            else:
                reg, err = Processor.parse_reg(arg)

            if oper in Processor.commands:
                handler = Processor.commands[oper]
            else:
                err = True

            return handler, val, reg, err


        self.R_cTick += 1
        self.R_tick = 0
        self.R_state = (self.R_state | 2) ^ 2

        handler, val, reg, err = command_parse()

        self.R_comm = oper + " " + (arg if reg != None or err else Processor.bits(val))
        self.R_comm = oper + " " + arg
        self.write()

        self.R_tick += 1
        if err:
            self.R_state |= 2
        else:
            self.R_state = (self.R_state | 1) ^ 1
            handler(self, reg, val)

        self.write()



def read_instructions(filename = "commands.com"):
    commands = []

    file = open(filename, "r")
    for line in file:
        try:
            comment_begin = line.index(";")
            line = line[:comment_begin]
        except:
            pass

        args = line.split()
        if len(args) == 2:
            commands.append(args)
    file.close()

    return commands;



def main():
    state = PState()
    program = read_instructions()

    for oper, arg in program:
        state.do(oper, arg)

main()
