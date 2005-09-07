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

#include <limits>
#include <sstream>

#include "StringAux.hh"

std::string
escape(const UCS4String& s)
{
  std::ostringstream os;
  UCS4String::const_iterator i = s.begin();
  while (i != s.end())
    {
      if (*i >= std::numeric_limits<char>::min() && *i <= std::numeric_limits<char>::max())
	os << static_cast<char>(*i);
      else
	{
	  os << "&#x" << std::hex;
	  os.width(4);
	  os.fill('0');
	  os << static_cast<int>(*i) << std::dec;
	  os.width(0);
	  os << ";";
	}
      i++;
    }

  return os.str();
}

std::ostream&
operator<<(std::ostream& os, const UCS4String& s)
{ return os << escape(s); }

