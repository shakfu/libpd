

import libpd

# custom receiver class
class PdObject(libpd.PdReceiver, libpd.PdMidiReceiver):

    # pd message receiver callbacks

    def print(self, msg):
        print(msg)

    def receiveBang(self, dest: str):
        print("bang:", dest)

    def receiveFloat(self, dest: str, num: float);
        print("float:", dest, num)

    def receiveSymbol(self, dest: str, symbol: str):
        print("symbol:", dest, symbol)

    def receiveList(self, dest: str, alist: libpd.List):
        print("libd.List", dest, ":")
        for i in range(alist.len()):
            if alist.isFloat(i):
                print("\tfloat:", alist.getFloat(i))
            elif alist.isSymbol(i):
                print("\tsymbol:", alist.getSymbol(i))

        print("types:", alist.types())

    def receiveMessage(self, dest: str, msg: str, alist):
        print("msg:", dest, msg, alist)
        
    def receiveNoteOn(self, channel: int,  pitch: int,  velocity: int):
        print("noteon:", channel, pitch, velocity)
    
    def receiveControlChange(self, channel: int, controller: int, value: int):
        print("cc:", channel, controller, value)

    def receiveProgramChange(self, channel: int, value: int):
        print("progchange:", channel, value)

    def receivePitchBend(self,  channel: int, value: int):
        print("pitchbend:", channel, value)

    def receiveAftertouch(self,  channel: int, value):
        print("aftertouch:", channel, value)

    def receivePolyAftertouch(self,  channel: int,  pitch: int,  value: int):
        print("polyaftertouch:", channel, pitch, value)

    def receiveMidiByte(self,  port: int,  byte: int):
        print("midibyte:", port, byyte)

