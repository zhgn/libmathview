// Copyright (C) 2000-2003, Luca Padovani <luca.padovani@cs.unibo.it>.
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
// http://helm.cs.unibo.it/mml-widget, or send a mail to
// <luca.padovani@cs.unibo.it>

#include <config.h>

#include <cassert>

#include <gdk/gdkx.h>

#include "Gtk_RenderingContext.hh"

Gtk_RenderingContext::Gtk_RenderingContext()
  : style(NORMAL_STYLE)//, xft_draw(0)
{ }

Gtk_RenderingContext::~Gtk_RenderingContext()
{
  releaseResources();
}

void
Gtk_RenderingContext::releaseResources()
{
  // should free the gc's? 
#if 0
  if (xft_draw)
    {
      // It seems that by using XftDrawDestroy the drawable will be destroyed
      // as well, so we only free the structure hoping that nothing bad
      // will happen. This was taken from gr_UnixGraphics.cpp in AbiWord
      free(xft_draw);
      xft_draw = 0;
    }
#endif
}

void
Gtk_RenderingContext::setDrawable(const GObjectPtr<GdkDrawable>& drawable)
{
  releaseResources();

  gdk_drawable = drawable;
  if (gdk_drawable)
    {
      for (unsigned i = 0; i < MAX_STYLE; i++)
	data[i].gdk_gc = gdk_gc_new(gdk_drawable);

#if 0      
      xft_draw = XftDrawCreate(GDK_DISPLAY(),
			       gdk_x11_drawable_get_xid(drawable),
			       GDK_VISUAL_XVISUAL(gdk_drawable_get_visual(drawable)),
			       GDK_COLORMAP_XCOLORMAP(gdk_colormap));
      assert(xft_draw);
#endif
    }
  else
    {
      for (unsigned i = 0; i < MAX_STYLE; i++)
	data[i].gdk_gc = 0;
    }
}

void
Gtk_RenderingContext::fill(const scaled& x, const scaled& y, const BoundingBox& box) const
{
  gdk_draw_rectangle(getDrawable(),
		     getGC(),
		     TRUE,
		     Gtk_RenderingContext::toGtkX(x),
		     Gtk_RenderingContext::toGtkY(y + box.height),
		     Gtk_RenderingContext::toGtkPixels(box.width),
		     Gtk_RenderingContext::toGtkPixels(box.height + box.depth));
}

void
Gtk_RenderingContext::draw(const scaled& x, const scaled& y, PangoLayout* layout) const
{
  gdk_draw_layout(getDrawable(),
		  getGC(),
		  Gtk_RenderingContext::toGtkX(x),
		  Gtk_RenderingContext::toGtkY(y),
		  layout);
}

void
Gtk_RenderingContext::draw(const scaled& x, const scaled& y, PangoLayoutLine* line) const
{
  gdk_draw_layout_line(getDrawable(),
		       getGC(),
		       Gtk_RenderingContext::toGtkX(x),
		       Gtk_RenderingContext::toGtkY(y),
		       line);
}

void
Gtk_RenderingContext::draw(const scaled& x, const scaled& y, PangoFont* font,
			   PangoGlyphString* glyphs) const
{
  gdk_draw_glyphs(getDrawable(),
		  getGC(),
		  font,
		  Gtk_RenderingContext::toGtkX(x),
		  Gtk_RenderingContext::toGtkY(y),
		  glyphs);
}
