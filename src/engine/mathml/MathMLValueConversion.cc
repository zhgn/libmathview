// Copyright (C) 2000-2004, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://helm.cs.unibo.it/mml-widget/, or send a mail to
// <lpadovan@cs.unibo.it>

#include <config.h>

#include "MathMLValueConversion.hh"
#include "MathFormattingContext.hh"
#include "MathMLElement.hh"

MathVariant
toMathVariant(TokenId id)
{
  switch (id)
    {
    case T_NORMAL: return NORMAL_VARIANT;
    case T_BOLD: return BOLD_VARIANT;
    case T_ITALIC: return ITALIC_VARIANT;
    case T_BOLD_ITALIC: return BOLD_ITALIC_VARIANT;
    case T_DOUBLE_STRUCK: return DOUBLE_STRUCK_VARIANT;
    case T_BOLD_FRAKTUR: return BOLD_FRAKTUR_VARIANT;
    case T_SCRIPT: return SCRIPT_VARIANT;
    case T_BOLD_SCRIPT: return BOLD_SCRIPT_VARIANT;
    case T_FRAKTUR: return FRAKTUR_VARIANT;
    case T_SANS_SERIF: return SANS_SERIF_VARIANT;
    case T_BOLD_SANS_SERIF: return BOLD_SANS_SERIF_VARIANT;
    case T_SANS_SERIF_ITALIC: return SANS_SERIF_ITALIC_VARIANT;
    case T_SANS_SERIF_BOLD_ITALIC: return SANS_SERIF_BOLD_ITALIC_VARIANT;
    case T_MONOSPACE: return MONOSPACE_VARIANT;
    default: assert(false);
    }
}

MathVariant
toMathVariant(const SmartPtr<Value>& value)
{
  return toMathVariant(ToTokenId(value));
}

MathFormattingContext::PropertyId
toMathSpaceId(TokenId id)
{
  switch (id)
    {
    case T_NEGATIVEVERYVERYTHICKMATHSPACE: return MathFormattingContext::NEGATIVE_VERYVERYTHICK_SPACE;
    case T_NEGATIVEVERYTHICKMATHSPACE: return MathFormattingContext::NEGATIVE_VERYTHICK_SPACE;
    case T_NEGATIVETHICKMATHSPACE: return MathFormattingContext::NEGATIVE_THICK_SPACE;
    case T_NEGATIVEMEDIUMMATHSPACE: return MathFormattingContext::NEGATIVE_MEDIUM_SPACE;
    case T_NEGATIVETHINMATHSPACE: return MathFormattingContext::NEGATIVE_THIN_SPACE;
    case T_NEGATIVEVERYTHINMATHSPACE: return MathFormattingContext::NEGATIVE_VERYTHIN_SPACE;
    case T_NEGATIVEVERYVERYTHINMATHSPACE: return MathFormattingContext::NEGATIVE_VERYVERYTHIN_SPACE;
    case T_VERYVERYTHINMATHSPACE: return MathFormattingContext::VERYVERYTHIN_SPACE;
    case T_VERYTHINMATHSPACE: return MathFormattingContext::VERYTHIN_SPACE;
    case T_THINMATHSPACE: return MathFormattingContext::THIN_SPACE;
    case T_MEDIUMMATHSPACE: return MathFormattingContext::MEDIUM_SPACE;
    case T_THICKMATHSPACE: return MathFormattingContext::THICK_SPACE;
    case T_VERYTHICKMATHSPACE: return MathFormattingContext::VERYTHICK_SPACE;
    case T_VERYVERYTHICKMATHSPACE: return MathFormattingContext::VERYVERYTHICK_SPACE;
    default:
      assert(false);
      return MathFormattingContext::ZERO_SPACE;
    }
}

SmartPtr<Value>
Resolve(const SmartPtr<Value>& value, const MathFormattingContext& ctxt, int i, int j)
{
  assert(value);

  SmartPtr<Value> realValue = GetComponent(value, i, j);
  assert(realValue);

  if (IsTokenId(value))
    return Variant<Length>::create(ctxt.getMathSpace(toMathSpaceId(ToTokenId(value))));
  else
    return realValue;
}