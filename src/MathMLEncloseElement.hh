// Copyright (C) 2000, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://cs.unibo.it/~lpadovan/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#ifndef MathMLEncloseElement_hh
#define MathMLEncloseElement_hh

#if defined(HAVE_MINIDOM)
#include <minidom.h>
#elif defined(HAVE_GMETADOM)
#include "gmetadom.hh"
#endif

#include "RGBValue.hh"
#include "MathMLNormalizingContainerElement.hh"

enum NotationType {
  NOTATION_LONGDIV,
  NOTATION_ACTUARIAL,
  NOTATION_RADICAL
};

class MathMLEncloseElement: public MathMLNormalizingContainerElement
{
public:
#if defined(HAVE_MINIDOM)
  MathMLEncloseElement(mDOMNodeRef);
#elif defined(HAVE_GMETADOM)
  MathMLEncloseElement(GMetaDOM::Element&);
#endif
  virtual const AttributeSignature* GetAttributeSignature(AttributeId) const;
  virtual void Setup(class RenderingEnvironment*);
  virtual void DoBoxedLayout(LayoutId, BreakId, scaled);
  virtual void SetPosition(scaled, scaled);
  virtual void Render(const DrawingArea&);
  virtual ~MathMLEncloseElement();

protected:
  void NormalizeRadicalElement(void);

  bool         normalized;

  NotationType notation;
  scaled       spacing;
  scaled       lineThickness;
  RGBValue     color;
};

#endif // MathMLEncloseElement_hh
