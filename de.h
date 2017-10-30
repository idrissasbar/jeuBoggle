#ifndef DE_H_INCLUDED
#define DE_H_INCLUDED


typedef struct{
    char characters[6];
    int selectedFace;   //number no selection=>-1 face [0:1:5]
    int visited;   // false or true
    int selected; // -1 if not selected [0,15] for the current dice selected
} De;


typedef struct{
    int selectedFace;   //number no selection=>-1 face [0:1:5]
    int visited;   // false or true
    int selected; // -1 if not selected [0,15] for the current dice selected
} Grille;




#endif // DE_H_INCLUDED
