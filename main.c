#include "app_main.h"
#include "css_provider.h"
#include<stdlib.h>
#include<time.h>


/** \brief fonction principal
 *
 * \param int
 * \param char*
 * \return int
 *
 */

int main (int argc, char *argv[])
    {
         App_main *app_main;
         GString *css;

        app_main = (App_main *) g_new (App_main, 1);

        gtk_init (&argc, &argv);

        app_main_init(app_main);
        srand(time(NULL));

        GET_UI_ELEMENT (GtkWidget, connexionWindow);

        css=g_string_new(css_reset);
        css=g_string_append(css,connexion_css);
        apply_css_to_widget(connexionWindow,css);

        gtk_widget_show_all(connexionWindow);

        gtk_main ();

        return 0;

    }
