from sets import Set
from random import *
from sys import argv
import re

def main(argv):
    if(len(argv)< 4):
        print "python parse.py inputtext parsedtext wordset"
        exit()

    
    inputfile = argv[1]
    outputfile = argv[2]
    wordfile = argv[3]
    parse(inputfile,outputfile)


    chooseWords(100,outputfile,wordfile)

def parse(inputfile, outputfile):
    out = open(outputfile,"w")
    text = open(inputfile,"r")
    for line in text:
        for word in line.split():
            charlist = re.findall(r'[A-Za-z]',word)
            word = "".join(charlist)
            out.write(word.lower())
            if not(word == ""):
                out.write('\n')
    out.close()

def chooseWords(defaultsize, text, wordfile):
    file = open(text,"r")
    numberOfLines = 0
    for line in file:
        numberOfLines = numberOfLines+1
    file.close()
    words = Set([])
    size = min(defaultsize,int(numberOfLines/4.0))
    #I want smaller of size, DISTINCT words in wordset
    if size < defaultsize:
        print 'Warning: changed size'

    for i in range(size):
        notadded = True
        while(notadded):
            index = randint(0,numberOfLines)
            file = open(text,"r")
            for i, line in enumerate(file):
                if i == index:
                    word = (line.split())[0]
                    if not (word in words):
                        words.add(word)
                        notadded = False
                        break
            file.close()
                        
    out = open(wordfile,"w")
    for word in words:
        out.write(word)
        out.write('\n')
    out.close()
                
    
    

if __name__ == "__main__":
    main(argv)
