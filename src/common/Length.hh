// Copyright (C) 2000-2007, Luca Padovani <padovani@sti.uniurb.it>.
//
// This file is part of GtkMathView, a flexible, high-quality rendering
// engine for MathML documents.
// 
// GtkMathView is free software; you can redistribute it and/or modify it
// either under the terms of the GNU Lesser General Public License version
// 3 as published by the Free Software Foundation (the "LGPL") or, at your
// option, under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation (the "GPL").  If you do not
// alter this notice, a recipient may use your version of this file under
// either the GPL or the LGPL.
//
// GtkMathView is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LGPL or
// the GPL for more details.
// 
// You should have received a copy of the LGPL and of the GPL along with
// this program in the files COPYING-LGPL-3 and COPYING-GPL-2; if not, see
// <http://www.gnu.org/licenses/>.

#ifndef __Length_hh__
#define __Length_hh__

struct Length
{
  enum Unit {
    UNDEFINED_UNIT,
    PURE_UNIT,
    INFINITY_UNIT,
    LT_UNIT,
    EM_UNIT,
    EX_UNIT,
    PX_UNIT,
    IN_UNIT,
    CM_UNIT,
    MM_UNIT,
    PT_UNIT,
    PC_UNIT,
    PERCENTAGE_UNIT,
    NEGATIVE_VERYVERYTHICK_SPACE,
    NEGATIVE_VERYTHICK_SPACE,
    NEGATIVE_THICK_SPACE,
    NEGATIVE_MEDIUM_SPACE,
    NEGATIVE_THIN_SPACE,
    NEGATIVE_VERYTHIN_SPACE,
    NEGATIVE_VERYVERYTHIN_SPACE,
    ZERO_SPACE,
    VERYVERYTHIN_SPACE,
    VERYTHIN_SPACE,
    THIN_SPACE,
    MEDIUM_SPACE,
    THICK_SPACE,
    VERYTHICK_SPACE,
    VERYVERYTHICK_SPACE,

    LAST_UNIT
  };
  
  Length(float v = 0.0f, Unit u = UNDEFINED_UNIT) : value(v), type(u) { }

  void set(float v = 0.0f, Unit u = UNDEFINED_UNIT) { value = v; type = u; }
  void unset(void) { type = UNDEFINED_UNIT; value = 0.0f; }
  bool defined(void) const { return type != UNDEFINED_UNIT; }
  bool absolute(void) const { return type >= IN_UNIT && type <= PC_UNIT; }
  bool isSpace(void) const { return type >= NEGATIVE_VERYVERYTHIN_SPACE && type <= VERYVERYTHICK_SPACE; }

  float value;
  Unit  type;
};

#endif // __Length_hh__
