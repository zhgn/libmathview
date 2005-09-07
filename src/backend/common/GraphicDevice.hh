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

#ifndef __GraphicDevice_hh__
#define __GraphicDevice_hh__

#include "Object.hh"
#include "Length.hh"
#include "scaled.hh"
#include "AreaFactory.hh"

class GMV_EXPORT GraphicDevice : public Object
{
protected:
  GraphicDevice(const SmartPtr<class AbstractLogger>&);
  virtual ~GraphicDevice();

public:
  SmartPtr<class AbstractLogger> getLogger(void) const;

  virtual void setFactory(const SmartPtr<AreaFactory>&);
  SmartPtr<AreaFactory> getFactory(void) const { return factory; }
  virtual void setShaperManager(const SmartPtr<class ShaperManager>&);
  SmartPtr<ShaperManager> getShaperManager(void) const;

  // Length evaluation, fundamental properties
  virtual double dpi(const class FormattingContext&) const;
  virtual scaled evaluate(const class FormattingContext&, const Length&, const scaled&) const;
  virtual scaled em(const class FormattingContext&) const;
  virtual scaled ex(const class FormattingContext&) const = 0;
  virtual scaled defaultLineThickness(const class FormattingContext&) const;

private:
  SmartPtr<class AbstractLogger> logger;
  SmartPtr<AreaFactory> factory;
  SmartPtr<class ShaperManager> shaperManager;
};

#endif // __GraphicDevice_hh__
