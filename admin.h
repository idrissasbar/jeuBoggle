#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

 #include <gtk/gtk.h>

    #define UI_DEFINITIONS_FILE "appUI.glade"

    #define GET_UI_ELEMENT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *) \
                                                app_main_get_ui_element(app, #ELEMENT);

    typedef struct _app_main
    {
        GtkBuilder *builder;
        GSList *objects;
    } App_main;

    void app_main_init (App_main * );
    GObject * app_main_get_ui_element (App_main * , const gchar * );


#endif // ADMIN_H_INCLUDED
