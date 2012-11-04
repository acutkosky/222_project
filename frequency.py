from sys import argv

def main(argv):
    if (len(argv)< 3):
        print "python frequency.py inputtext outputfile [1 for ordered by frequency]"
        exit()

    inputfile = argv[1]
    outputfile = argv[2]
    orderedbyfrequency = 0

    if (len(argv) == 4):
        orderedbyfrequency = int(argv[3])

    analyze(inputfile,outputfile, orderedbyfrequency)

def analyze(inputfile, outputfile, order):
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    alphalist = list(alphabet)
    alphacount = zip(alphabet, [0.0] * 26)

    out = open(outputfile, "w")
    text = open(inputfile, "r")
    for line in text:
        for word in line.split():
            if not (word == ""):
                firstchar = (list(word))[0]
                index = ord(firstchar)-ord('a')
                charfreqpair = alphacount[index]
                alphacount[index] = (charfreqpair[0],charfreqpair[1]+1)

    
    sum = reduce(lambda x,y: x + y[1], alphacount, 0)
    alphacount = map(lambda (x,y):(x, y/sum * 100.0), alphacount)


    text.close()

    if(order == 1):
        alphacount.sort(key = lambda x: x[1])
        alphacount.reverse()

    for (char,freq) in alphacount:
        out.write(char + ": \t" + str(freq) + "%\n")

    out.close()


if __name__=="__main__":
    main(argv)
