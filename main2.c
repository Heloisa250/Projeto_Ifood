#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* ===========================
   TIPOS / ESTRUTURAS
   =========================== */

typedef struct {
    char nome[50];
    char descricao[200];
    float preco;
    int estoque; /* NOVO: quantidade disponível */
} Produto;

typedef struct {
    char nome[50];
    Produto cardapio[20];
    int qtdProdutos;
} Restaurante;

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
    int produto_index; /* índice do produto no cardápio para restaurar estoque ao remover */
} ItemCarrinho;

/* ===========================
   VARIÁVEIS GLOBAIS
   =========================== */

Restaurante restaurante; /* apenas 1 restaurante (SUPER PRO - opção A) */
int restaurante_inicializado = 0;

ItemCarrinho carrinho[50];
int tamanhoCarrinho = 0;

/* Dados de usuário simplificados (mantidos do seu código) */
char nome_usuario[50];
char email_usuario[50];
char senha_usuario[20];
int usuario_cadastrado = 0;
char telefone_usuario[20];
char endereco_usuario[100];
int recebe_publicidade_usuario = 1; 


/* Usuário fixo p/ login */
char usuario_fixo_nome[];
char usuario_fixo_email[];
char usuario_fixo_senha[];

/* ===========================
   PROTÓTIPOS
   =========================== */

/* fluxo principal / páginas */
void pagina_inicial();
int le_valida_opcao_pagina_inicial();
void pagina_usuario();
void usuario_livre();
void cadastro_celular();
void codigo_whatsapp();
void cadastro_email();
void codigo_email();
void cadastro_final();
void tela_login();

/* admin (CRUD + estoque) - acessado por login_adm */
void login_adm();
void pagina_restaurante_admin();
void admin_adicionar_prato();
void admin_editar_prato();
void admin_excluir_prato();
void admin_ver_cardapio_admin();
void admin_ajustar_estoque();

/* parte do usuário (visualizar cardápio/pegar detalhes) */
void menuUsuario();
void listarRestaurantes(); /* aqui é apenas 1 restaurante, mas mantemos o fluxo */
void verCardapioUsuario();
void detalhesProdutoUsuario(int idx);
void menuContaUsuario();
void mostrarInformacoesUsuario();
void editarInformacoesUsuario();
void editarContatoUsuario();
void editarCredenciaisUsuario();
void configurarPublicidadeUsuario();


/* carrinho / pagamento / status */
void montarCarrinho(); /* abre o menu do carrinho */
void mostrarCarrinho();
void removerItemCarrinho();
int escolherPagamento();
void pagamentoCartao();
void pagamentoPix();
void pagamentoDinheiro(float total);
void confirmarPedido();
void statusEntrega();

/* utilitários */
void inicializarRestaurantePadrao();

/* ===========================
   MAIN
   =========================== */

int main() {
    setlocale(LC_ALL, "Portuguese");

    inicializarRestaurantePadrao();

    int opcao;

    do {
        pagina_inicial();
        opcao = le_valida_opcao_pagina_inicial();

        switch (opcao) {
            case 1:
                printf("\nPagina em construcao...\n");
                system("pause");
                break;
            case 2:
                login_adm();
                break;
            case 3:
                pagina_usuario();
                break;
            case 4:
                pagina_usuario();
                break;
            case 5:
                pagina_usuario();
                break;
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }

    } while (1);

    return 0;
}

/* ===========================
   INICIALIZAÇÃO RESTAURANTE
   =========================== */

void inicializarRestaurantePadrao() {
    if (restaurante_inicializado) return;

    strcpy(restaurante.nome, "Chicken Friends");
    restaurante.qtdProdutos = 8;

    strcpy(restaurante.cardapio[0].nome, "Frango Crocante Classico");
    strcpy(restaurante.cardapio[0].descricao, "350g de frango empanado extra crocante com tempero secreto e maionese artesanal da casa.");
    restaurante.cardapio[0].preco = 25.90;
    restaurante.cardapio[0].estoque = 10;

    strcpy(restaurante.cardapio[1].nome, "Coxinha Premium");
    strcpy(restaurante.cardapio[1].descricao, "Coxinha grande recheada com frango desfiado e catupiry verdadeiro, fritura sequinha.");
    restaurante.cardapio[1].preco = 8.50;
    restaurante.cardapio[1].estoque = 20;

    strcpy(restaurante.cardapio[2].nome, "Combo Frango + Refri");
    strcpy(restaurante.cardapio[2].descricao, "Porcao generosa de frango crocante com refrigerante lata.");
    restaurante.cardapio[2].preco = 32.00;
    restaurante.cardapio[2].estoque = 8;

    strcpy(restaurante.cardapio[3].nome, "Sanduiche Crispy Chicken");
    strcpy(restaurante.cardapio[3].descricao, "Pao brioche, frango crocante, alface americana, picles e maionese especial.");
    restaurante.cardapio[3].preco = 23.90;
    restaurante.cardapio[3].estoque = 12;

    strcpy(restaurante.cardapio[4].nome, "Batata Rustica com Ervas");
    strcpy(restaurante.cardapio[4].descricao, "Batatas grossas fritas com alecrim, alho dourado e sal especial.");
    restaurante.cardapio[4].preco = 12.00;
    restaurante.cardapio[4].estoque = 15;

    strcpy(restaurante.cardapio[5].nome, "Stick de Frango + Barbecue");
    strcpy(restaurante.cardapio[5].descricao, "Tiras de frango empanadas crocantes com molho barbecue defumado.");
    restaurante.cardapio[5].preco = 18.90;
    restaurante.cardapio[5].estoque = 10;

    strcpy(restaurante.cardapio[6].nome, "Onion Rings Especial");
    strcpy(restaurante.cardapio[6].descricao, "Cebola empanada crocante com molho ranch cremoso.");
    restaurante.cardapio[6].preco = 14.90;
    restaurante.cardapio[6].estoque = 7;

    strcpy(restaurante.cardapio[7].nome, "Milkshake Crocante");
    strcpy(restaurante.cardapio[7].descricao, "Milkshake de baunilha com borda de chocolate e pedacos de cookies crocantes.");
    restaurante.cardapio[7].preco = 16.50;
    restaurante.cardapio[7].estoque = 9;

    restaurante_inicializado = 1;
}

/* ===========================
   PAGINAS / FLUXO PRINCIPAL
   =========================== */

void pagina_inicial() {
    system("cls");
    printf("  IFOOD     (1)Entregador      (2)Admin        (3)Entrar/Cadastrar  ");
    printf("\n\n           Tudo para facilitar o seu dia a dia!\n\n");
    printf("        (4) Restaurantes");
    printf("              (5) Mercados\n\n");
}

int le_valida_opcao_pagina_inicial() {
    int opcao;
    printf("Escolha uma das opcoes (1,2,3,4 ou 5): ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

/* ===========================
   USUARIO: cadastro / login
   =========================== */

void pagina_usuario() {
    int opcao;

    do {
        system("cls");
        printf("=== USUARIO ===\n");
        printf("1 - Cadastrar novo usuario\n");
        printf("2 - Fazer login (usuario ja cadastrado)\n");
        printf("3 - Voltar para pagina inicial\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); opcao = -1; }

        if (opcao == 1) {
            cadastro_celular();
            return;
        } else if (opcao == 2) {
            tela_login();
            return;
        } else if (opcao == 3) {
            return;
        } else {
            printf("Opcao invalida!\n");
            system("pause");
        }

    } while (1);
}

void cadastro_celular() {
    system("cls");
    printf("Digite o numero do celular: ");
    scanf("%s", email_usuario); /* reuso rápido do campo email_usuario para entrada do contato (não persistimos celular separadamente aqui) */
    strcpy(telefone_usuario, email_usuario);
    printf("\nCodigo enviado pelo WhatsApp (simulado: 1234)\n");
    codigo_whatsapp();
}

void codigo_whatsapp() {
    int tentativas = 0;
    int codigo_digitado;
    do {
        printf("\nDigite o codigo recebido: ");
        if (scanf("%d", &codigo_digitado) != 1) { while (getchar() != '\n'); codigo_digitado = 0; }
        if (codigo_digitado == 1234) {
            printf("\nCodigo correto!\n");
            cadastro_email();
            return;
        } else {
            printf("\nCodigo incorreto!\n");
            tentativas++;
        }
    } while (tentativas < 3);
    printf("\nFalha no cadastro. Voltando ao menu anterior...\n");
    system("pause");
}

void cadastro_email() {
    system("cls");
    printf("Digite o email: ");
    scanf("%s", email_usuario);
    printf("\nCodigo enviado ao email (simulado: 5678)\n");
    codigo_email();
}

void codigo_email() {
    int tentativas = 0;
    int codigo_digitado;
    do {
        printf("\nDigite o codigo recebido: ");
        if (scanf("%d", &codigo_digitado) != 1) { while (getchar() != '\n'); codigo_digitado = 0; }
        if (codigo_digitado == 5678) {
            printf("\nCodigo correto!\n");
            cadastro_final();
            return;
        } else {
            printf("\nCodigo incorreto!\n");
            tentativas++;
        }
    } while (tentativas < 3);
    printf("\nFalha no cadastro. Voltando ao menu anterior...\n");
    system("pause");
}

void cadastro_final() {
    char confirma_senha[20];
    int senhas_iguais = 0;

    system("cls");
    printf("Digite o seu nome completo: ");
    getchar();
    fgets(nome_usuario, sizeof(nome_usuario), stdin);
    nome_usuario[strcspn(nome_usuario, "\n")] = '\0';

    printf("Endereco: ");
    fgets(senha_usuario, sizeof(senha_usuario), stdin); /* hack simples: não armazenamos endereco separado aqui */
    senha_usuario[strcspn(senha_usuario, "\n")] = '\0';
	strcpy(endereco_usuario, senha_usuario);

    do {
        printf("Senha: ");
        scanf("%s", senha_usuario);
        printf("Confirmar senha: ");
        scanf("%s", confirma_senha);
        senhas_iguais = strcmp(senha_usuario, confirma_senha);
        if (senhas_iguais != 0) printf("\nAs senhas nao conferem! Tente novamente.\n");
    } while (senhas_iguais != 0);

    usuario_cadastrado = 1;
    printf("\nCadastro concluido com sucesso!\n");
    printf("Nome: %s\nEmail: %s\n", nome_usuario, email_usuario);
    system("pause");
}

void tela_login() {
    int escolha;
    char email_local[50], senha_local[20], usuario_fixo_nome[40], usuario_fixo_email[40], usuario_fixo_senha[15];
    
    strcpy(usuario_fixo_nome, "Joao");
	strcpy(usuario_fixo_email, "joao@email.com"); 
	strcpy(usuario_fixo_senha, "1234");

    do {
        system("cls");
        printf("\n============= LOGIN =============");
        printf("\n1 - Entrar");
        printf("\n2 - Voltar");
        printf("\nEscolha: ");
        if (scanf("%d", &escolha) != 1) { while (getchar()!='\n'); escolha = -1; }

        if (escolha == 1) {
            system("cls");
            printf("\nEmail: ");
            scanf("%s", email_local);
            printf("Senha: ");
            scanf("%s", senha_local);

            if (usuario_cadastrado == 1 && strcmp(email_local, email_usuario) == 0 && strcmp(senha_local, senha_usuario) == 0) {
                printf("\nBem-vindo, %s!\n", nome_usuario);
                system("pause");
                menuUsuario();
                return;
            } else if (strcmp(email_local, usuario_fixo_email) == 0 && strcmp(senha_local, usuario_fixo_senha) == 0) {
                printf("\nBem-vindo, %s!\n", usuario_fixo_nome);
                system("pause");
                strcpy(nome_usuario, usuario_fixo_nome);
                strcpy(email_usuario, usuario_fixo_email);
                strcpy(senha_usuario, usuario_fixo_senha);
                usuario_cadastrado = 1;
                telefone_usuario[0] = '\0';
                endereco_usuario[0] = '\0';
                recebe_publicidade_usuario = 1;
                menuUsuario();
                return;
            } else {
                printf("\nEmail ou senha incorretos!\n");
                system("pause");
            }
        }
    } while (escolha != 2);
}

/* ===========================
   ADMIN: CRUD DO CARDÁPIO + ESTOQUE
   =========================== */

void login_adm() {
    char usuario[20], senha[20];
    int usuario_ok, senha_ok;
    int opcao;

    strcpy(usuario, "admin");
    strcpy(senha, "123");

    do {
        system("cls");
        printf("=== LOGIN ADM ===\n");

        printf("\nUsuario: ");
        scanf("%s", usuario);
        printf("Senha: ");
        scanf("%s", senha);

        usuario_ok = strcmp(usuario, "admin");
        senha_ok = strcmp(senha, "123");

        if (usuario_ok == 0 && senha_ok == 0) {
            printf("\nLogin ADM realizado com sucesso!\n");
            system("pause");
            /* garante que estamos administrando o restaurante correto (único) */
            pagina_restaurante_admin();
            return;
        } else {
            printf("\nUsuario ou senha incorretos!\n");
            printf("\nDeseja tentar novamente?\n");
            printf("1 - Sim\n2 - Voltar para a pagina inicial\nEscolha: ");
            scanf("%d", &opcao);
            if (opcao == 2) return;
        }
    } while (1);
}

void pagina_restaurante_admin() {
    int opcao;
    do {
        system("cls");
        printf("=== ADMIN - %s ===\n", restaurante.nome);
        printf("1 - Ver cardapio\n");
        printf("2 - Adicionar prato\n");
        printf("3 - Editar prato\n");
        printf("4 - Excluir prato\n");
        printf("5 - Ajustar estoque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) { while (getchar()!='\n'); opcao = -1; }

        switch (opcao) {
            case 1:
                admin_ver_cardapio_admin();
                break;
            case 2:
                admin_adicionar_prato();
                break;
            case 3:
                admin_editar_prato();
                break;
            case 4:
                admin_excluir_prato();
                break;
            case 5:
                admin_ajustar_estoque();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    } while (1);
}

void admin_ver_cardapio_admin() {
    system("cls");
    printf("=== CARDÁPIO (ADMIN) - %s ===\n", restaurante.nome);
    if (restaurante.qtdProdutos == 0) {
        printf("Nenhum prato cadastrado.\n");
    } else {
        for (int i = 0; i < restaurante.qtdProdutos; i++) {
            Produto *p = &restaurante.cardapio[i];
            printf("%d - %s | R$ %.2f | Estoque: %d\n   %s\n", i+1, p->nome, p->preco, p->estoque, p->descricao);
        }
    }
    system("pause");
}

void admin_adicionar_prato() {
    if (restaurante.qtdProdutos >= 20) {
        printf("Limite de pratos atingido (20).\n");
        system("pause");
        return;
    }
    Produto *p = &restaurante.cardapio[restaurante.qtdProdutos];

    getchar(); /* limpar newline */
    printf("Nome do prato: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Descricao: ");
    fgets(p->descricao, sizeof(p->descricao), stdin);
    p->descricao[strcspn(p->descricao, "\n")] = '\0';

    printf("Preco (use . como decimal): ");
    scanf("%f", &p->preco);

    printf("Quantidade em estoque: ");
    scanf("%d", &p->estoque);

    restaurante.qtdProdutos++;
    printf("\nPrato adicionado com sucesso!\n");
    system("pause");
}

void admin_editar_prato() {
    int idx;
    admin_ver_cardapio_admin();
    if (restaurante.qtdProdutos == 0) return;
    printf("Digite o numero do prato a editar: ");
    scanf("%d", &idx);
    if (idx < 1 || idx > restaurante.qtdProdutos) {
        printf("Indice invalido.\n");
        system("pause");
        return;
    }
    Produto *p = &restaurante.cardapio[idx - 1];
    getchar();
    printf("Novo nome (enter para manter): ");
    char buf[200];
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strncpy(p->nome, buf, sizeof(p->nome)-1);
        p->nome[sizeof(p->nome)-1] = '\0';
    }
    printf("Nova descricao (enter para manter): ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strncpy(p->descricao, buf, sizeof(p->descricao)-1);
        p->descricao[sizeof(p->descricao)-1] = '\0';
    }
    printf("Novo preco (0 para manter): ");
    float novo_preco;
    if (scanf("%f", &novo_preco) == 1 && novo_preco > 0) p->preco = novo_preco;
    printf("Novo estoque (-1 para manter): ");
    int novo_estoque;
    if (scanf("%d", &novo_estoque) == 1 && novo_estoque >= 0) p->estoque = novo_estoque;
    printf("\nPrato atualizado.\n");
    system("pause");
}

void admin_excluir_prato() {
    int idx;
    admin_ver_cardapio_admin();
    if (restaurante.qtdProdutos == 0) return;
    printf("Digite o numero do prato a excluir: ");
    scanf("%d", &idx);
    if (idx < 1 || idx > restaurante.qtdProdutos) {
        printf("Indice invalido.\n");
        system("pause");
        return;
    }
    /* shift left para remover */
    for (int i = idx - 1; i < restaurante.qtdProdutos - 1; i++) {
        restaurante.cardapio[i] = restaurante.cardapio[i+1];
    }
    restaurante.qtdProdutos--;
    printf("Prato excluido.\n");
    system("pause");
}

void admin_ajustar_estoque() {
    int idx;
    admin_ver_cardapio_admin();
    if (restaurante.qtdProdutos == 0) return;
    printf("Digite o numero do prato para ajustar estoque: ");
    scanf("%d", &idx);
    if (idx < 1 || idx > restaurante.qtdProdutos) {
        printf("Indice invalido.\n");
        system("pause");
        return;
    }
    Produto *p = &restaurante.cardapio[idx - 1];
    printf("Estoque atual de '%s': %d\n", p->nome, p->estoque);
    printf("Novo estoque: ");
    int novo;
    scanf("%d", &novo);
    if (novo >= 0) p->estoque = novo;
    printf("Estoque atualizado.\n");
    system("pause");
}

/* ===========================
   USUÁRIO: visualizar restaurantes/cardápio/detalhes
   =========================== */

void menuUsuario() {
    int opc;
    do {
        system("cls");
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1 - Ver Restaurantes\n");
        printf("2 - Minha conta\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { while (getchar() != '\n'); opc = -1; }
        
		if (opc == 2) {
            menuContaUsuario();
            continue; 
        }

        if (opc == 1) listarRestaurantes();
        else if (opc == 0) return;
        else {
            printf("\nOpcao invalida!\n");
            system("pause");
        }
    } while (1);
}

void menuContaUsuario() {
    int opc;
    do {
        system("cls");
        printf("\n--- MINHA CONTA ---\n");
        printf("1 - Informacoes do usuario\n");      
        printf("2 - Editar informacoes\n");          
        printf("3 - Editar dados de contato\n");     
        printf("4 - Credenciais (senha)\n");         
        printf("5 - Publicidade\n");                 
        printf("0 - Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { while (getchar() != '\n'); opc = -1; }

        switch (opc) {
            case 1:
                mostrarInformacoesUsuario();
                break;
            case 2:
                editarInformacoesUsuario();
                break;
            case 3:
                editarContatoUsuario();
                break;
            case 4:
                editarCredenciaisUsuario();
                break;
            case 5:
                configurarPublicidadeUsuario();
                break;
            case 0:
                return;
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }
    } while (1);
}

/* =========================
	Informacoes - usuario 
   =========================*/
void mostrarInformacoesUsuario() {
    if (!usuario_cadastrado) {
        printf("\nNenhum usuario cadastrado/logado no sistema.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("\n=== INFORMACOES DO USUARIO ===\n");
    printf("Nome: %s\n", nome_usuario);
    printf("Email: %s\n", email_usuario);

    if (telefone_usuario[0] != '\0')
        printf("Telefone: %s\n", telefone_usuario);
    else
        printf("Telefone: nao informado\n");

    if (endereco_usuario[0] != '\0')
        printf("Endereco: %s\n", endereco_usuario);
    else
        printf("Endereco: nao informado\n");

    printf("Recebe publicidade: %s\n", recebe_publicidade_usuario ? "Sim" : "Nao");

    system("pause");
}

/* =======================================
	Editar informacoes (nome e endereco) 
   =======================================*/
void editarInformacoesUsuario() {
    if (!usuario_cadastrado) {
        printf("\nNenhum usuario cadastrado/logado.\n");
        system("pause");
        return;
    }

    char buf[200];

    system("cls");
    printf("\n=== EDITAR INFORMACOES ===\n");
    printf("Nome atual: %s\n", nome_usuario);
    printf("Novo nome (enter para manter): ");

    getchar(); /* limpar o \n que sobrou do scanf */
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(nome_usuario, buf);
    }

    printf("Endereco atual: %s\n", (endereco_usuario[0] != '\0') ? endereco_usuario : "Nao informado");
    printf("Novo endereco (enter para manter): ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(endereco_usuario, buf);
    }

    printf("\nInformacoes atualizadas com sucesso!\n");
    system("pause");
}

/* =============================================
	Editar dados de contato (email e telefone)
   ============================================= */
void editarContatoUsuario() {
    if (!usuario_cadastrado) {
        printf("\nNenhum usuario cadastrado/logado.\n");
        system("pause");
        return;
    }

    char buf[200];

    system("cls");
    printf("\n=== EDITAR CONTATO ===\n");
    printf("Email atual: %s\n", email_usuario);
    printf("Novo email (enter para manter): ");

    getchar(); /* limpar \n do scanf anterior */
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(email_usuario, buf);
    }

    printf("Telefone atual: %s\n", (telefone_usuario[0] != '\0') ? telefone_usuario : "Nao informado");
    printf("Novo telefone (enter para manter): ");
    fgets(buf, sizeof(buf), stdin);
    if (buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        strcpy(telefone_usuario, buf);
    }

    printf("\nDados de contato atualizados com sucesso!\n");
    system("pause");
}

/* ================================= 
	Credenciais (alterar senha) 
   =================================*/
void editarCredenciaisUsuario() {
    if (!usuario_cadastrado) {
        printf("\nNenhum usuario cadastrado/logado.\n");
        system("pause");
        return;
    }

    char senhaAtual[20], novaSenha[20], confirma[20];

    system("cls");
    printf("\n=== CREDENCIAIS ===\n");
    printf("Digite a senha atual: ");
    scanf("%19s", senhaAtual);

    if (strcmp(senhaAtual, senha_usuario) != 0) {
        printf("\nSenha incorreta!\n");
        system("pause");
        return;
    }

    printf("Nova senha: ");
    scanf("%19s", novaSenha);
    printf("Confirmar nova senha: ");
    scanf("%19s", confirma);

    if (strcmp(novaSenha, confirma) != 0) {
        printf("\nAs senhas nao conferem. Nenhuma alteracao foi feita.\n");
        system("pause");
        return;
    }

    strcpy(senha_usuario, novaSenha);
    printf("\nSenha alterada com sucesso!\n");
    system("pause");
}

/* =======================================
	Publicidade (receber ou nao ofertas) 
   =======================================*/
void configurarPublicidadeUsuario() {
    if (!usuario_cadastrado) {
        printf("\nNenhum usuario cadastrado/logado.\n");
        system("pause");
        return;
    }

    int opc;

    system("cls");
    printf("\n=== PUBLICIDADE ===\n");
    printf("Status atual: %s\n", recebe_publicidade_usuario ? "Recebendo ofertas" : "Nao recebe ofertas");
    printf("1 - Quero receber ofertas e novidades\n");
    printf("2 - Nao quero receber publicidade\n");
    printf("0 - Voltar\n");
    printf("Escolha: ");
    if (scanf("%d", &opc) != 1) { while (getchar() != '\n'); opc = -1; }

    if (opc == 1) {
        recebe_publicidade_usuario = 1;
        printf("\nVoce passara a receber ofertas e novidades.\n");
    } else if (opc == 2) {
        recebe_publicidade_usuario = 0;
        printf("\nVoce nao recebera mais publicidade.\n");
    }

    system("pause");
}

void listarRestaurantes() {
    int opc;
    system("cls");
    printf("\n--- RESTAURANTES ---\n");
    printf("1 - %s\n", restaurante.nome);
    printf("0 - Voltar\nEscolha: ");
    if (scanf("%d", &opc) != 1) { while (getchar()!='\n'); opc = -1; }

    if (opc == 1) verCardapioUsuario();
    else if (opc == 0) return;
    else {
        printf("\nOpcao invalida!\n");
        system("pause");
        listarRestaurantes();
    }
}

void verCardapioUsuario() {
    system("cls");
    printf("\n--- CARDAPIO: %s ---\n", restaurante.nome);

    int mostrados = 0;
    for (int i = 0; i < restaurante.qtdProdutos; i++) {
        Produto *p = &restaurante.cardapio[i];
        if (p->estoque <= 0) continue; /* não mostra itens sem estoque */
        mostrados++;
        printf("%d - %s (R$ %.2f) | Estoque: %d\n", i + 1, p->nome, p->preco, p->estoque);
    }

    if (mostrados == 0) {
        printf("\nNenhum item disponivel no momento.\n");
        system("pause");
        return;
    }

    /* === NOVO: opção direta para acessar o carrinho === */
    printf("\nC - Ver carrinho");

    printf("\n0 - Voltar");
    printf("\nEscolha um item para ver detalhes: ");

    char entrada[10];
    scanf("%s", entrada);

    /* se usuário digitar C ou c  ver carrinho */
    if (strcmp(entrada, "C") == 0 || strcmp(entrada, "c") == 0) {
        montarCarrinho();
        verCardapioUsuario();
        return;
    }
    
    int opc = atoi(entrada);

    if (opc == 0) return;
    if (opc < 1 || opc > restaurante.qtdProdutos) {
        printf("Opcao invalida!\n");
        system("pause");
        verCardapioUsuario();
        return;
    }
    if (restaurante.cardapio[opc - 1].estoque <= 0) {
        printf("Item sem estoque.\n");
        system("pause");
        verCardapioUsuario();
        return;
    }

    detalhesProdutoUsuario(opc - 1);
}

void detalhesProdutoUsuario(int idx) {
    Produto *p = &restaurante.cardapio[idx];
    int opc;
    system("cls");
    printf("\n--- DETALHES DO PRODUTO ---\n");
    printf("Nome: %s\n", p->nome);
    printf("Descricao: %s\n", p->descricao);
    printf("Preco: R$ %.2f\n", p->preco);
    printf("Estoque disponivel: %d\n", p->estoque);

    printf("\nO que deseja fazer?");
    printf("\n1 - Adicionar ao carrinho");
    printf("\n2 - Ir para o carrinho (heloisa)");
    printf("\n0 - Voltar\nEscolha: ");
    if (scanf("%d", &opc) != 1) { while (getchar()!='\n'); opc = -1; }

    if (opc == 1) {
        int qtd;
        printf("Quantidade (max %d): ", p->estoque);
        if (scanf("%d", &qtd) != 1) { while (getchar()!='\n'); qtd = 0; }
        if (qtd <= 0) {
            printf("Quantidade invalida.\n");
            system("pause");
            detalhesProdutoUsuario(idx);
            return;
        }
        if (qtd > p->estoque) {
            printf("Quantidade superior ao estoque.\n");
            system("pause");
            detalhesProdutoUsuario(idx);
            return;
        }

        /* adiciona ao carrinho; se já existir o mesmo produto no carrinho, soma quantidade */
        int achou = 0;
        for (int i = 0; i < tamanhoCarrinho; i++) {
            if (carrinho[i].produto_index == idx) {
                carrinho[i].quantidade += qtd;
                achou = 1;
                break;
            }
        }
        if (!achou) {
            strncpy(carrinho[tamanhoCarrinho].nome, p->nome, sizeof(carrinho[tamanhoCarrinho].nome)-1);
            carrinho[tamanhoCarrinho].preco = p->preco;
            carrinho[tamanhoCarrinho].quantidade = qtd;
            carrinho[tamanhoCarrinho].produto_index = idx;
            tamanhoCarrinho++;
        }

        /* reserva estoque imediatamente */
        p->estoque -= qtd;
        printf("\n%s (x%d) adicionado ao carrinho.\n", p->nome, qtd);
        system("pause");
        verCardapioUsuario();
        return;
    }
    else if (opc == 2) {
        montarCarrinho();
        verCardapioUsuario();
        return;
    }
    else if (opc == 0) {
        verCardapioUsuario();
        return;
    }
    else {
        printf("Opcao invalida!\n");
        system("pause");
        detalhesProdutoUsuario(idx);
        return;
    }
}

/* ===========================
   CARRINHO / PAGAMENTO / STATUS
   =========================== */

void montarCarrinho() {
    int opc;

    do {
        system("cls");
        printf("\n=== CARRINHO ===\n");
        mostrarCarrinho();
        printf("\n1 - Remover item\n2 - Finalizar compra\n0 - Voltar\nEscolha: ");
        if (scanf("%d", &opc) != 1) { while (getchar()!='\n'); opc = -1; }

        if (opc == 1) {
            removerItemCarrinho();
        } else if (opc == 2) {
            if (tamanhoCarrinho == 0) {
                printf("\nCarrinho vazio. Adicione itens antes de finalizar.\n");
                system("pause");
                continue;
            }
            /* calcular total */
            float total = 0;
            for (int i = 0; i < tamanhoCarrinho; i++)
                total += carrinho[i].preco * carrinho[i].quantidade;

            printf("\nTotal: R$ %.2f\n", total);
            int metodo = escolherPagamento();
            switch (metodo) {
                case 1: pagamentoCartao(); break;
                case 2: pagamentoPix(); break;
                case 3: pagamentoDinheiro(total); break;
                default:
                    printf("Metodo invalido.\n");
                    system("pause");
                    continue;
            }
            confirmarPedido();
            statusEntrega();
            /* Ao confirmar, o estoque já foi reduzido ao adicionar ao carrinho.
               Aqui apenas limpamos o carrinho (itens efetivamente vendidos). */
            tamanhoCarrinho = 0;
            return;
        } else if (opc == 0) {
            return;
        } else {
            printf("Opcao invalida!\n");
            system("pause");
        }

    } while (1);
}

void mostrarCarrinho() {
    if (tamanhoCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }
    float total = 0;
    for (int i = 0; i < tamanhoCarrinho; i++) {
        printf("%d. %s - R$ %.2f x %d = R$ %.2f\n",
               i+1,
               carrinho[i].nome,
               carrinho[i].preco,
               carrinho[i].quantidade,
               carrinho[i].preco * carrinho[i].quantidade);
        total += carrinho[i].preco * carrinho[i].quantidade;
    }
    printf("Total: R$ %.2f\n", total);
}

/* remover item: restaura estoque ao remover */
void removerItemCarrinho() {
    if (tamanhoCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        system("pause");
        return;
    }
    mostrarCarrinho();
    printf("\nDigite o numero do item a remover: ");
    int idx;
    if (scanf("%d", &idx) != 1) { while (getchar()!='\n'); idx = -1; }
    if (idx < 1 || idx > tamanhoCarrinho) {
        printf("Indice invalido.\n");
        system("pause");
        return;
    }
    idx = idx - 1;
    /* restaurar estoque */
    int produto_idx = carrinho[idx].produto_index;
    if (produto_idx >=0 && produto_idx < restaurante.qtdProdutos) {
        restaurante.cardapio[produto_idx].estoque += carrinho[idx].quantidade;
    }
    /* shift left */
    for (int i = idx; i < tamanhoCarrinho - 1; i++) {
        carrinho[i] = carrinho[i+1];
    }
    tamanhoCarrinho--;
    printf("Item removido e estoque restaurado.\n");
    system("pause");
}

/* ===========================
   PAGAMENTO / STATUS (simples)
   =========================== */

int escolherPagamento() {
    int opcao;
    printf("\n=== MÉTODO DE PAGAMENTO ===\n");
    printf("1 - Cartao\n");
    printf("2 - Pix\n");
    printf("3 - Dinheiro\n");
    printf("Escolha uma opcao: ");
    if (scanf("%d", &opcao) != 1) { while (getchar()!='\n'); opcao = -1; }
    return opcao;
}

void pagamentoCartao() {
    char nomeTitular[50];
    char numero[20], validade[10], cvv[5];

    printf("\n=== PAGAMENTO COM CARTAO ===\n");
    getchar(); /* limpar newline */
    printf("Nome completo do titular: ");
    fgets(nomeTitular, sizeof(nomeTitular), stdin);
    nomeTitular[strcspn(nomeTitular, "\n")] = '\0';
    printf("Numero do cartao: ");
    scanf("%s", numero);
    printf("Validade (MM/AA): ");
    scanf("%s", validade);
    printf("CVV: ");
    scanf("%s", cvv);
    printf("\nPagamento aprovado!\n");
    system("pause");
}

void pagamentoPix() {
    printf("\n=== PAGAMENTO COM PIX ===\n");
    printf("Chave Pix: Chicken.friends_ofc@gmail.com\n");
    printf("Escaneie o QR Code no app do seu banco.\n\n");
    
    	
	printf("@@@@@@@:..*=*@#:-@:@@@@@@@\n");
	printf("@=**+-@: :=:=  ++@:@-+**=@\n");
	printf("@*@@#-@: @#   -*:=:@-*@@+@\n");
	printf("@@@@@@@: *-*@@* *@:@@@@@@@\n");
	printf("   ::  :   @@+..:-@::    :\n");
	printf("+---=#    # +#+   -:#--   \n");
	printf("@#  :+*+@-+--  # +   @#  #\n");
	printf("+    :+@@@*  --    ++   #*\n");
	printf("=         *@*   *@#:    =*\n");
	printf("=*@*   :@ *@+.::   @ @   :\n");
	printf("@@@@@@@ @--::*@*=   -*@@*#\n");
	printf("@=##+-@:*  +#@@   @ *++\n");
	printf("@*@@#-@: *:=+-.:++*  +:+  \n");
	printf("@@@@@@@:   @+:=@   @@@@+:+\n");
	printf("\n");
	printf("\n");

    getchar();
    printf("Pagamento confirmado!\n");
    system("pause");
}

void pagamentoDinheiro(float total) {
    float valor = 0;
    printf("\n=== PAGAMENTO EM DINHEIRO ===\n");
    do {
        printf("Informe o valor entregue: R$");
        if (scanf("%f", &valor) != 1) { while (getchar()!='\n'); valor = 0; }
        if (valor < total) {
            printf("Valor insuficiente! Total da compra: R$%.2f\n", total);
            printf("Por favor, informe outro valor.\n\n");
        }
    } while (valor < total);
    printf("Troco: R$%.2f\n", valor - total);
    printf("Pagamento confirmado!\n");
    system("pause");
}

void confirmarPedido() {
    printf("\nPedido confirmado! O restaurante esta preparando seu pedido...\n");
    system("pause");
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
				printf("Status: Pedido em preparacao.\n"); 
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
            printf("Pressione ENTER para ver o proximo status...\n");
            getchar();
        }
    }
    system("pause");
}
