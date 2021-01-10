import pd

p = pd.PatchManager()

def test_init():
    p.init()

def test_add_to_search_path():
    p.add_to_search_path('./archive')

def test_openfile_noargs():
    p.openfile()

def test_openfile_withargs():
    p.openfile('test2.pd')

def test_closefile():
    p.closefile()