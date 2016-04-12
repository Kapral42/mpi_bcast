import sys

def main(argv=None):
    if len(sys.argv) < 2:
        print "Where is my args men?"
        print "Give me file name please!"
        exit()

    fname = argv[1]
    lines = file(fname, 'r').read().split('\n')
    max_time = 0.0
    for l in lines:
        if l.find("Elapsed") != -1:
            time = float(l.split()[5])
            if time > max_time:
                max_time = time

    print max_time

if __name__ == "__main__":
        sys.exit(main(sys.argv))
