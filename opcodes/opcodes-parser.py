import re

class asm_line:
    def __init__(self, line_words):
        word_n = 1
        self.instruction = line_words[word_n]
        word_n += 1

        if(line_words[word_n] != ";"):
            if "," in line_words[word_n]:
                splited_line_word = line_words[word_n].split(",")
                self.data_to = splited_line_word[0]
                self.data_from = splited_line_word[1]
            else:
                self.data_to = word_n
                self.data_from = "null"
        else:
            self.data_to = "null"
            self.data_from = "null"
        
        word_n += 1
        self.number_of_bytes = len(line_words) - word_n
        # print(line_words[1])

    def show(self):
        out = ""
        out += str(self.instruction) + ": from=" + str(self.data_from) + "  to=" + str(self.data_to) + "  nb_bytes=" + str(self.number_of_bytes)
        return out
        
        

with open('./opcodes.txt', 'r') as file: 
    for line in file:
        if(line == ""):
            break
        words =  re.split(r'\s+', line)
        
        line_str = ""
        for w in words:
            line_str += w + " - "

        line_obj = asm_line(words)
        print(line_obj.show())

