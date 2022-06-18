# TODO


- [ ] add array() module array access

```python
import array

class PdManager:
	def __init__(self, inChannels, outChannels, sampleRate, ticks):
		self.__ticks = ticks
		self.__outbuf = array.array('b', 
			'\x00\x00'.encode() * outChannels * libpd_blocksize())
		libpd_compute_audio(1)
		libpd_init_audio(inChannels, outChannels, sampleRate)

	def process(self, inBuffer):
		libpd_process_short(self.__ticks, inBuffer, self.__outbuf)
		return self.__outbuf
```

- [ ] add embedded external example
- [ ] add Numpy array access
- [ ] add `release` to cypd
- [ ] add multi-instance support
- [ ] add multi-thread support
