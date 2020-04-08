#include "month.h"

Month const MONTHS[N_MONTHS] = {
        janeiro,
        fevereiro,
        marco,
        abril,
        maio,
        junho,
        julho,
        agosto,
        setembro,
        outubro,
        novembro,
        dezembro
};

char* mes_to_string(Month mes) {
    switch (mes) {
        case janeiro:
            return "janeiro";
        case fevereiro:
            return "fevereiro";
        case marco:
            return "marco";
        case abril:
            return "abril";
        case maio:
            return "maio";
        case junho:
            return "junho";
        case julho:
            return "julho";
        case agosto:
            return "agosto";
        case setembro:
            return "setembro";
        case outubro:
            return "outubro";
        case novembro:
            return "novembro";
        default:
            return "dezembro";
    }
}
