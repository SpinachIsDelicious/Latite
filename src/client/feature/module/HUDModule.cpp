/* Copyright (C) Imrglop, All rights reserved
 * Copyright (C) Latite Client contributors, All rights reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited without the permission of the author.
 * Proprietary and confidential
 * Written by Imrglop <contact: latiteclientgithub@gmail.com>, 2023
 */

#include "HUDModule.h"
#include "util/Util.h"
#include <client/Latite.h>

void HUDModule::renderSelected() {
	DXContext dc;
	dc.fillRectangle(this->getRect(), { 1.f, 1.f, 1.f, 0.2f });
}

void HUDModule::renderFrame()
{
	DXContext ctx;
	ctx.fillRectangle(this->getRect(), { 0.F, 0.F, 0.F, 0.4F });
	ctx.drawRectangle(this->getRect(), d2d::Colors::BLACK, 0.6f);
}

void HUDModule::renderPost()
{
	DXContext ctx;
	ctx.drawText(getRect(), util::StrToWStr(this->getDisplayName()), d2d::Color(0.5F, 1.0F, 1.0F, 1.f), Renderer::FontSelection::Light,
		16.f);
}

void HUDModule::afterLoadConfig() {
	auto ss = Latite::getRenderer().getScreenSize();
	auto& sp = std::get<Vec2Value>(this->storedPos);
	setPos({ sp.x * ss.width, sp.y * ss.height });
}

void HUDModule::storePos() {
	auto& vec = std::get<Vec2Value>(storedPos);
	auto ss = Latite::getRenderer().getScreenSize();
	vec.x = rect.left / ss.width;
	vec.y = rect.top / ss.height;
}

d2d::Rect HUDModule::getRect() {
	return { rect.left, rect.top, rect.left + ((rect.getWidth()) * getScale()), rect.top + ((rect.getHeight()) * getScale()) };
}
