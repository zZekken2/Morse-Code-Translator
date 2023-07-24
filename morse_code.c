#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <wchar.h>

                //    Aa    Bb     Cc    Dd   Ee    Ff    Gg     Hh    Ii    Jj
char *alpha[1000] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                //    Kk    Ll    Mm   Nn   Oo     Pp     Qq    Rr    Ss   Tt   Uu
                    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
                //    Vv     Ww    Xx     Yy     Zz
                    "...-",".--","-..-","-.--","--.."};

                //     0       1       2       3       4       5       6       7       8       9
char *beta[1000] = {"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};

char *omega[1000] = {"-.-.--", // Exclamação(!)
                ".-..-.", // Aspas("")
                " ",
                "...-..-", // Cifrão($
                " ", // [4]
                ".-...", // 'e' Comercial(&)
                ".----.", // Apóstrofo(')
                "-.--.", // ( 
                "-.--.-", // )
                " ", " ",
                "--..--", // Vírgula(,)
                "-....-", // Hífen(-)
                ".-.-.-", // Ponto(.)
                " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                "---...", // Dois Pontos(:)
                "-.-.-.", // Ponto e Vírgula(;)
                " ",
                "-...-",
                " ",
                "..--..", // Interrogação(?)
                ".--.-.", // Arroba(@)
                " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "," ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
                "..--.-" // Underline(_)
};

int main(){
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    int l=0, v, o;
    wchar_t str[1000];

    wprintf(L"\nInsira uma frase: ");
    wscanf_s(L"%[^\n]%*c", str);

    while(str[l] != '\0'){
        v = str[l] - 192;
        o = str[l] - 33;

        if(v>=0 && v<=60){
            if((v>=0 && v<=6) || (v>=32 && v<=38)){
                v = 0;
            }
            else if((v>=8 && v<=11) || (v>=40 && v<=43)){ //e
                v = 4;
            }
            else if((v>=12 && v<=15) || (v>=44 && v<=47)){ //i
                v = 8;
            }
            else if((v>=18 && v<=22) || (v>=50 && v<=54)){ //o
                v = 14;
            }
            else if((v>=25 && v<=28) || (v>=57 && v<=60)){ //u
                v = 20;
            }
            wprintf(L"%s (%c)", alpha[v], str[l]);
        }
        else if((o>=0 && o<=31) || o == 62){
            if(str[l+1] == ' ' || str[l+1] == '\0'){
                wprintf(L"%s (%c)", omega[(str[l])-33], str[l]);
            }
            else{
                wprintf(L"%s (%c) | ", omega[(str[l])-33], str[l]);
            }
        }
        else if(str[l] != ' ' && (!isdigit(str[l]))){
            if(str[l+1] == ' ' || str[l+1] == '\0'){
                wprintf(L"%s (%c)", alpha[toupper(str[l])-65], str[l]);
            }
            else{
                wprintf(L"%s (%c) | ", alpha[toupper(str[l])-65], str[l]);
            }
        }
        else if (str[l] != ' ' && isdigit(str[l])){
            if(str[l+1] == ' ' || str[l+1] == '\0'){
                wprintf(L"%s (%c)", beta[str[l]-48], str[l]);
            }
            else{
                wprintf(L"%s (%c) | ", beta[str[l]-48], str[l]);
            }
        }
        else if(str[l] == ' '){
            wprintf(L" // ");
        }
        l++;
    }
    wprintf(L"\n");

    return 0;
}
