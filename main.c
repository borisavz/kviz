#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
FILE *otvori_datoteku(const char *);
void oslobodi(char **, int);
char linija[200];
int main() {
    int i, ii, iii, iiii, odgovor, *opcija, tacan_odgovor, *tacni, broj_pitanja,
        broj_odgovora, broj_igraca, broj_opisa;
    bool *prekinuo;
    char **opis, **ime;
    FILE *pitanja = otvori_datoteku("Unesi putanju datoteke sa pitanjima:"),
        *odgovori = otvori_datoteku("\nUnesi putanju datoteke sa odgovorima:");
    printf("\nUnesi broj igraca: ");
    scanf("%d", &broj_igraca);
    getchar();
    ime = malloc(broj_igraca * sizeof(char *));
    tacni = calloc(broj_igraca, sizeof(int));
    prekinuo = calloc(broj_igraca, sizeof(bool));
    puts("\nUnesi ime:");
    for(i = 0; i < broj_igraca; i++) {
        printf("\tIgrac %d: ", i + 1);
        fgets(linija, 100, stdin);
        ii = strlen(linija);
        ime[i] = malloc(ii * sizeof(char));
        strcpy(ime[i], linija);
        ime[i][ii - 1] = '\0';
    }
    fgets(linija, 200, pitanja);
    printf("-----\nKviz - %s-----\nUnesi 0 da prekines kviz\n\n", linija);
    fscanf(odgovori, "%d %d", &broj_pitanja, &broj_opisa);
    opis = malloc(broj_opisa * sizeof(char *));
    for(i = 0; i < broj_opisa; i++) {
        fgets(linija, 200, pitanja);
        opis[i] = malloc(strlen(linija) * sizeof(char));
        strcpy(opis[i], linija);
    }
    for(i = 0; i < broj_pitanja; i++) {
        fgets(linija, 200, pitanja);
        fscanf(odgovori, "%d %d", &broj_odgovora, &tacan_odgovor);
        opcija = calloc(broj_odgovora, sizeof(int));
        printf("%d - %s", i + 1, linija);
        for(ii = 0; ii < broj_odgovora; ii++) {
            fgets(linija, 200, pitanja);
            printf("\t%d. %s", ii + 1, linija);
        }
        puts("\n-----");
        for(ii = 0; ii < broj_igraca; ii++) {
            printf("%s: ", ime[ii]);
            if(prekinuo[ii])
                puts("/ (prekinuo)");
            else {
                if(broj_igraca == 1)
                    scanf("%d", &odgovor);
                else {
                    iii = 0;
                    while((odgovor = getch()) != '\r' && iii <= 200) {
                        if(odgovor == '\b') {
                            if(iii > 0) {
                                printf("\b \b");
                                iii--;
                            } else
                                putchar('\a');
                            continue;
                        }
                        putchar('*');
                        linija[iii] = odgovor;
                        iii++;
                    }
                    putchar('\n');
                    linija[iii] = '\0';
                    odgovor = atoi(linija);
                }
                if(odgovor == tacan_odgovor)
                    tacni[ii]++;
                else if(!odgovor) {
                    puts("Da li ste sigurni? y/n");
                    do
                        iii = getchar();
                    while(iii != 'y' && iii != 'n');
                    if(iii == 'y')
                        prekinuo[ii] = true;
                    else
                        ii--;
                }
            }
            if(odgovor > 0 && odgovor <= broj_odgovora)
                opcija[odgovor - 1]++;
        }
        putchar('\n');
        for(ii = 0; ii < broj_odgovora; ii++) {
            printf("%d|", ii + 1);
            while(opcija[ii]--)
                putchar('*');
            putchar('\n');
        }
        printf("\nTacan odgovor je pod %d\n\n", tacan_odgovor);
        free(opcija);
    }
    puts("Rezultati:");
    for(i = 0; i < broj_igraca; i++) {
        printf("\t%s: %d/%d (%.2f %%)\n", ime[i], tacni[i], broj_pitanja,
            ((float) tacni[i] / broj_pitanja) * 100);
        for(ii = 0; ii < broj_opisa; ii++)
            if(tacni[i] == ii) {
                printf("\t\t%s\n", *(opis + ii));
                break;
            }
    }
    fclose(pitanja);
    fclose(odgovori);
    free(tacni);
    free(prekinuo);
    oslobodi(ime, broj_igraca);
    oslobodi(opis, broj_opisa);
    fseek(stdin, 0, SEEK_END);
    getch();
    return 0;
}
FILE *otvori_datoteku(const char *poruka) {
    FILE *datoteka;
    puts(poruka);
    fgets(linija, 200, stdin);
    linija[strlen(linija) - 1] = '\0';
    if((datoteka = fopen(linija, "r")) == NULL) {
        perror("\nGreska");
        printf("Kod greske: %d\n", errno);
        getch();
        exit(errno);
    }
    return datoteka;
}
void oslobodi(char **niz, int duzina_niza) {
    while(duzina_niza--)
        free(niz[duzina_niza]);
    free(niz);
}
