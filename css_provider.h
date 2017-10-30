#ifndef CSS_PROVIDER_H_INCLUDED
#define CSS_PROVIDER_H_INCLUDED
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <gio/gio.h>

/** \brief fonction qui permet d'ajouter du css a un objet
 *
 */
static void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{
  gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
  if (GTK_IS_CONTAINER (widget))
    gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
}

GtkWidget * apply_css_to_widget (GtkWidget *widget,GString *css)
{
      GtkStyleProvider *provider;
       GBytes *bytes;
      gsize data_size;
      const guint8 *data;
      provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
     bytes = g_string_free_to_bytes(css);

      data = g_bytes_get_data (bytes, &data_size);
      gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider), (gchar *)data, data_size, NULL);
      g_bytes_unref (bytes);
      apply_css (widget, provider);

  return widget;
}


#endif // CSS_PROVIDER_H_INCLUDED
