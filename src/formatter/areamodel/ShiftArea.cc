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

#include "ShiftArea.hh"
#include "AreaId.hh"

void
ShiftArea::render(class RenderingContext& context, const scaled& x, const scaled& y) const
{
  getChild()->render(context, x, y + shift);
}

BoundingBox
ShiftArea::box() const
{
  BoundingBox childBox = getChild()->box();
  return
    childBox.defined()
    ? BoundingBox(childBox.width, childBox.height + shift, childBox.depth - shift)
    : childBox;
}

#if 0
bool
ShiftArea::find(class SearchingContext& context, const scaled& x, const scaled& y) const
{
  return BinContainerArea::find(context, x, y + shift);
}

std::pair<scaled,scaled>
ShiftArea::origin(AreaId::const_iterator id, AreaId::const_iterator empty, const scaled& x, const scaled& y) const
{
  return BinContainerArea::origin(id, empty, x, y + shift);
}
#endif

bool
ShiftArea::searchByCoords(AreaId& id, const scaled& x, const scaled& y) const
{
  id.append(0, getChild(), scaled::zero(), shift);
  if (getChild()->searchByCoords(id, x, y - shift)) return true; // ?????
  id.pop_back();
  return false;
}

void
ShiftArea::origin(unsigned i, scaled&, scaled& y) const
{
  assert(i == 0);
  y += shift;
}
