#include "admin.h"
#include<gdk/gdk.h>

    GObject * app_main_get_ui_element (App_main * app_main, const gchar * name)
    {
        const gchar *buildable;
        GSList *list;

        list = app_main->objects;

        do {
            buildable = gtk_buildable_get_name (list->data);

            if (strcmp (buildable, name) == 0) {
                return list->data;
            }

        } while (list = g_slist_next (list));

        return NULL;
    }

    void app_main_init (App_main * app_main)
    {
        GError *error = NULL;

        app_main->builder = gtk_builder_new ();

        gtk_builder_add_from_file (app->builder,
                                   UI_DEFINITIONS_FILE, &error);

        if (error != NULL) {
            g_printerr
                ("erreur lors du téléchargement du fichier ui: %s\n",
                 error->message);
            g_error_free (error);
            gtk_main_quit ();
        }

        gtk_builder_connect_signals (app_main->builder, app_main);

        app_main->objects = gtk_builder_get_objects (app->builder);

    }
