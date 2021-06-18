
import sys
from os.path import dirname

sys.path.insert(0, dirname(dirname(__file__)))

import pd


p = pd.Patch(name='test.pd', dir='tests/pd')
p.play()
