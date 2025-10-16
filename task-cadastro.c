#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char email[100];
    int tel;       
    int aniver;    
} Dados;

/**
 * Função para cadastrar um novo contato no arquivo.
 * Lê os dados do usuário e grava no final do arquivo.
 */
void cadastro() {
    Dados user;
    FILE *f = fopen("DATA.TXT", "ab"); // modo binário append
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Coleta dos dados
    printf("Digite o nome do usuario: ");
    scanf("%s", user.nome); // atenção: não lê espaço
    printf("Digite o email do usuario: ");
    scanf("%s", user.email);
    printf("Digite o telefone do usuario (somente numeros): ");
    scanf("%d", &user.tel);
    printf("Digite o aniversario do usuario (ex: 1203 para 12/03): ");
    scanf("%d", &user.aniver);

    // Grava o registro no arquivo
    fwrite(&user, sizeof(Dados), 1, f);

    fclose(f);
    printf("Usuario cadastrado com sucesso!\n");
}

/**
 * Função para alterar os dados de um contato existente.
 * Busca pelo nome e substitui os dados encontrados.
 */
void alterarDados() {
    char nome[30];
    int found = 0;
    Dados user;
    FILE *f = fopen("DATA.TXT", "rb");
    FILE *temp = fopen("TEMP.TXT", "wb");
    if (f == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuario que deseja alterar: ");
    scanf("%s", nome);

    // Lê todos os registros e regrava, alterando o encontrado
    while (fread(&user, sizeof(Dados), 1, f)) {
        if (strcmp(user.nome, nome) == 0) {
            found = 1;
            printf("Digite o novo email: ");
            scanf("%s", user.email);
            printf("Digite o novo telefone: ");
            scanf("%d", &user.tel);
            printf("Digite o novo aniversario: ");
            scanf("%d", &user.aniver);
        }
        fwrite(&user, sizeof(Dados), 1, temp);
    }

    fclose(f);
    fclose(temp);
    remove("DATA.TXT");
    rename("TEMP.TXT", "DATA.TXT");

    if (found)
        printf("Dados alterados com sucesso!\n");
    else
        printf("Usuario nao encontrado!\n");
}

/**
 * Função para excluir um contato pelo nome.
 */
void excluirUsuario() {
    char nome[30];
    int found = 0;
    Dados user;
    FILE *f = fopen("DATA.TXT", "rb");
    FILE *temp = fopen("TEMP.TXT", "wb");
    if (f == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuario que deseja excluir: ");
    scanf("%s", nome);

    // Copia todos os registros, exceto o que será excluído
    while (fread(&user, sizeof(Dados), 1, f)) {
        if (strcmp(user.nome, nome) == 0) {
            found = 1;
            continue; // pula esse registro
        }
        fwrite(&user, sizeof(Dados), 1, temp);
    }

    fclose(f);
    fclose(temp);
    remove("DATA.TXT");
    rename("TEMP.TXT", "DATA.TXT");

    if (found)
        printf("Usuario excluido com sucesso!\n");
    else
        printf("Usuario nao encontrado!\n");
}

/**
 * Função para exibir os dados de um único contato pelo nome.
 */
void exibirDadosUser() {
    char nome[30];
    int found = 0;
    Dados user;
    FILE *f = fopen("DATA.TXT", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o nome do usuario que deseja exibir: ");
    scanf("%s", nome);

    while (fread(&user, sizeof(Dados), 1, f)) {
        if (strcmp(user.nome, nome) == 0) {
            found = 1;
            printf("Nome: %s\nEmail: %s\nTelefone: %d\nAniversario: %d\n",
                   user.nome, user.email, user.tel, user.aniver);
            break;
        }
    }

    fclose(f);
    if (!found)
        printf("Usuario nao encontrado!\n");
}

/**
 * Função para exibir todos os contatos cadastrados.
 */
void exibirDadosTodos() {
    Dados user;
    FILE *f = fopen("DATA.TXT", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Dados de todos os usuarios:\n");
    while (fread(&user, sizeof(Dados), 1, f)) {
        printf("Nome: %s\nEmail: %s\nTelefone: %d\nAniversario: %d\n",
               user.nome, user.email, user.tel, user.aniver);
        printf("-----------------------\n");
    }
    fclose(f);
}

/**
 * Função principal com menu de opções.
 */
int main() {
    int op;

    // Loop até o usuário escolher sair
    do {
        printf("\nBem vindo ao sistema de cadastro!\n");
        printf("1 - Cadastrar novo usuario\n");
        printf("2 - Alterar dados de usuario\n");
        printf("3 - Excluir usuario\n");
        printf("4 - Exibir dados de usuario\n");
        printf("5 - Exibir dados de todos os contatos\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op) {
        case 1: cadastro(); break;
        case 2: alterarDados(); break;
        case 3: excluirUsuario(); break;
        case 4: exibirDadosUser(); break;
        case 5: exibirDadosTodos(); break;
        case 6: printf("Saindo do programa...\n"); break;
        default: printf("Opcao invalida!\n"); break;
        }
    } while (op != 6);

    return 0;
}
