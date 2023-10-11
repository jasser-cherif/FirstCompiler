#include <stdio.h>

// Déclaration des constantes pour les symboles
#define PROGRAM 1
#define ID 2
#define PV 3   // ;
#define PT 4   // .
#define VAR 5
#define DP 6   // :
#define V 7    // ,
#define INTEGER 8
#define CHAR 9
#define BEGIN 10
#define END 11
#define IF 12
#define WHILE 13
#define WRITE 14
#define WRITELN 15
#define READ 16
#define READLN 17
#define AFF 18   // :=
#define PO 19   // (
#define PF 20   // )
#define OPADD 21
#define OPMUL 22
#define OPREL 23
#define NB 24
#define ELSE 25
#define THEN 26
#define DO 27

// Déclaration de la fonction terme_suivant
int terme_suivant();

int terme; // Variable pour stocker le terme en cours de traitement

// Déclaration des fonctions
void accept(int T);
void erreur();
void G();
void Dcl();
void Dp();
void Liste_id();
void Lp();
void TYPE();
void Inst_comp();
void Inst();
void Liste_Inst();
void LIp();
void I();
void Exp();
void Ep();
void Exp_simple();
void ESp();
void Terme();
void Tp();
void Facteur();

int main() {
    // Initialisation du terme avec le premier symbole
    printf("donner un symbol : ");
	scanf("%d",&terme);
    G();
    printf("Fin du programme.\n");
    return 0;
}

void accept(int T) {
    if (terme == T) {
        terme = terme_suivant();
    } else {
        erreur();
    }
}

void erreur() {
    printf("Symbole non accepté !\n");
}

int terme_suivant() {
    int s;
    printf("Donnez le symbole suivant : ");
    scanf("%d", &s);
    return s;
}

void G() {
    if (terme == PROGRAM) {
        accept(PROGRAM);
        accept(ID);
        accept(PV);
        Dcl();
        Inst_comp();
        accept(PT);
    } else {
        erreur();
    }
}

void Dcl() {
    if ((terme == VAR)||(terme== PV)) {
        Dp();
    } else {
        erreur();
    }
}

void Dp() {
    if (terme == VAR) {
        accept(VAR);
        Liste_id();
        accept(DP);
        TYPE();
        accept(PV);
        Dp();
    } else if (terme == PV) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void Liste_id() {
    if (terme == ID) {
        accept(ID);
        Lp();
    } else {
        erreur();
    }
}

void Lp() {
    if (terme == V) {
        accept(V);
        accept(ID);
        Lp();
    } else if (terme == PV) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void TYPE() {
    if (terme == INTEGER) {
        accept(INTEGER);
    } else if (terme == CHAR) {
        accept(CHAR);
    } else {
        erreur();
    }
}

void Inst_comp() {
    if (terme == BEGIN) {
        accept(BEGIN);
        Inst();
        accept(END);
    } else {
        erreur();
    }
}

void Inst() {
    if (terme == ID || terme == IF || terme == WHILE || terme == READ || terme == READLN || terme == WRITE || terme == WRITELN) {
        Liste_Inst();
    } else if (terme == PT) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void Liste_Inst() {
    if (terme == ID || terme == IF || terme == WHILE || terme == READ || terme == READLN || terme == WRITE || terme == WRITELN) {
        I();
        LIp();
    } else {
        erreur();
    }
}

void LIp() {
    if (terme == PV) {
        accept(PV);
        I();
        LIp();
    } else if (terme == PT) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void I() {
    if (terme == ID) {
        accept(ID);
        accept(AFF);
        Exp_simple();
    } else if (terme == IF) {
        accept(IF);
        Exp();
        accept(THEN);
        I();
        accept(ELSE);
        I();
    } else if (terme == WHILE) {
        accept(WHILE);
        Exp();
        accept(DO);
        I();
    } else if (terme == READ || terme == READLN || terme == WRITE || terme == WRITELN) {
        accept(terme);
        accept(PO);
        accept(ID);
        accept(PF);
    } else {
        erreur();
    }
}

void Exp() {
    if (terme == ID || terme == NB) {
        Exp_simple();
        Ep();
    } else {
        erreur();
    }
}

void Exp_simple() {
    if (terme == ID || terme == NB) {
        Terme();
        ESp();
    } else {
        erreur();
    }
}

void ESp() {
    if (terme == OPADD) {
        accept(OPADD);
        Terme();
        ESp();
    } else if (terme == OPREL || terme == PT) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void Terme() {
    if (terme == ID) {
        accept(ID);
    } else if (terme == NB) {
        accept(NB);
    } else if (terme == PO) {
        accept(PO);
        Exp_simple();
        accept(PF);
    } else {
        erreur();
    }
}

void Tp() {
    if (terme == OPMUL) {
        accept(OPMUL);
        Facteur();
        Tp();
    } else if (terme == OPREL || terme == OPADD || terme == PT) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}

void Facteur() {
    if (terme == ID) {
        accept(ID);
    } else if (terme == NB) {
        accept(NB);
    } else if (terme == PO) {
        accept(PO);
        Exp_simple();
        accept(PF);
    } else {
        erreur();
    }
}

void Ep() {
    if (terme == OPREL) {
        accept(OPREL);
        Exp_simple();
    } else if (terme == PT || terme == PV) {
        // Épsilon (vide) est autorisé ici
    } else {
        erreur();
    }
}



