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


import random
import math
from copy import deepcopy

class MyFloat:
    EXP_BIT = 10
    MANTISSA_BIT = 8

    EXP_SHIFT = (1 << (EXP_BIT - 1)) - 1
    MAX_E = (1 << EXP_BIT) - 1
    MAX_M = (1 << MANTISSA_BIT) - 1

    NULL_POS = "0" + ("0" + "1" * (EXP_BIT-1)) + ("0" * MANTISSA_BIT)
    NULL_NEG = "1" + ("0" + "1" * (EXP_BIT-1)) + ("0" * MANTISSA_BIT)
    MAX = "0" + ("1" * (EXP_BIT-1) + "0") + ("1" * MANTISSA_BIT)
    MIN = "1" + ("1" * (EXP_BIT-1) + "0") + ("1" * MANTISSA_BIT)
    NAN = "1" + ("1" * EXP_BIT) + ("0" * (MANTISSA_BIT-1) + "1")
    INF_POS = "0" + ("1" * EXP_BIT) + ("0" * MANTISSA_BIT)
    INF_NEG = "1" + ("1" * EXP_BIT) + ("0" * MANTISSA_BIT)


    def __init__(self, s = NULL_POS):
        if not isinstance(s, str):
            self.set(0, 0, 0)
        else:
            self.set(s[0 : 1], 
                     s[1 : 1+self.EXP_BIT], 
                     s[1+self.EXP_BIT : 1+self.EXP_BIT+self.MANTISSA_BIT])


    def set_float(self, x):
        if x == float("+inf"): self.__init__(MyFloat().INF_POS); return self
        if x == float("-inf"): self.__init__(MyFloat().INF_NEG); return self
        if x != x:  self.__init__(MyFloat().NAN); return self
        if x == float("+0.0"): self.__init__(MyFloat().NULL_POS); return self
        if x == float("-0.0"): self.__init__(MyFloat().NULL_NEG); return self
        
        self.S = x < 0
        if x < 0:
            x = -x

        try:
            lg = int(math.log(x, 2))
            self.E = lg + self.EXP_SHIFT
            if self.E < 1:
                raise ValueError
            self.M = int((x - 2**lg) * 2**(self.MANTISSA_BIT - lg) )
        except: 
            if self.S:
                self.__init__(MyFloat().NULL_NEG)
            else:
                self.__init__(MyFloat().NULL_POS)
        
        return self


    def get_float(self):
        if self.bin() == MyFloat().NULL_NEG: return float("-0.0")
        if self.bin() == MyFloat().NULL_POS: return float("+0.0")
        if self.bin() == MyFloat().INF_POS: return float("+inf")
        if self.bin() == MyFloat().INF_NEG: return float("-inf")
        if self.bin() == MyFloat().NAN: return float("nan")
        
        res = 1 + (self.M / 2**self.MANTISSA_BIT);
        res *= 2**(self.E - self.EXP_SHIFT)
        if self.S:
            res = -res
        return res


    def bound(self, l, x, r):
        if x < l:
            return l
        if x > r:
            return r
        return x


    def set(self, S, E, M):
        self.S = bool(S);
        self.E = self.bound(0, int(E, 2), self.MAX_E);
        self.M = self.bound(0, int(M, 2), self.MAX_M);


    def bin(self, sep=""):
        Ss = str(int(self.S))
        Es = bin(self.E)[2:]
        Es = "0" * (self.EXP_BIT - len(Es)) + Es
        Ms = bin(self.M)[2:]
        Ms = "0" * (self.MANTISSA_BIT - len(Ms)) + Ms
        return Ss + sep + Es + sep + Ms
    

    def set_rand(self):
        self.S = random.randint(0, 1);
        self.E = random.randint(0, self.MAX_E)
        self.M = random.randint(0, self.MAX_M)
        return self;


    def __str__(self):
        specials = dict.fromkeys(
            [MyFloat(self.NAN).bin(), 
            MyFloat(self.INF_POS).bin(), 
            MyFloat(self.INF_NEG).bin(), 
            MyFloat(self.NULL_POS).bin(), 
            MyFloat(self.NULL_NEG).bin()],
            ["NaN", "+Inf", "-Inf", "+0.0", "-0.0"]
        )
        if self.bin() in specials:
            return specials[self.bin()]
        return str(self.get_float())
        


class Processor:
    def c_PUSH(state, val):
        state.R[state.R_ss] = deepcopy(val)
        state.R_ss += 1

    def c_CPY(state, val):
        state.R[state.R_ss] = deepcopy(state.R[state.R_ss - 1 - val])
        state.R_ss += 1
        
    def c_POP(state, val=None):
        state.R_ss -= 1
        
    def c_SWP(state, val=None):
        state.R[state.R_ss-1], state.R[state.R_ss-2] = state.R[state.R_ss-2], state.R[state.R_ss-1]
        
    def c_ADD(state, val=None):
        x = state.R[state.R_ss-1].get_float()
        state.R_ss -= 1
        y = state.R[state.R_ss-1].get_float()
        state.R[state.R_ss-1].set_float(x + y)
        
    def c_SUB(state, val=None):
        x = state.R[state.R_ss-1].get_float()
        state.R_ss -= 1
        y = state.R[state.R_ss-1].get_float()
        state.R[state.R_ss-1] = MyFloat().set_float(x - y) 

    
    def c_DIV(state, val=None):
        x = state.R[state.R_ss-1].get_float()
        state.R_ss -= 1
        y = state.R[state.R_ss-1].get_float()
        try:
            res = x / y
        except ZeroDivisionError:
            res = float("nan")
        state.R[state.R_ss-1].set_float(res)
    

    tick_count = 2
    register_count = 8
    commands = {
        "PUSH":c_PUSH, 
        "CPY":c_CPY, 
        "POP":c_POP, 
        "SWP":c_SWP, 
        "ADD":c_ADD, 
        "SUB":c_SUB, 
        "DIV":c_DIV
    }


class PState(Processor):
        # Registers:
    R = [MyFloat() for i in range(Processor.register_count)]
    R_comm = ""     # text literal of current command
    R_ss = 0        # stack selector, id of first non-used element
    R_state = 0     # last bit for sign, pre-last for invalid command 
    R_tick = 0      # from `0` to tick_count-1
    R_cTick = 0     # sequence number of current command


    def __init__(self):
        self.init_random()


    def write(self):        
        def w(name, val):
            num = ""
            if isinstance(val, int):
                width = 8
                num = f" ({val})"
                val = bin(val)[2:]
                val = "0" * (width - len(val)) + val

            if isinstance(val, MyFloat):
                num = " ({0:+.6e})".format(val.get_float())
                val = val.bin("_")
            
            print(" {:<7} : {}{}".format(name, val, num))


        w("R_comm", self.R_comm)
        for i in range(Processor.register_count):
            w("R"+str(i), self.R[i])

        w("R_ss", self.R_ss)
        w("R_state", self.R_state)
        w("R_tick", self.R_tick)
        w("R_cTick", self.R_cTick)
        
        input("Press Enter for next step ")
        print()


    def init_random(self):        
        for i in range(Processor.register_count):
            self.R[i] = MyFloat().set_rand();


    def do(self, oper, arg):
        def command_parse():
            val, handler, err = None, None, None
            
            if arg != "":
                is_float = '.' in arg
                # try:
                if is_float:
                    val = MyFloat().set_float(float(arg))
                else:
                    val = int(arg)
                # except:
                #     err = True

            if oper in Processor.commands:
                handler = Processor.commands[oper]
            else:
                err = True

            return handler, val, err


        self.R_cTick += 1
        self.R_tick = 0
        self.R_state = (self.R_state | 2) ^ 2

        handler, val, err = command_parse()

        self.R_comm = oper
        if arg != None:
            self.R_comm += " " + arg

        self.write()

        self.R_tick += 1
        if err:
            self.R_state |= 2
        else:
            self.R_state = (self.R_state | 1) ^ 1
            handler(self, val)

        self.write()



def read_instructions(filename = "commands.com"):
    cnt_args = 2
    commands = []

    file = open(filename, "r")
    for line in file:
        try:
            comment_begin = line.index(";")
            line = line[:comment_begin]
        except:
            pass

        args = line.split()
        if len(args) > 0:
            while len(args) < cnt_args:
                args.append("")
            commands.append(args)
    file.close()

    return commands;



def main():
    state = PState()
    program = read_instructions()

    for oper, arg in program:
        state.do(oper, arg)

main()
