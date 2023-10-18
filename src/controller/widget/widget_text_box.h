/*
 * Copyright (C) 2014 Emmanuel Durand
 *
 * This file is part of Splash.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Splash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Splash.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * @widget_text_box.h
 * The text box widget, to display texts based on a given function
 */

#ifndef SPLASH_WIDGET_TEXT_BOX_H
#define SPLASH_WIDGET_TEXT_BOX_H

#include "./widget.h"

namespace Splash
{

/*************/
class GuiTextBox : public GuiWidget
{
  public:
    GuiTextBox(Scene* scene, const std::string& name = "")
        : GuiWidget(scene, name)
    {
    }
    void render() final;
    void setTextFunc(const std::function<std::string()>& func) { getText = func; }

  private:
    std::function<std::string()> getText;
};

} // namespace Splash

#endif
