#include <stdio.h>
#include <string.h>
#include <locale.h>

struct Item {
    char nome[50];
    float preco;
    int quantidade;
};

int montarCarrinho(struct Item carrinho[]) {
    int opcao, qtd, i = 0;
    char continuar = 's';

    printf("=== SELEÇÃO DE PRODUTOS ===\n");
    while (continuar == 's' || continuar == 'S') {
        printf("\nEscolha um produto para adicionar ao carrinho:\n");
        printf("1 - Pudim (R$6,00)\n");
        printf("2 - Pizza (R$35,00)\n");
        printf("3 - Refrigerante (R$8,00)\n");
        printf("4 - Macarrão Carbonara (R$28,00)\n");
        printf("5 - Suco (R$7,00)\n");
        printf("6 - Pastel de Carne (R$10,00)\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        printf("Quantidade: ");
        scanf("%d", &qtd);

        switch (opcao) {
            case 1:
                strcpy(carrinho[i].nome, "Pudim");
                carrinho[i].preco = 6.00;
                break;
            case 2:
                strcpy(carrinho[i].nome, "Pizza");
                carrinho[i].preco = 35.00;
                break;
            case 3:
                strcpy(carrinho[i].nome, "Refrigerante");
                carrinho[i].preco = 8.00;
                break;
            case 4:
                strcpy(carrinho[i].nome, "Macarrão Carbonara");
                carrinho[i].preco = 28.00;
                break;
            case 5:
                strcpy(carrinho[i].nome, "Suco");
                carrinho[i].preco = 7.00;
                break;
            case 6:
                strcpy(carrinho[i].nome, "Pastel de Carne");
                carrinho[i].preco = 10.00;
                break;
            default:
                printf("Opção inválida!\n");
                continue;
        }

        carrinho[i].quantidade = qtd;
        i++;

        printf("Deseja adicionar outro produto? (s/n): ");
        scanf(" %c", &continuar);
    }

    return i; 
}

void mostrarCarrinho(struct Item carrinho[], int tamanho) {
    float total = 0;
    printf("\n=== CARRINHO ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s - R$%.2f x %d = R$%.2f\n", 
            i+1, carrinho[i].nome, carrinho[i].preco,carrinho[i].quantidade, carrinho[i].preco * carrinho[i].quantidade);
       		total += carrinho[i].preco * carrinho[i].quantidade;
    }
    printf("Total: R$%.2f\nFrete gratis\n", total);
}

int escolherPagamento() {
    int opcao;
    printf("\n=== MÉTODO DE PAGAMENTO ===\n");
    printf("1 - Cartão\n");
    printf("2 - Pix\n");
    printf("3 - Dinheiro\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void pagamentoCartao() {
    char nomeTitular[50]; 
    char numero[20], validade[10], cvv[5];

    printf("\n=== PAGAMENTO COM CARTÃO ===\n");

    printf("Nome completo do titular: "); 
    fflush(stdin);
    fgets(nomeTitular, sizeof(nomeTitular), stdin);
    nomeTitular[strcspn(nomeTitular, "\n")] = '\0';

    printf("Número do cartão: ");
    scanf("%s", numero);
    printf("Validade (MM/AA): ");
    scanf("%s", validade);
    printf("CVV: ");
    scanf("%s", cvv);
    printf("\nPagamento aprovado!\n"); 
}

void pagamentoPix() {
    printf("\n=== PAGAMENTO COM PIX ===\n");
    printf("Chave Pix: Chicken.friends_ofc@gmail.com\n");
    printf("Escaneie o QR Code abaixo no app do seu banco:\n\n");
	//QR code aqui
	printf("QR CODE AQUI\n");
    printf("Pagamento confirmado!\n");
}

void pagamentoDinheiro(float total) {  
    float valor = 0;

    printf("\n=== PAGAMENTO EM DINHEIRO ===\n");

    do {
        printf("Informe o valor entregue: R$");
        scanf("%f", &valor);

        if (valor < total) {
            printf("Valor insuficiente! Total da compra: R$%.2f\n", total);
            printf("Por favor, informe outro valor.\n\n");
        }

    } while (valor < total);

    printf("Troco: R$%.2f\n", valor - total);
    printf("Pagamento confirmado!\n");
}

void confirmarPedido() {
    printf("\nPedido confirmado! O restaurante está preparando seu pedido...\n");
}

void statusEntrega() {
    int status = 0;
    printf("\n=== STATUS DA ENTREGA ===\n");
    while (status < 4) {
        switch (status) {
            case 0:
                printf("Status: Pedido recebido pelo restaurante.\n");
                break;
            case 1:
                printf("Status: Pedido em preparação.\n");
                break;
            case 2:
                printf("Status: Pedido saiu para entrega.\n");
                break;
            case 3:
                printf("Status: Pedido entregue! Bom apetite.\n");
                break;
        }
        status++;
        if (status < 4) {
            printf("Pressione ENTER para ver o próximo status...\n");
            getchar();
            getchar();
        }
    }
}

int main() {
	setlocale(LC_ALL,"portuguese");
	
    struct Item carrinho[50];
    int tamanhoCarrinho;
    int metodo;
    float total = 0;

    tamanhoCarrinho = montarCarrinho(carrinho);
    
    system("cls");

    mostrarCarrinho(carrinho, tamanhoCarrinho);

    for (int i = 0; i < tamanhoCarrinho; i++) {
        total += carrinho[i].preco * carrinho[i].quantidade;
    }

    metodo = escolherPagamento();

    switch (metodo) {
        case 1:
            pagamentoCartao();
            break;
        case 2:
            pagamentoPix();
            break;
        case 3:
            pagamentoDinheiro(total); 
            break;
        default:
            printf("Método inválido.\n");
            return 0;
    }

    confirmarPedido();
    statusEntrega();

    printf("\nAGRADECEMOS PELA PREFERÊNCIA, SOMOS TODOS CHICKEN FRIENDS <3\n");
    return 0;
}

