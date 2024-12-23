f = open("refman.tex","rb")
data = f.read()
f.close()
for i in range(len(data)):
    ch = data[i]
    if(ch > 0x7F): # non ASCII character
        print("char: %c, idx: %d, file: %s"%(ch,i,"refman.tex"))
        str2 = str(data[i-30:i+30])#.decode("utf-8")
        print("txt: %s" % (str2))
