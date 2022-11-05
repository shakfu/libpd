#include <PdMidiReceiver.hpp>
#include <PdReceiver.hpp>
#include <PdTypes.hpp>
#include <ios>
#include <locale>
#include <memory>
#include <ostream>
#include <sstream> // __str__
#include <streambuf>
#include <string>
#include <string_view>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// pd::PdReceiver file:PdReceiver.hpp line:24
struct PyCallBack_pd_PdReceiver : public pd::PdReceiver {
	using pd::PdReceiver::PdReceiver;

	void print(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "print");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::print(a0);
	}
	void receiveBang(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveBang");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::receiveBang(a0);
	}
	void receiveFloat(const std::string & a0, float a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveFloat");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::receiveFloat(a0, a1);
	}
	void receiveSymbol(const std::string & a0, const std::string & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveSymbol");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::receiveSymbol(a0, a1);
	}
	void receiveList(const std::string & a0, const class pd::List & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveList");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::receiveList(a0, a1);
	}
	void receiveMessage(const std::string & a0, const std::string & a1, const class pd::List & a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveMessage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdReceiver::receiveMessage(a0, a1, a2);
	}
};

// pd::PdMidiReceiver file:PdMidiReceiver.hpp line:24
struct PyCallBack_pd_PdMidiReceiver : public pd::PdMidiReceiver {
	using pd::PdMidiReceiver::PdMidiReceiver;

	void receiveNoteOn(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveNoteOn");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receiveNoteOn(a0, a1, a2);
	}
	void receiveControlChange(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveControlChange");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receiveControlChange(a0, a1, a2);
	}
	void receiveProgramChange(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveProgramChange");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receiveProgramChange(a0, a1);
	}
	void receivePitchBend(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receivePitchBend");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receivePitchBend(a0, a1);
	}
	void receiveAftertouch(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveAftertouch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receiveAftertouch(a0, a1);
	}
	void receivePolyAftertouch(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receivePolyAftertouch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receivePolyAftertouch(a0, a1, a2);
	}
	void receiveMidiByte(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveMidiByte");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdMidiReceiver::receiveMidiByte(a0, a1);
	}
};

void bind_PdTypes(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // pd::Patch file:PdTypes.hpp line:33
		pybind11::class_<pd::Patch, std::shared_ptr<pd::Patch>> cl(M("pd"), "Patch", "a pd patch\n\n if you use the copy constructor/operator, keep in mind the libpd void*\n pointer patch handle is copied and problems can arise if one object is used\n to close a patch that other copies may be referring to");
		cl.def( pybind11::init( [](){ return new pd::Patch(); } ) );
		cl.def( pybind11::init<const std::string &, const std::string &>(), pybind11::arg("filename"), pybind11::arg("path") );

		cl.def( pybind11::init<void *, int, const std::string &, const std::string &>(), pybind11::arg("handle"), pybind11::arg("dollarZero"), pybind11::arg("filename"), pybind11::arg("path") );

		cl.def( pybind11::init( [](pd::Patch const &o){ return new pd::Patch(o); } ) );
		cl.def("handle", (void * (pd::Patch::*)() const) &pd::Patch::handle, "get the raw pointer to the patch instance\n\nC++: pd::Patch::handle() const --> void *", pybind11::return_value_policy::automatic);
		cl.def("dollarZero", (int (pd::Patch::*)() const) &pd::Patch::dollarZero, "get the unqiue instance $0 ID\n\nC++: pd::Patch::dollarZero() const --> int");
		cl.def("filename", (std::string (pd::Patch::*)() const) &pd::Patch::filename, "get the patch filename\n\nC++: pd::Patch::filename() const --> std::string");
		cl.def("path", (std::string (pd::Patch::*)() const) &pd::Patch::path, "get the parent dir path for the file\n\nC++: pd::Patch::path() const --> std::string");
		cl.def("dollarZeroStr", (std::string (pd::Patch::*)() const) &pd::Patch::dollarZeroStr, "get the unique instance $0 ID as a string\n\nC++: pd::Patch::dollarZeroStr() const --> std::string");
		cl.def("isValid", (bool (pd::Patch::*)() const) &pd::Patch::isValid, "is the patch pointer valid?\n\nC++: pd::Patch::isValid() const --> bool");
		cl.def("clear", (void (pd::Patch::*)()) &pd::Patch::clear, "clear patch pointer and dollar zero (does not close patch!)\n\n note: does not clear filename and path so the object can be reused\n\nC++: pd::Patch::clear() --> void");
		cl.def("assign", (void (pd::Patch::*)(const class pd::Patch &)) &pd::Patch::operator=, "copy operator\n\nC++: pd::Patch::operator=(const class pd::Patch &) --> void", pybind11::arg("from"));

		cl.def("__str__", [](pd::Patch const &o) -> std::string { std::ostringstream s; s << o; return s.str(); } );
	}
	{ // pd::Bang file:PdTypes.hpp line:120
		pybind11::class_<pd::Bang, std::shared_ptr<pd::Bang>> cl(M("pd"), "Bang", "bang event");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("dest") );

		cl.def( pybind11::init( [](pd::Bang const &o){ return new pd::Bang(o); } ) );
		cl.def_readonly("dest", &pd::Bang::dest);
	}
	{ // pd::Float file:PdTypes.hpp line:128
		pybind11::class_<pd::Float, std::shared_ptr<pd::Float>> cl(M("pd"), "Float", "float value");
		cl.def( pybind11::init<const std::string &, const float>(), pybind11::arg("dest"), pybind11::arg("num") );

		cl.def( pybind11::init( [](pd::Float const &o){ return new pd::Float(o); } ) );
		cl.def_readonly("dest", &pd::Float::dest);
		cl.def_readonly("num", &pd::Float::num);
	}
	{ // pd::Symbol file:PdTypes.hpp line:138
		pybind11::class_<pd::Symbol, std::shared_ptr<pd::Symbol>> cl(M("pd"), "Symbol", "symbol value");
		cl.def( pybind11::init<const std::string &, const std::string &>(), pybind11::arg("dest"), pybind11::arg("symbol") );

		cl.def( pybind11::init( [](pd::Symbol const &o){ return new pd::Symbol(o); } ) );
		cl.def_readonly("dest", &pd::Symbol::dest);
		cl.def_readonly("symbol", &pd::Symbol::symbol);
	}
	{ // pd::List file:PdTypes.hpp line:148
		pybind11::class_<pd::List, std::shared_ptr<pd::List>> cl(M("pd"), "List", "a compound message containing floats and symbols");
		cl.def( pybind11::init( [](){ return new pd::List(); } ) );
		cl.def( pybind11::init( [](pd::List const &o){ return new pd::List(o); } ) );
		cl.def("isFloat", (bool (pd::List::*)(const unsigned int) const) &pd::List::isFloat, "check if index is a float type\n\nC++: pd::List::isFloat(const unsigned int) const --> bool", pybind11::arg("index"));
		cl.def("isSymbol", (bool (pd::List::*)(const unsigned int) const) &pd::List::isSymbol, "check if index is a symbol type\n\nC++: pd::List::isSymbol(const unsigned int) const --> bool", pybind11::arg("index"));
		cl.def("getFloat", (float (pd::List::*)(const unsigned int) const) &pd::List::getFloat, "get index as a float\n\nC++: pd::List::getFloat(const unsigned int) const --> float", pybind11::arg("index"));
		cl.def("getSymbol", (std::string (pd::List::*)(const unsigned int) const) &pd::List::getSymbol, "get index as a symbol\n\nC++: pd::List::getSymbol(const unsigned int) const --> std::string", pybind11::arg("index"));
		cl.def("addFloat", (void (pd::List::*)(const float)) &pd::List::addFloat, "add a float to the list\n\nC++: pd::List::addFloat(const float) --> void", pybind11::arg("num"));
		cl.def("addSymbol", (void (pd::List::*)(const std::string &)) &pd::List::addSymbol, "add a symbol to the list\n\nC++: pd::List::addSymbol(const std::string &) --> void", pybind11::arg("symbol"));
		cl.def("len", (const unsigned int (pd::List::*)() const) &pd::List::len, "return number of items\n\nC++: pd::List::len() const --> const unsigned int");
		cl.def("types", (const std::string & (pd::List::*)() const) &pd::List::types, "return OSC style type string ie \"fsfs\"\n\nC++: pd::List::types() const --> const std::string &", pybind11::return_value_policy::automatic);
		cl.def("clear", (void (pd::List::*)()) &pd::List::clear, "clear all objects\n\nC++: pd::List::clear() --> void");
		cl.def("toString", (std::string (pd::List::*)() const) &pd::List::toString, "get list as a string\n\nC++: pd::List::toString() const --> std::string");

		cl.def("__str__", [](pd::List const &o) -> std::string { std::ostringstream s; s << o; return s.str(); } );
	}
	{ // pd::StartMessage file:PdTypes.hpp line:325
		pybind11::class_<pd::StartMessage, std::shared_ptr<pd::StartMessage>> cl(M("pd"), "StartMessage", "start a compound message");
		cl.def( pybind11::init( [](){ return new pd::StartMessage(); } ) );
	}
	{ // pd::FinishList file:PdTypes.hpp line:330
		pybind11::class_<pd::FinishList, std::shared_ptr<pd::FinishList>> cl(M("pd"), "FinishList", "finish a compound message as a list");
		cl.def( pybind11::init<const std::string &>(), pybind11::arg("dest") );

		cl.def( pybind11::init( [](pd::FinishList const &o){ return new pd::FinishList(o); } ) );
		cl.def_readonly("dest", &pd::FinishList::dest);
	}
	{ // pd::FinishMessage file:PdTypes.hpp line:338
		pybind11::class_<pd::FinishMessage, std::shared_ptr<pd::FinishMessage>> cl(M("pd"), "FinishMessage", "finish a compound message as a typed message");
		cl.def( pybind11::init<const std::string &, const std::string &>(), pybind11::arg("dest"), pybind11::arg("msg") );

		cl.def( pybind11::init( [](pd::FinishMessage const &o){ return new pd::FinishMessage(o); } ) );
		cl.def_readonly("dest", &pd::FinishMessage::dest);
		cl.def_readonly("msg", &pd::FinishMessage::msg);
	}
	{ // pd::NoteOn file:PdTypes.hpp line:351
		pybind11::class_<pd::NoteOn, std::shared_ptr<pd::NoteOn>> cl(M("pd"), "NoteOn", "send a note on event (set vel = 0 for noteoff)");
		cl.def( pybind11::init( [](const int & a0, const int & a1){ return new pd::NoteOn(a0, a1); } ), "doc" , pybind11::arg("channel"), pybind11::arg("pitch"));
		cl.def( pybind11::init<const int, const int, const int>(), pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("velocity") );

		cl.def_readonly("channel", &pd::NoteOn::channel);
		cl.def_readonly("pitch", &pd::NoteOn::pitch);
		cl.def_readonly("velocity", &pd::NoteOn::velocity);
	}
	{ // pd::ControlChange file:PdTypes.hpp line:362
		pybind11::class_<pd::ControlChange, std::shared_ptr<pd::ControlChange>> cl(M("pd"), "ControlChange", "change a control value aka send a CC message");
		cl.def( pybind11::init<const int, const int, const int>(), pybind11::arg("channel"), pybind11::arg("controller"), pybind11::arg("value") );

		cl.def_readonly("channel", &pd::ControlChange::channel);
		cl.def_readonly("controller", &pd::ControlChange::controller);
		cl.def_readonly("value", &pd::ControlChange::value);
	}
	{ // pd::ProgramChange file:PdTypes.hpp line:373
		pybind11::class_<pd::ProgramChange, std::shared_ptr<pd::ProgramChange>> cl(M("pd"), "ProgramChange", "change a program value (ie an instrument)");
		cl.def( pybind11::init<const int, const int>(), pybind11::arg("channel"), pybind11::arg("value") );

		cl.def_readonly("channel", &pd::ProgramChange::channel);
		cl.def_readonly("value", &pd::ProgramChange::value);
	}
	{ // pd::PitchBend file:PdTypes.hpp line:383
		pybind11::class_<pd::PitchBend, std::shared_ptr<pd::PitchBend>> cl(M("pd"), "PitchBend", "change the pitch bend value");
		cl.def( pybind11::init<const int, const int>(), pybind11::arg("channel"), pybind11::arg("value") );

		cl.def_readonly("channel", &pd::PitchBend::channel);
		cl.def_readonly("value", &pd::PitchBend::value);
	}
	{ // pd::Aftertouch file:PdTypes.hpp line:393
		pybind11::class_<pd::Aftertouch, std::shared_ptr<pd::Aftertouch>> cl(M("pd"), "Aftertouch", "change an aftertouch value");
		cl.def( pybind11::init<const int, const int>(), pybind11::arg("channel"), pybind11::arg("value") );

		cl.def_readonly("channel", &pd::Aftertouch::channel);
		cl.def_readonly("value", &pd::Aftertouch::value);
	}
	{ // pd::PolyAftertouch file:PdTypes.hpp line:403
		pybind11::class_<pd::PolyAftertouch, std::shared_ptr<pd::PolyAftertouch>> cl(M("pd"), "PolyAftertouch", "change a poly aftertouch value");
		cl.def( pybind11::init<const int, const int, const int>(), pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("value") );

		cl.def_readonly("channel", &pd::PolyAftertouch::channel);
		cl.def_readonly("pitch", &pd::PolyAftertouch::pitch);
		cl.def_readonly("value", &pd::PolyAftertouch::value);
	}
	{ // pd::MidiByte file:PdTypes.hpp line:414
		pybind11::class_<pd::MidiByte, std::shared_ptr<pd::MidiByte>> cl(M("pd"), "MidiByte", "a raw midi byte");
		cl.def( pybind11::init<const int, unsigned char>(), pybind11::arg("port"), pybind11::arg("byte") );

		cl.def_readonly("port", &pd::MidiByte::port);
		cl.def_readonly("byte", &pd::MidiByte::byte);
	}
	{ // pd::StartMidi file:PdTypes.hpp line:424
		pybind11::class_<pd::StartMidi, std::shared_ptr<pd::StartMidi>> cl(M("pd"), "StartMidi", "start a raw midi byte stream");
		cl.def( pybind11::init( [](){ return new pd::StartMidi(); } ), "doc" );
		cl.def( pybind11::init<const int>(), pybind11::arg("port") );

		cl.def_readonly("port", &pd::StartMidi::port);
	}
	{ // pd::StartSysex file:PdTypes.hpp line:432
		pybind11::class_<pd::StartSysex, std::shared_ptr<pd::StartSysex>> cl(M("pd"), "StartSysex", "start a raw sysex byte stream");
		cl.def( pybind11::init( [](){ return new pd::StartSysex(); } ), "doc" );
		cl.def( pybind11::init<const int>(), pybind11::arg("port") );

		cl.def_readonly("port", &pd::StartSysex::port);
	}
	{ // pd::StartSysRealTime file:PdTypes.hpp line:440
		pybind11::class_<pd::StartSysRealTime, std::shared_ptr<pd::StartSysRealTime>> cl(M("pd"), "StartSysRealTime", "start a sys realtime byte stream");
		cl.def( pybind11::init( [](){ return new pd::StartSysRealTime(); } ), "doc" );
		cl.def( pybind11::init<const int>(), pybind11::arg("port") );

		cl.def_readonly("port", &pd::StartSysRealTime::port);
	}
	{ // pd::Finish file:PdTypes.hpp line:448
		pybind11::class_<pd::Finish, std::shared_ptr<pd::Finish>> cl(M("pd"), "Finish", "finish a midi byte stream");
		cl.def( pybind11::init( [](){ return new pd::Finish(); } ) );
	}
	{ // pd::PdReceiver file:PdReceiver.hpp line:24
		pybind11::class_<pd::PdReceiver, std::shared_ptr<pd::PdReceiver>, PyCallBack_pd_PdReceiver> cl(M("pd"), "PdReceiver", "a pd message receiver base class");
		cl.def( pybind11::init( [](){ return new pd::PdReceiver(); }, [](){ return new PyCallBack_pd_PdReceiver(); } ) );
		cl.def("print", (void (pd::PdReceiver::*)(const std::string &)) &pd::PdReceiver::print, "receive a print\n\nC++: pd::PdReceiver::print(const std::string &) --> void", pybind11::arg("message"));
		cl.def("receiveBang", (void (pd::PdReceiver::*)(const std::string &)) &pd::PdReceiver::receiveBang, "receive a bang\n\nC++: pd::PdReceiver::receiveBang(const std::string &) --> void", pybind11::arg("dest"));
		cl.def("receiveFloat", (void (pd::PdReceiver::*)(const std::string &, float)) &pd::PdReceiver::receiveFloat, "receive a float\n\nC++: pd::PdReceiver::receiveFloat(const std::string &, float) --> void", pybind11::arg("dest"), pybind11::arg("num"));
		cl.def("receiveSymbol", (void (pd::PdReceiver::*)(const std::string &, const std::string &)) &pd::PdReceiver::receiveSymbol, "receive a symbol\n\nC++: pd::PdReceiver::receiveSymbol(const std::string &, const std::string &) --> void", pybind11::arg("dest"), pybind11::arg("symbol"));
		cl.def("receiveList", (void (pd::PdReceiver::*)(const std::string &, const class pd::List &)) &pd::PdReceiver::receiveList, "receive a list\n\nC++: pd::PdReceiver::receiveList(const std::string &, const class pd::List &) --> void", pybind11::arg("dest"), pybind11::arg("list"));
		cl.def("receiveMessage", (void (pd::PdReceiver::*)(const std::string &, const std::string &, const class pd::List &)) &pd::PdReceiver::receiveMessage, "receive a named message ie. sent from a message box like:\n [; dest msg arg1 arg2 arg3(\n\nC++: pd::PdReceiver::receiveMessage(const std::string &, const std::string &, const class pd::List &) --> void", pybind11::arg("dest"), pybind11::arg("msg"), pybind11::arg("list"));
		cl.def("assign", (class pd::PdReceiver & (pd::PdReceiver::*)(const class pd::PdReceiver &)) &pd::PdReceiver::operator=, "C++: pd::PdReceiver::operator=(const class pd::PdReceiver &) --> class pd::PdReceiver &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
	{ // pd::PdMidiReceiver file:PdMidiReceiver.hpp line:24
		pybind11::class_<pd::PdMidiReceiver, std::shared_ptr<pd::PdMidiReceiver>, PyCallBack_pd_PdMidiReceiver> cl(M("pd"), "PdMidiReceiver", "a pd MIDI receiver base class");
		cl.def( pybind11::init( [](){ return new pd::PdMidiReceiver(); }, [](){ return new PyCallBack_pd_PdMidiReceiver(); } ) );
		cl.def("receiveNoteOn", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receiveNoteOn, "receive a MIDI note on\n\nC++: pd::PdMidiReceiver::receiveNoteOn(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("velocity"));
		cl.def("receiveControlChange", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receiveControlChange, "receive a MIDI control change\n\nC++: pd::PdMidiReceiver::receiveControlChange(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("controller"), pybind11::arg("value"));
		cl.def("receiveProgramChange", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveProgramChange, "receive a MIDI program change,\n note: pgm value is 1-128\n\nC++: pd::PdMidiReceiver::receiveProgramChange(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("receivePitchBend", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receivePitchBend, "receive a MIDI pitch bend\n\nC++: pd::PdMidiReceiver::receivePitchBend(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("receiveAftertouch", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveAftertouch, "receive a MIDI aftertouch message\n\nC++: pd::PdMidiReceiver::receiveAftertouch(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("receivePolyAftertouch", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receivePolyAftertouch, "receive a MIDI poly aftertouch message\n\nC++: pd::PdMidiReceiver::receivePolyAftertouch(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("value"));
		cl.def("receiveMidiByte", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveMidiByte, "receive a raw MIDI byte (sysex, realtime, etc)\n\nC++: pd::PdMidiReceiver::receiveMidiByte(const int, const int) --> void", pybind11::arg("port"), pybind11::arg("byte"));
		cl.def("assign", (class pd::PdMidiReceiver & (pd::PdMidiReceiver::*)(const class pd::PdMidiReceiver &)) &pd::PdMidiReceiver::operator=, "C++: pd::PdMidiReceiver::operator=(const class pd::PdMidiReceiver &) --> class pd::PdMidiReceiver &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}
