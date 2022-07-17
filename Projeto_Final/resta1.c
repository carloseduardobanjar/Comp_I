#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAXLETRAS 10

typedef struct{
    char nome[20];
    int qtdPecas;
}Jogo;

void ordenaVetor(Jogo vetor[], int n)
{
    int i, j;
	Jogo temp;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if(vetor[j].qtdPecas > vetor[j+1].qtdPecas)
			{
				temp = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = temp;
			}
		}
	}
}

void escreveNoArquivo(Jogo novoJogo){
    int i, j;
    FILE *fp;
    Jogo vetor[50];
    fp = fopen("placar.txt", "r");
    if(!fp) printf("erro");
    for(i = 0; !feof(fp); i++){ //preenche o vetor
        fscanf(fp, "%s %d", vetor[i].nome, &vetor[i].qtdPecas);
    }
    printf("%d", i);
    fclose(fp);
    fp = fopen("placar.txt", "w");
    if(!fp) printf("erro");
    strcpy(vetor[i - 1].nome, novoJogo.nome);
    vetor[i - 1].qtdPecas = novoJogo.qtdPecas;
    ordenaVetor(vetor, i);
    for(j = 0; j < 1; j++){
        //fprintf(fp, "%s %d\n", vetor[j].nome, vetor[j].qtdPecas);
        printf("j = %d", j);
        printf("%s %d\n", vetor[j].nome, vetor[j].qtdPecas);
    }
    fclose(fp);
}

void imprimeArquivo(){
    int i, qtdPecas;
    char nome[50];
    FILE *fp;
    fp = fopen("placar.txt", "r");
    if(!fp) printf("erro");
    printf("Placar: \n\n");
    printf("%*s%8s\n", -MAXLETRAS, "Aluno", "Resto");
    for(i = 0; !feof(fp); i++){
        fscanf(fp, "%s %d\n", nome, &qtdPecas);
        printf("%*s%8d\n", -MAXLETRAS, nome, qtdPecas); 
    }
    printf("\n");
    fclose(fp);
}

void imprimeMatriz(int matriz[7][7]){
    int i, j;
    printf("  ");
    for(i = 0; i < 7; i++)
        printf("%3d", i);
    printf("\n\n");
    for(i = 0; i < 7; i++){
        printf("%d ", i);
        for(j = 0; j < 7; j++)
            if(matriz[i][j] == 0) printf("%3d", matriz[i][j]);
            else printf("%3c", ' ');
        printf("\n");
    }
}

void iniciarJogo(int matriz[7][7]){
    int difHor, difVert, lin, col, linFut, colFut;
    clock_t t1;
    time_t segundosInicio, segundosAtual;
    time_t difTempo;
    struct tm *data_hora_atual;
    int h, m, s, resto;
    char nome[20];

    time(&segundosInicio);   
    // data_hora_atual = localtime(&segundos); 
    // printf("\nHora ........: %d:",data_hora_atual->tm_hour);//hora   
    // printf("%d:",data_hora_atual->tm_min);//minuto
    // printf("%d\n",data_hora_atual->tm_sec);//segundo 
    printf("Nome do jogador: ");
    scanf("%s", nome);
    printf("\n\n");
    while(1){
        imprimeMatriz(matriz);
        printf("\nDigite a linha e a coluna da peça que vai andar: ");
        scanf("%d %d", &lin, &col);
        if(lin == -1) break;
        printf("\nDigite para onde ela vai andar: ");
        scanf("%d %d", &linFut, &colFut);
        system("cls");   /* windows */
        system("clear"); /* linux   */
        time(&segundosAtual);
            difTempo = segundosAtual - segundosInicio;
           
    
            h = difTempo / 3600;
            resto = difTempo % 3600;
            m = resto / 60;
            s = resto % 60;

            printf("Jogador: %s      Tempo de jogo: %d:%d:%d\n", nome, h, m, s);
        if(matriz[linFut][colFut] == 0 || matriz[linFut][colFut] == 2) 
            printf("\nPeça indisponível.\n");
        else{
            printf("\nJogada válidas!\n");
            difHor = lin - linFut; 
            difVert = col - colFut;
            if(abs(difHor) != 2 && abs(difVert) != 2) 
                printf("Você deve andar duas posições.\n");
            else{ //sei que ele andou duas então tenho que saber se tem um 0 entre elas
                if(abs(difHor) == 2){
                    if(matriz[lin][col + 1] != 0)
                        printf("Você precisa comer uma peça para saltar. \n");
                    else{
                        if(difHor == 2){ //linha maior para menor
                            matriz[linFut][colFut] = 0;
                            matriz[lin][col] = 1;
                            matriz[lin - 1][col] = 1;
                        }
                        else{ //linha menor para maior
                            matriz[linFut][colFut] = 0;
                            matriz[lin][col] = 1;
                            matriz[lin + 1][col] = 1;
                        }
                    }
                }
                else{
                    if(matriz[lin + 1][col] != 0){ 
                        printf("Você precisa comer uma peça para saltar. \n");
                    }
                    else{
                        if(difVert == 2){ //coluna maior para menor
                            matriz[linFut][colFut] = 0;
                            matriz[lin][col] = 1;
                            matriz[lin][col - 1] = 1;
                        }
                        else{ //coluna menor para maior
                            matriz[linFut][colFut] = 0;
                            matriz[lin][col] = 1;
                            matriz[lin][col + 1] = 1;
                        }
                    }
                }
            }
        }
    }
}

void inicializaMatriz(int matriz[7][7]){
    int i, j;
    for(i = 0; i < 7; i++)
        for(j = 0; j < 7; j++)
            matriz[i][j] = 0;
    matriz[3][3] = 1;
    matriz[0][0] = 2;
    matriz[0][1] = 2;
    matriz[0][5] = 2;
    matriz[0][6] = 2;
    matriz[1][0] = 2;
    matriz[1][1] = 2;
    matriz[1][5] = 2;
    matriz[1][6] = 2;
    matriz[5][0] = 2;
    matriz[5][1] = 2;
    matriz[5][5] = 2;
    matriz[5][6] = 2;
    matriz[6][0] = 2;
    matriz[6][1] = 2;
    matriz[6][5] = 2;
    matriz[6][6] = 2;
}

int main(void){ 
    int matriz[7][7], i, j;
    clock_t t1, t2;
    int peca, op;
    float difTempo;
    char nome[20];
    Jogo novoJogo;
    while(1){
        printf("O que deseja?\n1. Iniciar jogo\n2. Mostrar placar\n3. Sair\n");
        scanf("%d", &op);
        system("cls");   /* windows */
        system("clear"); /* linux   */
        if(op == 3) break;
        switch (op)
        {
        case 1:
            inicializaMatriz(matriz);
            // printf("Nome do jogador: ");
            // scanf("%s", nome);
            // strcpy(novoJogo.nome, nome);
            iniciarJogo(matriz);
            peca = 0;

            for(i = 0; i < 7; i++){
                for(j = 0; j < 7; j++){
                    if(matriz[i][j] == 0) peca++;
                }
            }
            novoJogo.qtdPecas = peca;
            // difTempo = (((float)t2 - (float)t1));
            // printf("\n\nTempo de execucao: %f", difTempo); 
            escreveNoArquivo(novoJogo);
            if(peca == 1) 
                printf("YOU WIN!");
            else
                printf("GAME OVER!\n");
            break;
        case 2:
            imprimeArquivo();
            break;
        }
    }


    // exibir score 
    // salvar no txt
    // op com tempo tempo de jogo 
    // menu princiapal (placar e inicia jogo e sair)
    
    return 0;
}

  

  
