

data_from_table = {"null": "NOP",
                   # direct
                   "N": "DataFromN",
                   "NN": "DataFromNN",
                   # 8-bits reg
                   "A" : "DataFromRegA",
                   "B" : "DataFromRegB",
                   "C" : "DataFromRegC",
                   "D" : "DataFromRegD",
                   "E" : "DataFromRegE",
                   "H" : "DataFromRegH",
                   "L" : "DataFromRegL",
                   "I" : "DataFromRegI",
                   "R" : "DataFromRegR",
                   # 16-bits reg
                   "AF" : "DataFromRegAF",
                   "BC" : "DataFromRegBC",
                   "DE" : "DataFromRegDE",
                   "HL" : "DataFromRegHL",
                   "IX" : "DataFromRegIX",
                   "IY" : "DataFromRegIY",
                   "SP" : "DataFromRegSP",
                   "AF'" : "DataFromRegAFp",
                   "BC'" : "DataFromRegBCp",
                   "DE'" : "DataFromRegDEp",
                   "HL'" : "DataFromRegHLp",
                   "IX'" : "DataFromRegIXp",
                   "IY'" : "DataFromRegIYp",
                   # 16-bits addr
                   "(BC)" : "DataFromBCaddr",
                   "(DE)" : "DataFromDEaddr",
                   "(HL)" : "DataFromHLaddr",
                   "(IX)" : "DataFromIXaddr",
                   "(IY)" : "DataFromIYaddr",
                   "(NN)" : "DataFromNNaddr",
                   # ???
                   "$+2" : "",
                   "$+3" : "",
                   # IO addr
                   "(N)" : "DataFromNIOaddr",
                   "(C)" : "DataFromCIOaddr"}

data_to_table = {}