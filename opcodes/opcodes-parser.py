import re
from instruction_map import *

class asm_line:
    def __init__(self, line_words, line):
        word_n = 1
        self.instruction = line_words[word_n]
        self.complete_instruction = "\""
        
        word_n += 1
        
        if(line_words[word_n] != ";"):
            if "," in line_words[word_n]:
                splited_line_word = line_words[word_n].split(",")
                self.data_to = splited_line_word[0]
                self.data_from = splited_line_word[1]
            else:
                self.data_from = line_words[word_n]
                self.data_to = "null"

            for n in range(0, word_n + 1):
                self.complete_instruction += line_words[n]
                if(n > 0 and n < word_n):
                    self.complete_instruction += " "
            self.complete_instruction += "\""

        else:
            self.data_to = "null"
            self.data_from = "null"
            word_n-=1

            for n in range(0, word_n+1):
                self.complete_instruction += line_words[n]
            self.complete_instruction += "\""

        word_n += 1
        self.opcode = line_words[word_n+1]
        self.number_of_bytes = len(line_words) - word_n - 2
        # print(line_words[1])

    def show(self):
        out = ""
        out += self.opcode + " " + str(self.instruction) + ": from=" + str(self.data_from) + "  to=" + str(self.data_to) + "  nb_bytes=" + str(self.number_of_bytes)
        return out
        
        
def main():
    line_obj_list = []
    with open('./opcodes-clean.txt', 'r') as file: 
        i = 0
        for line in file:
            if(line == ""):
                break
            words =  re.split(r'\s+', line)
            
            # print(i)
            # i += 1
            # for w in words:
            #     print(w)

            line_obj_list.append(asm_line(words, line))

            output_file = open("./instruction-list.c", "w")
            

    output_file.write("instruction_table = {")
    cpt = 0
    for inst in line_obj_list :
        str_inst = "{" + inst.complete_instruction + ", 0x" + inst.opcode + ", " + str(inst.number_of_bytes)
        str_inst += ", &z80::" + data_from_table[inst.data_from] + ", &z80::" + data_to_table[inst.data_to] + ", &z80::" + inst.instruction + ", 0},"
        output_file.write(str_inst)
        cpt += 1
        if(cpt == 16):
            output_file.write("\n")
            cpt = 0
        
    output_file.write("}")
    
        

main()