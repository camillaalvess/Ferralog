#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

#define MAX_FERRAMENTAS 100

typedef struct {
    char nome[100];
    int codigo_qr;
    float valor_compra;
    char possui_garantia;
    int setor;
} Ferramenta;

void telaCarregamento();
void cadastrarFerramenta(Ferramenta estoque[], int *total);
void consultarPorSetor(Ferramenta estoque[], int total);
void verificarGarantia(Ferramenta estoque[], int total);
int buscarPorQR(Ferramenta estoque[], int total, int qr);
void buscarEExibirPorQR(Ferramenta estoque[], int total);
void editarFerramenta(Ferramenta estoque[], int total);
void excluirFerramenta(Ferramenta estoque[], int *total);
const char* obterNomeSetor(int setor);

int main() {
    setlocale(LC_ALL, "Portuguese");

    Ferramenta estoque[MAX_FERRAMENTAS];
    int total_ferramentas = 0;
    int opcao;

    telaCarregamento();

    do {
        system("cls");

        printf("=====================================================\n");
        printf("    SISTEMA DE CONTROLE LOGISTICO DE FERRAMENTAS     \n");
        printf("                      FERRALOG                       \n");
        printf("=====================================================\n\n");

        printf("Itens Cadastrados: %d / %d\n\n", total_ferramentas, MAX_FERRAMENTAS);
        printf("Menu Principal:\n\n");
        printf("[ 1 ] - Cadastrar nova ferramenta\n");
        printf("[ 2 ] - Consultar ferramenta por setor\n");
        printf("[ 3 ] - Verificar status de garantia\n");
        printf("[ 4 ] - Buscar ferramenta por Codigo QR\n");
        printf("[ 5 ] - Editar ferramenta\n");
        printf("[ 6 ] - Excluir ferramenta\n");
        printf("[ 7 ] - Sair do sistema\n\n");

        printf("=====================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFerramenta(estoque, &total_ferramentas);
                break;
            case 2:
                consultarPorSetor(estoque, total_ferramentas);
                break;
            case 3:
                verificarGarantia(estoque, total_ferramentas);
                break;
            case 4:
                buscarEExibirPorQR(estoque, total_ferramentas);
                break;
            case 5:
                editarFerramenta(estoque, total_ferramentas);
                break;
            case 6:
                excluirFerramenta(estoque, &total_ferramentas);
                break;
            case 7:
                system("cls");
                printf("Encerrando o FerraLog...\n");
                Sleep(1000);
                break;
            default:
                system("cls");
                printf("Opcao invalida!\n\n");
                printf("Aperte qualquer tecla para tentar novamente...");
                getch();
                break;
        }
    } while (opcao != 7);

    return 0;
}

void telaCarregamento() {
    printf("Iniciando o sistema FerraLog...\n");
    Sleep(600);
    printf("[ OK ] Carregando rotinas de gerenciamento e busca...\n");
    Sleep(500);
    system("cls");
}

const char* obterNomeSetor(int setor) {
    switch (setor) {
        case 1: return "Almoxarifado Central";
        case 2: return "Manutencao e Operacoes";
        case 3: return "Usinagem e Oficina";
        default: return "Setor Desconhecido";
    }
}

int buscarPorQR(Ferramenta estoque[], int total, int qr) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo_qr == qr) {
            return i;
        }
    }
    return -1;
}

void cadastrarFerramenta(Ferramenta estoque[], int *total) {
    if (*total >= MAX_FERRAMENTAS) {
        system("cls");
        printf("Erro: Limite maximo de ferramentas atingido (%d)!\n\n", MAX_FERRAMENTAS);
        printf("Aperte qualquer tecla para voltar...");
        getch();
        return;
    }

    Ferramenta nova;

    system("cls");
    printf("--- Cadastro de Ferramenta ---\n\n");
    printf("Digite o codigo QR: ");
    scanf("%d", &nova.codigo_qr);

    if (buscarPorQR(estoque, *total, nova.codigo_qr) != -1) {
        system("cls");
        printf("Erro: Ja existe uma ferramenta cadastrada com este Codigo QR!\n\n");
        printf("Aperte qualquer tecla para voltar...");
        getch();
        return;
    }

    system("cls");
    printf("--- Cadastro de Ferramenta ---\n\n");
    printf("Digite o nome da ferramenta: ");
    scanf(" %[^\n]", nova.nome);

    system("cls");
    printf("--- Cadastro de Ferramenta ---\n\n");
    printf("Digite o valor de compra: ");
    scanf("%f", &nova.valor_compra);

    if (nova.valor_compra <= 0) {
        system("cls");
        printf("Erro: VALOR INVALIDO! O valor deve ser maior que R$ 0.00.\n\n");
        printf("Aperte qualquer tecla para tentar novamente...");
        getch();
        return;
    }

    system("cls");
    printf("--- Cadastro de Ferramenta ---\n\n");
    printf("A ferramenta possui garantia? (S/N): ");
    scanf(" %c", &nova.possui_garantia);

    system("cls");
    printf("--- Seleção de Setor ---\n\n");
    printf("[ 1 ] - Almoxarifado Central\n");
    printf("[ 2 ] - Manutencao e Operacoes\n");
    printf("[ 3 ] - Usinagem e Oficina\n\n");
    printf("Selecione o setor de destino: ");
    scanf("%d", &nova.setor);

    if (nova.setor < 1 || nova.setor > 3) {
        nova.setor = 1;
    }

    estoque[*total] = nova;
    (*total)++;

    system("cls");
    printf("=====================================================\n");
    printf("                  RECIBO DE CADASTRO                 \n");
    printf("=====================================================\n\n");

    printf("Ferramenta Cadastrada: %s\n", nova.nome);
    printf("Codigo QR: %d\n", nova.codigo_qr);
    printf("Valor da Ferramenta: R$ %.2f\n", nova.valor_compra);
    printf("Possui Garantia: %c\n", nova.possui_garantia);
    printf("Setor: %s\n\n", obterNomeSetor(nova.setor));

    if (nova.valor_compra > 1000.00 && (nova.possui_garantia == 'N' || nova.possui_garantia == 'n')) {
        printf("*****************************************************\n");
        printf("   ALERTA DE ALTO RISCO: FERRAMENTA SEM GARANTIA E   \n");
        printf("   COM VALOR SUPERIOR A R$ 1.000,00!                 \n");
        printf("*****************************************************\n\n");
    } else {
        printf("Classificacao de risco: Normal.\n\n");
    }

    printf("Aperte qualquer tecla para voltar ao menu...");
    getch();
}

void consultarPorSetor(Ferramenta estoque[], int total) {
    int setor_opcao;
    int encontradas = 0;

    system("cls");
    printf("=====================================================\n");
    printf("                 CONSULTA POR SETOR                  \n");
    printf("=====================================================\n\n");

    printf("Selecione o setor desejado:\n\n");
    printf("[ 1 ] - Almoxarifado Central\n");
    printf("[ 2 ] - Manutencao e Operacoes\n");
    printf("[ 3 ] - Usinagem e Oficina\n");
    printf("[ 4 ] - Voltar\n\n");
    printf("Opcao: ");
    scanf("%d", &setor_opcao);

    if (setor_opcao == 4 || setor_opcao < 1 || setor_opcao > 3) {
        return;
    }

    system("cls");
    printf("--- Ferramentas no Setor: %s ---\n\n", obterNomeSetor(setor_opcao));

    for (int i = 0; i < total; i++) {
        if (estoque[i].setor == setor_opcao) {
            printf("[%d] Nome: %s | Cod QR: %d | R$ %.2f | Garantia: %c\n",
                   i + 1, estoque[i].nome, estoque[i].codigo_qr, estoque[i].valor_compra, estoque[i].possui_garantia);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma ferramenta cadastrada neste setor.\n");
    }

    printf("\nTotal de itens encontrados: %d\n\n", encontradas);
    printf("Aperte qualquer tecla para voltar ao menu...");
    getch();
}

void verificarGarantia(Ferramenta estoque[], int total) {
    system("cls");
    printf("=====================================================\n");
    printf("            STATUS DE GARANTIA DO ESTOQUE            \n");
    printf("=====================================================\n\n");

    if (total == 0) {
        printf("Nenhuma ferramenta cadastrada no sistema.\n\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("ID: %d | Nome: %s | QR: %d\n", i + 1, estoque[i].nome, estoque[i].codigo_qr);
            if (estoque[i].possui_garantia == 'S' || estoque[i].possui_garantia == 's') {
                printf("Status: [ COBERTO POR GARANTIA ]\n");
            } else {
                printf("Status: [ SEM GARANTIA ]\n");
            }
            printf("-----------------------------------------------------\n");
        }
    }

    printf("\nAperte qualquer tecla para voltar ao menu...");
    getch();
}

void buscarEExibirPorQR(Ferramenta estoque[], int total) {
    int qr;

    system("cls");
    printf("=====================================================\n");
    printf("             BUSCAR FERRAMENTA POR CODIGO QR         \n");
    printf("=====================================================\n\n");

    printf("Digite o Codigo QR desejado: ");
    scanf("%d", &qr);

    int idx = buscarPorQR(estoque, total, qr);

    system("cls");
    if (idx != -1) {
        printf("--- Ferramenta Encontrada ---\n\n");
        printf("Nome: %s\n", estoque[idx].nome);
        printf("Codigo QR: %d\n", estoque[idx].codigo_qr);
        printf("Valor: R$ %.2f\n", estoque[idx].valor_compra);
        printf("Garantia: %c\n", estoque[idx].possui_garantia);
        printf("Setor: %s\n\n", obterNomeSetor(estoque[idx].setor));
    } else {
        printf("Ferramenta com o Codigo QR %d nao foi encontrada!\n\n", qr);
    }

    printf("Aperte qualquer tecla para voltar...");
    getch();
}

void editarFerramenta(Ferramenta estoque[], int total) {
    int qr;

    system("cls");
    printf("=====================================================\n");
    printf("                 EDITAR FERRAMENTA                   \n");
    printf("=====================================================\n\n");

    printf("Digite o Codigo QR da ferramenta que deseja editar: ");
    scanf("%d", &qr);

    int idx = buscarPorQR(estoque, total, qr);

    if (idx == -1) {
        system("cls");
        printf("Ferramenta nao encontrada!\n\n");
        printf("Aperte qualquer tecla para voltar...");
        getch();
        return;
    }

    system("cls");
    printf("--- Editando Ferramenta: %s (QR: %d) ---\n\n", estoque[idx].nome, estoque[idx].codigo_qr);

    printf("Novo Nome (Atual: %s): ", estoque[idx].nome);
    scanf(" %[^\n]", estoque[idx].nome);

    printf("Novo Valor (Atual: R$ %.2f): ", estoque[idx].valor_compra);
    scanf("%f", &estoque[idx].valor_compra);

    printf("Possui Garantia? S/N (Atual: %c): ", estoque[idx].possui_garantia);
    scanf(" %c", &estoque[idx].possui_garantia);

    printf("Novo Setor [1-Almoxarifado, 2-Manutencao, 3-Usinagem] (Atual: %d): ", estoque[idx].setor);
    scanf("%d", &estoque[idx].setor);

    if (estoque[idx].setor < 1 || estoque[idx].setor > 3) {
        estoque[idx].setor = 1;
    }

    system("cls");
    printf("Cadastro atualizado com sucesso!\n\n");
    printf("Aperte qualquer tecla para voltar...");
    getch();
}

void excluirFerramenta(Ferramenta estoque[], int *total) {
    int qr;
    char confirma;

    system("cls");
    printf("=====================================================\n");
    printf("                EXCLUIR FERRAMENTA                   \n");
    printf("=====================================================\n\n");

    printf("Digite o Codigo QR da ferramenta a ser removida: ");
    scanf("%d", &qr);

    int idx = buscarPorQR(estoque, *total, qr);

    if (idx == -1) {
        system("cls");
        printf("Ferramenta nao encontrada!\n\n");
        printf("Aperte qualquer tecla para voltar...");
        getch();
        return;
    }

    system("cls");
    printf("Tem certeza que deseja excluir '%s' (QR: %d)? (S/N): ", estoque[idx].nome, estoque[idx].codigo_qr);
    scanf(" %c", &confirma);

    if (confirma == 'S' || confirma == 's') {

        for (int i = idx; i < (*total) - 1; i++) {
            estoque[i] = estoque[i + 1];
        }
        (*total)--;

        system("cls");
        printf("Ferramenta excluida com sucesso!\n\n");
    } else {
        system("cls");
        printf("Operacao cancelada.\n\n");
    }

    printf("Aperte qualquer tecla para voltar...");
    getch();
}
