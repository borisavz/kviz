#include <stdio.h>
#include <stdlib.h>
int main() {
    int i, ii, odgovor, tacan_odgovor, tacni = 0, netacni = 0,
        broj_pitanja, broj_odgovora;
    char linija[200];
    FILE *pitanja, *odgovori;
    printf("Unesi putanju datoteke sa pitanjima: ");
    scanf("%s", linija);
    pitanja = fopen(linija, "r");
    printf("Unesi putanju datoteke sa odgovorima: ");
    scanf("%s", linija);
    odgovori = fopen(linija, "r");
    fgets(linija, 200, pitanja);
    printf("-----\nKviz - %s-----\n\n", linija);
    fscanf(odgovori, "%d", &broj_pitanja);
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
        scanf("%d", &odgovor);
        if(odgovor == tacan_odgovor) {
            puts("Tacno!");
            tacni++;
        } else {
            puts("Netacno!");
            netacni++;
        }
    }
    printf("\n\nTacno: %d (%.2f %%)\n", tacni, ((float) tacni / broj_pitanja) * 100);
    printf("Netacno: %d (%.2f %%)\n", netacni, ((float) netacni / broj_pitanja) * 100);
    fclose(pitanja);
    fclose(odgovori);
    fseek(stdin, 0, SEEK_END);
    getchar();
    return 0;
}
