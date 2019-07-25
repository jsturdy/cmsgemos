#!/usr/bin/env python

from rw_reg import *
from mcs import *
from time import *
import array
import struct
import os,signal

## https://stackoverflow.com/questions/18499497/how-to-process-sigterm-signal-gracefully
class GracefulKiller:
    kill_now = False
    def __init__(self):
        signal.signal(signal.SIGINT,  self.exit_gracefully)
        signal.signal(signal.SIGTERM, self.exit_gracefully)
        signal.signal(signal.SIGILL,  self.exit_gracefully)        

    def exit_gracefully(self,signum, frame):
        self.kill_now = True

def singledispatch(args):
    import random,time
    rvals = []
    wvals = []
    # from timeit import default_timer as timer
    # start = timer()
    start = time.time()
    nodeName = getNode(args.reg)
    initval = parseInt(readReg(nodeName))
    stop = time.time()
    print("Single call took {}".format(stop-start))
    start = time.time()
    for tval in range(args.num):
        if args.d:
            if args.write:
                wval = random.randint(args.vmin,args.vmax)
                writeReg(nodeName,int(wval))
            rval = parseInt(readReg(nodeName))
        else:
            if args.write:
                wvals.append(random.randint(args.vmin,args.vmax))
                writeReg(nodeName,int(wvals[tval]))
            rvals.append(parseInt(readReg(nodeName)))
    end = time.time()
    print("Comparison took {}".format(end-start))
    finval = parseInt(readReg(nodeName))
    print("initial value 0x{:x}, final value 0x{:x}".format(initval,finval))
    if args.write:
        writeReg(nodeName,initval)
    finval = parseInt(readReg(nodeName))
    print("After reset, final value 0x{:x}".format(finval))
    if args.d:
        exit(0)
        print("rvals",["0x{:x}".format(x) for x in rvals])
        if args.write:
            print("wvals",["0x{:x}".format(x) for x in wvals])

    from itertools import izip
    mismatches = 0
    if args.write:
        for x,y in izip(rvals,wvals):
            if x != y:
                mismatches += 1
    else:
        for x,y in izip(rvals[1:],rvals[0:-1]):
            if x != y:
                mismatches += 1
    print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,mismatches))
    return

def main(args):
    killer = GracefulKiller()
    parseXML()

    startVal = parseInt(readReg(nodeName))
    print("Initial value of {} is 0x{:08x}".format(args.reg,startVal))

    print("Testing where each transaction is dispatched individually")
    singledispatch(args)
    pass

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()

    parser.add_argument("-g","--link", help="Link number",      type=int)
    parser.add_argument("-s","--slot", help="Slot number",      type=int)
    parser.add_argument("-c","--shelf",help="uTCA shelf number",type=int)
    parser.add_argument("--reg",       help="regName",          type=str)
    parser.add_argument("--num",       help="Number of tests",  type=int)
    subparserCmds = parser.add_subparsers(help="regtester command help")

    parser_write = subparserCmds.add_parser("--write", help="Perform a write/readback test with random values in the range vmin,vmax")
    parser_write.add_argument("vmin",      help="Minimum value",    type=int)
    parser_write.add_argument("vmax",      help="Maximum value",    type=int)

    parser.add_argument("-d",          help="debug", action='store_true')

    args = parser.parse_args()

    print("Running checks")
    if (args.link < 0 and args.link != -1) or args.link > 9:
        print("Invalid link specified {}".format(args.link))
        exit(0)
    if args.slot < 0 or args.slot > 12:
        print("Invalid slot specified {}".format(args.slot))
        exit(0)
    if args.vmin < 0:
        print("Invalid minimum value specified {}".format(args.vmin))
        exit(0)

    print("Executing main")
    main(args)

