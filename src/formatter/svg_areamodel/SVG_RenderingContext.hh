// Copyright (C) 2000-2005, Luca Padovani <luca.padovani@cs.unibo.it>.
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

#ifndef __Gtk_RenderingContext_hh__
#define __Gtk_RenderingContext_hh__

#include "Char.hh"
#include "SmartPtr.hh"
#include "RGBColor.hh"
#include "BoundingBox.hh"
#include "RenderingContext.hh"
#include "String.hh"

class SVG_RenderingContext : public RenderingContext
{
public:
  SVG_RenderingContext(const SmartPtr<class AbstractLogger>&);
  virtual ~SVG_RenderingContext();

  void setForegroundColor(const RGBColor& c) { fgColor = c; }
  void setBackgroundColor(const RGBColor& c) { bgColor = c; }

  RGBColor getForegroundColor(void) const { return fgColor; }
  RGBColor getBackgroundColor(void) const { return bgColor; }

  virtual void documentStart(const scaled&, const scaled&);
  virtual void documentEnd(void);
  virtual void fill(const scaled&, const scaled&, const BoundingBox&);
  virtual void draw(const scaled&, const scaled&, const SmartPtr<class TFM_T1Font>&, Char8);
  virtual void wrapperStart(const scaled&, const scaled&, const BoundingBox&);
  virtual void wrapperEnd(void);

  static scaled toSVGX(const scaled& x) { return x; }
  static scaled toSVGY(const scaled& y) { return -y; }

protected:
  static String toSVGLength(const scaled&);
  static String toSVGColor(const RGBColor&);
  static String toSVGOpacity(const RGBColor&);

  virtual void beginDocument(const scaled&, const scaled&) = 0;
  virtual void endDocument(void) = 0;
  virtual void beginGroup(void) = 0;
  virtual void endGroup(void) = 0;
  virtual void text(const scaled&, const scaled&, const String&, const scaled&,
		    const RGBColor&, const RGBColor&, const scaled&, const String&) = 0;
  virtual void rect(const scaled&, const scaled&, const scaled&, const scaled&,
		    const RGBColor&, const RGBColor&, const scaled&) = 0;
  virtual void line(const scaled&, const scaled&, const scaled&, const scaled&,
		    const RGBColor&, const scaled&) = 0;

protected:
  SmartPtr<class AbstractLogger> logger;

  RGBColor fgColor;
  RGBColor bgColor;
};

#endif // __SVG_RenderingContext_hh__