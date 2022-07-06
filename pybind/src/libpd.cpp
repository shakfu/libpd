#include <PdBase.hpp>
#include <PdMidiReceiver.hpp>
#include <PdReceiver.hpp>
#include <PdTypes.hpp>

#include <algorithm>
#include <functional>
#include <ios>
#include <locale>
#include <map>
#include <memory>
#include <ostream>
#include <sstream> // __str__
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include <pybind11/pybind11.h>



namespace py = pybind11;

// using namespace pd;
using namespace py::literals;

template <typename... Args>
using overload_cast_ = py::detail::overload_cast_impl<Args...>;

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif


PYBIND11_MODULE(libpd, m)
{
    m.doc() = "libpd: a python libpd wrapper using pybind11.";
    m.attr("__version__") = "0.0.1";

	struct PyCallBack_pd_PdBase : public pd::PdBase {
		using pd::PdBase::PdBase;

		bool init(const int a0, const int a1, const int a2, bool a3) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "init");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2, a3);
				if (py::detail::cast_is_temporary_value_reference<bool>::value) {
					static py::detail::override_caster_t<bool> caster;
					return py::detail::cast_ref<bool>(std::move(o), caster);
				}
				else return py::detail::cast_safe<bool>(std::move(o));
			}
			return PdBase::init(a0, a1, a2, a3);
		}
		void clear() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "clear");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::clear();
		}
		void addToSearchPath(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "addToSearchPath");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::addToSearchPath(a0);
		}
		void clearSearchPath() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "clearSearchPath");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::clearSearchPath();
		}
		class pd::Patch openPatch(const std::string & a0, const std::string & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "openPatch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<class pd::Patch>::value) {
					static py::detail::override_caster_t<class pd::Patch> caster;
					return py::detail::cast_ref<class pd::Patch>(std::move(o), caster);
				}
				else return py::detail::cast_safe<class pd::Patch>(std::move(o));
			}
			return PdBase::openPatch(a0, a1);
		}
		class pd::Patch openPatch(class pd::Patch & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "openPatch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<class pd::Patch>::value) {
					static py::detail::override_caster_t<class pd::Patch> caster;
					return py::detail::cast_ref<class pd::Patch>(std::move(o), caster);
				}
				else return py::detail::cast_safe<class pd::Patch>(std::move(o));
			}
			return PdBase::openPatch(a0);
		}
		void closePatch(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "closePatch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::closePatch(a0);
		}
		void closePatch(class pd::Patch & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "closePatch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::closePatch(a0);
		}
		void computeAudio(bool a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "computeAudio");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::computeAudio(a0);
		}
		void subscribe(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "subscribe");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::subscribe(a0);
		}
		void unsubscribe(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "unsubscribe");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::unsubscribe(a0);
		}
		bool exists(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "exists");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<bool>::value) {
					static py::detail::override_caster_t<bool> caster;
					return py::detail::cast_ref<bool>(std::move(o), caster);
				}
				else return py::detail::cast_safe<bool>(std::move(o));
			}
			return PdBase::exists(a0);
		}
		void unsubscribeAll() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "unsubscribeAll");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::unsubscribeAll();
		}
		void receiveMessages() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "receiveMessages");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::receiveMessages();
		}
		void receiveMidi() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "receiveMidi");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::receiveMidi();
		}
		void sendBang(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendBang");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendBang(a0);
		}
		void sendFloat(const std::string & a0, float a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendFloat");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendFloat(a0, a1);
		}
		void sendSymbol(const std::string & a0, const std::string & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendSymbol");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendSymbol(a0, a1);
		}
		void startMessage() override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "startMessage");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>();
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::startMessage();
		}
		void addFloat(const float a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "addFloat");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::addFloat(a0);
		}
		void addSymbol(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "addSymbol");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::addSymbol(a0);
		}
		void finishList(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "finishList");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::finishList(a0);
		}
		void finishMessage(const std::string & a0, const std::string & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "finishMessage");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::finishMessage(a0, a1);
		}
		void sendList(const std::string & a0, const class pd::List & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendList");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendList(a0, a1);
		}
		void sendMessage(const std::string & a0, const std::string & a1, const class pd::List & a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendMessage");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendMessage(a0, a1, a2);
		}
		void sendNoteOn(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendNoteOn");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendNoteOn(a0, a1, a2);
		}
		void sendControlChange(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendControlChange");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendControlChange(a0, a1, a2);
		}
		void sendProgramChange(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendProgramChange");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendProgramChange(a0, a1);
		}
		void sendPitchBend(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendPitchBend");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendPitchBend(a0, a1);
		}
		void sendAftertouch(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendAftertouch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendAftertouch(a0, a1);
		}
		void sendPolyAftertouch(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendPolyAftertouch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendPolyAftertouch(a0, a1, a2);
		}
		void sendMidiByte(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendMidiByte");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendMidiByte(a0, a1);
		}
		void sendSysex(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendSysex");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendSysex(a0, a1);
		}
		void sendSysRealTime(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "sendSysRealTime");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::sendSysRealTime(a0, a1);
		}
		void clearArray(const std::string & a0, int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdBase *>(this), "clearArray");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdBase::clearArray(a0, a1);
		}
	};

	py::class_<pd::PdBase, std::shared_ptr<pd::PdBase>, PyCallBack_pd_PdBase>(m, "PdBase", "a Pure Data instance\n\n use this class directly or extend it and any of its virtual functions\n\n note: libpd currently does not support multiple states and it is\n       suggested that you use only one PdBase-derived object at a time\n\n       calls from multiple PdBase instances currently use a global context\n       kept in a singleton object, thus only one Receiver & one MidiReceiver\n       can be used within a single program\n\n       multiple context support will be added if/when it is included within\n       libpd")
		.def( py::init( [](){ return new pd::PdBase(); }, [](){ return new PyCallBack_pd_PdBase(); } ) )
		.def("init", [](pd::PdBase &o, const int & a0, const int & a1, const int & a2) -> bool { return o.init(a0, a1, a2); }, "", py::arg("numInChannels"), py::arg("numOutChannels"), py::arg("sampleRate"))
		.def("init", (bool (pd::PdBase::*)(const int, const int, const int, bool)) &pd::PdBase::init, "initialize resources and set up the audio processing\n\n set the audio latency by setting the libpd ticks per buffer:\n ticks per buffer * lib pd block size (always 64)\n\n ie 4 ticks per buffer * 64 = buffer len of 512\n\n you can call this again after loading patches & setting receivers\n in order to update the audio settings\n\n the lower the number of ticks, the faster the audio processing\n if you experience audio dropouts (audible clicks), increase the\n ticks per buffer\n\n set queued = true to use the built in ringbuffers for message and\n midi event passing, you will then need to call receiveMessages() and\n receiveMidi() in order to pass messages from the ringbuffers to your\n PdReceiver and PdMidiReceiver implementations\n\n the queued ringbuffers are useful when you need to receive events\n on a gui thread and don't want to use locking\n\n return true if setup successfully\n\n note: must be called before processing\n\nC++: pd::PdBase::init(const int, const int, const int, bool) --> bool", py::arg("numInChannels"), py::arg("numOutChannels"), py::arg("sampleRate"), py::arg("queued"))
		.def("clear", (void (pd::PdBase::*)()) &pd::PdBase::clear, "clear resources\n\nC++: pd::PdBase::clear() --> void")
		.def("addToSearchPath", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::addToSearchPath, "add to the pd search path\n takes an absolute or relative path (in data folder)\n\n note: fails silently if path not found\n\nC++: pd::PdBase::addToSearchPath(const std::string &) --> void", py::arg("path"))
		.def("clearSearchPath", (void (pd::PdBase::*)()) &pd::PdBase::clearSearchPath, "clear the current pd search path\n\nC++: pd::PdBase::clearSearchPath() --> void")
		.def("openPatch", (class pd::Patch (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::openPatch, "open a patch file (aka somefile.pd) at a specified parent dir path\n returns a Patch object\n\n use Patch::isValid() to check if a patch was opened successfully:\n\n     Patch p1 = pd.openPatch(\"somefile.pd\", \"/some/dir/path/\");\n     if(!p1.isValid()) {\n         cout << \"aww ... p1 couldn't be opened\" << std::endl;\n     }\n\nC++: pd::PdBase::openPatch(const std::string &, const std::string &) --> class pd::Patch", py::arg("patch"), py::arg("path"))
		.def("openPatch", (class pd::Patch (pd::PdBase::*)(class pd::Patch &)) &pd::PdBase::openPatch, "open a patch file using the filename and path of an existing patch\n\n set the filename within the patch object or use a previously opened\n object\n\n     // open an instance of \"somefile.pd\"\n     Patch p2(\"somefile.pd\", \"/some/path\"); // set file and path\n     pd.openPatch(p2);\n\n     // open a new instance of \"somefile.pd\"\n     Patch p3 = pd.openPatch(p2);\n\n     // p2 and p3 refer to 2 different instances of \"somefile.pd\"\n\nC++: pd::PdBase::openPatch(class pd::Patch &) --> class pd::Patch", py::arg("patch"))
		.def("closePatch", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::closePatch, "close a patch file\n takes only the patch's basename (filename without extension)\n\nC++: pd::PdBase::closePatch(const std::string &) --> void", py::arg("patch"))
		.def("closePatch", (void (pd::PdBase::*)(class pd::Patch &)) &pd::PdBase::closePatch, "close a patch file, takes a patch object\n note: clears the given Patch object\n\nC++: pd::PdBase::closePatch(class pd::Patch &) --> void", py::arg("patch"))
		.def("processFloat", (bool (pd::PdBase::*)(int, const float *, float *)) &pd::PdBase::processFloat, "process float buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processFloat(int, const float *, float *) --> bool", py::arg("ticks"), py::arg("inBuffer"), py::arg("outBuffer"))
		.def("processShort", (bool (pd::PdBase::*)(int, const short *, short *)) &pd::PdBase::processShort, "process short buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processShort(int, const short *, short *) --> bool", py::arg("ticks"), py::arg("inBuffer"), py::arg("outBuffer"))
		.def("processDouble", (bool (pd::PdBase::*)(int, const double *, double *)) &pd::PdBase::processDouble, "process double buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processDouble(int, const double *, double *) --> bool", py::arg("ticks"), py::arg("inBuffer"), py::arg("outBuffer"))
		.def("processRaw", (bool (pd::PdBase::*)(const float *, float *)) &pd::PdBase::processRaw, "process one pd tick, writes raw float data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRaw(const float *, float *) --> bool", py::arg("inBuffer"), py::arg("outBuffer"))
		.def("processRawShort", (bool (pd::PdBase::*)(const short *, short *)) &pd::PdBase::processRawShort, "process one pd tick, writes raw short data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRawShort(const short *, short *) --> bool", py::arg("inBuffer"), py::arg("outBuffer"))
		.def("processRawDouble", (bool (pd::PdBase::*)(const double *, double *)) &pd::PdBase::processRawDouble, "process one pd tick, writes raw double data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRawDouble(const double *, double *) --> bool", py::arg("inBuffer"), py::arg("outBuffer"))
		.def("computeAudio", (void (pd::PdBase::*)(bool)) &pd::PdBase::computeAudio, "start/stop audio processing\n\n in general, once started, you won't need to turn off audio\n\n shortcut for [; pd dsp 1( & [; pd dsp 0(\n\nC++: pd::PdBase::computeAudio(bool) --> void", py::arg("state"))
		.def("subscribe", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::subscribe, "subscribe to messages sent by a pd send source\n\n aka this like a virtual pd receive object\n\n     [r source]\n     |\n\nC++: pd::PdBase::subscribe(const std::string &) --> void", py::arg("source"))
		.def("unsubscribe", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::unsubscribe, "unsubscribe from messages sent by a pd send source\n\nC++: pd::PdBase::unsubscribe(const std::string &) --> void", py::arg("source"))
		.def("exists", (bool (pd::PdBase::*)(const std::string &)) &pd::PdBase::exists, "is a pd send source subscribed?\n\nC++: pd::PdBase::exists(const std::string &) --> bool", py::arg("source"))
		.def("unsubscribeAll", (void (pd::PdBase::*)()) &pd::PdBase::unsubscribeAll, "/ receivers will be unsubscribed from *all* pd send sources\n\nC++: pd::PdBase::unsubscribeAll() --> void")
		.def("receiveMessages", (void (pd::PdBase::*)()) &pd::PdBase::receiveMessages, "process waiting messages\n\nC++: pd::PdBase::receiveMessages() --> void")
		.def("receiveMidi", (void (pd::PdBase::*)()) &pd::PdBase::receiveMidi, "process waiting midi messages\n\nC++: pd::PdBase::receiveMidi() --> void")
		.def("setReceiver", (void (pd::PdBase::*)(class pd::PdReceiver *)) &pd::PdBase::setReceiver, "set the incoming event receiver, disables the event queue\n\n automatically receives from all currently subscribed sources\n\n set this to NULL to disable callback receiving and re-enable the\n event queue\n\nC++: pd::PdBase::setReceiver(class pd::PdReceiver *) --> void", py::arg("receiver"))
		.def("setMidiReceiver", (void (pd::PdBase::*)(class pd::PdMidiReceiver *)) &pd::PdBase::setMidiReceiver, "set the incoming midi event receiver, disables the midi queue\n\n automatically receives from all midi channels\n\n set this to NULL to disable midi events and re-enable the midi queue\n\nC++: pd::PdBase::setMidiReceiver(class pd::PdMidiReceiver *) --> void", py::arg("midiReceiver"))
		.def("sendBang", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::sendBang, "send a bang message\n\nC++: pd::PdBase::sendBang(const std::string &) --> void", py::arg("dest"))
		.def("sendFloat", (void (pd::PdBase::*)(const std::string &, float)) &pd::PdBase::sendFloat, "send a float\n\nC++: pd::PdBase::sendFloat(const std::string &, float) --> void", py::arg("dest"), py::arg("value"))
		.def("sendSymbol", (void (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::sendSymbol, "send a symbol\n\nC++: pd::PdBase::sendSymbol(const std::string &, const std::string &) --> void", py::arg("dest"), py::arg("symbol"))
		.def("startMessage", (void (pd::PdBase::*)()) &pd::PdBase::startMessage, "start a compound list or message\n\nC++: pd::PdBase::startMessage() --> void")
		.def("addFloat", (void (pd::PdBase::*)(const float)) &pd::PdBase::addFloat, "add a float to the current compound list or message\n\nC++: pd::PdBase::addFloat(const float) --> void", py::arg("num"))
		.def("addSymbol", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::addSymbol, "add a symbol to the current compound list or message\n\nC++: pd::PdBase::addSymbol(const std::string &) --> void", py::arg("symbol"))
		.def("finishList", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::finishList, "finish and send as a list\n\nC++: pd::PdBase::finishList(const std::string &) --> void", py::arg("dest"))
		.def("finishMessage", (void (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::finishMessage, "finish and send as a list with a specific message name\n\nC++: pd::PdBase::finishMessage(const std::string &, const std::string &) --> void", py::arg("dest"), py::arg("msg"))
		.def("sendList", (void (pd::PdBase::*)(const std::string &, const class pd::List &)) &pd::PdBase::sendList, "send a list using the PdBase List type\n\n     List list;\n     list.addSymbol(\"hello\");\n     list.addFloat(1.23);\n     pd.sstd::endlist(\"test\", list);\n\n sends [list hello 1.23( -> [r test]\n\n stream operators work as well:\n\n     list << \"hello\" << 1.23;\n     pd.sstd::endlist(\"test\", list);\n\nC++: pd::PdBase::sendList(const std::string &, const class pd::List &) --> void", py::arg("dest"), py::arg("list"))
		.def("sendMessage", [](pd::PdBase &o, const std::string & a0, const std::string & a1) -> void { return o.sendMessage(a0, a1); }, "", py::arg("dest"), py::arg("msg"))
		.def("sendMessage", (void (pd::PdBase::*)(const std::string &, const std::string &, const class pd::List &)) &pd::PdBase::sendMessage, "pd.sendMessage(\"test\", \"msg1\", list);\n\nC++: pd::PdBase::sendMessage(const std::string &, const std::string &, const class pd::List &) --> void", py::arg("dest"), py::arg("msg"), py::arg("list"))
		.def("sendNoteOn", [](pd::PdBase &o, const int & a0, const int & a1) -> void { return o.sendNoteOn(a0, a1); }, "", py::arg("channel"), py::arg("pitch"))
		.def("sendNoteOn", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendNoteOn, "send a MIDI note on\n\n pd does not use note off MIDI messages, so send a note on with vel = 0\n\nC++: pd::PdBase::sendNoteOn(const int, const int, const int) --> void", py::arg("channel"), py::arg("pitch"), py::arg("velocity"))
		.def("sendControlChange", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendControlChange, "send a MIDI control change\n\nC++: pd::PdBase::sendControlChange(const int, const int, const int) --> void", py::arg("channel"), py::arg("controller"), py::arg("value"))
		.def("sendProgramChange", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendProgramChange, "send a MIDI program change\n\nC++: pd::PdBase::sendProgramChange(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("sendPitchBend", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendPitchBend, "send a MIDI pitch bend\n\n in pd: [bendin] takes 0 - 16383 while [bendout] returns -8192 - 8192\n\nC++: pd::PdBase::sendPitchBend(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("sendAftertouch", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendAftertouch, "send a MIDI aftertouch\n\nC++: pd::PdBase::sendAftertouch(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("sendPolyAftertouch", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendPolyAftertouch, "send a MIDI poly aftertouch\n\nC++: pd::PdBase::sendPolyAftertouch(const int, const int, const int) --> void", py::arg("channel"), py::arg("pitch"), py::arg("value"))
		.def("sendMidiByte", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendMidiByte, "send a raw MIDI byte\n\n value is a raw midi byte value 0 - 255\n port is the raw portmidi port #, similar to a channel\n\n for some reason, [midiin], [sysexin] & [realtimein] add 2 to the\n port num, so sending to port 1 in PdBase returns port 3 in pd\n\n however, [midiout], [sysexout], & [realtimeout] do not add to the\n port num, so sending port 1 to [midiout] returns port 1 in PdBase\n\nC++: pd::PdBase::sendMidiByte(const int, const int) --> void", py::arg("port"), py::arg("value"))
		.def("sendSysex", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendSysex, "send a raw MIDI sysex byte\n\nC++: pd::PdBase::sendSysex(const int, const int) --> void", py::arg("port"), py::arg("value"))
		.def("sendSysRealTime", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendSysRealTime, "send a raw MIDI realtime byte\n\nC++: pd::PdBase::sendSysRealTime(const int, const int) --> void", py::arg("port"), py::arg("value"))
		.def("isMessageInProgress", (bool (pd::PdBase::*)()) &pd::PdBase::isMessageInProgress, "is a message or byte stream currently in progress?\n\nC++: pd::PdBase::isMessageInProgress() --> bool")
		.def("arraySize", (int (pd::PdBase::*)(const std::string &)) &pd::PdBase::arraySize, "get the size of a pd array\n returns 0 if array not found\n\nC++: pd::PdBase::arraySize(const std::string &) --> int", py::arg("name"))
		.def("resizeArray", (bool (pd::PdBase::*)(const std::string &, long)) &pd::PdBase::resizeArray, "(re)size a pd array\n sizes <= 0 are clipped to 1\n returns true on success, false on failure\n\nC++: pd::PdBase::resizeArray(const std::string &, long) --> bool", py::arg("name"), py::arg("size"))
		.def("clearArray", [](pd::PdBase &o, const std::string & a0) -> void { return o.clearArray(a0); }, "", py::arg("name"))
		.def("clearArray", (void (pd::PdBase::*)(const std::string &, int)) &pd::PdBase::clearArray, "clear array and set to a specific value\n\nC++: pd::PdBase::clearArray(const std::string &, int) --> void", py::arg("name"), py::arg("value"))
		.def("isInited", (bool (pd::PdBase::*)()) &pd::PdBase::isInited, "has the global pd instance been initialized?\n\nC++: pd::PdBase::isInited() --> bool")
		.def("isQueued", (bool (pd::PdBase::*)()) &pd::PdBase::isQueued, "is the global pd instance using the ringerbuffer queue\n for message padding?\n\nC++: pd::PdBase::isQueued() --> bool")
		.def_static("blockSize", (int (*)()) &pd::PdBase::blockSize, "get the blocksize of pd (sample length per channel)\n\nC++: pd::PdBase::blockSize() --> int")
		.def("setMaxMessageLen", (void (pd::PdBase::*)(unsigned int)) &pd::PdBase::setMaxMessageLen, "set the max length of messages and lists, default: 32\n\nC++: pd::PdBase::setMaxMessageLen(unsigned int) --> void", py::arg("len"))
		.def("maxMessageLen", (unsigned int (pd::PdBase::*)()) &pd::PdBase::maxMessageLen, "get the max length of messages and lists\n\nC++: pd::PdBase::maxMessageLen() --> unsigned int")
		.def("assign", (class pd::PdBase & (pd::PdBase::*)(const class pd::PdBase &)) &pd::PdBase::operator=, "C++: pd::PdBase::operator=(const class pd::PdBase &) --> class pd::PdBase &", py::return_value_policy::automatic, py::arg(""))
		;


	struct PyCallBack_pd_PdReceiver : public pd::PdReceiver {
		using pd::PdReceiver::PdReceiver;

		void print(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "print");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::print(a0);
		}
		void receiveBang(const std::string & a0) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveBang");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::receiveBang(a0);
		}
		void receiveFloat(const std::string & a0, float a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveFloat");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::receiveFloat(a0, a1);
		}
		void receiveSymbol(const std::string & a0, const std::string & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveSymbol");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::receiveSymbol(a0, a1);
		}
		void receiveList(const std::string & a0, const class pd::List & a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveList");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::receiveList(a0, a1);
		}
		void receiveMessage(const std::string & a0, const std::string & a1, const class pd::List & a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdReceiver *>(this), "receiveMessage");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdReceiver::receiveMessage(a0, a1, a2);
		}
	};


	struct PyCallBack_pd_PdMidiReceiver : public pd::PdMidiReceiver {
		using pd::PdMidiReceiver::PdMidiReceiver;

		void receiveNoteOn(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveNoteOn");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receiveNoteOn(a0, a1, a2);
		}
		void receiveControlChange(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveControlChange");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receiveControlChange(a0, a1, a2);
		}
		void receiveProgramChange(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveProgramChange");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receiveProgramChange(a0, a1);
		}
		void receivePitchBend(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receivePitchBend");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receivePitchBend(a0, a1);
		}
		void receiveAftertouch(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveAftertouch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receiveAftertouch(a0, a1);
		}
		void receivePolyAftertouch(const int a0, const int a1, const int a2) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receivePolyAftertouch");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1, a2);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receivePolyAftertouch(a0, a1, a2);
		}
		void receiveMidiByte(const int a0, const int a1) override {
			py::gil_scoped_acquire gil;
			py::function overload = py::get_overload(static_cast<const pd::PdMidiReceiver *>(this), "receiveMidiByte");
			if (overload) {
				auto o = overload.operator()<py::return_value_policy::reference>(a0, a1);
				if (py::detail::cast_is_temporary_value_reference<void>::value) {
					static py::detail::override_caster_t<void> caster;
					return py::detail::cast_ref<void>(std::move(o), caster);
				}
				else return py::detail::cast_safe<void>(std::move(o));
			}
			return PdMidiReceiver::receiveMidiByte(a0, a1);
		}
	};

	py::class_<pd::Patch, std::shared_ptr<pd::Patch>>(m, "Patch", "a pd patch\n\n if you use the copy constructor/operator, keep in mind the libpd void*\n pointer patch handle is copied and problems can arise if one object is used\n to close a patch that other copies may be referring to")
		.def( py::init( [](){ return new pd::Patch(); } ) )
		.def( py::init<const std::string &, const std::string &>(), py::arg("filename"), py::arg("path") )
		.def( py::init<void *, int, const std::string &, const std::string &>(), py::arg("handle"), py::arg("dollarZero"), py::arg("filename"), py::arg("path") )
		.def( py::init( [](pd::Patch const &o){ return new pd::Patch(o); } ) )
		.def("handle", (void * (pd::Patch::*)() const) &pd::Patch::handle, "get the raw pointer to the patch instance\n\nC++: pd::Patch::handle() const --> void *", py::return_value_policy::automatic)
		.def("dollarZero", (int (pd::Patch::*)() const) &pd::Patch::dollarZero, "get the unqiue instance $0 ID\n\nC++: pd::Patch::dollarZero() const --> int")
		.def("filename", (std::string (pd::Patch::*)() const) &pd::Patch::filename, "get the patch filename\n\nC++: pd::Patch::filename() const --> std::string")
		.def("path", (std::string (pd::Patch::*)() const) &pd::Patch::path, "get the parent dir path for the file\n\nC++: pd::Patch::path() const --> std::string")
		.def("dollarZeroStr", (std::string (pd::Patch::*)() const) &pd::Patch::dollarZeroStr, "get the unique instance $0 ID as a string\n\nC++: pd::Patch::dollarZeroStr() const --> std::string")
		.def("isValid", (bool (pd::Patch::*)() const) &pd::Patch::isValid, "is the patch pointer valid?\n\nC++: pd::Patch::isValid() const --> bool")
		.def("clear", (void (pd::Patch::*)()) &pd::Patch::clear, "clear patch pointer and dollar zero (does not close patch!)\n\n note: does not clear filename and path so the object can be reused\n\nC++: pd::Patch::clear() --> void")
		.def("assign", (void (pd::Patch::*)(const class pd::Patch &)) &pd::Patch::operator=, "copy operator\n\nC++: pd::Patch::operator=(const class pd::Patch &) --> void", py::arg("from"))
		.def("__str__", [](pd::Patch const &o) -> std::string { std::ostringstream s; s << o; return s.str(); } )
		;

	py::class_<pd::Bang, std::shared_ptr<pd::Bang>>(m, "Bang", "bang event")
		.def( py::init<const std::string &>(), py::arg("dest") )
		.def( py::init( [](pd::Bang const &o){ return new pd::Bang(o); } ) )
		.def_readonly("dest", &pd::Bang::dest)
		;

	py::class_<pd::Float, std::shared_ptr<pd::Float>>(m, "Float", "float value")
		.def( py::init<const std::string &, const float>(), py::arg("dest"), py::arg("num") )
		.def( py::init( [](pd::Float const &o){ return new pd::Float(o); } ) )
		.def_readonly("dest", &pd::Float::dest)
		.def_readonly("num", &pd::Float::num)
		;

	py::class_<pd::Symbol, std::shared_ptr<pd::Symbol>>(m, "Symbol", "symbol value")
		.def( py::init<const std::string &, const std::string &>(), py::arg("dest"), py::arg("symbol") )
		.def( py::init( [](pd::Symbol const &o){ return new pd::Symbol(o); } ) )
		.def_readonly("dest", &pd::Symbol::dest)
		.def_readonly("symbol", &pd::Symbol::symbol)
		;

	py::class_<pd::List, std::shared_ptr<pd::List>>(m, "List", "a compound message containing floats and symbols")
		.def( py::init( [](){ return new pd::List(); } ) )
		.def( py::init( [](pd::List const &o){ return new pd::List(o); } ) )
		.def("isFloat", (bool (pd::List::*)(const unsigned int) const) &pd::List::isFloat, "check if index is a float type\n\nC++: pd::List::isFloat(const unsigned int) const --> bool", py::arg("index"))
		.def("isSymbol", (bool (pd::List::*)(const unsigned int) const) &pd::List::isSymbol, "check if index is a symbol type\n\nC++: pd::List::isSymbol(const unsigned int) const --> bool", py::arg("index"))
		.def("getFloat", (float (pd::List::*)(const unsigned int) const) &pd::List::getFloat, "get index as a float\n\nC++: pd::List::getFloat(const unsigned int) const --> float", py::arg("index"))
		.def("getSymbol", (std::string (pd::List::*)(const unsigned int) const) &pd::List::getSymbol, "get index as a symbol\n\nC++: pd::List::getSymbol(const unsigned int) const --> std::string", py::arg("index"))
		.def("addFloat", (void (pd::List::*)(const float)) &pd::List::addFloat, "add a float to the list\n\nC++: pd::List::addFloat(const float) --> void", py::arg("num"))
		.def("addSymbol", (void (pd::List::*)(const std::string &)) &pd::List::addSymbol, "add a symbol to the list\n\nC++: pd::List::addSymbol(const std::string &) --> void", py::arg("symbol"))
		.def("len", (const unsigned int (pd::List::*)() const) &pd::List::len, "return number of items\n\nC++: pd::List::len() const --> const unsigned int")
		.def("types", (const std::string & (pd::List::*)() const) &pd::List::types, "return OSC style type string ie \"fsfs\"\n\nC++: pd::List::types() const --> const std::string &", py::return_value_policy::automatic)
		.def("clear", (void (pd::List::*)()) &pd::List::clear, "clear all objects\n\nC++: pd::List::clear() --> void")
		.def("toString", (std::string (pd::List::*)() const) &pd::List::toString, "get list as a string\n\nC++: pd::List::toString() const --> std::string")
		.def("__str__", [](pd::List const &o) -> std::string { std::ostringstream s; s << o; return s.str(); } );
		;

	py::class_<pd::StartMessage, std::shared_ptr<pd::StartMessage>>(m, "StartMessage", "start a compound message")
		.def( py::init( [](){ return new pd::StartMessage(); } ) )
		;

	py::class_<pd::FinishList, std::shared_ptr<pd::FinishList>>(m, "FinishList", "finish a compound message as a list")
		.def( py::init<const std::string &>(), py::arg("dest") )
		.def( py::init( [](pd::FinishList const &o){ return new pd::FinishList(o); } ) )
		.def_readonly("dest", &pd::FinishList::dest)
		;

	py::class_<pd::FinishMessage, std::shared_ptr<pd::FinishMessage>>(m, "FinishMessage", "finish a compound message as a typed message")
		.def( py::init<const std::string &, const std::string &>(), py::arg("dest"), py::arg("msg") )
		.def( py::init( [](pd::FinishMessage const &o){ return new pd::FinishMessage(o); } ) )
		.def_readonly("dest", &pd::FinishMessage::dest)
		.def_readonly("msg", &pd::FinishMessage::msg)
		;

	py::class_<pd::NoteOn, std::shared_ptr<pd::NoteOn>>(m, "NoteOn", "send a note on event (set vel = 0 for noteoff)")
		.def( py::init( [](const int & a0, const int & a1){ return new pd::NoteOn(a0, a1); } ), "doc" , py::arg("channel"), py::arg("pitch"))
		.def( py::init<const int, const int, const int>(), py::arg("channel"), py::arg("pitch"), py::arg("velocity") )
		.def_readonly("channel", &pd::NoteOn::channel)
		.def_readonly("pitch", &pd::NoteOn::pitch)
		.def_readonly("velocity", &pd::NoteOn::velocity)
		;

	py::class_<pd::ControlChange, std::shared_ptr<pd::ControlChange>>(m, "ControlChange", "change a control value aka send a CC message")
		.def( py::init<const int, const int, const int>(), py::arg("channel"), py::arg("controller"), py::arg("value") )
		.def_readonly("channel", &pd::ControlChange::channel)
		.def_readonly("controller", &pd::ControlChange::controller)
		.def_readonly("value", &pd::ControlChange::value)
		;

	py::class_<pd::ProgramChange, std::shared_ptr<pd::ProgramChange>>(m, "ProgramChange", "change a program value (ie an instrument)")
		.def( py::init<const int, const int>(), py::arg("channel"), py::arg("value") )
		.def_readonly("channel", &pd::ProgramChange::channel)
		.def_readonly("value", &pd::ProgramChange::value)
		;

	py::class_<pd::PitchBend, std::shared_ptr<pd::PitchBend>>(m, "PitchBend", "change the pitch bend value")
		.def( py::init<const int, const int>(), py::arg("channel"), py::arg("value") )
		.def_readonly("channel", &pd::PitchBend::channel)
		.def_readonly("value", &pd::PitchBend::value)
		;

	py::class_<pd::Aftertouch, std::shared_ptr<pd::Aftertouch>>(m, "Aftertouch", "change an aftertouch value")
		.def( py::init<const int, const int>(), py::arg("channel"), py::arg("value") )
		.def_readonly("channel", &pd::Aftertouch::channel)
		.def_readonly("value", &pd::Aftertouch::value)
		;

	py::class_<pd::PolyAftertouch, std::shared_ptr<pd::PolyAftertouch>>(m, "PolyAftertouch", "change a poly aftertouch value")
		.def( py::init<const int, const int, const int>(), py::arg("channel"), py::arg("pitch"), py::arg("value") )
		.def_readonly("channel", &pd::PolyAftertouch::channel)
		.def_readonly("pitch", &pd::PolyAftertouch::pitch)
		.def_readonly("value", &pd::PolyAftertouch::value)
		;

	py::class_<pd::MidiByte, std::shared_ptr<pd::MidiByte>>(m, "MidiByte", "a raw midi byte")
		.def( py::init<const int, unsigned char>(), py::arg("port"), py::arg("byte") )
		.def_readonly("port", &pd::MidiByte::port)
		.def_readonly("byte", &pd::MidiByte::byte)
		;

	py::class_<pd::StartMidi, std::shared_ptr<pd::StartMidi>>(m, "StartMidi", "start a raw midi byte stream")
		.def( py::init( [](){ return new pd::StartMidi(); } ), "doc" )
		.def( py::init<const int>(), py::arg("port") )
		.def_readonly("port", &pd::StartMidi::port)
		;

	py::class_<pd::StartSysex, std::shared_ptr<pd::StartSysex>>(m, "StartSysex", "start a raw sysex byte stream")
		.def( py::init( [](){ return new pd::StartSysex(); } ), "doc" )
		.def( py::init<const int>(), py::arg("port") )
		.def_readonly("port", &pd::StartSysex::port)
		;

	py::class_<pd::StartSysRealTime, std::shared_ptr<pd::StartSysRealTime>>(m, "StartSysRealTime", "start a sys realtime byte stream")
		.def( py::init( [](){ return new pd::StartSysRealTime(); } ), "doc" )
		.def( py::init<const int>(), py::arg("port") )
		.def_readonly("port", &pd::StartSysRealTime::port)
		;

	py::class_<pd::Finish, std::shared_ptr<pd::Finish>>(m, "Finish", "finish a midi byte stream")
		.def( py::init( [](){ return new pd::Finish(); } ) )
		;

	py::class_<pd::PdReceiver, std::shared_ptr<pd::PdReceiver>, PyCallBack_pd_PdReceiver>(m, "PdReceiver", "a pd message receiver base class")
		.def( py::init( [](){ return new pd::PdReceiver(); }, [](){ return new PyCallBack_pd_PdReceiver(); } ) )
		.def("print", (void (pd::PdReceiver::*)(const std::string &)) &pd::PdReceiver::print, "receive a print\n\nC++: pd::PdReceiver::print(const std::string &) --> void", py::arg("message"))
		.def("receiveBang", (void (pd::PdReceiver::*)(const std::string &)) &pd::PdReceiver::receiveBang, "receive a bang\n\nC++: pd::PdReceiver::receiveBang(const std::string &) --> void", py::arg("dest"))
		.def("receiveFloat", (void (pd::PdReceiver::*)(const std::string &, float)) &pd::PdReceiver::receiveFloat, "receive a float\n\nC++: pd::PdReceiver::receiveFloat(const std::string &, float) --> void", py::arg("dest"), py::arg("num"))
		.def("receiveSymbol", (void (pd::PdReceiver::*)(const std::string &, const std::string &)) &pd::PdReceiver::receiveSymbol, "receive a symbol\n\nC++: pd::PdReceiver::receiveSymbol(const std::string &, const std::string &) --> void", py::arg("dest"), py::arg("symbol"))
		.def("receiveList", (void (pd::PdReceiver::*)(const std::string &, const class pd::List &)) &pd::PdReceiver::receiveList, "receive a list\n\nC++: pd::PdReceiver::receiveList(const std::string &, const class pd::List &) --> void", py::arg("dest"), py::arg("list"))
		.def("receiveMessage", (void (pd::PdReceiver::*)(const std::string &, const std::string &, const class pd::List &)) &pd::PdReceiver::receiveMessage, "receive a named message ie. sent from a message box like:\n [; dest msg arg1 arg2 arg3(\n\nC++: pd::PdReceiver::receiveMessage(const std::string &, const std::string &, const class pd::List &) --> void", py::arg("dest"), py::arg("msg"), py::arg("list"))
		.def("assign", (class pd::PdReceiver & (pd::PdReceiver::*)(const class pd::PdReceiver &)) &pd::PdReceiver::operator=, "C++: pd::PdReceiver::operator=(const class pd::PdReceiver &) --> class pd::PdReceiver &", py::return_value_policy::automatic, py::arg(""))
		;

	py::class_<pd::PdMidiReceiver, std::shared_ptr<pd::PdMidiReceiver>, PyCallBack_pd_PdMidiReceiver>(m, "PdMidiReceiver", "a pd MIDI receiver base class")
		.def( py::init( [](){ return new pd::PdMidiReceiver(); }, [](){ return new PyCallBack_pd_PdMidiReceiver(); } ) )
		.def("receiveNoteOn", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receiveNoteOn, "receive a MIDI note on\n\nC++: pd::PdMidiReceiver::receiveNoteOn(const int, const int, const int) --> void", py::arg("channel"), py::arg("pitch"), py::arg("velocity"))
		.def("receiveControlChange", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receiveControlChange, "receive a MIDI control change\n\nC++: pd::PdMidiReceiver::receiveControlChange(const int, const int, const int) --> void", py::arg("channel"), py::arg("controller"), py::arg("value"))
		.def("receiveProgramChange", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveProgramChange, "receive a MIDI program change,\n note: pgm value is 1-128\n\nC++: pd::PdMidiReceiver::receiveProgramChange(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("receivePitchBend", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receivePitchBend, "receive a MIDI pitch bend\n\nC++: pd::PdMidiReceiver::receivePitchBend(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("receiveAftertouch", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveAftertouch, "receive a MIDI aftertouch message\n\nC++: pd::PdMidiReceiver::receiveAftertouch(const int, const int) --> void", py::arg("channel"), py::arg("value"))
		.def("receivePolyAftertouch", (void (pd::PdMidiReceiver::*)(const int, const int, const int)) &pd::PdMidiReceiver::receivePolyAftertouch, "receive a MIDI poly aftertouch message\n\nC++: pd::PdMidiReceiver::receivePolyAftertouch(const int, const int, const int) --> void", py::arg("channel"), py::arg("pitch"), py::arg("value"))
		.def("receiveMidiByte", (void (pd::PdMidiReceiver::*)(const int, const int)) &pd::PdMidiReceiver::receiveMidiByte, "receive a raw MIDI byte (sysex, realtime, etc)\n\nC++: pd::PdMidiReceiver::receiveMidiByte(const int, const int) --> void", py::arg("port"), py::arg("byte"))
		.def("assign", (class pd::PdMidiReceiver & (pd::PdMidiReceiver::*)(const class pd::PdMidiReceiver &)) &pd::PdMidiReceiver::operator=, "C++: pd::PdMidiReceiver::operator=(const class pd::PdMidiReceiver &) --> class pd::PdMidiReceiver &", py::return_value_policy::automatic, py::arg(""))
		;

}

