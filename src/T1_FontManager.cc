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

#include <config.h>

#ifdef HAVE_LIBT1

#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <t1lib.h>

#include "T1_Font.hh"
#include "Iterator.hh"
#include "MathEngine.hh"
#include "T1_FontManager.hh"

bool T1_FontManager::firstTime = true;

T1_FontManager::T1_FontManager()
{
  if (firstTime) {
    void* res = T1_InitLib(LOGFILE | IGNORE_FONTDATABASE);
    if (res == NULL) {
      MathEngine::logger(LOG_ERROR, "could not initialize T1 library (aborted)");
      exit(-1);
    }
    assert(res != NULL);
    firstTime = false;
  }
}

T1_FontManager::~T1_FontManager()
{
  int res = T1_CloseLib();
  if (res != 0)
    MathEngine::logger(LOG_WARNING, "T1 lib could not uninitialize itself properly, please consult the log file");

  firstTime = true;
}

const AFont*
T1_FontManager::SearchNativeFont(const FontAttributes& fa,
				 const ExtraFontAttributes* efa) const
{
  // FIXME: maybe with the new version of t1lib it can be done like
  // for Gtk_FontManager, because it is not necessary any more to know
  // the file name from the config file. Maybe.
  if (efa == NULL) return NULL;

  const char* type = efa->GetProperty("type");
  if (type == NULL) {
    MathEngine::logger(LOG_ERROR, "could not determine font type (check the font configuration file)");
    return NULL;
  }

  if (strcmp(type, "type1") && strcmp(type, "ps")) return NULL;

  const char* fileName = efa->GetProperty("ps-file");
  if (fileName == NULL) {
    MathEngine::logger(LOG_WARNING, "Type1 font `%s' has no file attribute", fa.family);
    return NULL;
  }

  int n = T1_Get_no_fonts();
  int i;
  for (i = 0; i < n && strcmp(fileName, T1_GetFontFileName(i)); i++) ;

  if (i == n) {
    MathEngine::logger(LOG_INFO, "adding font file `%s' to the font database", fileName);
    i = T1_AddFont(const_cast<char*>(fileName));
    if (i < 0) {
      MathEngine::logger(LOG_WARNING, "could not load Type1 font file `%s'", fileName);
      return NULL;
    }
    MathEngine::logger(LOG_INFO, "loading font ID: %d", i);
    T1_LoadFont(i);
  }

  float size = 1.0;
  if (fa.HasSize())
    size = (fa.size.GetUnitId() == UNIT_PT) ? fa.size.GetValue() : sp2pt(fa.size.ToScaledPoints());

  AFont* f = (i >= 0) ? new T1_Font(i, size) : NULL;

  return f;
}

void
T1_FontManager::SetLogLevel(int level)
{
  T1_SetLogLevel(level + 1);
}

#endif // HAVE_LIBT1
