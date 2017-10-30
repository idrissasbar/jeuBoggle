#ifndef APP_MAIN_H_INCLUDED
#define APP_MAIN_H_INCLUDED

 #include <gtk/gtk.h>
 #include "css.h"
 #include"grid.h"
 #include "player.h"
    #define N 101 // taille max de password

    #define UI_DEFINITIONS_FILE "appUI.glade" // define to add glade file

    #define PARTIES_FILE "binpart.bin" //

    #define PLAYERS_FILE "binplay.bin" //

    #define GET_UI_ELEMENT(TYPE, ELEMENT)   TYPE *ELEMENT = (TYPE *) \
                                                app_main_get_ui_element(app_main, #ELEMENT);

static char *admin="admin",*password="ensias123";
/** \brief
 *  la structure principal qui regroupe l'ensemble des widgets et les parties
 *  aussi le builder pour recuperer les objets a partir du fichier glade
 *
 */

    typedef struct _app_main
    {
        GtkBuilder *builder;
        GSList *objects;
        GList *players;
        GList *parties;
        GList *words_parties;
        GList *words_player;
        Grid grid;
        Player *current_player;
        De des[16];
        guint timer_id;
        guint time;
    } App_main;

    void app_main_init (App_main * );
    GObject * app_main_get_ui_element (App_main * , const gchar * );

#endif // APP_MAIN_H_INCLUDED
