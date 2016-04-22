#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int i, ii, iii, odgovor, tacan_odgovor, *tacni, broj_pitanja,
        broj_odgovora, broj_igraca;
    char linija[200];
    FILE *pitanja, *odgovori;
    printf("Unesi putanju datoteke sa pitanjima: ");
    fgets(linija, 200, stdin);
    linija[strlen(linija) - 1] = '\0';
    pitanja = fopen(linija, "r");
    printf("Unesi putanju datoteke sa odgovorima: ");
    fgets(linija, 200, stdin);
    linija[strlen(linija) - 1] = '\0';
    odgovori = fopen(linija, "r");
    if((pitanja == NULL) || (odgovori == NULL)) {
        perror("\nGreska");
        printf("Kod greske: %d", errno);
        getchar();
        exit(1);
    }
    fgets(linija, 200, pitanja);
    printf("Unesi broj igraca: ");
    scanf("%d", &broj_igraca);
    getchar();
    char ime[broj_igraca][11];
    puts("Unesi ime:");
    for(i = 0; i < broj_igraca; i++) {
        printf("\tIgrac %d: ", i + 1);
        fgets(ime[i], 11, stdin);
        ime[i][strlen(ime[i]) - 1] = '\0';
    }
    printf("-----\nKviz - %s-----\nUnesi 0 da prekines kviz\n\n", linija);
    fscanf(odgovori, "%d %d", &broj_pitanja, &iii);
    char opis[iii][100];
    for(i = 0; i < iii; i++)
        fgets(opis[i], 100, pitanja);
    tacni = calloc(broj_igraca, sizeof(int));
    for(i = 0; i < broj_pitanja; i++) {
        fgets(linija, 200, pitanja);
        fscanf(odgovori, "%d %d", &broj_odgovora, &tacan_odgovor);
        printf("%d - %s", i + 1, linija);
        for(ii = 0; ii < broj_odgovora; ii++) {
            fgets(linija, 200, pitanja);
            printf("\t%d. %s", ii + 1, linija);
        }
        puts("\n----");
        for(ii = 0; ii < broj_igraca; ii++) {
            printf("%s: ", ime[ii]);
            scanf("%d", &odgovor);
            if(odgovor == 0)
                exit(0);
            if(odgovor == tacan_odgovor)
                *(tacni + ii) += 1;
        }
        printf("\nTacan odgovor je pod %d\n\n", tacan_odgovor);
    }
    puts("Rezultati:");
    for(i = 0, ii = 0; i < broj_igraca; i++) {
        printf("\t%s: %d/%d (%.2f %%)\n", ime[i], *(tacni + i), broj_pitanja,
            ((float) *(tacni + i) / broj_pitanja) * 100);
        fseek(odgovori, -iii, SEEK_CUR);
        for(ii = 0; ii < iii; ii++)
            if(*(tacni + i) == ii) {
                printf("\t\t%s\n", opis[ii]);
                ii = iii;
            }
    }
    fclose(pitanja);
    fclose(odgovori);
    free(tacni);
    fseek(stdin, 0, SEEK_END);
    getchar();
    return 0;
}
