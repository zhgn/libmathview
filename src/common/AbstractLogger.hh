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

#ifndef __AbstractLogger_hh__
#define __AbstractLogger_hh__

#include "Object.hh"
#include "String.hh"

enum LogLevelId { LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG };

class AbstractLogger : public Object
{
protected:
  AbstractLogger(void);
  virtual ~AbstractLogger();

public:
  void setLogLevel(LogLevelId);
  LogLevelId getLogLevel(void) const { return logLevel; }

  void out(LogLevelId, const char*, ...) const;

protected:
  virtual void outString(const String&) const = 0;

private:
  LogLevelId logLevel;  
};

#endif // __AbstractLogger_hh__