# Dev Notes



also see:

- [allocation example](https://github.com/pure-data/pure-data/blob/master/src/x_text.c)
- [forum question](https://www.mail-archive.com/pd-dev@lists.iem.at/msg02689.html)




## Portaudio Notes

Steps to writing a PortAudio application using the callback technique:

1. Write a callback function that will be called by PortAudio when audio processing is needed.

2. Initialize the PA library and open a stream for audio I/O.

3. Start the stream. Your callback function will be now be called repeatedly by PA in the background.

4. In your callback you can read audio data from the inputBuffer and/or write data to the outputBuffer.

5. Stop the stream by returning 1 from your callback, or by calling a stop function.

6. Close the stream and terminate the library.
