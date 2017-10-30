#include "app_main.h"
#include "player.h"
#include "chalange.h"
#include <math.h>



/** \brief fonction qui gere l'evenement de cliquer sur le bouton nouveau joueur
 *         afficher le dialog pour entrer les donnees deu joueur
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
G_MODULE_EXPORT void on_newPlayer_clicked(GtkButton * button, App_main * app_main){

   GET_UI_ELEMENT (GtkDialog, newPlayerDialog);

   GET_UI_ELEMENT (GtkEntry, newName);
   GET_UI_ELEMENT (GtkEntry, newPWD);
   GET_UI_ELEMENT (GtkEntry, confirmPWD);
   GET_UI_ELEMENT (GtkLabel, message);

   gtk_entry_set_text(newName,"");
   gtk_entry_set_text(newPWD,"");
   gtk_entry_set_text(confirmPWD,"");
   gtk_label_set_label(message,"");

   gtk_dialog_run(newPlayerDialog);
}


/**
* masquer la fenetre de dialog
**/
G_MODULE_EXPORT int on_newPlayerDialog_delete_event(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

G_MODULE_EXPORT int on_newPlayerDialog_destroy(GtkWidget * win, App_main * app_main){

      gtk_widget_hide(win);
      return TRUE;
   }

/** \brief fonction qui permet d'ajouter le joueur dans la liste des joueurs
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
G_MODULE_EXPORT void on_addPlayer_clicked(GtkButton * button, App_main * app_main){
    Player *player;
    GList *list;
    gchar *name,*pwd,*confirm_pwd;

   GET_UI_ELEMENT (GtkEntry, newName);
   GET_UI_ELEMENT (GtkEntry, newPWD);
   GET_UI_ELEMENT (GtkEntry, confirmPWD);
   GET_UI_ELEMENT (GtkLabel, message);

   name=gtk_entry_get_text(newName);
   pwd=gtk_entry_get_text(newPWD);
   confirm_pwd=gtk_entry_get_text(confirmPWD);
   if(strlen(name)<2 ){
    gtk_label_set_label(message,"nom vide ou < 2 !!! ");
    return ;
   }
   if(strlen(pwd)!=strlen(confirm_pwd)||strcmp(pwd,confirm_pwd)!=0||strlen(pwd)<1){
    gtk_label_set_label(message,"Mot de pass  !!! ");
    return;
   }

    list=app_main->players;

    while(list){
            player=(Player*)(list->data);
        if(strcmp(name,player->name)==0){
                gtk_label_set_label(message,"nom deja existe  !!! ");
                return;
        }
        list=g_list_next(list);
        }

   player=(Player*)malloc(sizeof(Player));
   player->name=name;
   player->password=pwd;
   player->nombreChalange=0;
   player->partie=0;
   player->score=0;

   app_main->players=g_list_append(app_main->players,player);
   GET_UI_ELEMENT (GtkDialog, newPlayerDialog);
    gtk_widget_hide(newPlayerDialog);
}

/**
* annuler l'ajoute du joueur
**/
G_MODULE_EXPORT void on_annulerPlayer_clicked(GtkButton * button, App_main * app_main){

   GET_UI_ELEMENT (GtkDialog, newPlayerDialog);

   gtk_widget_hide(newPlayerDialog);
}

/** \brief connexion de joueur
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
G_MODULE_EXPORT void on_connexion_clicked(GtkButton * button, App_main * app_main)
    {   gchar *name,*password_player;
        Player *tmp;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;
        GtkTreeViewColumn *treeviewcolumn;
        gchar nbr_partie_text[10],score_text[10];
        GList *list;
        gboolean connex=FALSE;
        GString *css;
        FILE *dic=NULL;
        gchar *mot=malloc(201),c;

        GET_UI_ELEMENT (GtkWidget, connexionWindow);

        GET_UI_ELEMENT (GtkEntry, playerName);

         GET_UI_ELEMENT (GtkEntry, playerPWD);

        GET_UI_ELEMENT (GtkWidget, playerPanel);

        name=gtk_entry_get_text(playerName);
        password_player=gtk_entry_get_text(playerPWD);

        list=app_main->players;
        while(list){
            tmp=(Player*)(list->data);
        if(strcmp(name,tmp->name)==0&&strcmp(password_player,tmp->password)==0){
                connex=TRUE;
                app_main->current_player=tmp;
                list=NULL;
        }
        list=g_list_next(list);
        }
        if(connex){
    treestore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_INT);
    list=app_main->players;
    int cpt=10;
    while(list&&cpt){
            cpt--;
        gtk_tree_store_append(treestore, &treeiter,NULL);
        gtk_tree_store_set(treestore, &treeiter, 0,((Player*)list->data)->name , 1,((Player*)list->data)->score , -1);
        list=g_list_next(list);
    }

    GET_UI_ELEMENT (GtkWidget, top10treeview_player);
    GET_UI_ELEMENT (GtkWidget, nbrPartie_player);
    GET_UI_ELEMENT (GtkWidget, score);

    sprintf(nbr_partie_text,"%d", g_list_length(app_main->parties));
    sprintf(score_text,"%d", app_main->current_player->score);

    gtk_label_set_text(nbrPartie_player,nbr_partie_text);
    gtk_label_set_text(score,score_text);

    gtk_tree_view_set_rules_hint (top10treeview_player,TRUE);


    GtkCellRenderer *cellrenderertext = gtk_cell_renderer_text_new();
    gtk_cell_renderer_set_fixed_size(cellrenderertext,125,36);
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Joueur",
                                                              cellrenderertext,
                                                              "text", 0,
                                                              NULL);
    gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
    gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 125  );
    gtk_tree_view_set_fixed_height_mode(GTK_TREE_VIEW(top10treeview_player),TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(top10treeview_player), treeviewcolumn);
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("Score",
                                                              cellrenderertext,
                                                              "text", 1, NULL);
    gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
    gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 125  );
    gtk_tree_view_append_column(GTK_TREE_VIEW(top10treeview_player), treeviewcolumn);

    gtk_tree_view_set_model(top10treeview_player,GTK_TREE_STORE(treestore));

    /******************************************************************************/

      GET_UI_ELEMENT (GtkWidget, words_players);

      treestore = gtk_tree_store_new(1, G_TYPE_STRING);

    cellrenderertext = gtk_cell_renderer_text_new();
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("mots",
                                                              cellrenderertext,
                                                              "text", 0,
                                                              NULL);
        gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
        gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 175  );
        gtk_tree_view_set_fixed_height_mode(GTK_TREE_VIEW(words_players),TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(words_players), treeviewcolumn);
        gtk_tree_view_set_model(words_players,GTK_TREE_STORE(treestore));

        GET_UI_ELEMENT (GtkWidget, words_partie);

      treestore = gtk_tree_store_new(1, G_TYPE_STRING);

    cellrenderertext = gtk_cell_renderer_text_new();
    treeviewcolumn = gtk_tree_view_column_new_with_attributes("mots",
                                                              cellrenderertext,
                                                              "text", 0,
                                                              NULL);
      gtk_tree_view_column_set_sizing ( treeviewcolumn , GTK_TREE_VIEW_COLUMN_FIXED );
    gtk_tree_view_column_set_fixed_width ( treeviewcolumn , 175  );
    gtk_tree_view_set_fixed_height_mode(GTK_TREE_VIEW(words_partie),TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(words_partie), treeviewcolumn);
      gtk_tree_view_set_model(words_partie,GTK_TREE_STORE(treestore));


            css=g_string_new(css_reset);
            css=g_string_append(css,playerPanel_css);
            apply_css_to_widget(playerPanel,css);
            gtk_widget_show_all(playerPanel);
            gtk_widget_destroy(connexionWindow);
        }

    printf("connexion %s  %s\n",name,password_player);

    }

/**
*
*
**/
    G_MODULE_EXPORT void on_reset_clicked (GtkButton * button, App_main * app_main)
    {
        GET_UI_ELEMENT (GtkEntry, playerName);

         GET_UI_ELEMENT (GtkEntry, playerPWD);

        gtk_entry_set_text(playerName,"");
        gtk_entry_set_text(playerPWD,"");

    }

    int file_word(FILE *flot,char *word){   // 0 1 2
        char tmp_word[31];
        unsigned int positions[26]={0,266756,423318,807861,1288906,1678337,1808497,1914116,1977103,2116759,2139828,2144546,2213374,2389439
                                    ,2429414,2485754,2786107,2799213,3206386,3456640,3632836,3642983,3717534,3719525,3720170,3720921};
        int cmp,length_1,length_2;
        rewind(flot);
        fseek(flot,positions[word[0]-'a'],SEEK_SET);
        while(!feof(flot)){
                        fgets(tmp_word,30,flot);
                        tmp_word[strlen(tmp_word)-1]='\0';
                        length_1=strlen(tmp_word);
                        length_2=strlen(word);
                    if(length_1>=length_2){
                     if(!feof(flot)){
                            tmp_word[length_2]='\0';
                           cmp=strcmp(tmp_word,word);
                        if(cmp==0){
                            if(length_1==length_2)
                                return 2;
                            else
                                return 1;
                        }
                        if(cmp>0)
                            return 0;
                     }
                    }
                    }
                    return 0;

    }



    /**
    *
    * recherche en dfs pour touts les mots possible d'une partie
    *
    **/
 void dfs(GString *prefix, int i, int j,App_main * app_main,FILE *flot) {
        int ii,jj;
        int exist;
        if (i < 0 || j < 0 || i >= 4 || j >= 4) return;

        if (app_main->grid.grille[i][j].visited==TRUE) return;



        prefix = g_string_append_c(prefix ,app_main->des[app_main->grid.grille[i][j].selected].characters[app_main->grid.grille[i][j].selectedFace]);
        prefix= g_string_down(prefix);
        exist=file_word(flot,prefix->str);
        if (!exist) return;

        app_main->grid.grille[i][j].visited=TRUE;

        if (strlen(prefix->str)>=3&&exist==2){
            app_main->words_parties=g_list_append(app_main->words_parties,prefix->str);
            printf(" add %s \n",prefix->str);
        }

        for ( ii = -1; ii <= 1; ii++){
            for ( jj = -1; jj <= 1; jj++){
                dfs(g_string_new(prefix->str),  i+ii,  j+jj, app_main,flot);
            }
        }

        app_main->grid.grille[i][j].visited=FALSE;
    }

/**
*
* countdown timer
**/
    int timer_callBack(App_main *app_main){
        char label_time[6];
        GET_UI_ELEMENT (GtkWidget, timer);//
        app_main->time-=1;

        sprintf(label_time,"0%d:%s%d",app_main->time/60,(app_main->time%60)<10?"0":"",app_main->time%60);
        gtk_label_set_text(timer,label_time);
        if(app_main->time==0){
            //g_source_remove(app_main->timer_id);
                return FALSE;
        }
        return TRUE;

    }



     void reset_grid_play(App_main *app_main){
        int indice_1,indice_2;
        GtkStyleContext *context;
        GtkButton *selected_button;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;

      GET_UI_ELEMENT (GtkWidget, gridPlay);
      GET_UI_ELEMENT (GtkWidget, words_players);
      GET_UI_ELEMENT (GtkWidget, words_partie);
      GET_UI_ELEMENT (GtkWidget, word_entry);
      GET_UI_ELEMENT (GtkWidget, scorePartie);

      g_source_remove(app_main->timer_id);
      gtk_label_set_text(scorePartie,"0");
      gtk_entry_set_text(word_entry,"");

        app_main->grid.selectX=-1;
        app_main->grid.selectY=-1;

        app_main->words_parties=NULL;
        app_main->words_player=NULL;

        treestore=gtk_tree_view_get_model(words_players);
        gtk_tree_store_clear(treestore);
        gtk_tree_view_set_model(words_players,GTK_TREE_STORE(treestore));

        treestore=gtk_tree_view_get_model(words_partie);
        gtk_tree_store_clear(treestore);
        gtk_tree_view_set_model(words_partie,GTK_TREE_STORE(treestore));

   for(indice_1=0;indice_1<4;indice_1++){
         for(indice_2=0;indice_2<4;indice_2++){
            app_main->grid.grille[indice_1][indice_2].visited=FALSE;
            selected_button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,indice_1,indice_2));
            context = gtk_widget_get_style_context(GTK_WIDGET (selected_button));
            gtk_style_context_remove_class(context,"buttonSelected");
            gtk_style_context_remove_class(context,"buttonOldSelected");
            gtk_style_context_remove_class(context,"buttonNeighbor");
      }
      }
   }

/** \brief fonction qui gere l'evenement de cliquer sur play
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
    G_MODULE_EXPORT void on_play_clicked (GtkButton * button, App_main * app_main)
    {   GList *list;
        GString *css;
        GString *prefix;
        GtkButton *selected_button;
        gchar label[2];
        int indice_1,indice_2;
        FILE *flot;

        reset_grid_play(app_main);
        app_main->time=180;
        GET_UI_ELEMENT (GtkWidget, gridPlay);//map des 16 boutons
        GET_UI_ELEMENT (GtkEntry, playerPanel);
        GET_UI_ELEMENT (GtkEntry, playGrid);//fenetre

        if(app_main->current_player->partie < g_list_length(app_main->parties)){

        flot=fopen("diction.txt","r");
        app_main->grid=*((Grid*)g_list_nth(app_main->parties,app_main->current_player->partie)->data);
        app_main->grid.selectX=-1;
        app_main->grid.selectY=-1;
        for(indice_1=0;indice_1<4;indice_1++){
            for(indice_2=0;indice_2<4;indice_2++){
            sprintf(label,"%c",app_main->des[app_main->grid.grille[indice_1][indice_2].selected].characters[app_main->grid.grille[indice_1][indice_2].selectedFace]);
            selected_button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,indice_1,indice_2));
            gtk_button_set_label(selected_button,label);
            app_main->grid.grille[indice_1][indice_2].visited=FALSE;
            prefix=g_string_new("");
            rewind(flot);
            dfs(g_string_new(""),indice_1,indice_2,app_main,flot);
            }
            }
            fclose(flot);
            css=g_string_new(css_reset);
            css=g_string_append(css,playGrid_css);
            apply_css_to_widget(playGrid,css);
            gtk_widget_show_all(playGrid);
            app_main->timer_id=g_timeout_add(1000,timer_callBack,app_main);
        }
    }



/** \brief fonction qui gere l'evenement de cliquer sur l'un des boutons de la grille de jeu
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
    G_MODULE_EXPORT void on_grid_play_clicked(GtkButton * button, App_main * app_main){
        gint left,top,indice_1,indice_2;
        GtkStyleContext *context;
        GString *text;
        GString *css;
        GtkButton *selected_button;
        gchar *text_entry;
        GET_UI_ELEMENT (GtkWidget, playGrid);
        GET_UI_ELEMENT (GtkWidget, gridPlay);
        GET_UI_ELEMENT (GtkWidget, word_entry);

        if(app_main->time){
        if(app_main->grid.selectX==-1&&app_main->grid.selectY==-1){
            gtk_container_child_get (GTK_CONTAINER (gridPlay), GTK_WIDGET(button),"left-attach", &app_main->grid.selectX,"top-attach", &app_main->grid.selectY,NULL);
            text=g_string_new(gtk_button_get_label(GTK_BUTTON(button)));
            text_entry=g_string_free(text,FALSE);
            gtk_entry_set_text(word_entry,text_entry);
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].visited=TRUE;
            context = gtk_widget_get_style_context(GTK_WIDGET (button));
            gtk_style_context_add_class(context,"buttonSelected");
        }else{

            gtk_container_child_get (GTK_CONTAINER (gridPlay), GTK_WIDGET(button),"left-attach", &left,"top-attach", &top,NULL);
            if(((abs(top-app_main->grid.selectY)==1&&abs(left-app_main->grid.selectX)==1)||
               (abs(top-app_main->grid.selectY)==0&&abs(left-app_main->grid.selectX)==1)||
               (abs(top-app_main->grid.selectY)==1&&abs(left-app_main->grid.selectX)==0))&&
                app_main->grid.grille[left][top].visited==FALSE){
            text=g_string_new(gtk_entry_get_text(word_entry));
            text=g_string_append(text,gtk_button_get_label(GTK_BUTTON(button)));
            text_entry=g_string_free(text,FALSE);
            gtk_entry_set_text(word_entry,text_entry);

            selected_button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,app_main->grid.selectX,app_main->grid.selectY));
            context = gtk_widget_get_style_context(GTK_WIDGET (selected_button));
            gtk_style_context_remove_class(context,"buttonSelected");
            gtk_style_context_add_class(context,"buttonOldSelected");

            app_main->grid.selectX=left;
            app_main->grid.selectY=top;
            app_main->grid.grille[app_main->grid.selectX][app_main->grid.selectY].visited=TRUE;
            context = gtk_widget_get_style_context(GTK_WIDGET (button));
            gtk_style_context_add_class(context,"buttonSelected");
             gtk_style_context_remove_class(context,"buttonNeighbor");
            }

        }

        for(indice_1=0;indice_1<4;indice_1++){
            for(indice_2=0;indice_2<4;indice_2++){
                button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,indice_1,indice_2));
                context = gtk_widget_get_style_context(GTK_WIDGET (button));
                gtk_style_context_remove_class(context,"buttonNeighbor");
             }
        }
        for(indice_1=-1;indice_1<=1;indice_1++){
            for(indice_2=-1;indice_2<=1;indice_2++){
             if(indice_1==0&&indice_2==0)
                continue;
             left=app_main->grid.selectX+indice_1;
             top=app_main->grid.selectY+indice_2;
             if(left>=0&&left<=3&&top>=0&&top<=3&&app_main->grid.grille[left][top].visited==FALSE){
                button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,left,top));
                context = gtk_widget_get_style_context(GTK_WIDGET (button));
                gtk_style_context_add_class(context,"buttonNeighbor");
             }
        }
        }

        css=g_string_new(playGrid_css);
        apply_css_to_widget(gridPlay,css);
        }
   }

   int string_equals(char *str1,char *str2){

    if(strcmp(str1,str2)==0)
            return 0;
    return 1;

   }



//   on_addWord_clicked
  G_MODULE_EXPORT void on_addWord_clicked(GtkButton * button, App_main * app_main){
        GString *word;
        GString *css;
        int points[17]={0,0,0,1,1,2,3,5,11,11,11,11,11,11,11,11,11};
        gchar *score_label;
        int score;
        GtkStyleContext *context;
        GtkButton *selected_button;
        int indice_1,indice_2;
        GList *list_1,*list_2;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;

      GET_UI_ELEMENT (GtkWidget, gridPlay);
      GET_UI_ELEMENT (GtkWidget, words_players);
      GET_UI_ELEMENT (GtkWidget, word_entry);
      GET_UI_ELEMENT (GtkWidget, scorePartie);
      if(app_main->time){
        word=g_string_new(gtk_entry_get_text(word_entry));
        word=g_string_down(word);
        list_1=g_list_find_custom(app_main->words_parties,word->str,string_equals);
        list_2=g_list_find_custom(app_main->words_player,word->str,string_equals);
      if(strlen(word->str)>=3&&(list_1!=NULL)&&(list_2==NULL)){

      app_main->words_player=g_list_append(app_main->words_player,word->str);
      treestore = gtk_tree_view_get_model(words_players);
      gtk_tree_store_append(treestore, &treeiter,NULL);
      gtk_tree_store_set(treestore, &treeiter, 0, word->str, -1);
      gtk_tree_view_set_model(words_players,GTK_TREE_STORE(treestore));
      score_label=gtk_label_get_text(scorePartie);
      sscanf(score_label,"%d",&score);
      sprintf(score_label,"%d",score+points[strlen(word->str)]);
      gtk_label_set_label(scorePartie,score_label);


      }
      gtk_entry_set_text(word_entry,"");
        app_main->grid.selectX=-1;
        app_main->grid.selectY=-1;
      for(indice_1=0;indice_1<4;indice_1++){
         for(indice_2=0;indice_2<4;indice_2++){

            app_main->grid.grille[indice_1][indice_2].visited=FALSE;
            selected_button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,indice_1,indice_2));
            context = gtk_widget_get_style_context(GTK_WIDGET (selected_button));
            gtk_style_context_remove_class(context,"buttonSelected");
            gtk_style_context_remove_class(context,"buttonOldSelected");
            gtk_style_context_remove_class(context,"buttonNeighbor");
      }
      }

        css=g_string_new(playGrid_css);
        apply_css_to_widget(gridPlay,css);
      }
   }
  // on_resetWord_clicked
 G_MODULE_EXPORT void on_resetWord_clicked(GtkButton * button, App_main * app_main){
        GtkStyleContext *context;
        GtkButton *selected_button;
        int indice_1,indice_2;
        GString *css;

        GET_UI_ELEMENT (GtkWidget, gridPlay);
        GET_UI_ELEMENT (GtkWidget, word_entry);
        gtk_entry_set_text(word_entry,"");
        app_main->grid.selectX=-1;
        app_main->grid.selectY=-1;
      for(indice_1=0;indice_1<4;indice_1++){
         for(indice_2=0;indice_2<4;indice_2++){

            app_main->grid.grille[indice_1][indice_2].visited=FALSE;
            selected_button=GTK_BUTTON(gtk_grid_get_child_at(gridPlay,indice_1,indice_2));
            context = gtk_widget_get_style_context(GTK_WIDGET (selected_button));
            gtk_style_context_remove_class(context,"buttonSelected");
            gtk_style_context_remove_class(context,"buttonOldSelected");
            gtk_style_context_remove_class(context,"buttonNeighbor");
      }
      }

        css=g_string_new(playGrid_css);
        apply_css_to_widget(gridPlay,css);
   }


   //on_savePlay_clicked
   G_MODULE_EXPORT void on_savePlay_clicked(GtkButton * button, App_main * app_main){
        gchar *word;
        gchar score_text[10];
        GtkDialog *pInfo;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;
        gchar *score_label;
        int score;
        int resp;

      GET_UI_ELEMENT (GtkWidget, words_partie);
      GET_UI_ELEMENT (GtkWidget, word_entry);
      GET_UI_ELEMENT (GtkWidget, scorePartie);
      GET_UI_ELEMENT (GtkWidget, playGrid);

      score_label=gtk_label_get_text(scorePartie);
      sscanf(score_label,"%d",&score);
        if(app_main->time==0&&score!=0){
      resp=YesNo(playGrid,"enregistrer score ?");
        if(resp){
       app_main->current_player->score+=score;
       app_main->current_player->partie+=1;
       gtk_widget_hide(playGrid);

       GET_UI_ELEMENT (GtkWidget, score);
       sprintf(score_text,"%d", app_main->current_player->score);
       gtk_label_set_text(score,score_text);
        }
        }else{

        pInfo = gtk_message_dialog_new(playGrid,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"partie non encore termine !! ");
         gtk_dialog_run(GTK_DIALOG(pInfo));
        gtk_widget_destroy(pInfo);
        }
   }


   //on_solution_clicked
    G_MODULE_EXPORT void on_solution_clicked(GtkButton * button, App_main * app_main){
        gchar *word;
        GtkTreeStore *treestore;
        GtkTreeIter treeiter;
        gchar *score_label;
        int score;
        int resp;

      GET_UI_ELEMENT (GtkWidget, words_partie);
      GET_UI_ELEMENT (GtkWidget, word_entry);
      GET_UI_ELEMENT (GtkWidget, scorePartie);
      GET_UI_ELEMENT (GtkWidget, playGrid);
      score_label=gtk_label_get_text(scorePartie);
      sscanf(score_label,"%d",&score);

                resp=YesNo(playGrid,"enregistrer score ?");
        if(resp){
        word=gtk_entry_get_text(word_entry);
        g_source_remove(app_main->timer_id);
        app_main->time=0;
        app_main->current_player->score+=score;
        app_main->current_player->partie+=1;
        gtk_label_set_label(scorePartie,"0");

      treestore = gtk_tree_view_get_model(words_partie);
      while(app_main->words_parties){
      gtk_tree_store_append(treestore, &treeiter,NULL);
      gtk_tree_store_set(treestore, &treeiter, 0, app_main->words_parties->data, -1);
      gtk_tree_view_set_model(words_partie,GTK_TREE_STORE(treestore));
        app_main->words_parties=g_list_next(app_main->words_parties);
      }
        }

   }


    /*********************** destroy *******************/

    //on_endPlay_clicked
    G_MODULE_EXPORT int on_endPlay_clicked(GtkButton * button, App_main * app_main){
        int resp;
         gchar score_text[10];
        GET_UI_ELEMENT (GtkEntry, playGrid);
        GET_UI_ELEMENT (GtkWidget, score);
        resp=YesNo(playGrid,"quitter partie !!");
        if(resp){
        g_source_remove(app_main->timer_id);
        sprintf(score_text,"%d", app_main->current_player->score);
        gtk_label_set_text(score,score_text);
        gtk_widget_hide(playGrid);
      return TRUE;
        }
        return FALSE;
   }

    G_MODULE_EXPORT int on_playGrid_delete_event(GtkWidget * win, App_main * app_main){

        gtk_widget_hide(win);
      return TRUE;
   }




/** \brief fonction qui gere l'evenement de deconnexion sauvgarde des donnees
 *
 * \param GtkButton*
 * \param App_main*
 * \return void
 *
 */
      G_MODULE_EXPORT void on_logOutPlayer_clicked(GtkWidget * button, App_main * app_main){
        int resp;
        int taille;
        GList *list;
        Player *player;
        FILE *file;
        GET_UI_ELEMENT (GtkWidget, playGrid);
        resp=YesNo(playGrid,"Deconnexion");
        if(resp){
                file=fopen(PLAYERS_FILE,"wb");
                file=fopen(PLAYERS_FILE,"wb");
                if(file){
                    list=app_main->players;
                     while(list){
                        player=(Player*)list->data;
                        taille=strlen(player->name);
                        fwrite(&taille,sizeof(int),1,file);
                        fwrite(player->name,strlen(player->name)*sizeof(char),1,file);

                        taille=strlen(player->password);
                        fwrite(&taille,sizeof(int),1,file);
                        fwrite(player->password,strlen(player->password)*sizeof(char),1,file);

                        fwrite(&player->score,sizeof(int),1,file);
                        fwrite(&player->partie,sizeof(int),1,file);
                         fwrite(&player->nombreChalange,sizeof(int),1,file);

                        list=g_list_next(list);
                    }
                    fclose(file);
                }
                gtk_main_quit();
        }
   }



