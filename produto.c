#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"    
#include "util.h"

//Auxiliar
static int prateleiraValida(char p) {
    return p == 'A' || p == 'B' || p == 'C' || p == 'D';
}

// Regra de disponibilidade
static int calcularDisponivel(int quantidade) {
    return quantidade > 0 ? 1 : 0;
}

// Conta quantos produtos est�o ativos
static int contarAtivos(Produto lista[], int total) {
    int n = 0;
    for (int i = 0; i < total; i++) {
        if (lista[i].ativo == 1) n++;
    }
    return n;
}

// Busca por c�digo apenas entre produtos ativos (devolve -1 se n�o achar ou se estiver removido)
static int buscarAtivoPorCodigo(Produto lista[], int total, int codigo) {
    int pos = buscarPorCodigo(lista, total, codigo);
    if (pos != -1 && lista[pos].ativo == 1) return pos;
    return -1;
}

// Exibir os dados de um Ãºnico produto (recebe uma struct Produto).
void exibirProduto(Produto prod, Categoria categorias[], int totalCat) {
    char nomeCategoria[30] = "Desconhecida";
    int posCat = buscarCategoriaPorCodigo(categorias, totalCat, prod.codigoCategoria);
    if (posCat != -1) {
        strcpy(nomeCategoria, categorias[posCat].nome);
    }

    printf("\n====================================\n");
    printf("Codigo:              %d\n", prod.codigo);
    printf("Nome:                %s\n", prod.nome);
    printf("Categoria:           %s (Cod: %d)\n", nomeCategoria, prod.codigoCategoria);
    printf("Prateleira:          %c\n", prod.prateleira);
    printf("Preco Unitario:      R$ %.2f\n", prod.preco);
    printf("Qtd em Estoque:      %d\n", prod.quantidade);
    printf("Disponivel P/ Venda: %s (%d)\n", 
            prod.disponivel == 1 ? "SIM" : "NAO", prod.disponivel);
    printf("====================================\n");
}

// 1. Buscar um produto pelo codigo (devolve a posicao dele na lista, ou -1 se nao achar).
int buscarPorCodigo(Produto lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i; // Retorna o Ã­ndice onde o produto foi encontrado
        }
    }
    return -1; // Retorna -1 indicando que nÃ£o foi encontrado
}

// 2. Funco de buscar um produto pelo nome (devolve a posicao na lista, ou -1 se nao achar).
int buscarPorNome(Produto lista[], int total, const char *nome) {
    for (int i = 0; i < total; i++) {
        if (lista[i].ativo == 1 && strcmp(lista[i].nome, nome) == 0) {
            return i; 
        }
    }
    return -1; 
}

// 3. Funcao de cadastrar um produto na lista.
int cadastrarProduto(Produto lista[], int total, Categoria categorias[], int totalCat) {
    if (totalCat == 0) {
        printf("\n[ERRO] Cadastre ao menos uma categoria antes de cadastrar produtos!\n");
        return total;
    }
    if (total >= CAPACIDADE) {
        printf("\n[ERRO] A lista de produtos esta cheia (limite de %d produtos)!\n", CAPACIDADE);
        return total;
    }

    Produto prod;
    printf("\n--- CADASTRO DE PRODUTO ---\n");

    listarCategorias(categorias, totalCat);
    do {
        prod.codigoCategoria = lerInteiro("Digite o Codigo da Categoria do produto: ");
        if (buscarCategoriaPorCodigo(categorias, totalCat, prod.codigoCategoria) == -1) {
            printf("[ERRO] Categoria nao encontrada!\n");
        }
    } while (buscarCategoriaPorCodigo(categorias, totalCat, prod.codigoCategoria) == -1);

    do {
        prod.codigo = lerInteiro("Digite o Codigo do produto (inteiro positivo): ");
        if (!ehPositivoInt(prod.codigo)) {
            printf("[ERRO] Codigo invalido! Deve ser maior que zero.\n");
        } else if (buscarPorCodigo(lista, total, prod.codigo) != -1) {
            printf("[ERRO] Codigo ja cadastrado! Digite um codigo diferente.\n");
        }
    } while (!ehPositivoInt(prod.codigo) || buscarPorCodigo(lista, total, prod.codigo) != -1);

    do {
        lerTexto("Digite o Nome do produto: ", prod.nome, sizeof(prod.nome));
        if (!textoPreenchido(prod.nome)) {
            printf("[ERRO] O nome nao pode ficar em branco!\n");
        }
    } while (!textoPreenchido(prod.nome));

    do {
        prod.prateleira = toupper((unsigned char)lerCaractere("Digite a Prateleira ('A', 'B', 'C' ou 'D'): "));
        if (!prateleiraValida(prod.prateleira)) {
            printf("[ERRO] Prateleira invalida! Escolha apenas A, B, C ou D.\n");
        }
    } while (!prateleiraValida(prod.prateleira));

    do {
        prod.preco = lerFloat("Digite o Preco unitario: ");
        if (!ehPositivoFloat(prod.preco)) {
            printf("[ERRO] Preco invalido! Deve ser maior que zero.\n");
        }
    } while (!ehPositivoFloat(prod.preco));

    do {
        prod.quantidade = lerInteiro("Digite a Quantidade em estoque: ");
        if (!ehNaoNegativo(prod.quantidade)) {
            printf("[ERRO] Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (!ehNaoNegativo(prod.quantidade));

  	prod.disponivel = calcularDisponivel(prod.quantidade);
    prod.ativo = 1;

    lista[total] = prod;
    printf("\n[SUCESSO] Produto cadastrado com sucesso!\n");
    exibirProduto(prod, categorias, totalCat);
    return total + 1;
}

// Listar todos os produtos da lista.
void listarProdutos(Produto lista[], int total, Categoria categorias[], int totalCat) {
    if (contarAtivos(lista, total) == 0) {
        printf("\n[AVISO] Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE PRODUTOS ===\n");
    for (int i = 0; i < total; i++) {
        if (lista[i].ativo == 1) {
            exibirProduto(lista[i], categorias, totalCat);
        }
    }
}

// FunÃ§Ã£o auxiliar para o sub-menu de pesquisa
void pesquisarProduto(Produto lista[], int total, Categoria categorias[], int totalCat) {
  	if (contarAtivos(lista, total) == 0) {
        printf("\n[AVISO] Nenhum produto cadastrado para pesquisar.\n");
        return;
    }

    int opcaoBusca;
    printf("\n--- PESQUISAR PRODUTO ---\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
	opcaoBusca = lerInteiro("Escolha o tipo de busca: ");

    if (opcaoBusca == 1) {
        int codigoBusca;
        codigoBusca =lerInteiro("Digite o codigo que deseja buscar: ");

        int pos = buscarAtivoPorCodigo(lista, total, codigoBusca);
        if (pos != -1) {
            printf("\n[SUCESSO] Produto encontrado!");
            exibirProduto(lista[pos], categorias, totalCat);
        } else {
            printf("\n[ERRO] Nenhum produto encontrado com o codigo informado.\n");
        }
    } else if (opcaoBusca == 2) {
        char nomeBusca[50];
       	lerTexto("Digite o nome que deseja buscar: ", nomeBusca, sizeof(nomeBusca));

        int pos = buscarPorNome(lista, total, nomeBusca);
        if (pos != -1) {
            printf("\n[SUCESSO] Produto encontrado!");
            exibirProduto(lista[pos], categorias, totalCat);
        } else {
            printf("\n[ERRO] Nenhum produto encontrado com o nome informado.\n");
        }
    } else {
        printf("\n[ERRO] Opcao de busca invalida!\n");
    }
}

// Registra entrada ou saida no estoque de um produto
void alterarEstoque(Produto lista[], int total, Categoria categorias[], int totalCat) {
    if (contarAtivos(lista, total) == 0) {
        printf("\n[AVISO] Nenhum produto cadastrado para alterar.\n");
        return;
    }

    printf("\n--- ALTERAR ESTOQUE ---\n");
    int codigo = lerInteiro("Digite o codigo do produto: ");
    int pos = buscarAtivoPorCodigo(lista, total, codigo);
    if (pos == -1) {
        printf("\n[ERRO] Produto com codigo %d nao encontrado!\n", codigo);
        return;                                  
    }

    printf("\nProduto: %s | Estoque atual: %d\n", lista[pos].nome, lista[pos].quantidade);
    printf("1 - Entrada (chegada de mercadoria)\n");
    printf("2 - Saida (venda ou retirada)\n");

    int tipo;
    do {
        tipo = lerInteiro("Escolha o tipo de movimentacao: ");
        if (tipo != 1 && tipo != 2) {
            printf("[ERRO] Opcao invalida! Escolha 1 ou 2.\n");
        }
    } while (tipo != 1 && tipo != 2);

    int qtd;
    do {
        qtd = lerInteiro("Digite a quantidade: ");
        if (!ehPositivoInt(qtd)) {
            printf("[ERRO] A quantidade deve ser maior que zero.\n");
        }
    } while (!ehPositivoInt(qtd));

    if (tipo == 1) {
        lista[pos].quantidade += qtd;
    } else {
        if (qtd > lista[pos].quantidade) {
            printf("\n[ERRO] Saida maior que o estoque atual (%d). Operacao cancelada.\n",
                   lista[pos].quantidade);
            return;                               
        }
        lista[pos].quantidade -= qtd;
    }

    lista[pos].disponivel = calcularDisponivel(lista[pos].quantidade);

    printf("\n[SUCESSO] Estoque atualizado!\n");
    exibirProduto(lista[pos], categorias, totalCat);
}

// PersistÃªncia: Salvar produtos em arquivo de texto
void salvarProdutosArquivo(Produto lista[], int total) {
    FILE *file = fopen("produtos.txt", "w");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%d\n", total);
    for (int i = 0; i < total; i++) {
        fprintf(file, "%d\n%s\n%c\n%.2f\n%d\n%d\n%d\n%d\n",
        	lista[i].codigo,
        	lista[i].nome,
        	lista[i].prateleira,
        	lista[i].preco,
	        lista[i].quantidade,
	        lista[i].disponivel,
        	lista[i].codigoCategoria,
       		lista[i].ativo);
    }
    fclose(file);
}

void removerProduto(Produto lista[], int total) {
    if (contarAtivos(lista, total) == 0) {
        printf("\n[AVISO] Nenhum produto cadastrado para remover.\n");
        return;
    }

    printf("\n--- REMOVER PRODUTO ---\n");
    int codigo = lerInteiro("Digite o codigo do produto que deseja remover: ");
    int pos = buscarAtivoPorCodigo(lista, total, codigo);
    if (pos == -1) {
        printf("\n[ERRO] Produto com codigo %d nao encontrado!\n", codigo);
        return;
    }

    lista[pos].ativo = 0;     
    printf("\n[SUCESSO] Produto removido com sucesso!\n");
}

// PersistÃªncia: Carregar produtos do arquivo de texto
int carregarProdutosArquivo(Produto lista[]) {
    FILE *file = fopen("produtos.txt", "r");
    if (file == NULL) return 0;          

    int total = 0;
    if (fscanf(file, "%d", &total) != 1 || total < 0) {
        fclose(file);
        return 0;
    }
    if (total > CAPACIDADE) total = CAPACIDADE;

    int lidos = 0;
    for (int i = 0; i < total; i++) {
        Produto p;
        if (fscanf(file, "%d", &p.codigo) != 1) break;
        fgetc(file);                      // consome o '\n' depois do número
        if (fgets(p.nome, sizeof(p.nome), file) == NULL) break;
        p.nome[strcspn(p.nome, "\n")] = '\0';
        if (fscanf(file, " %c %f %d %d %d %d", &p.prateleira, &p.preco,
                   &p.quantidade, &p.disponivel, &p.codigoCategoria, &p.ativo) != 6) break;
        lista[lidos++] = p;
    }
    fclose(file);
    return lidos;
}
