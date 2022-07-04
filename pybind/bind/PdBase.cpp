#include <PdBase.hpp>
#include <PdMidiReceiver.hpp>
#include <PdReceiver.hpp>
#include <PdTypes.hpp>
#include <memory>
#include <sstream> // __str__
#include <string>
#include <string_view>
#include <vector>

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

// pd::PdBase file:PdBase.hpp line:55
struct PyCallBack_pd_PdBase : public pd::PdBase {
	using pd::PdBase::PdBase;

	bool init(const int a0, const int a1, const int a2, bool a3) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "init");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3);
			if (pybind11::detail::cast_is_temporary_value_reference<bool>::value) {
				static pybind11::detail::override_caster_t<bool> caster;
				return pybind11::detail::cast_ref<bool>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<bool>(std::move(o));
		}
		return PdBase::init(a0, a1, a2, a3);
	}
	void clear() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "clear");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::clear();
	}
	void addToSearchPath(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "addToSearchPath");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::addToSearchPath(a0);
	}
	void clearSearchPath() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "clearSearchPath");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::clearSearchPath();
	}
	class pd::Patch openPatch(const std::string & a0, const std::string & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "openPatch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<class pd::Patch>::value) {
				static pybind11::detail::override_caster_t<class pd::Patch> caster;
				return pybind11::detail::cast_ref<class pd::Patch>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<class pd::Patch>(std::move(o));
		}
		return PdBase::openPatch(a0, a1);
	}
	class pd::Patch openPatch(class pd::Patch & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "openPatch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<class pd::Patch>::value) {
				static pybind11::detail::override_caster_t<class pd::Patch> caster;
				return pybind11::detail::cast_ref<class pd::Patch>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<class pd::Patch>(std::move(o));
		}
		return PdBase::openPatch(a0);
	}
	void closePatch(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "closePatch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::closePatch(a0);
	}
	void closePatch(class pd::Patch & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "closePatch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::closePatch(a0);
	}
	void computeAudio(bool a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "computeAudio");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::computeAudio(a0);
	}
	void subscribe(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "subscribe");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::subscribe(a0);
	}
	void unsubscribe(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "unsubscribe");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::unsubscribe(a0);
	}
	bool exists(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "exists");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<bool>::value) {
				static pybind11::detail::override_caster_t<bool> caster;
				return pybind11::detail::cast_ref<bool>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<bool>(std::move(o));
		}
		return PdBase::exists(a0);
	}
	void unsubscribeAll() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "unsubscribeAll");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::unsubscribeAll();
	}
	void receiveMessages() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "receiveMessages");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::receiveMessages();
	}
	void receiveMidi() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "receiveMidi");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::receiveMidi();
	}
	void sendBang(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendBang");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendBang(a0);
	}
	void sendFloat(const std::string & a0, float a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendFloat");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendFloat(a0, a1);
	}
	void sendSymbol(const std::string & a0, const std::string & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendSymbol");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendSymbol(a0, a1);
	}
	void startMessage() override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "startMessage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>();
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::startMessage();
	}
	void addFloat(const float a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "addFloat");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::addFloat(a0);
	}
	void addSymbol(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "addSymbol");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::addSymbol(a0);
	}
	void finishList(const std::string & a0) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "finishList");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::finishList(a0);
	}
	void finishMessage(const std::string & a0, const std::string & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "finishMessage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::finishMessage(a0, a1);
	}
	void sendList(const std::string & a0, const class pd::List & a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendList");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendList(a0, a1);
	}
	void sendMessage(const std::string & a0, const std::string & a1, const class pd::List & a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendMessage");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendMessage(a0, a1, a2);
	}
	void sendNoteOn(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendNoteOn");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendNoteOn(a0, a1, a2);
	}
	void sendControlChange(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendControlChange");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendControlChange(a0, a1, a2);
	}
	void sendProgramChange(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendProgramChange");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendProgramChange(a0, a1);
	}
	void sendPitchBend(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendPitchBend");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendPitchBend(a0, a1);
	}
	void sendAftertouch(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendAftertouch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendAftertouch(a0, a1);
	}
	void sendPolyAftertouch(const int a0, const int a1, const int a2) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendPolyAftertouch");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendPolyAftertouch(a0, a1, a2);
	}
	void sendMidiByte(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendMidiByte");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendMidiByte(a0, a1);
	}
	void sendSysex(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendSysex");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendSysex(a0, a1);
	}
	void sendSysRealTime(const int a0, const int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "sendSysRealTime");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::sendSysRealTime(a0, a1);
	}
	bool readArray(const std::string & a0, class std::vector<float, class std::allocator<float> > & a1, int a2, int a3) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "readArray");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3);
			if (pybind11::detail::cast_is_temporary_value_reference<bool>::value) {
				static pybind11::detail::override_caster_t<bool> caster;
				return pybind11::detail::cast_ref<bool>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<bool>(std::move(o));
		}
		return PdBase::readArray(a0, a1, a2, a3);
	}
	bool writeArray(const std::string & a0, class std::vector<float, class std::allocator<float> > & a1, int a2, int a3) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "writeArray");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1, a2, a3);
			if (pybind11::detail::cast_is_temporary_value_reference<bool>::value) {
				static pybind11::detail::override_caster_t<bool> caster;
				return pybind11::detail::cast_ref<bool>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<bool>(std::move(o));
		}
		return PdBase::writeArray(a0, a1, a2, a3);
	}
	void clearArray(const std::string & a0, int a1) override {
		pybind11::gil_scoped_acquire gil;
		pybind11::function overload = pybind11::get_overload(static_cast<const pd::PdBase *>(this), "clearArray");
		if (overload) {
			auto o = overload.operator()<pybind11::return_value_policy::reference>(a0, a1);
			if (pybind11::detail::cast_is_temporary_value_reference<void>::value) {
				static pybind11::detail::override_caster_t<void> caster;
				return pybind11::detail::cast_ref<void>(std::move(o), caster);
			}
			else return pybind11::detail::cast_safe<void>(std::move(o));
		}
		return PdBase::clearArray(a0, a1);
	}
};

void bind_PdBase(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	{ // pd::PdBase file:PdBase.hpp line:55
		pybind11::class_<pd::PdBase, std::shared_ptr<pd::PdBase>, PyCallBack_pd_PdBase> cl(M("pd"), "PdBase", "a Pure Data instance\n\n use this class directly or extend it and any of its virtual functions\n\n note: libpd currently does not support multiple states and it is\n       suggested that you use only one PdBase-derived object at a time\n\n       calls from multiple PdBase instances currently use a global context\n       kept in a singleton object, thus only one Receiver & one MidiReceiver\n       can be used within a single program\n\n       multiple context support will be added if/when it is included within\n       libpd");
		cl.def( pybind11::init( [](){ return new pd::PdBase(); }, [](){ return new PyCallBack_pd_PdBase(); } ) );
		cl.def("init", [](pd::PdBase &o, const int & a0, const int & a1, const int & a2) -> bool { return o.init(a0, a1, a2); }, "", pybind11::arg("numInChannels"), pybind11::arg("numOutChannels"), pybind11::arg("sampleRate"));
		cl.def("init", (bool (pd::PdBase::*)(const int, const int, const int, bool)) &pd::PdBase::init, "initialize resources and set up the audio processing\n\n set the audio latency by setting the libpd ticks per buffer:\n ticks per buffer * lib pd block size (always 64)\n\n ie 4 ticks per buffer * 64 = buffer len of 512\n\n you can call this again after loading patches & setting receivers\n in order to update the audio settings\n\n the lower the number of ticks, the faster the audio processing\n if you experience audio dropouts (audible clicks), increase the\n ticks per buffer\n\n set queued = true to use the built in ringbuffers for message and\n midi event passing, you will then need to call receiveMessages() and\n receiveMidi() in order to pass messages from the ringbuffers to your\n PdReceiver and PdMidiReceiver implementations\n\n the queued ringbuffers are useful when you need to receive events\n on a gui thread and don't want to use locking\n\n return true if setup successfully\n\n note: must be called before processing\n\nC++: pd::PdBase::init(const int, const int, const int, bool) --> bool", pybind11::arg("numInChannels"), pybind11::arg("numOutChannels"), pybind11::arg("sampleRate"), pybind11::arg("queued"));
		cl.def("clear", (void (pd::PdBase::*)()) &pd::PdBase::clear, "clear resources\n\nC++: pd::PdBase::clear() --> void");
		cl.def("addToSearchPath", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::addToSearchPath, "add to the pd search path\n takes an absolute or relative path (in data folder)\n\n note: fails silently if path not found\n\nC++: pd::PdBase::addToSearchPath(const std::string &) --> void", pybind11::arg("path"));
		cl.def("clearSearchPath", (void (pd::PdBase::*)()) &pd::PdBase::clearSearchPath, "clear the current pd search path\n\nC++: pd::PdBase::clearSearchPath() --> void");
		cl.def("openPatch", (class pd::Patch (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::openPatch, "open a patch file (aka somefile.pd) at a specified parent dir path\n returns a Patch object\n\n use Patch::isValid() to check if a patch was opened successfully:\n\n     Patch p1 = pd.openPatch(\"somefile.pd\", \"/some/dir/path/\");\n     if(!p1.isValid()) {\n         cout << \"aww ... p1 couldn't be opened\" << std::endl;\n     }\n\nC++: pd::PdBase::openPatch(const std::string &, const std::string &) --> class pd::Patch", pybind11::arg("patch"), pybind11::arg("path"));
		cl.def("openPatch", (class pd::Patch (pd::PdBase::*)(class pd::Patch &)) &pd::PdBase::openPatch, "open a patch file using the filename and path of an existing patch\n\n set the filename within the patch object or use a previously opened\n object\n\n     // open an instance of \"somefile.pd\"\n     Patch p2(\"somefile.pd\", \"/some/path\"); // set file and path\n     pd.openPatch(p2);\n\n     // open a new instance of \"somefile.pd\"\n     Patch p3 = pd.openPatch(p2);\n\n     // p2 and p3 refer to 2 different instances of \"somefile.pd\"\n\nC++: pd::PdBase::openPatch(class pd::Patch &) --> class pd::Patch", pybind11::arg("patch"));
		cl.def("closePatch", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::closePatch, "close a patch file\n takes only the patch's basename (filename without extension)\n\nC++: pd::PdBase::closePatch(const std::string &) --> void", pybind11::arg("patch"));
		cl.def("closePatch", (void (pd::PdBase::*)(class pd::Patch &)) &pd::PdBase::closePatch, "close a patch file, takes a patch object\n note: clears the given Patch object\n\nC++: pd::PdBase::closePatch(class pd::Patch &) --> void", pybind11::arg("patch"));
		cl.def("processFloat", (bool (pd::PdBase::*)(int, const float *, float *)) &pd::PdBase::processFloat, "process float buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processFloat(int, const float *, float *) --> bool", pybind11::arg("ticks"), pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("processShort", (bool (pd::PdBase::*)(int, const short *, short *)) &pd::PdBase::processShort, "process short buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processShort(int, const short *, short *) --> bool", pybind11::arg("ticks"), pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("processDouble", (bool (pd::PdBase::*)(int, const double *, double *)) &pd::PdBase::processDouble, "process double buffers for a given number of ticks\n returns false on error\n\nC++: pd::PdBase::processDouble(int, const double *, double *) --> bool", pybind11::arg("ticks"), pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("processRaw", (bool (pd::PdBase::*)(const float *, float *)) &pd::PdBase::processRaw, "process one pd tick, writes raw float data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRaw(const float *, float *) --> bool", pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("processRawShort", (bool (pd::PdBase::*)(const short *, short *)) &pd::PdBase::processRawShort, "process one pd tick, writes raw short data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRawShort(const short *, short *) --> bool", pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("processRawDouble", (bool (pd::PdBase::*)(const double *, double *)) &pd::PdBase::processRawDouble, "process one pd tick, writes raw double data to/from buffers\n returns false on error\n\nC++: pd::PdBase::processRawDouble(const double *, double *) --> bool", pybind11::arg("inBuffer"), pybind11::arg("outBuffer"));
		cl.def("computeAudio", (void (pd::PdBase::*)(bool)) &pd::PdBase::computeAudio, "start/stop audio processing\n\n in general, once started, you won't need to turn off audio\n\n shortcut for [; pd dsp 1( & [; pd dsp 0(\n\nC++: pd::PdBase::computeAudio(bool) --> void", pybind11::arg("state"));
		cl.def("subscribe", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::subscribe, "subscribe to messages sent by a pd send source\n\n aka this like a virtual pd receive object\n\n     [r source]\n     |\n\nC++: pd::PdBase::subscribe(const std::string &) --> void", pybind11::arg("source"));
		cl.def("unsubscribe", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::unsubscribe, "unsubscribe from messages sent by a pd send source\n\nC++: pd::PdBase::unsubscribe(const std::string &) --> void", pybind11::arg("source"));
		cl.def("exists", (bool (pd::PdBase::*)(const std::string &)) &pd::PdBase::exists, "is a pd send source subscribed?\n\nC++: pd::PdBase::exists(const std::string &) --> bool", pybind11::arg("source"));
		cl.def("unsubscribeAll", (void (pd::PdBase::*)()) &pd::PdBase::unsubscribeAll, "/ receivers will be unsubscribed from *all* pd send sources\n\nC++: pd::PdBase::unsubscribeAll() --> void");
		cl.def("receiveMessages", (void (pd::PdBase::*)()) &pd::PdBase::receiveMessages, "process waiting messages\n\nC++: pd::PdBase::receiveMessages() --> void");
		cl.def("receiveMidi", (void (pd::PdBase::*)()) &pd::PdBase::receiveMidi, "process waiting midi messages\n\nC++: pd::PdBase::receiveMidi() --> void");
		cl.def("setReceiver", (void (pd::PdBase::*)(class pd::PdReceiver *)) &pd::PdBase::setReceiver, "set the incoming event receiver, disables the event queue\n\n automatically receives from all currently subscribed sources\n\n set this to NULL to disable callback receiving and re-enable the\n event queue\n\nC++: pd::PdBase::setReceiver(class pd::PdReceiver *) --> void", pybind11::arg("receiver"));
		cl.def("setMidiReceiver", (void (pd::PdBase::*)(class pd::PdMidiReceiver *)) &pd::PdBase::setMidiReceiver, "set the incoming midi event receiver, disables the midi queue\n\n automatically receives from all midi channels\n\n set this to NULL to disable midi events and re-enable the midi queue\n\nC++: pd::PdBase::setMidiReceiver(class pd::PdMidiReceiver *) --> void", pybind11::arg("midiReceiver"));
		cl.def("sendBang", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::sendBang, "send a bang message\n\nC++: pd::PdBase::sendBang(const std::string &) --> void", pybind11::arg("dest"));
		cl.def("sendFloat", (void (pd::PdBase::*)(const std::string &, float)) &pd::PdBase::sendFloat, "send a float\n\nC++: pd::PdBase::sendFloat(const std::string &, float) --> void", pybind11::arg("dest"), pybind11::arg("value"));
		cl.def("sendSymbol", (void (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::sendSymbol, "send a symbol\n\nC++: pd::PdBase::sendSymbol(const std::string &, const std::string &) --> void", pybind11::arg("dest"), pybind11::arg("symbol"));
		cl.def("startMessage", (void (pd::PdBase::*)()) &pd::PdBase::startMessage, "start a compound list or message\n\nC++: pd::PdBase::startMessage() --> void");
		cl.def("addFloat", (void (pd::PdBase::*)(const float)) &pd::PdBase::addFloat, "add a float to the current compound list or message\n\nC++: pd::PdBase::addFloat(const float) --> void", pybind11::arg("num"));
		cl.def("addSymbol", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::addSymbol, "add a symbol to the current compound list or message\n\nC++: pd::PdBase::addSymbol(const std::string &) --> void", pybind11::arg("symbol"));
		cl.def("finishList", (void (pd::PdBase::*)(const std::string &)) &pd::PdBase::finishList, "finish and send as a list\n\nC++: pd::PdBase::finishList(const std::string &) --> void", pybind11::arg("dest"));
		cl.def("finishMessage", (void (pd::PdBase::*)(const std::string &, const std::string &)) &pd::PdBase::finishMessage, "finish and send as a list with a specific message name\n\nC++: pd::PdBase::finishMessage(const std::string &, const std::string &) --> void", pybind11::arg("dest"), pybind11::arg("msg"));
		cl.def("sendList", (void (pd::PdBase::*)(const std::string &, const class pd::List &)) &pd::PdBase::sendList, "send a list using the PdBase List type\n\n     List list;\n     list.addSymbol(\"hello\");\n     list.addFloat(1.23);\n     pd.sstd::endlist(\"test\", list);\n\n sends [list hello 1.23( -> [r test]\n\n stream operators work as well:\n\n     list << \"hello\" << 1.23;\n     pd.sstd::endlist(\"test\", list);\n\nC++: pd::PdBase::sendList(const std::string &, const class pd::List &) --> void", pybind11::arg("dest"), pybind11::arg("list"));
		cl.def("sendMessage", [](pd::PdBase &o, const std::string & a0, const std::string & a1) -> void { return o.sendMessage(a0, a1); }, "", pybind11::arg("dest"), pybind11::arg("msg"));
		cl.def("sendMessage", (void (pd::PdBase::*)(const std::string &, const std::string &, const class pd::List &)) &pd::PdBase::sendMessage, "pd.sendMessage(\"test\", \"msg1\", list);\n\nC++: pd::PdBase::sendMessage(const std::string &, const std::string &, const class pd::List &) --> void", pybind11::arg("dest"), pybind11::arg("msg"), pybind11::arg("list"));
		cl.def("sendNoteOn", [](pd::PdBase &o, const int & a0, const int & a1) -> void { return o.sendNoteOn(a0, a1); }, "", pybind11::arg("channel"), pybind11::arg("pitch"));
		cl.def("sendNoteOn", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendNoteOn, "send a MIDI note on\n\n pd does not use note off MIDI messages, so send a note on with vel = 0\n\nC++: pd::PdBase::sendNoteOn(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("velocity"));
		cl.def("sendControlChange", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendControlChange, "send a MIDI control change\n\nC++: pd::PdBase::sendControlChange(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("controller"), pybind11::arg("value"));
		cl.def("sendProgramChange", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendProgramChange, "send a MIDI program change\n\nC++: pd::PdBase::sendProgramChange(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("sendPitchBend", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendPitchBend, "send a MIDI pitch bend\n\n in pd: [bendin] takes 0 - 16383 while [bendout] returns -8192 - 8192\n\nC++: pd::PdBase::sendPitchBend(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("sendAftertouch", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendAftertouch, "send a MIDI aftertouch\n\nC++: pd::PdBase::sendAftertouch(const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("value"));
		cl.def("sendPolyAftertouch", (void (pd::PdBase::*)(const int, const int, const int)) &pd::PdBase::sendPolyAftertouch, "send a MIDI poly aftertouch\n\nC++: pd::PdBase::sendPolyAftertouch(const int, const int, const int) --> void", pybind11::arg("channel"), pybind11::arg("pitch"), pybind11::arg("value"));
		cl.def("sendMidiByte", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendMidiByte, "send a raw MIDI byte\n\n value is a raw midi byte value 0 - 255\n port is the raw portmidi port #, similar to a channel\n\n for some reason, [midiin], [sysexin] & [realtimein] add 2 to the\n port num, so sending to port 1 in PdBase returns port 3 in pd\n\n however, [midiout], [sysexout], & [realtimeout] do not add to the\n port num, so sending port 1 to [midiout] returns port 1 in PdBase\n\nC++: pd::PdBase::sendMidiByte(const int, const int) --> void", pybind11::arg("port"), pybind11::arg("value"));
		cl.def("sendSysex", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendSysex, "send a raw MIDI sysex byte\n\nC++: pd::PdBase::sendSysex(const int, const int) --> void", pybind11::arg("port"), pybind11::arg("value"));
		cl.def("sendSysRealTime", (void (pd::PdBase::*)(const int, const int)) &pd::PdBase::sendSysRealTime, "send a raw MIDI realtime byte\n\nC++: pd::PdBase::sendSysRealTime(const int, const int) --> void", pybind11::arg("port"), pybind11::arg("value"));
		cl.def("isMessageInProgress", (bool (pd::PdBase::*)()) &pd::PdBase::isMessageInProgress, "is a message or byte stream currently in progress?\n\nC++: pd::PdBase::isMessageInProgress() --> bool");
		cl.def("arraySize", (int (pd::PdBase::*)(const std::string &)) &pd::PdBase::arraySize, "get the size of a pd array\n returns 0 if array not found\n\nC++: pd::PdBase::arraySize(const std::string &) --> int", pybind11::arg("name"));
		cl.def("resizeArray", (bool (pd::PdBase::*)(const std::string &, long)) &pd::PdBase::resizeArray, "(re)size a pd array\n sizes <= 0 are clipped to 1\n returns true on success, false on failure\n\nC++: pd::PdBase::resizeArray(const std::string &, long) --> bool", pybind11::arg("name"), pybind11::arg("size"));
		cl.def("readArray", [](pd::PdBase &o, const std::string & a0, class std::vector<float, class std::allocator<float> > & a1) -> bool { return o.readArray(a0, a1); }, "", pybind11::arg("name"), pybind11::arg("dest"));
		cl.def("readArray", [](pd::PdBase &o, const std::string & a0, class std::vector<float, class std::allocator<float> > & a1, int const & a2) -> bool { return o.readArray(a0, a1, a2); }, "", pybind11::arg("name"), pybind11::arg("dest"), pybind11::arg("readLen"));
		cl.def("readArray", (bool (pd::PdBase::*)(const std::string &, class std::vector<float, class std::allocator<float> > &, int, int)) &pd::PdBase::readArray, "read from a pd array\n\n resizes given vector to readLen, checks readLen and offset\n\n returns true on success, false on failure\n\n calling without setting readLen and offset reads the whole array:\n\n vector<float> array1;\n readArray(\"array1\", array1);\n\nC++: pd::PdBase::readArray(const std::string &, class std::vector<float, class std::allocator<float> > &, int, int) --> bool", pybind11::arg("name"), pybind11::arg("dest"), pybind11::arg("readLen"), pybind11::arg("offset"));
		cl.def("writeArray", [](pd::PdBase &o, const std::string & a0, class std::vector<float, class std::allocator<float> > & a1) -> bool { return o.writeArray(a0, a1); }, "", pybind11::arg("name"), pybind11::arg("source"));
		cl.def("writeArray", [](pd::PdBase &o, const std::string & a0, class std::vector<float, class std::allocator<float> > & a1, int const & a2) -> bool { return o.writeArray(a0, a1, a2); }, "", pybind11::arg("name"), pybind11::arg("source"), pybind11::arg("writeLen"));
		cl.def("writeArray", (bool (pd::PdBase::*)(const std::string &, class std::vector<float, class std::allocator<float> > &, int, int)) &pd::PdBase::writeArray, "write to a pd array\n\n calling without setting writeLen and offset writes the whole array:\n\n writeArray(\"array1\", array1);\n\nC++: pd::PdBase::writeArray(const std::string &, class std::vector<float, class std::allocator<float> > &, int, int) --> bool", pybind11::arg("name"), pybind11::arg("source"), pybind11::arg("writeLen"), pybind11::arg("offset"));
		cl.def("clearArray", [](pd::PdBase &o, const std::string & a0) -> void { return o.clearArray(a0); }, "", pybind11::arg("name"));
		cl.def("clearArray", (void (pd::PdBase::*)(const std::string &, int)) &pd::PdBase::clearArray, "clear array and set to a specific value\n\nC++: pd::PdBase::clearArray(const std::string &, int) --> void", pybind11::arg("name"), pybind11::arg("value"));
		cl.def("isInited", (bool (pd::PdBase::*)()) &pd::PdBase::isInited, "has the global pd instance been initialized?\n\nC++: pd::PdBase::isInited() --> bool");
		cl.def("isQueued", (bool (pd::PdBase::*)()) &pd::PdBase::isQueued, "is the global pd instance using the ringerbuffer queue\n for message padding?\n\nC++: pd::PdBase::isQueued() --> bool");
		cl.def_static("blockSize", (int (*)()) &pd::PdBase::blockSize, "get the blocksize of pd (sample length per channel)\n\nC++: pd::PdBase::blockSize() --> int");
		cl.def("setMaxMessageLen", (void (pd::PdBase::*)(unsigned int)) &pd::PdBase::setMaxMessageLen, "set the max length of messages and lists, default: 32\n\nC++: pd::PdBase::setMaxMessageLen(unsigned int) --> void", pybind11::arg("len"));
		cl.def("maxMessageLen", (unsigned int (pd::PdBase::*)()) &pd::PdBase::maxMessageLen, "get the max length of messages and lists\n\nC++: pd::PdBase::maxMessageLen() --> unsigned int");
		cl.def("assign", (class pd::PdBase & (pd::PdBase::*)(const class pd::PdBase &)) &pd::PdBase::operator=, "C++: pd::PdBase::operator=(const class pd::PdBase &) --> class pd::PdBase &", pybind11::return_value_policy::automatic, pybind11::arg(""));
	}
}
