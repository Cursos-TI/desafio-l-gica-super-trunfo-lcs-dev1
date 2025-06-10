#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTADO 50
#define MAX_CODIGO 10
#define MAX_NOME 50

typedef struct {
    char estado[MAX_ESTADO];
    char codigo[MAX_CODIGO];
    char nome[MAX_NOME];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} CartaCidade;

float calcularDensidade(CartaCidade c) {
    return c.populacao / c.area;
}

void exibirCarta(CartaCidade c) {
    printf("\n--- Carta da Cidade %s ---\n", c.nome);
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Nome: %s\n", c.nome);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f milhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", calcularDensidade(c));
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
    limparTela();
}

void lerStringSeguramente(char *dest, int tamanho, const char *mensagem) {
    while (1) {
        printf("%s", mensagem);
        if (fgets(dest, tamanho, stdin)) {
            if (strchr(dest, '\n') == NULL) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("Texto muito longo! Máximo de %d caracteres.\n", tamanho - 1);
            } else {
                dest[strcspn(dest, "\n")] = 0;
                break;
            }
        }
    }
}

int lerInteiroSeguramente(const char *mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while (getchar() != '\n');
            return valor;
        } else {
            printf("Entrada inválida! Digite um número inteiro.\n");
            while (getchar() != '\n');
        }
    }
}

float lerFloatSeguramente(const char *mensagem) {
    float valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%f", &valor) == 1) {
            while (getchar() != '\n');
            return valor;
        } else {
            printf("Entrada inválida! Digite um número decimal.\n");
            while (getchar() != '\n');
        }
    }
}

void compararUmAtributo(CartaCidade c1, CartaCidade c2) {
    int escolha;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("Opção: ");
    scanf("%d", &escolha);
    while (getchar() != '\n');

    switch (escolha) {
        case 1:
            if (c1.populacao > c2.populacao)
                printf("%s venceu por maior população.\n", c1.nome);
            else if (c1.populacao < c2.populacao)
                printf("%s venceu por maior população.\n", c2.nome);
            else
                printf("Populações iguais.\n");
            break;
        case 2:
            if (c1.area > c2.area)
                printf("%s venceu por maior área.\n", c1.nome);
            else if (c1.area < c2.area)
                printf("%s venceu por maior área.\n", c2.nome);
            else
                printf("Áreas iguais.\n");
            break;
        case 3:
            if (c1.pib > c2.pib)
                printf("%s venceu por maior PIB.\n", c1.nome);
            else if (c1.pib < c2.pib)
                printf("%s venceu por maior PIB.\n", c2.nome);
            else
                printf("PIBs iguais.\n");
            break;
        case 4:
            if (c1.pontosTuristicos > c2.pontosTuristicos)
                printf("%s venceu por mais pontos turísticos.\n", c1.nome);
            else if (c1.pontosTuristicos < c2.pontosTuristicos)
                printf("%s venceu por mais pontos turísticos.\n", c2.nome);
            else
                printf("Pontos turísticos iguais.\n");
            break;
        case 5:
            if (calcularDensidade(c1) > calcularDensidade(c2))
                printf("%s venceu por maior densidade populacional.\n", c1.nome);
            else if (calcularDensidade(c1) < calcularDensidade(c2))
                printf("%s venceu por maior densidade populacional.\n", c2.nome);
            else
                printf("Densidades populacionais iguais.\n");
            break;
        default:
            printf("Opção inválida.\n");
    }
}

void compararMultiplosAtributos(CartaCidade c1, CartaCidade c2) {
    int atributosEscolhidos[5];
    int numAtributos;
    int pontosC1 = 0, pontosC2 = 0;

    printf("\nQuantos atributos você deseja comparar? (1 a 5): ");
    scanf("%d", &numAtributos);
    while (getchar() != '\n');

    if (numAtributos < 1 || numAtributos > 5) {
        printf("Número inválido de atributos.\n");
        return;
    }

    printf("\nEscolha os atributos na ordem de prioridade:\n");
    printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional\n");

    for (int i = 0; i < numAtributos; i++) {
        printf("Atributo %d: ", i + 1);
        scanf("%d", &atributosEscolhidos[i]);
        while (getchar() != '\n');

        if (atributosEscolhidos[i] < 1 || atributosEscolhidos[i] > 5) {
            printf("Atributo inválido. Reinicie o processo.\n");
            return;
        }
    }

    printf("\n🔍 Comparando todos os atributos escolhidos...\n");

    for (int i = 0; i < numAtributos; i++) {
        int atributo = atributosEscolhidos[i];

        switch (atributo) {
            case 1:
                if (c1.populacao > c2.populacao) {
                    pontosC1++;
                    printf("✅ %s venceu em População.\n", c1.nome);
                } else if (c2.populacao > c1.populacao) {
                    pontosC2++;
                    printf("✅ %s venceu em População.\n", c2.nome);
                } else {
                    printf("🤝 Empate em População.\n");
                }
                break;

            case 2:
                if (c1.area > c2.area) {
                    pontosC1++;
                    printf("✅ %s venceu em Área.\n", c1.nome);
                } else if (c2.area > c1.area) {
                    pontosC2++;
                    printf("✅ %s venceu em Área.\n", c2.nome);
                } else {
                    printf("🤝 Empate em Área.\n");
                }
                break;

            case 3:
                if (c1.pib > c2.pib) {
                    pontosC1++;
                    printf("✅ %s venceu em PIB.\n", c1.nome);
                } else if (c2.pib > c1.pib) {
                    pontosC2++;
                    printf("✅ %s venceu em PIB.\n", c2.nome);
                } else {
                    printf("🤝 Empate em PIB.\n");
                }
                break;

            case 4:
                if (c1.pontosTuristicos > c2.pontosTuristicos) {
                    pontosC1++;
                    printf("✅ %s venceu em Pontos Turísticos.\n", c1.nome);
                } else if (c2.pontosTuristicos > c1.pontosTuristicos) {
                    pontosC2++;
                    printf("✅ %s venceu em Pontos Turísticos.\n", c2.nome);
                } else {
                    printf("🤝 Empate em Pontos Turísticos.\n");
                }
                break;

            case 5:
                if (calcularDensidade(c1) > calcularDensidade(c2)) {
                    pontosC1++;
                    printf("✅ %s venceu em Densidade Populacional.\n", c1.nome);
                } else if (calcularDensidade(c2) > calcularDensidade(c1)) {
                    pontosC2++;
                    printf("✅ %s venceu em Densidade Populacional.\n", c2.nome);
                } else {
                    printf("🤝 Empate em Densidade Populacional.\n");
                }
                break;

            default:
                printf("Atributo inválido.\n");
                return;
        }
    }

    printf("\n📊 Resultado final:\n");
    printf("%s: %d ponto(s)\n", c1.nome, pontosC1);
    printf("%s: %d ponto(s)\n", c2.nome, pontosC2);

    if (pontosC1 > pontosC2) {
        printf("🏆 %s venceu no total!\n", c1.nome);
    } else if (pontosC2 > pontosC1) {
        printf("🏆 %s venceu no total!\n", c2.nome);
    } else {
        printf("⚖️ Empate total!\n");
    }
}

void compararDoisAtributos(CartaCidade c1, CartaCidade c2) {
    int a1, a2, pontosC1 = 0, pontosC2 = 0;
    printf("\nEscolha o primeiro atributo:\n");
    printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional (menor vence)\n");
    scanf("%d", &a1); while (getchar() != '\n');

    printf("Escolha o segundo atributo: ");
    scanf("%d", &a2); while (getchar() != '\n');

    int atributos[2] = {a1, a2};

    for (int i = 0; i < 2; i++) {
        switch (atributos[i]) {
            case 1:
                if (c1.populacao > c2.populacao) pontosC1++;
                else if (c2.populacao > c1.populacao) pontosC2++;
                break;
            case 2:
                if (c1.area > c2.area) pontosC1++;
                else if (c2.area > c1.area) pontosC2++;
                break;
            case 3:
                if (c1.pib > c2.pib) pontosC1++;
                else if (c2.pib > c1.pib) pontosC2++;
                break;
            case 4:
                if (c1.pontosTuristicos > c2.pontosTuristicos) pontosC1++;
                else if (c2.pontosTuristicos > c1.pontosTuristicos) pontosC2++;
                break;
            case 5:
                if (calcularDensidade(c1) < calcularDensidade(c2)) pontosC1++;
                else if (calcularDensidade(c2) < calcularDensidade(c1)) pontosC2++;
                break;
        }
    }

    printf("\nResultado da comparação com dois atributos:\n");
    if (pontosC1 > pontosC2)
        printf("%s venceu!\n", c1.nome);
    else if (pontosC2 > pontosC1)
        printf("%s venceu!\n", c2.nome);
    else
        printf("Empate nos dois atributos!\n");
}

int main() {
    CartaCidade c1, c2;

    printf("Cadastro da Cidade 1:\n");
    lerStringSeguramente(c1.estado, sizeof(c1.estado), "Estado: ");
    lerStringSeguramente(c1.codigo, sizeof(c1.codigo), "Código: ");
    lerStringSeguramente(c1.nome, sizeof(c1.nome), "Nome: ");
    c1.populacao = lerInteiroSeguramente("População: ");
    c1.area = lerFloatSeguramente("Área (km²): ");
    c1.pib = lerFloatSeguramente("PIB (milhões): ");
    c1.pontosTuristicos = lerInteiroSeguramente("Pontos Turísticos: ");

    printf("\nCadastro da Cidade 2:\n");
    lerStringSeguramente(c2.estado, sizeof(c2.estado), "Estado: ");
    lerStringSeguramente(c2.codigo, sizeof(c2.codigo), "Código: ");
    lerStringSeguramente(c2.nome, sizeof(c2.nome), "Nome: ");
    c2.populacao = lerInteiroSeguramente("População: ");
    c2.area = lerFloatSeguramente("Área (km²): ");
    c2.pib = lerFloatSeguramente("PIB (milhões): ");
    c2.pontosTuristicos = lerInteiroSeguramente("Pontos Turísticos: ");

    int opcao;
    do {
        limparTela();
        printf("\n=== MENU SUPER TRUNFO ===\n");
        printf("1. Exibir Cartas\n");
        printf("2. Comparar por Um Atributo (Nível Novato)\n");
        printf("3. Comparar com Múltiplos Atributos (Nível Aventureiro)\n");
        printf("4. Comparar por Dois Atributos (Nível Mestre)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n');
            opcao = -1;
            pausar();
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                exibirCarta(c1);
                exibirCarta(c2);
                pausar();
                break;
            case 2:
                compararUmAtributo(c1, c2);
                pausar();
                break;
            case 3:
                compararMultiplosAtributos(c1, c2);
                pausar();
                break;
            case 4:
                compararDoisAtributos(c1, c2);
                pausar();
                break;
            case 0:
                printf("Encerrando o jogo!\n");
                pausar();
                break;
            default:
                printf("Opção inválida.\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}
