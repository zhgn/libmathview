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

#include "AreaId.hh"
#include "BinContainerArea.hh"

BoundingBox
BinContainerArea::box() const
{
  return child->box();
}

void
BinContainerArea::render(class RenderingContext& context, const scaled& x, const scaled& y) const
{
  child->render(context, x, y);
}

scaled
BinContainerArea::leftEdge() const
{
  return child->leftEdge();
}

scaled
BinContainerArea::rightEdge() const
{
  return child->rightEdge();
}

bool
BinContainerArea::searchByArea(AreaId& id, const AreaRef& area) const
{
  if (area == this)
    return true;
  else
    {
      id.append(0, child);
      if (child->searchByArea(id, area)) return true;
      id.pop_back();
      return false;
    }
}

bool
BinContainerArea::searchByCoords(AreaId& id, const scaled& x, const scaled& y) const
{
  id.append(0, this, scaled::zero(), scaled::zero());
  if (child->searchByCoords(id, x, y)) return true;
  id.pop_back();
  return false;
}

bool
BinContainerArea::searchByIndex(AreaId& id, int index) const
{
  id.append(0, this);
  if (child->searchByIndex(id, index)) return true;
  id.pop_back();
  return false;
}

AreaRef
BinContainerArea::fit(const scaled& w, const scaled& h, const scaled& d) const
{
  AreaRef fitChild = child->fit(w, h, d);
  if (fitChild == child) return this;
  else return clone(fitChild);
}

void
BinContainerArea::strength(int& w, int& h, int& d) const
{
  child->strength(w, h, d);
}

AreaRef
BinContainerArea::node(unsigned i) const
{
  assert(i == 0);
  return getChild();
}

void
BinContainerArea::origin(unsigned i, scaled&, scaled&) const
{
  assert(i == 0);
}

int
BinContainerArea::lengthTo(unsigned i) const
{
  assert(i == 0);
  return 0;
}

AreaRef
BinContainerArea::replace(unsigned i, const AreaRef& newChild) const
{
  assert(i == 0);
  return (child == newChild) ? this : clone(newChild);
}

