#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Uma macro para mandar uma mensagem na tela e, em seguida, pausar a tela
#define PAUSAR(...) \
printf(__VA_ARGS__); \
fflush(stdin); \
getchar()

#define PROGRAM_NAME "\t\tInformacoes do Aluno\n\n"
#define AUTOR "\t\tAutor: Guilherme\n\n"

struct infoAluno {
	char nome[15];
	uint8_t turma;
	char disc[15];
	uint8_t nota;
};

typedef struct infoAluno infoAluno;

/**********************************
* Função que remove caractere de  *
* nova lina que, na tabela ascii, *
* é representado pelo número 10   *
* (0xA em base hexadecimal)       *
***********************************/

void removernl(char * str, int tam) {
	for (int indice = 0; indice != tam; indice++) {
		if (str[indice] == '\n') str[indice] = '\0';
	}
}

// Definir informações do aluno
void defInfAln(struct infoAluno * x) {
	printf("Nome do aluno > ");
	fgets(x->nome, 15, stdin);
	fflush(stdin);
	removernl(x->nome, 15);

	printf("Turma > ");
	scanf("%d", &x->turma);
	fflush(stdin);

	printf("Disciplina > ");
	fgets(x->disc, 15, stdin);
	fflush(stdin);
	removernl(x->disc, 15);

	printf("Nota > ");
	scanf("%d", &x->nota);
}

int main(void) {
	printf(PROGRAM_NAME);
	printf(AUTOR);


	infoAluno aluno;

	defInfAln(&aluno);

	system("cls");

	printf("Aluno: %s\nTurma: %d\nDisciplina: %s\nNota: %d\n",
			aluno.nome, aluno.turma, aluno.disc, aluno.nota);

	printf("\nCriando arquivo...\n");
	FILE * arq = fopen("./inf.txt", "w");

	if (arq == NULL) {
		printf("Nao foi possivel criar arquivo\n");
		return -1;
	}

	fprintf(arq, "%s%sNome do aluno: %s\nTurma: %d\nDisciplina: %s\nNota: %d\n",
			PROGRAM_NAME, AUTOR, aluno.nome, aluno.turma, aluno.disc, aluno.nota);

	printf("Arquivo criado e escrito com sucesso!\n\n");

	PAUSAR("Tecle ENTER para sair.");

	fclose(arq);

	return 0;
}
