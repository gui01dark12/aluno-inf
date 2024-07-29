#include <stdio.h>
#include <stdlib.h>


// Uma macro para mandar uma mensagem na tela e, depois de limpar o buffer do teclado, pausar a tela
#define PAUSAR(...) \
printf(__VA_ARGS__); \
fflush(stdin); \
getchar()

#define SOFTWARE_NAME "\t\tInformacoes dos Alunos\n\n"
#define AUTOR "\t\tAutor do software: Guilherme\n\n"

// Estrutura contendo o nome e a nota do aluno
struct Alunos {
	char nome[16];
	float nota;
};

// Estrutura contendo a turma, a quantidade de alunos e a disciplina
struct TurmDisQuant {
	unsigned turma;
	unsigned quantidade;
	char disciplina[16];
};

typedef struct Alunos Alunos;
typedef struct TurmDisQuant TurmDisQuant;

/*
* Função que remove caractere de nova lina que, na tabela ascii,
* é representado pelo número 10(0xA em base hexadecimal)
*/
void removernl(char * str, int tam) {

	for (int indice = 0; indice != tam; indice++) {
		if (str[indice] == '\n') str[indice] = '\0';
	}
}


// Definir informações do aluno
void def(Alunos * pointer_aln, TurmDisQuant estrutTdq) {

	printf("%s%sTurma: %d\nQuantidade: %d\nDisciplina: %s\n",
			SOFTWARE_NAME,
			AUTOR,
			estrutTdq.turma,
			estrutTdq.quantidade,
			estrutTdq.disciplina
	);

	for (unsigned indice = 0; indice != estrutTdq.quantidade; indice++) {
		printf("\n%do aluno:\n", indice + 1);

		printf("Nome > ");
		fgets(pointer_aln->nome, 16, stdin);
		removernl(pointer_aln->nome, 16);
		fflush(stdin);

		printf("Nota > ");
		scanf("%f", &pointer_aln->nota);
		fflush(stdin);

		if (estrutTdq.quantidade - indice == 1) continue;
		pointer_aln++;
	}

}

// Função que mostra as informações dos alunos
void mostrarInfs(Alunos aln[], TurmDisQuant tdq) {

	system("cls");

	printf(SOFTWARE_NAME);
	printf(AUTOR);

	printf("Mostrando as informacoes dos alunos:\n\n");

	printf("Turma: %d\nQuantidade: %d\nDisciplina: %s\n",
			tdq.turma,
			tdq.quantidade,
			tdq.disciplina
	);

	for (unsigned indice = 0; indice != tdq.quantidade; indice++) {
		printf("\n%do aluno:\n", indice + 1);

		printf("Nome: %s\nNota: %.2f\n", aln[indice].nome, aln[indice].nota);
	}

}

// Função que cria um arquivo com as informaçoes dos alunos
int criarArq(Alunos aln[], TurmDisQuant tdq) {

	printf("\nCriando arquivo...\n");

	FILE * arq = fopen("./inf.txt", "w");

	if (arq == NULL) {
		printf("Erro ao criar arquivo\n");
		return -1;
	}

	fprintf(arq, "%s%sTurma: %d\nQuantidade: %d\nDisciplina: %s\n",
			SOFTWARE_NAME,
			AUTOR,
			tdq.turma,
			tdq.quantidade,
			tdq.disciplina
	);

	for (unsigned indice = 0; indice != tdq.quantidade; indice++) {
		fprintf(arq, "\n%do aluno:\n", indice + 1);

		fprintf(arq, "Nome: %s\nNota: %.2f\n",
				aln[indice].nome,
				aln[indice].nota
		);
	}

	fclose(arq);

	printf("Arquivo criado e escrito com sucesso!\n");

}

int main(void) {

	printf(SOFTWARE_NAME);
	printf(AUTOR);

	TurmDisQuant tdqAluno;

	printf("Turma > ");
	scanf("%d", &tdqAluno.turma);
	fflush(stdin);

	printf("Disciplina > ");
	fgets(tdqAluno.disciplina, 16, stdin);
	removernl(tdqAluno.disciplina, 16);
	fflush(stdin);

	printf("Quantidade de alunos > ");
	scanf("%d", &tdqAluno.quantidade);
	fflush(stdin);

	system("cls");

	Alunos alunos[tdqAluno.quantidade];

	def(alunos, tdqAluno);

	mostrarInfs(alunos, tdqAluno);

	criarArq(alunos, tdqAluno);

	PAUSAR("\nTecle ENTER para sair.");

	return 0;

}
