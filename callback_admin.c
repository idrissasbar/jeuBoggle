#include "app_main.h"
#include "grid.h"
#include <string.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <stdio.h>
#include <cairo.h>
/**************************************************************************************/



/***************************************************************************************/

/** \brief fonction de connexion admin
 *
 * \param GtkButton le bouton de connexion
 * \param App_main
 * \return void
 *
 */

static int gtime_cpt=0;
G_MODULE_EXPORT void on_connexionAdmin_clicked (GtkButton * button, App_main * app_main)
    {   gchar *admin_name,*admin_password;
        gchar nbr_partie_text[10];
        GString *css;
        GtkTreeStore *treestore;
        GList *list;
        GtkTreeIter treeiter;
        FILE *dic=NULL;

        gchar *mot=malloc(201),c;

        GET_UI_ELEMENT (GtkWidget, connexionWindow);/**< recuperer la fenetre de connexion  */

        GET_UI_ELEMENT (GtkEntry, adminName); /**< recuperer le champ de text qui contient le nom d'admin  */

         GET_UI_ELEMENT (GtkEntry, adminPassword); /**< recuperer le champ de text qui contient le mot de pass d'admin  */

        GET_UI_ELEMENT (GtkWidget, adminpanel); /**< recuperer la fenetre principal d'admin  */

        admin_name=gtk_entry_get_text(adminName);
        admin_password=gtk_entry_get_text(adminPassword);
        if(strcmp(admin_name,admin)==0&&strcmp(admin_password,password)==0){ /**< tester si le nom et le mot de pass sont correct  */


    treestore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    list=app_main->players;
    int cpt=10;
    while(list&&cpt){
            cpt--;
        gtk_tree_store_append(treestore, &treeiter,NULL);
        gtk_tree_store_set(treestore, &treeiter, 0,((Player*)list->data)->name , 1,((Player*)list->data)->score , -1);
        list=g_list_next(list);
    }

    GET_UI_ELEMENT (GtkWidget, top10treeview);
    GET_UI_ELEMENT (GtkWidget, nbrPartie);
    sprintf(nbr_partie_text,"%d", g_list_length(app_main->parties));

    gtk_label_set_text(nbrPartie,nbr_partie_text);
    gtk_tree_view_set_rules_hint (top10treeview,TRUE);
    //gtk_tree_store_set(treestore,top10treeview);


    GtkCellRenderer *cellrenderertext = gtk_cell_renderer_text_new();
    gtk_cell_renderer_set_fixed_size(cellrenderertext,125,36);
    GtkTreeViewColumn *treeviewcolumn;
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Joueur",
                                                              cellrenderertext,
                                                              "text", 0,
                                                              NULL);
    gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
    gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 125  );
    gtk_tree_view_set_fixed_height_mode(GTK_TREE_VIEW(top10treeview),TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(top10treeview), treeviewcolumn);
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Score",
                                                              cellrenderertext,
                                                              "text", 1, NULL);
    gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
    gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 125  );
    gtk_tree_view_append_column(GTK_TREE_VIEW(top10treeview), treeviewcolumn);

    gtk_tree_view_set_model(top10treeview,GTK_TREE_STORE(treestore));

            css=g_string_new(css_reset);
            css=g_string_append(css,paneladmin_css);
            apply_css_to_widget(adminpanel,css);
            gtk_widget_show_all(adminpanel); /**< afficher le panneau d'admin */
            gtk_widget_destroy(connexionWindow);/**< détruire la fenetre de connexion */
        }

    }


    /** \brief effacer les donnees dans les champs de text
     *
     * \param GtkButton*
     * \param App_main*
     * \return void
     *
     */
    G_MODULE_EXPORT void on_resetAdmin_clicked (GtkButton * button, App_main * app_main)
    {
        GET_UI_ELEMENT (GtkEntry, adminName);

         GET_UI_ELEMENT (GtkEntry, adminPassword);

        gtk_entry_set_text(adminName,"");
        gtk_entry_set_text(adminPassword,"");

    }



/** \brief  fonction de callback qui repand au click sur le bouton de nouvelle partie
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
    G_MODULE_EXPORT void  on_newPartie_clicked(GtkButton * button, App_main * app_main)
    {   int indice_1,indice_2;
        GString *css;
        GtkWidget *buttongrid;
        GtkStyleContext *context;

        css=g_string_new(css_reset);
        css=g_string_append(css,newPartie_css);
        GET_UI_ELEMENT (GtkWidget, NewPartieWindow);
        GET_UI_ELEMENT (GtkWidget, grid);
        grid_init(&app_main->grid);
        des_init(app_main->des);
        for(indice_1=0;indice_1<4;indice_1++){
          for(indice_2=0;indice_2<4;indice_2++){
               buttongrid=gtk_grid_get_child_at(grid,indice_1,indice_2);
               gtk_button_set_label(buttongrid,"?");
               context = gtk_widget_get_style_context(GTK_WIDGET (buttongrid));
               gtk_style_context_remove_class(context,"buttonFace");

            }
        }
        apply_css_to_widget(NewPartieWindow,css);
        //g_timeout_add(1000,timeout_cb,&gtime_cpt);
        gtk_widget_show(NewPartieWindow);


    }

    /**
    * hadi mzl ma khdama
    *
    **/
    G_MODULE_EXPORT void  on_editPartie_clicked(GtkButton * button, App_main * app_main)
    {
        GList *list;
        Grid *nw_grid;
        list=app_main->parties;
        while(list){
                nw_grid=(Grid*)list->data;
          printf("partie\n");
          list=g_list_next(list);
        }

    }

    /**
    * hadi mzl ma khdama
    *
    **/
    G_MODULE_EXPORT void  on_deletePartie_clicked(GtkButton * button, App_main * app_main)
    {
        GList *list;
        Grid *nw_grid;
        list=app_main->parties;
        while(list){
                nw_grid=(Grid*)list->data;
          printf("%d  partie\n",nw_grid->grille[0][0].selected);
          list=g_list_next(list);
        }

    }

/** \brief fonction qui gere l'evenement de cliquer sur l'un des boutons de la grille de jeu
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
   G_MODULE_EXPORT void on_grid_button_press_event(GtkButton * button, App_main * app_main){

     printf("click\n");
   }

   G_MODULE_EXPORT void on_grid_clicked(GtkButton * button, App_main * app_main){
        GString *css;
        int old_selected_dice;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;
        GtkStyleContext *context;
        char *label;

        gint left,top=1,indice;
        css=g_string_new(css_reset);
        css=g_string_append(css,newPartie_css);

        GET_UI_ELEMENT (GtkWidget, grid);

        gtk_container_child_get (GTK_CONTAINER (grid), GTK_WIDGET(button),"left-attach", &app_main->grid.selectX,"top-attach", &app_main->grid.selectY,NULL);

        GET_UI_ELEMENT (GtkComboBoxText, dices);
        treestore=gtk_tree_store_new(1,G_TYPE_STRING);

        for(indice=0;indice<16;indice++){
                sprintf(label,"de %d",indice+1);

        if(app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected==indice){
            app_main->des[indice].selected=-1;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected=-1;
            old_selected_dice=indice;
        }

        if(app_main->des[indice].selected==-1){
        gtk_combo_box_text_append_text(dices,label);
        }
        }

        GET_UI_ELEMENT (GtkWidget, setFace);
        gtk_dialog_run(setFace);

       //printf("%d %d\n",app_main->grid.selectX,app_main->grid.selectY);
        gtk_combo_box_text_remove_all(dices);

        if(app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected==-1){
        context = gtk_widget_get_style_context(GTK_WIDGET (button));
        gtk_button_set_label(button,"?");
        gtk_style_context_remove_class( context,"buttonFace");
        //app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected=old_selected_dice;
        //gtk_style_context_remove_class( context,"buttonFace");
    }

        apply_css_to_widget(button,css);

   }

    G_MODULE_EXPORT int on_NewPartieWindow_destroy(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

   G_MODULE_EXPORT int on_NewPartieWindow_delete_event(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

   G_MODULE_EXPORT int on_setFace_destroy(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

   G_MODULE_EXPORT int on_setFace_delete_event(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

/** \brief fonction qui gere la selection des dés pour chaque case dans la grille
 *
 * \param GtkWidget*
 * \param App_main*
 * \return void
 *
 */
  G_MODULE_EXPORT void on_faceValide_clicked(GtkWidget * radio_button, App_main * app_main){
    GSList *radio_list;
     gchar *sLabel;
    GtkWidget *pInfo,*button;
     GtkStyleContext *context;
     int selected_face=-1,tmp_face=5;

        GET_UI_ELEMENT (GtkWidget, face1);
        GET_UI_ELEMENT (GtkWidget, setFace);
        radio_list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(face1));

       while(radio_list){

            if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_list->data))){
                sLabel = gtk_button_get_label(GTK_BUTTON(radio_list->data));
                selected_face=tmp_face;
        radio_list = NULL;
        }else{

        radio_list = g_slist_next(radio_list);
        tmp_face--;
        }
    }
    init_radio_button_group_label(face1);
    GET_UI_ELEMENT (GtkWidget, grid);
    app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selectedFace=selected_face;
    app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].visited=FALSE;
    button=gtk_grid_get_child_at(grid,app_main->grid.selectX,app_main->grid.selectY);
    context = gtk_widget_get_style_context(GTK_WIDGET (button));
    if(app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected==-1){
    pInfo = gtk_message_dialog_new (GTK_WINDOW(setFace),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"aucun De na ete selectionner", sLabel);gtk_dialog_run(GTK_DIALOG(pInfo));
        gtk_widget_destroy(pInfo);
        gtk_button_set_label(button,"?");
        gtk_style_context_remove_class( context,"buttonFace");
    }else{
        //sLabel[0]=app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].characters[selected_face];
        sLabel[0]=app_main->des[app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected].characters[selected_face];
        sLabel[1]='\0';
        gtk_button_set_label(button,sLabel);
        gtk_style_context_add_class( context,"buttonFace");
    }
        gtk_style_context_save (context);
        gtk_style_context_set_state (context, GTK_STATE_FLAG_ACTIVE);
        gtk_style_context_restore (context);

    gtk_widget_hide(setFace);


}


/** \brief gerer le changement des dés entre les cases de la grille
 *
 * \param GtkWidget*
 * \param App_main*
 * \return void
 *
 */
   G_MODULE_EXPORT void on_dices_changed(GtkWidget * combo_dices, App_main * app_main){
      char *active,tmp[5]="";
     int indice=0;

     active=gtk_combo_box_text_get_active_text(combo_dices);
     if(active){
            GET_UI_ELEMENT (GtkWidget, face1);
            GET_UI_ELEMENT (GtkWidget, face2);
            GET_UI_ELEMENT (GtkWidget, face3);
            GET_UI_ELEMENT (GtkWidget, face4);
            GET_UI_ELEMENT (GtkWidget, face5);
            GET_UI_ELEMENT (GtkWidget, face6);
            sscanf(active,"%s %d",tmp,&indice);
            indice-=1;

            printf("%c \n",app_main->des[indice].characters[0]);
            tmp[0]=app_main->des[indice].characters[0];
            tmp[1]='\0';
            gtk_button_set_label(face1,tmp);
            tmp[0]=app_main->des[indice].characters[1];
            tmp[1]='\0';
            gtk_button_set_label(face2,tmp);
            tmp[0]=app_main->des[indice].characters[2];
            tmp[1]='\0';
            gtk_button_set_label(face3,tmp);
            tmp[0]=app_main->des[indice].characters[3];
            tmp[1]='\0';
            gtk_button_set_label(face4,tmp);
            tmp[0]=app_main->des[indice].characters[4];
            tmp[1]='\0';
            gtk_button_set_label(face5,tmp);
            tmp[0]=app_main->des[indice].characters[5];
            tmp[1]='\0';
            gtk_button_set_label(face6,tmp);

            app_main->des[indice].selected=indice;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected=indice;
            gtk_toggle_button_set_active(face1,TRUE);
     }
   }

/** \brief fonction qui permet de generer une grille automatiquement
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
   G_MODULE_EXPORT void on_shuffle_clicked(GtkButton * button, App_main * app_main){
        GString *css;
        GtkStyleContext *context;
        GtkButton *selected_button;
        int indice_1,indice_2,rnd_dice,rnd_face;
        gchar label[2];
        css=g_string_new(newPartie_css);
        GET_UI_ELEMENT (GtkWidget, grid);
        for(indice_1=0;indice_1<4;indice_1++){
            for(indice_2=0;indice_2<4;indice_2++){
            do{
            rnd_dice=rand()%16;
            }while(app_main->des[rnd_dice].visited==TRUE);

            app_main->des[rnd_dice].visited=TRUE;
            rnd_face=rand()%6;
            app_main->grid.selectX=indice_1;
            app_main->grid.selectY=indice_2;
            app_main->des[rnd_dice].selected=rnd_dice;
            app_main->des[rnd_dice].selectedFace=rnd_face;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected=rnd_dice;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selectedFace=rnd_face;
            sprintf(label,"%c",app_main->des[rnd_dice].characters[rnd_face]);
            selected_button=GTK_BUTTON(gtk_grid_get_child_at(grid,app_main->grid.selectX,app_main->grid.selectY));
            gtk_button_set_label(selected_button,label);
            context = gtk_widget_get_style_context(GTK_WIDGET (selected_button));
            gtk_style_context_add_class( context,"buttonFace");

        }
        }
        for(indice_1=0;indice_1<16;indice_1++){
            app_main->des[indice_1].selectedFace=-1;
            app_main->des[indice_1].visited=FALSE;
        }

         apply_css_to_widget(grid,css);
   }


     G_MODULE_EXPORT void on_cancel_clicked(GtkWidget * button, App_main * app_main){
        int indice_1,indice_2,rnd_dice,rnd_face;

        for(indice_1=0;indice_1<4;indice_1++){
            for(indice_2=0;indice_2<4;indice_2++){
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selected=-1;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].selectedFace=-1;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].visited=FALSE;

        }
        }
        for(indice_1=0;indice_1<16;indice_1++){
            app_main->des[indice_1].selectedFace=-1;
            app_main->des[indice_1].selected=-1;
            app_main->des[indice_1].visited=FALSE;
        }
        GET_UI_ELEMENT (GtkWidget, NewPartieWindow);
         gtk_widget_hide(NewPartieWindow);
   }

int YesNo (GtkWidget *parent,char *Message)
{
    GtkWidget *dialog;
    int resp;

    dialog = gtk_message_dialog_new(  parent,GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,Message);


            gtk_window_set_modal(dialog,TRUE);
            gtk_window_set_position(dialog,GTK_WIN_POS_CENTER);
            resp=gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            //printf("resp=%d \n",resp);
         return -8==resp;
}


/** \brief fonction qui gere l'evenement de deconnexion sauvgarde des donnees
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
      G_MODULE_EXPORT void on_logOut_clicked(GtkWidget * button, App_main * app_main){
        int resp;
        GList *list;
        Grid *nw_grid;
        FILE *parties_file;
        GET_UI_ELEMENT (GtkWidget, adminpanel);
        resp=YesNo(adminpanel,"Deconnexion");
        if(resp){
                parties_file=fopen(PARTIES_FILE,"wb");
                if(parties_file){
                    list=app_main->parties;
                     while(list){
                        nw_grid=(Grid*)list->data;
                        fwrite(nw_grid,sizeof(Grid),1,parties_file);
                        list=g_list_next(list);
                    }
                    fclose(parties_file);
                }
                gtk_main_quit();
        }
   }




   /*************************************************/
   Grid* copyGrid(Grid grid){
       int indice_1,indice_2;
      Grid *new_grid;
      new_grid=(Grid*)malloc(sizeof(Grid));
      new_grid->level=grid.level;
      new_grid->num=grid.num;
      new_grid->selectX=grid.selectX;
      new_grid->selectY=grid.selectY;

      for(indice_1=0;indice_1<4;indice_1++){
        for(indice_2=0;indice_2<4;indice_2++){
            new_grid->grille[indice_1][indice_2].selected=grid.grille[indice_1][indice_2].selected;
            new_grid->grille[indice_1][indice_2].selectedFace=grid.grille[indice_1][indice_2].selectedFace;
            new_grid->grille[indice_1][indice_2].visited=grid.grille[indice_1][indice_2].visited;
      }
      }
   return new_grid;

   }

/** \brief fonction qui permet de tester si la grille est valide ou non
 *
 * \param Grid*
 * \return int vrai ou faux
 *
 */
   int grid_is_valide(Grid *grid){
        int indice_1,indice_2;
        for(indice_1=0;indice_1<4;indice_1++){
           for(indice_2=0;indice_2<4;indice_2++){
            if(grid->grille[indice_1][indice_2].selected==-1){
                return 0;
            }
        }
        }
        return 1;

   }
   /******************************************/

   G_MODULE_EXPORT void on_validate_clicked(GtkWidget * button, App_main * app_main){
        Grid *new_grid;
        GtkDialog *pInfo;
        GET_UI_ELEMENT (GtkWidget, NewPartieWindow);
        if(grid_is_valide(&app_main->grid)){
        new_grid=copyGrid(app_main->grid);
        app_main->parties=g_list_append(app_main->parties,new_grid);
         gtk_widget_hide(NewPartieWindow);
        }else{
         pInfo = gtk_message_dialog_new (GTK_WINDOW(NewPartieWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"grille non valide");
         gtk_dialog_run(GTK_DIALOG(pInfo));
        gtk_widget_destroy(pInfo);
        }
   }





