

from sys import argv


if(len(argv)<4):
    print "python filterpositives.py wordset positives output"
    exit()



wordset = argv[1]
positives = argv[2]
output = argv[3]

words = open(wordset)

wordset = set(words.readlines())

words.close()

positivefile = open(positives)
outputfile = open(output,"w")
for line in positivefile.readlines():
    if line not in wordset:
        outputfile.write(line)

outputfile.close()
positivefile.close()
