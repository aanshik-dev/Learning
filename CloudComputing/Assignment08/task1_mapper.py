import sys
import re

for line in sys.stdin:
    line = re.sub(r'[^\w\s]', ' ', line)
    line = line.lower().strip()
    words = line.split()
    for word in words:
        if word:
            print("%s\t1" % word)
