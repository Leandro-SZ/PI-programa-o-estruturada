#include <stdio.h> 

  

void menuPaciente() { 

    int opcao; 

    do { 

        printf("\n--- [ MENU PACIENTE ] ---\n"); 

        printf("1 -> SOLICITAR AGENDAMENTO\n"); 

        printf("2 -> SOLICITAR CANCELAMENTO\n"); 

        printf("9 -> VOLTAR\n"); 

        printf("Escolha uma opcao: "); 

        scanf("%d", &opcao); 

  

        switch(opcao) { 

            case 1: 

                printf("\n[Processando solicitacao de agendamento...]\n"); 

                break; 

            case 2: 

                printf("\n[Processando solicitacao de cancelamento...]\n"); 

                break; 

            case 9: 

                printf("\nRetornando ao Menu Principal...\n"); 

                break; 

            default: 

                printf("\nOpcao invalida! Tente novamente.\n"); 

        } 

    } while(opcao != 9); 

} 

  

void menuRecepcao() { 

    int opcao; 

    do { 

        printf("\n--- [ MENU RECEPCAO ] ---\n"); 

        printf("1 -> CONFIRMAR CONSULTA\n"); 

        printf("2 -> CANCELAR CONSULTA\n"); 

        printf("9 -> VOLTAR\n"); 

        printf("Escolha uma opcao: "); 

        scanf("%d", &opcao); 

  

        switch(opcao) { 

            case 1: 

                printf("\n[Processando confirmacao de consulta...]\n"); 

                break; 

            case 2: 

                printf("\n[Processando cancelamento de consulta...]\n"); 

                break; 

            case 9: 

                printf("\nRetornando ao Menu Principal...\n"); 

                break; 

            default: 

                printf("\nOpcao invalida! Tente novamente.\n"); 

        } 

    } while(opcao != 9); 

} 

  

void menuEnfermeiro() { 

    int opcao; 

    do { 

        printf("\n--- [ MENU ENFERMEIRO ] ---\n"); 

        printf("1 -> REGISTRAR SINAIS VITAIS\n"); 

        printf("2 -> CLASSIFICACAO DE RISCO\n"); 

        printf("9 -> VOLTAR\n"); 

        printf("Escolha uma opcao: "); 

        scanf("%d", &opcao); 
        
        char c;
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        };

        switch(opcao) { 

            case 1: 

                printf("\n[Registrando sinais vitais do paciente...]\n"); 

                break; 

            case 2: 

                printf("\n[Realizando classificacao de risco...]\n"); 

                break; 

            case 9: 

                printf("\nRetornando ao Menu Principal...\n"); 

                break; 

            default: 

                printf("\nOpcao invalida! Tente novamente.\n"); 

        } 

    } while(opcao != 9); 

} 

  

void menuMedico() { 

    int opcao; 

    do { 

        printf("\n--- [ MENU MEDICO ] ---\n"); 

        printf("1 -> ACESSAR PRONTUARIO\n"); 

        printf("2 -> SOLICITAR EXAMES\n"); 

        printf("9 -> VOLTAR\n"); 

        printf("Escolha uma opcao: "); 

        scanf("%d", &opcao); 

  

        switch(opcao) { 

            case 1: 

                printf("\n[Acessando Prontuario Eletronico do Paciente - PEP...]\n"); 

                break; 

            case 2: 

                printf("\n[Solicitando exames complementares...]\n"); 

                break; 

            case 9: 

                printf("\nRetornando ao Menu Principal...\n"); 

                break; 

            default: 

                printf("\nOpcao invalida! Tente novamente.\n"); 

        } 

    } while(opcao != 9); 

} 

  

int main() { 

    int opcao; 

    do { 

        printf("\n====================================\n"); 

        printf("     SISTEMA HJK - MENU PRINCIPAL   \n"); 

        printf("====================================\n"); 

        printf("1 -> [MENU PACIENTE]\n"); 

        printf("2 -> [MENU RECEPCAO]\n"); 

        printf("3 -> [MENU ENFERMEIRO]\n"); 

        printf("4 -> [MENU MEDICO]\n"); 

        printf("0 -> SAIR\n"); 

        printf("Escolha uma opcao: "); 

        scanf("%d", &opcao); 

  

        switch(opcao) { 

            case 1: 

                menuPaciente(); 

                break; 

            case 2: 

                menuRecepcao(); 

                break; 

            case 3: 

                menuEnfermeiro(); 

                break; 

            case 4: 

                menuMedico(); 

                break; 

            case 0: 

                printf("\nEncerrando o Sistema HJK. Ate logo!\n"); 

                break; 

            default: 

                printf("\nOpcao invalida! Tente novamente.\n"); 

        } 

    } while(opcao != 0); 

  

    return 0; 

}