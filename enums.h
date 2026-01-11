    #ifndef ENUMS_H
    #define ENUMS_H 

    // Les énumérateurs d’un enum classique sont associés à des valeurs entières consécutives,
    // en commençant par 0 si aucune valeur n’est précisée.
    // Un enum class évite ce comportement afin d’offrir une meilleure sécurité de types.

    // Ce fichier .h contient uniquement des définitions de types,
    // il ne contient pas de logique ni d’implémentation et ne nécessite donc pas de fichier .cpp associé.

    enum class Player {
        NO_PLAYER,
        PLAYER_1,
        PLAYER_2
    };

    enum class Size {
        NONE,
        SMALL,
        MEDIUM,
        LARGE
    };

    enum class Status {
        OK = 0,
        INVALID_SOURCE = 1,
        INVALID_TARGET = 2,
        INVALID_ENTRY  = 3
    };

    enum class LineType {
        NO_LINE,
        DIAGONAL,
        ANTIDIAGONAL,
        ROW,
        COLUMN
    };

    #endif
