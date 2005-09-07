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

#ifndef __MathMLOperatorDictionary_hh__
#define __MathMLOperatorDictionary_hh__

#include "SmartPtr.hh"
#include "String.hh"
#include "StringHash.hh"
#include "HashMap.hh"
#include "Object.hh"

class GMV_EXPORT MathMLOperatorDictionary : public Object
{
protected:
  MathMLOperatorDictionary(void);
  virtual ~MathMLOperatorDictionary();

public:
  static SmartPtr<MathMLOperatorDictionary> create(void) { return new MathMLOperatorDictionary; }

  void add(const class AbstractLogger&,
	   const String&, const String&, const SmartPtr<class AttributeSet>&);
  void search(const String&,
	      SmartPtr<class AttributeSet>&,
	      SmartPtr<class AttributeSet>&,
	      SmartPtr<class AttributeSet>&) const;

private:
  void unload(void);

  struct FormDefaults
  {
    SmartPtr<class AttributeSet> prefix;
    SmartPtr<class AttributeSet> infix;
    SmartPtr<class AttributeSet> postfix;
  };

  typedef HASH_MAP_NS::hash_map<String,FormDefaults,StringHash,StringEq> Dictionary;
  Dictionary items;
};

#endif // __MathMLOperatorDictionary_hh__

