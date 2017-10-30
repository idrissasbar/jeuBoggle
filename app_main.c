#include "app_main.h"
#include<gdk/gdk.h>
int compare_player_score(gconstpointer *player1,gconstpointer *player2){

    return  ((Player*)player2)->score - ((Player*)player1)->score;

}
/** \brief  fonction qui permet de recuperer les objets graphique a partir de la list des objets (widgets)
 *
 * \param App_main
 * \param char * le nom de l'objet a recuperer
 * \return GObject* pointeur vers l'objet désirer NULL s'il n'existe pas
 *
 */
    GObject * app_main_get_ui_element (App_main * app_main, const gchar * name)
    {
        const gchar *buildable;
        GSList *list,*tmp;

        list = app_main->objects;
        tmp=list;

        while(list){
             buildable = gtk_buildable_get_name (list->data);

            if (strcmp (buildable, name) == 0) {
                return list->data;
            }
            list = g_slist_next (list);  // list= list->next;
        }
        list=tmp;
        return NULL;
    }

    /** \brief fonction qui initialise l'ensemble des dés avec des alphabet d'une densité deja donner
     *
     * \param De[]  est un tableau de dés
     * \return void
     *
     */

    void des_init(De des[]){
          char *alphabets="ETUKNOEVGTINDECAMPIELRUWEHIFSERECALSENTDOSOFXRIANAVEDZEIOATAGLENYUBMAQJOTLIBRASPULTEAIMSORENHRIS";
          int indice_1,indice_2,cpt=0;

          for(indice_1=0;indice_1<16;indice_1++){
            for(indice_2=0;indice_2<6;indice_2++){
                des[indice_1].characters[indice_2]=alphabets[cpt++];
            }
            des[indice_1].selected=-1;
            des[indice_1].selectedFace=-1;
            des[indice_1].visited=FALSE;
          }
    }


    /** \brief fonction qui permet d'initialiser la grille de jeu
     *
     * \param Grid*
     * \return void
     *
     */
    void grid_init(Grid *init_grid){
        int indice_1,indice_2;

        for(indice_1=0;indice_1<4;indice_1++){
            for(indice_2=0;indice_2<4;indice_2++){
                init_grid->grille[indice_1][indice_2].selected=-1;
                init_grid->grille[indice_1][indice_2].selectedFace=-1;
                init_grid->grille[indice_1][indice_2].visited=FALSE;

            }
    }
    init_grid->level=-1;
    init_grid->selectX=-1;
    init_grid->selectY=-1;

    }


    /** \brief fonction qui initialise tout l'application
     *          charger les joueurs les parties et les objets graphique
     * \param App_main
     * \return void
     *
     */
    void app_main_init (App_main * app_main)
    {   int taille;
        GError *error = NULL;
        GList *list;
        Grid *nw_grid;
        Player *player;
        FILE *file;
        app_main->builder = gtk_builder_new ();

        gtk_builder_add_from_file (app_main->builder,
                                   UI_DEFINITIONS_FILE, &error);

        if (error != NULL) {
            g_printerr
                ("erreur lors du chargement du fichier ui: %s\n",
                 error->message);
            g_error_free (error);
            gtk_main_quit ();
        }

        app_main->objects = gtk_builder_get_objects (app_main->builder);
        gtk_builder_connect_signals (app_main->builder, app_main);
        app_main->parties=NULL;
        app_main->players=NULL;
        app_main->words_parties=NULL;
        app_main->words_player=NULL;

                file=fopen(PARTIES_FILE,"rb");
                if(file){
                     while(!feof(file)){
                        nw_grid=(Grid*)malloc(sizeof(Grid));
                        fread(nw_grid,sizeof(Grid),1,file);
                     if(!feof(file)){
                        app_main->parties=g_list_append(app_main->parties,nw_grid);
                     }
                    }
                    fclose(file);
                }
                file=fopen(PLAYERS_FILE,"rb");
                if(file){
                     while(!feof(file)){
                        player=(Player*)malloc(sizeof(Player));

                        fread(&taille,sizeof(int),1,file);
                        player->name=(char*)malloc(taille*sizeof(char));
                        fread(player->name,taille*sizeof(char),1,file);
                        player->name[taille]='\0';
                        fread(&taille,sizeof(int),1,file);
                        player->password=(char*)malloc(taille*sizeof(char));
                        fread(player->password,taille*sizeof(char),1,file);
                            player->password[taille]='\0';
                        fread(&player->score,sizeof(int),1,file);
                        fread(&player->partie,sizeof(int),1,file);
                        fread(&player->nombreChalange,sizeof(int),1,file);
                     if(!feof(file)){
                        app_main->players=g_list_append(app_main->players,player);
                     }
                    }
                    fclose(file);
                }
                app_main->players=g_list_sort(app_main->players,compare_player_score);

        des_init(app_main->des);
        grid_init(&app_main->grid);
    }

    void init_radio_button_group_label(GtkWidget *radio_button){

    GSList *radio_list;

        radio_list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button));
    if(radio_list){
    gtk_button_set_label(GTK_BUTTON(radio_list->data),"?");
    gtk_toggle_button_set_active(GTK_BUTTON(radio_list->data),TRUE);
    radio_list=radio_list->next;
    }
    while(radio_list){
    gtk_button_set_label(GTK_BUTTON(radio_list->data),"?");
    gtk_toggle_button_set_active(GTK_BUTTON(radio_list->data),FALSE);
    radio_list=radio_list->next;
    }

    }
