#ifndef CHALANGE_H_INCLUDED
#define CHALANGE_H_INCLUDED

typedef struct{
    gchar player_1[101];
    gchar player_2[101];
    guint partie;
    GList *player_1_wrd;
    GList *player_2_wrd;
}Chalange;

/**< on a pas encore terminer cette partie pour les chalanges mais le principe est le meme pour simple joueur */

#endif // CHALANGE_H_INCLUDED
