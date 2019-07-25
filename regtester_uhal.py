#!/bin/env python

from gempython.tools.glib_system_info_uhal import getSystemFWVer,getSystemFWDate
from gempython.tools.vfat_user_functions_uhal import *
from gempython.tools.amc_user_functions_uhal import *
from gempython.utils.rate_calculator import errorRate

import logging
from gempython.utils.gemlogger import colors,getGEMLogger

from gempython.utils.nesteddict import nesteddict
from gempython.utils.standardopts import parser

def multidispatch(args,amc):
    import random,time
    rvals = []
    wvals = []
    from timeit import default_timer as timer
    # start = timer()
    start = time.time()
    initval = amc.getNode(args.reg).read()
    amc.dispatch()
    stop = time.time()
    print("Single call took {}".format(stop-start))
    start = time.time()
    for tval in range(args.num):
        if args.write:
            wvals.append(random.randint(args.vmin,args.vmax))
            amc.getNode(args.reg).write(wvals[tval])
        rvals.append(amc.getNode(args.reg).read())
        if tval % 4 == 3:
            amc.dispatch()
    amc.dispatch()
    end    = time.time()
    print("Comparison took {}".format(end-start))
    finval = amc.getNode(args.reg).read()
    amc.dispatch()
    print("initial value 0x{:x}, final value 0x{:x}".format(initval,finval))
    if args.write:
        amc.getNode(args.reg).write(int(initval))
    finval = amc.getNode(args.reg).read()
    amc.dispatch()
    print("After reset, final value 0x{:x}".format(finval))
    if args.d:
        print("rvals",["0x{:x}".format(x) for x in rvals])
        if args.write:
            print("wvals",["0x{:x}".format(x) for x in wvals])

    import numpy as np
    if args.write:
        rovals = np.array(rvals)
        wovals = np.array(wvals)
        print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,(rovals!=wovals).sum()))
    else:
        rovals1 = np.array(rvals[0:-1])
        rovals2 = np.array(rvals[1:])
        print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,(rovals1!=rovals2).sum()))
    return

def singledispatch(args,amc):
    import random,time
    rvals = []
    wvals = []
    from timeit import default_timer as timer
    start = time.time()
    initval = readRegister(amc,args.reg)
    stop = time.time()
    print("Single call took {}".format(stop-start))
    start = time.time()
    for tval in range(args.num):
        if args.d:
            if args.write:
                wval = random.randint(args.vmin,args.vmax)
                writeRegister(amc,'{:s}'.format(args.reg),int(wval))
            rval = readRegister(amc,'{:s}'.format(args.reg))
        else:
            if args.write:
                wvals.append(random.randint(args.vmin,args.vmax))
                writeRegister(amc,'{:s}'.format(args.reg),int(wvals[tval]))
            rvals.append(readRegister(amc,'{:s}'.format(args.reg)))
    end = time.time()
    print("Comparison took {}".format(end-start))
    finval = readRegister(amc,args.reg)
    print("initial value 0x{:x}, final value 0x{:x}".format(initval,finval))
    if args.write:
        writeRegister(amc,args.reg,initval)
    finval = readRegister(amc,args.reg,)
    print("After reset, final value 0x{:x}".format(finval))
    if args.d:
        exit(0)
        print("rvals",["0x{:x}".format(x) for x in rvals])
        if args.write:
            print("wvals",["0x{:x}".format(x) for x in wvals])

    import numpy as np
    from itertools import izip
    mismatches = 0
    if args.write:
        rovals = np.array(rvals)
        wovals = np.array(wvals)
        for x,y in izip(rvals,wvals):
            if x != y:
                mismatches += 1
        # print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,(rovals!=wovals).sum()))
    else:
        rovals1 = np.array(rvals[1:])
        rovals2 = np.array(rvals[0:-1])
        for x,y in izip(rvals[1:],rvals[0:-1]):
            if x != y:
                mismatches += 1
        # print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,(rovals1!=rovals2).sum()))
        pass
    print("Ran {} total checks on {}, and had {} mismatches".format(args.num,args.reg,mismatches))
    return

def main(args):
    import random,time

    if 'GEM_AMC.OH.OH' in args.reg:
        print("Creating an OptoHybrid connection")
        device = getOHObject(args.slot,args.link,args.shelf,args.d)
        setOHLogLevel(logging.INFO)
        setVFATLogLevel(logging.INFO)
    else:
        print("Creating an AMC connection")
        device = getAMCObject(args.slot,args.shelf,args.d)
        setAMCLogLevel(logging.INFO)

    startVal = readRegister(device,'{:s}'.format(args.reg))
    print("Initial value of {} is 0x{:08x}".format(args.reg,startVal))

    print("Testing where all transactions are dispatched together")
    multidispatch(args,device)
    print("")
    print("Testing where each transaction is dispatched individually")
    singledispatch(args,device)

    pass

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()

    parser.add_argument("-g","--link", help="Link number",      type=int)
    parser.add_argument("-s","--slot", help="Slot number",      type=int)
    parser.add_argument("-c","--shelf",help="uTCA shelf number",type=int)
    parser.add_argument("--reg",       help="regName",          type=str)
    parser.add_argument("--num",       help="Number of tests",  type=int)
    # subparserCmds = parser.add_subparsers(help="regtester command help")

    # parser_write = subparserCmds.add_parser("--write", help="Perform a write/readback test with random values in the range vmin,vmax")
    parser.add_argument("--write",   action='store_true',
                        help="Perform a write/readback test with random values in the range vmin,vmax")
    parser.add_argument("--vmin",    help="Minimum value",    type=int)
    parser.add_argument("--vmax",    help="Maximum value",    type=int)

    parser.add_argument("-d",          help="debug", action='store_true')

    args = parser.parse_args()

    gemlogger = getGEMLogger(__name__)
    gemlogger.setLevel(logging.INFO)

    uhal.setLogLevelTo( uhal.LogLevel.ERROR )

    print("Running checks")
    if (args.link < 0 and args.link != -1) or args.link > 9:
        print("Invalid link specified {}".format(args.link))
        exit(0)
    if args.slot < 0 or args.slot > 12:
        print("Invalid slot specified {}".format(args.slot))
        exit(0)
    if args.write and args.vmin < 0:
        print("Invalid minimum value specified {}".format(args.vmin))
        exit(0)
    if args.write and not (args.vmin or args.vmax):
        print("Please specify a min/max for the write test")
        exit(0)

    print("Executing main")
    main(args)

