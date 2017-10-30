#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

typedef struct{
    gchar *name;
    gchar *password;
    guint score;
    guint partie;
    guint nombreChalange;
}Player;


#endif // PLAYER_H_INCLUDED
