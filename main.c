#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int i, ii, odgovor, tacan_odgovor, *tacni, broj_pitanja,
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
        perror("Greska");
        getchar();
        exit(1);
    }
    fgets(linija, 200, pitanja);
    printf("Unesi broj igraca: ");
    scanf("%d", &broj_igraca);
    printf("-----\nKviz - %s-----\nUnesi 0 da prekines kviz\n\n", linija);
    fscanf(odgovori, "%d", &broj_pitanja);
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
        getchar();
        for(ii = 0; ii < broj_igraca; ii++) {
            printf("Igrac %d: ", ii + 1);
            scanf("%d", &odgovor);
            if(odgovor == 0)
                exit(0);
            if(odgovor == tacan_odgovor)
                *(tacni + ii) += 1;
        }
        printf("\nTacan odgovor je pod %d\n\n", tacan_odgovor);
    }
    puts("Rezultati:");
    for(ii = 0; ii < broj_igraca; ii++)
        printf("\tIgrac %d: %d/%d (%.2f %%)\n", ii + 1, *(tacni + ii), broj_pitanja,
            ((float) *(tacni + ii) / broj_pitanja) * 100);
    fclose(pitanja);
    fclose(odgovori);
    free(tacni);
    fseek(stdin, 0, SEEK_END);
    getchar();
    return 0;
}
