// Copyright (C) 2000-2003, Luca Padovani <luca.padovani@cs.unibo.it>.
//
// This file is part of GtkMathView, a Gtk widget for MathML.
// 
// GtkMathView is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// GtkMathView is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GtkMathView; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// For details, see the GtkMathView World-Wide-Web page,
// http://helm.cs.unibo.it/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#include <config.h>

#include <cassert>

#include "MathMLErrorElement.hh"
#include "MathFormattingContext.hh"
#include "MathGraphicDevice.hh"

MathMLErrorElement::MathMLErrorElement(const SmartPtr<class MathMLView>& view)
  : MathMLNormalizingContainerElement(view)
{
}

MathMLErrorElement::~MathMLErrorElement()
{
}

#if 0
void
MathMLErrorElement::Setup(RenderingEnvironment& env)
{
  if (dirtyAttribute() || dirtyAttributeP())
    {
      env.Push();
      RGBColor color = env.GetColor();

      if (color == RGBColor::RED()) env.SetColor(RGBColor::BLUE());
      else env.SetColor(RGBColor::RED());

      MathMLNormalizingContainerElement::Setup(env);
      env.Drop();
      resetDirtyAttribute();
    }
}
#endif

AreaRef
MathMLErrorElement::format(MathFormattingContext& ctxt)
{
  if (dirtyLayout())
    {
      ctxt.push(this);
      if (ctxt.getColor() == RGBColor::RED()) ctxt.setColor(RGBColor::BLUE());
      else ctxt.setColor(RGBColor::RED());
      AreaRef res = getChild() ? getChild()->format(ctxt) : 0;
      setArea(res ? ctxt.getDevice()->wrapper(ctxt, res) : 0);
      ctxt.pop();
      resetDirtyLayout();
    }

  return getArea();
}

