# Variant 9:
# f(a, b) = (a+b) / (b-a)
# Command:
#   PUSH val    ; add `val` on stack top
#   CPY pos     ; copy value at `pos` position from top
#   POP         ; del top element
#   SWP         ; swap 2 upper elements
#   ADD         ; remove 2 element, add their sum
#   SUB         ; remove 2 element, add subtract
#   DIV         ; remove 2 element, add their quotient
# (for birany functions left element is top of stack)

# PUSH a
# PUSH b
# CPY 1     ; =a
# CPY 1     ; =b
# SWP
# ; stack = [a, b, a, b]
# SUB       ; =a-b
# ; stack = [a, b, a-b]
# CPY 2     ; =a
# CPY 2     ; =b
# ; stack = [a, b, a-b, b, a]
# ADD
# ; stack = [a, b, a-b, a+b]
# DIV       ; 
# ; stack = [a, b, (a+b)/(a-b)]
# SWP
# POP
# SWP
# POP
# ; stack = [(a+b)/(a-b)]

# 𓆏


import random
import math

class MyFloat:
    EXP_BIT = 10
    MANTISSA_BIT = 5

    __EXP_SHIFT = (1 << (EXP_BIT - 1)) - 1
    __MAX_E = (1 << EXP_BIT) - 1
    __MAX_M = (1 << MANTISSA_BIT) - 1
    __MAX = 0
    __MIN = 0
    __NAN = 0
    __INF_POS = 0
    __INF_NEG = 0
    # MAX = Number('0111111111111110111111111')
    # MIN = Number('1111111111111110000000000')
    # close_to_zero = Number('0000000000000001000000000')
    # inf_pos = Number('0111111111111111000000000')
    # inf_neg = Number('1111111111111111000000000')
    # nan = Number('1111111111111111000000110')


    def __init__(self, s):
        if not isinstance(s, str):
            self.set(0, 0, 0)
        else:
            self.set(s[0 : 1], 
                     s[1 : 1+self.EXP_BIT], 
                     s[1+self.EXP_BIT : 1+self.EXP_BIT+self.MANTISSA_BIT])


    def set_float(self, x):
        lg = int(math.log(x, 2))
        self.E = lg + self.__EXP_SHIFT
        self.M = int((x - 2**lg) * 2**(self.MANTISSA_BIT - lg) )
        self.S = x < 0


    def get_float(self):
        res = 1 + (self.M / 2**self.MANTISSA_BIT);
        res *= 2**(self.E - self.__EXP_SHIFT)
        if self.S:
            res = -res
        return str(res)


    def bound(self, l, x, r):
        if x < l:
            return l
        if x > r:
            return r
        return x


    def set(self, S, E, M):
        print(S, E, M, self.__MAX_E)
        self.S = bool(S);
        self.E = self.bound(0, int(E), self.__MAX_E);
        self.M = self.bound(0, int(M), self.__MAX_M);


    def bin(self, sep=""):
        Ss = str(int(self.S))
        Es = bin(self.E)[2:]
        Es = "0" * (self.EXP_BIT - len(Es)) + Es
        Ms = bin(self.M)[2:]
        Ms = "0" * (self.MANTISSA_BIT - len(Ms)) + Ms
        # print("   ", Ms + "_2 =", int(Ms, 2))
        return Ss + sep + Es + sep + Ms
    

    def __str__(self):
        specials = dict.fromkeys(
            [self.__NAN, self.__INF_POS, self.__INF_NEG],
            ["NaN", "+Inf", "-Inf"]
        )
        if self.bin() in specials:
            return specials[self.bin()]
        return str(self.get_float())
        

t = math.acos(-1)
x = MyFloat(0)
x.set_float(t)
print(t)
print(x, "(", x.S, x.E, x.M, ")")
print(x.bin(" "))
print(x.get_float())
#print( MyFloat(). )
exit(0)

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
    register_count = 8
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
        commands.append(args)
    file.close()

    return commands;



def main():
    state = PState()
    program = read_instructions()

    for oper, arg in program:
        state.do(oper, arg)

main()
