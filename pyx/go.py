#!/usr/bin/env python3

import sys

import pd

if __name__ == '__main__':
    if len(sys.argv) < 2:
        pdfile = 'test.pd'

    else:
        pdfile = sys.argv[1]
    print(f'pdfile: {pdfile}')    
    p = pd.Patch(pdfile)
    p.main()
