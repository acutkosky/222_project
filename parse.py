from sets import Set
from random import *

def main():
    inputfile = "AV1611Bible.txt"
#    inputfile = "text.txt"
    outputfile = "out.txt"
    parse(inputfile,outputfile)


    wordfile = "words.txt";
    chooseWords(100,outputfile,wordfile)

def parse(inputfile, outputfile):
    out = open(outputfile,"w")
    text = open(inputfile,"r")
    for line in text:
        for word in line.split():
            if word.isalpha():
                out.write(word.lower())
                out.write('\n')
    out.close()

def chooseWords(size, text, wordfile):
    file = open(text,"r")
    numberOfLines = 0
    for line in file:
        numberOfLines = numberOfLines+1
    file.close()
    words = Set([])
    for i in range(size):
        notadded = True
        while(notadded):
            index = randint(0,numberOfLines)
            file = open(text,"r")
            for i, line in enumerate(file):
                if i == index:
                    word = (line.split())[0]
                    if not (line in words):
                        words.add(word)
                        notadded = False
            file.close()
                        
    out = open(wordfile,"w")
    for word in words:
        out.write(word)
        out.write('\n')
    out.close()
                
    
    

if __name__ == "__main__":
    main()
