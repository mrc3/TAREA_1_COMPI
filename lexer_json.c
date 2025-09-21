
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// ALUMNOS: Marcelo Caceres - 5165343, Roberto Arce - 4500872

// --- Utilidades ---
static int is_sign(int c){ return c=='+' || c=='-'; }
static int is_newline(int c){ return c=='\n' || c=='\r'; }
static int is_hspace(int c){ return c==' ' || c=='\t' || c=='\f' || c=='\v'; }

// --- Escaneo de tokens dentro de una línea ---
static int scan_token(const char *line, size_t *i, char *out, size_t out_cap){
    // Saltar espacios horizontales
    while (is_hspace((unsigned char)line[*i])) (*i)++;

    unsigned char c = line[*i];
    if (c=='\0' || is_newline(c)) {
        return 2; // fin de línea
    }

    // Puntuación
    switch(c){
        case '[': (*i)++; snprintf(out, out_cap, "L_CORCHETE"); return 1;
        case ']': (*i)++; snprintf(out, out_cap, "R_CORCHETE"); return 1;
        case '{': (*i)++; snprintf(out, out_cap, "L_LLAVE"); return 1;
        case '}': (*i)++; snprintf(out, out_cap, "R_LLAVE"); return 1;
        case ',': (*i)++; snprintf(out, out_cap, "COMA"); return 1;
        case ':': (*i)++; snprintf(out, out_cap, "DOS_PUNTOS"); return 1;
    }

    // Cadenas (STRING)
    if (c=='"'){
        size_t j = *i + 1;
        int escaped = 0;
        for(; line[j] != '\0' && !is_newline((unsigned char)line[j]); ++j){
            if (escaped){ escaped = 0; continue; }
            if (line[j] == '\\'){ escaped = 1; continue; }
            if (line[j] == '"'){
                *i = j + 1;
                snprintf(out, out_cap, "STRING");
                return 1;
            }
        }
        return 0; // error léxico
    }

    // Números
    if (isdigit(c)){
        size_t j = *i;
        while (isdigit((unsigned char)line[j])) j++;
        if (line[j]=='.' && isdigit((unsigned char)line[j+1])){
            j++;
            while (isdigit((unsigned char)line[j])) j++;
        }
        if (line[j]=='e' || line[j]=='E'){
            size_t k = j + 1;
            if (is_sign((unsigned char)line[k])) k++;
            if (!isdigit((unsigned char)line[k])) return 0;
            while (isdigit((unsigned char)line[k])) k++;
            j = k;
        }
        *i = j;
        snprintf(out, out_cap, "NUMBER");
        return 1;
    }

    // Palabras reservadas
    if (isalpha(c)){
        char buf[16]; size_t j = *i, b=0;
        while (isalpha((unsigned char)line[j]) && b+1 < sizeof(buf)){
            buf[b++] = (char)tolower((unsigned char)line[j]);
            j++;
        }
        buf[b] = '\0';
        if (strcmp(buf,"true")==0){ *i += 4; snprintf(out,out_cap,"PR_TRUE"); return 1; }
        if (strcmp(buf,"false")==0){ *i += 5; snprintf(out,out_cap,"PR_FALSE"); return 1; }
        if (strcmp(buf,"null")==0){ *i += 4; snprintf(out,out_cap,"PR_NULL"); return 1; }
        return 0;
    }

    return 0; // carácter desconocido
}

int main(int argc, char **argv){
    if (argc < 2){
        fprintf(stderr, "Uso: %s <archivo_fuente>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f){ perror("No se pudo abrir el archivo fuente"); return 1; }

    char buf[2048];
    unsigned long linea = 0;

    while (fgets(buf, sizeof(buf), f)){
        linea++;
        size_t i = 0;
        while (buf[i]==' ' || buf[i]=='\t') { putchar(buf[i]); i++; }

        int first = 1;
        while (1){
            char tok[32];
            size_t pos = i;
            int r = scan_token(buf, &i, tok, sizeof(tok));
            if (r == 2) break;
            if (r == 0){
                printf("ERROR_LEXICO(linea %lu, pos %zu)", linea, pos+1);
                break;
            }
            if (!first) putchar(' ');
            fputs(tok, stdout);
            first = 0;
        }
        putchar('\n');
    }

    fclose(f);
    return 0;
}
    