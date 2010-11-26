/**
 * 
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 * 
 */

package org.puredata.core;

import org.easymock.EasyMock;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import org.puredata.core.utils.PdUtils;


/**
 * Some basic tests for messaging and MIDI support in libpd.
 * 
 * @author Peter Brinkmann (peter.brinkmann@gmail.com) 
 *
 */
public class PdIntegrationTest {

	private String patch;
	private PdReceiver receiver;
	private PdMidiReceiver midiReceiver;

	@Before
	public void setUp() throws Exception {
		receiver = EasyMock.createStrictMock(PdReceiver.class);
		midiReceiver = EasyMock.createStrictMock(PdMidiReceiver.class);
		PdBase.setReceiver(receiver);
		PdBase.setMidiReceiver(midiReceiver);
		patch = PdUtils.openPatch("javatests/org/puredata/core/test_callbacks.pd");
		PdBase.subscribe("eggs");
	}

	@After
	public void tearDown() throws Exception {
		PdUtils.closePatch(patch);
		PdBase.release();
	}

	@Test
	public void testPrint() {
		receiver.print("print: 0\n");
		receiver.print("print: 1\n");
		EasyMock.replay(receiver);
		PdBase.sendFloat("foo", 0);
		PdBase.sendFloat("foo", 1);
		EasyMock.verify(receiver);
	}

	@Test
	public void testReceive() {
		receiver.receiveBang("eggs");
		receiver.receiveFloat("eggs", 42);
		receiver.receiveSymbol("eggs", "hund katze maus");
		receiver.receiveList("eggs", "hund", 1.0f, "katze", 2.0f, "maus", 3.0f);
		receiver.receiveMessage("eggs", "testing", "one", 1.0f, "two", 2.0f);
		EasyMock.replay(receiver);
		PdBase.sendBang("spam");
		PdBase.sendFloat("spam", 42);
		PdBase.sendSymbol("spam", "hund katze maus");
		PdBase.sendList("spam", "hund", 1, "katze", 2, "maus", 3);
		PdBase.sendMessage("spam", "testing", "one", 1, "two", 2);
		EasyMock.verify(receiver);
	}

	@Test
	public void testNoteOn() {
		midiReceiver.receiveNoteOn(0, 64, 127);
		midiReceiver.receiveNoteOn(12, 0, 127);
		midiReceiver.receiveNoteOn(30, 10, 15);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendNoteOn(0, 64, 127));
		assertEquals(0, PdBase.sendNoteOn(12, 0, 127));
		assertEquals(0, PdBase.sendNoteOn(30, 10, 15));
		assertEquals(-1, PdBase.sendNoteOn(-1, 64, 127));
		assertEquals(-1, PdBase.sendNoteOn(12, -1, 127));
		assertEquals(-1, PdBase.sendNoteOn(30, 10, -1));
		assertEquals(-1, PdBase.sendNoteOn(12, 128, 127));
		assertEquals(-1, PdBase.sendNoteOn(30, 10, 128));
		EasyMock.verify(midiReceiver);
	}

	@Test
	public void testControlChange() {
		midiReceiver.receiveControlChange(0, 64, 127);
		midiReceiver.receiveControlChange(12, 0, 127);
		midiReceiver.receiveControlChange(30, 10, 15);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendControlChange(0, 64, 127));
		assertEquals(0, PdBase.sendControlChange(12, 0, 127));
		assertEquals(0, PdBase.sendControlChange(30, 10, 15));
		assertEquals(-1, PdBase.sendControlChange(-1, 64, 127));
		assertEquals(-1, PdBase.sendControlChange(12, -1, 127));
		assertEquals(-1, PdBase.sendControlChange(30, 10, -1));
		assertEquals(-1, PdBase.sendControlChange(12, 128, 127));
		assertEquals(-1, PdBase.sendControlChange(30, 10, 128));
		EasyMock.verify(midiReceiver);
	}

	@Test
	public void testPolyAftertouch() {
		midiReceiver.receivePolyAftertouch(0, 64, 127);
		midiReceiver.receivePolyAftertouch(12, 0, 127);
		midiReceiver.receivePolyAftertouch(30, 10, 15);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendPolyAftertouch(0, 64, 127));
		assertEquals(0, PdBase.sendPolyAftertouch(12, 0, 127));
		assertEquals(0, PdBase.sendPolyAftertouch(30, 10, 15));
		assertEquals(-1, PdBase.sendPolyAftertouch(-1, 64, 127));
		assertEquals(-1, PdBase.sendPolyAftertouch(12, -1, 127));
		assertEquals(-1, PdBase.sendPolyAftertouch(30, 10, -1));
		assertEquals(-1, PdBase.sendPolyAftertouch(12, 128, 127));
		assertEquals(-1, PdBase.sendPolyAftertouch(30, 10, 128));
		EasyMock.verify(midiReceiver);
	}

	@Test
	public void testProgramChange() {
		midiReceiver.receiveProgramChange(0, 64);
		midiReceiver.receiveProgramChange(12, 0);
		midiReceiver.receiveProgramChange(30, 127);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendProgramChange(0, 64));
		assertEquals(0, PdBase.sendProgramChange(12, 0));
		assertEquals(0, PdBase.sendProgramChange(30, 127));
		assertEquals(-1, PdBase.sendProgramChange(-1, 64));
		assertEquals(-1, PdBase.sendProgramChange(12, -1));
		assertEquals(-1, PdBase.sendProgramChange(10, 128));
		EasyMock.verify(midiReceiver);
	}

	@Test
	public void testAftertouch() {
		midiReceiver.receiveAftertouch(0, 64);
		midiReceiver.receiveAftertouch(12, 0);
		midiReceiver.receiveAftertouch(30, 127);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendAftertouch(0, 64));
		assertEquals(0, PdBase.sendAftertouch(12, 0));
		assertEquals(0, PdBase.sendAftertouch(30, 127));
		assertEquals(-1, PdBase.sendAftertouch(-1, 64));
		assertEquals(-1, PdBase.sendAftertouch(12, -1));
		assertEquals(-1, PdBase.sendAftertouch(10, 128));
		EasyMock.verify(midiReceiver);
	}

	@Test
	public void testPitchBend() {
		midiReceiver.receivePitchBend(0, 64);
		midiReceiver.receivePitchBend(12, 0);
		midiReceiver.receivePitchBend(30, 8191);
		midiReceiver.receivePitchBend(8, -237);
		midiReceiver.receivePitchBend(10, -8192);
		EasyMock.replay(midiReceiver);
		assertEquals(0, PdBase.sendPitchBend(0, 64));
		assertEquals(0, PdBase.sendPitchBend(12, 0));
		assertEquals(0, PdBase.sendPitchBend(30, 8191));
		assertEquals(0, PdBase.sendPitchBend(8, -237));
		assertEquals(0, PdBase.sendPitchBend(10, -8192));
		assertEquals(-1, PdBase.sendPitchBend(-1, 64));
		assertEquals(-1, PdBase.sendPitchBend(12, -8193));
		assertEquals(-1, PdBase.sendPitchBend(12, 8192));
		EasyMock.verify(midiReceiver);
	}
}