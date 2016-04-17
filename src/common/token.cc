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

#include <config.h>

#include <cassert>

#include <unordered_map>
#include "StringHash.hh"
#include "token.hh"

struct Entry
{
  TokenId id;
  const char32_t* literal;
};

static Entry token[] =
  {
#include "token.def"
    { T__NOTVALID, nullptr }
  };

typedef std::unordered_map<std::u32string,TokenId,std::hash<std::u32string>> Map;
static Map map;

TokenId
tokenIdOfString(const std::u32string &s)
{
  static bool initialized = false;
  if (!initialized)
    {
      for (unsigned i = 1; token[i].literal; i++)
        map[std::u32string(token[i].literal)] = token[i].id;
      initialized = true;
    }

  auto p = map.find(s);
  return (p != map.end()) ? (*p).second : T__NOTVALID;
}
