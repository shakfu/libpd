#!/usr/bin/env python3

import sys
from os.path import dirname

sys.path.insert(0, dirname(dirname(__file__)))

import pd

if __name__ == '__main__':
    if len(sys.argv) < 2:
        pdfile = 'tests/pd/test.pd'
    else:
        pdfile = sys.argv[1]
    print(f'pdfile: {pdfile}')    
    p = pd.Patch(pdfile, 'tests/pd')
    p.main()
