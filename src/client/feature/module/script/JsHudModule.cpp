#include "pch.h"
#include "JsHudModule.h"
#include <client/script/objects/D2DScriptingObject.h>
#include <client/script/JsScript.h>

JsHUDModule::JsHUDModule(std::string const& name, std::string const& displayName, std::string const& desc, int key, bool resizable) : HUDModule(name, displayName, desc, SCRIPT, key, resizable) {
	JS::JsAddRef(object, nullptr);
	JS::JsGetCurrentContext(&this->ctx);

	script = JsScript::getThis();

	this->eventListeners[L"enable"] = {};
	this->eventListeners[L"disable"] = {};
	this->eventListeners[L"get-hold-to-toggle"] = {};
	this->eventListeners[L"render"] = {};
}

void JsHUDModule::onEnable(){
	Chakra::SetContext(ctx);
	Event ev{ L"enable", {  } };
	auto ret = dispatchEvent(ev.name, ev);
	if (ret != JS_INVALID_REFERENCE) {
		Chakra::Release(ret);
	}
}

void JsHUDModule::onDisable() {
	Chakra::SetContext(ctx);
	Event ev{ L"disable", {  } };
	auto ret = dispatchEvent(ev.name, ev);
	if (ret != JS_INVALID_REFERENCE) {
		Chakra::Release(ret);
	}
}

bool JsHUDModule::shouldHoldToToggle() {
	if (Latite::isMainThread()) {
		return cachedHoldToToggle;
	}

	Chakra::SetContext(ctx);
	Event ev{ L"get-hold-to-toggle", {  } };
	auto ret = dispatchEvent(ev.name, ev);
	if (ret != JS_INVALID_REFERENCE) {
		bool b;
		if (JS::JsBooleanToBool(ret, &b) == JsNoError) {
			cachedHoldToToggle = b;
			return b;
		}
		else {
			Chakra::ThrowError(L"get-hold-to-toggle must return boolean");
		}
		Chakra::Release(ret);
	}
	cachedHoldToToggle = false;
	return false;
}

void JsHUDModule::render(DrawUtil&, bool, bool) {
}

void JsHUDModule::preRender(bool mcRend, bool isPreview, bool isEditor) {
	Chakra::SetContext(ctx);
	auto obj = script->getObject<D2DScriptingObject>();
	bool oMinecraftRend = obj->usingMinecraftRend();
	obj->setUseMinecraftRend(mcRend);
	Event ev{ L"render", { isPreview ? Chakra::GetTrue() : Chakra::GetFalse(), isEditor ? Chakra::GetTrue() : Chakra::GetFalse()} };
	dispatchEvent(ev.name, ev);
	obj->setUseMinecraftRend(oMinecraftRend);
}
