/* Copyright (C) Imrglop, All rights reserved
 * Copyright (C) Latite Client contributors, All rights reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited without the permission of the author.
 * Proprietary and confidential
 * Written by Imrglop <contact: latiteclientgithub@gmail.com>, 2023
 */

#pragma once
#include "api/eventing/Event.h"
#include "util/FNV32.h"
#include "util/DXUtil.h"

class RenderOverlayEvent : public Event {
public:
	static const uint32_t hash = TOHASH(RenderOverlayEvent);

	RenderOverlayEvent(ID2D1DeviceContext* ctx) : ctx(ctx) {};
	[[nodiscard]] ID2D1DeviceContext* getDeviceContext() noexcept { return ctx; };
private:
	ID2D1DeviceContext* ctx;
};