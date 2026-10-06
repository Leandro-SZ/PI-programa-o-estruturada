/*
 * SISTEMA HJK - Menus de console
 *
 * Compilar: gcc -Wall -Wextra -o sistema_hjk sistema_hjk.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ---------- Configuracoes ---------- */

#ifdef _WIN32
    #define COMANDO_LIMPAR "cls"
#else
    #define COMANDO_LIMPAR "clear"
#endif

#define LARGURA_BANNER 36
#define TAM_BUFFER     64
#define OPCAO_INVALIDA (-1)
#define OPCAO_EOF      (-2)
#define CODIGO_SAIR    0
#define CODIGO_VOLTAR  9
#define QTD_ITENS(v)   (sizeof(v) / sizeof((v)[0]))

/* Um item de menu: ou executa uma funcao (submenu) ou mostra uma mensagem */
typedef void (*FuncaoAcao)(void);

typedef struct {
    int         codigo;
    const char *rotulo;
    const char *mensagem;
    FuncaoAcao  acao;
} ItemMenu;

/* ---------- Utilitarios de tela e entrada ---------- */

static void limparTela(void) {
    if (system(COMANDO_LIMPAR) != 0) {
        printf("\033[2J\033[H"); /* alternativa ANSI se o comando falhar */
    }
}

static void descartarLinha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* consome o resto da linha */
    }
}

static void aguardarEnter(void) {
    printf("\nPressione ENTER para continuar...");
    descartarLinha();
}

/*
 * Le uma linha inteira e converte para numero.
 * Retorna OPCAO_INVALIDA (letras, vazio, lixo) ou OPCAO_EOF (fim da entrada).
 */
static int lerOpcao(void) {
    char  buffer[TAM_BUFFER];
    char *fim;
    long  valor;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return OPCAO_EOF;
    }

    /* Linha maior que o buffer: joga fora o resto para nao sobrar lixo */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        descartarLinha();
        return OPCAO_INVALIDA;
    }

    errno = 0;
    valor = strtol(buffer, &fim, 10);
    if (fim == buffer || errno == ERANGE) {
        return OPCAO_INVALIDA;
    }

    while (*fim == ' ' || *fim == '\t') {
        fim++;
    }
    if (*fim != '\n' && *fim != '\r' && *fim != '\0') {
        return OPCAO_INVALIDA; /* ex.: "1abc" ou "1 2" */
    }
    if (valor < 0 || valor > 999) {
        return OPCAO_INVALIDA;
    }
    return (int)valor;
}

static void imprimirLinha(char c) {
    int i;
    for (i = 0; i < LARGURA_BANNER; i++) {
        putchar(c);
    }
    putchar('\n');
}

static void imprimirCentralizado(const char *texto) {
    int pad = (LARGURA_BANNER - (int)strlen(texto)) / 2;
    if (pad < 0) {
        pad = 0;
    }
    printf("%*s%s\n", pad, "", texto);
}

static void imprimirBanner(const char *subtitulo) {
    imprimirLinha('=');
    imprimirCentralizado("SISTEMA HJK");
    imprimirCentralizado(subtitulo);
    imprimirLinha('=');
    putchar('\n');
}

/* ---------- Motor de menus (reaproveitado por todos os menus) ---------- */

static void executarMenu(const char *subtitulo, const ItemMenu *itens, size_t qtd,
                         int codigoSaida, const char *rotuloSaida) {
    int             opcao;
    size_t          i;
    const ItemMenu *escolhido;

    for (;;) {
        limparTela();
        imprimirBanner(subtitulo);

        for (i = 0; i < qtd; i++) {
            printf("%d -> %s\n", itens[i].codigo, itens[i].rotulo);
        }
        printf("%d -> %s\n", codigoSaida, rotuloSaida);
        printf("\nEscolha uma opcao: ");

        opcao = lerOpcao();
        if (opcao == OPCAO_EOF || opcao == codigoSaida) {
            return;
        }

        escolhido = NULL;
        for (i = 0; i < qtd; i++) {
            if (itens[i].codigo == opcao) {
                escolhido = &itens[i];
                break;
            }
        }

        if (escolhido == NULL) {
            printf("\nOpcao invalida! Tente novamente.\n");
            aguardarEnter();
        } else if (escolhido->acao != NULL) {
            escolhido->acao();
        } else {
            printf("\n[%s]\n", escolhido->mensagem);
            aguardarEnter();
        }
    }
}

/* ---------- Submenus ---------- */

static void menuPaciente(void) {
    static const ItemMenu itens[] = {
        {1, "SOLICITAR AGENDAMENTO",  "Processando solicitacao de agendamento...",  NULL},
        {2, "SOLICITAR CANCELAMENTO", "Processando solicitacao de cancelamento...", NULL}
    };
    executarMenu("MENU PACIENTE", itens, QTD_ITENS(itens), CODIGO_VOLTAR, "VOLTAR");
}

static void menuRecepcao(void) {
    static const ItemMenu itens[] = {
        {1, "CONFIRMAR CONSULTA", "Processando confirmacao de consulta...",  NULL},
        {2, "CANCELAR CONSULTA",  "Processando cancelamento de consulta...", NULL}
    };
    executarMenu("MENU RECEPCAO", itens, QTD_ITENS(itens), CODIGO_VOLTAR, "VOLTAR");
}

static void menuEnfermeiro(void) {
    static const ItemMenu itens[] = {
        {1, "REGISTRAR SINAIS VITAIS", "Registrando sinais vitais do paciente...", NULL},
        {2, "CLASSIFICACAO DE RISCO",  "Realizando classificacao de risco...",     NULL}
    };
    executarMenu("MENU ENFERMEIRO", itens, QTD_ITENS(itens), CODIGO_VOLTAR, "VOLTAR");
}

static void menuMedico(void) {
    static const ItemMenu itens[] = {
        {1, "ACESSAR PRONTUARIO", "Acessando Prontuario Eletronico do Paciente - PEP...", NULL},
        {2, "SOLICITAR EXAMES",   "Solicitando exames complementares...",                 NULL}
    };
    executarMenu("MENU MEDICO", itens, QTD_ITENS(itens), CODIGO_VOLTAR, "VOLTAR");
}

/* ---------- Programa principal ---------- */

int main(void) {
    static const ItemMenu itens[] = {
        {1, "MENU PACIENTE",   NULL, menuPaciente},
        {2, "MENU RECEPCAO",   NULL, menuRecepcao},
        {3, "MENU ENFERMEIRO", NULL, menuEnfermeiro},
        {4, "MENU MEDICO",     NULL, menuMedico}
    };

    executarMenu("MENU PRINCIPAL", itens, QTD_ITENS(itens), CODIGO_SAIR, "SAIR");

    limparTela();
    printf("Encerrando o Sistema HJK. Ate logo!\n");
    return 0;
}
