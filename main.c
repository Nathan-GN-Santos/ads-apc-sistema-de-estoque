//EXECUTAR
//.\main.exe

//Dicionário
//Funções Nativas do C:
// scanf = scan formatted, função que lê dados do teclado e  salva em uma variável.
// fgets = file get string ,função que lê uma linha de texto do teclado e salva em uma variável do tipo string.

//Especificadores:
// %d = inteiro decimal

//CÓDIGO
#include <stdio.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"

int main() {
    // Configura a saída e entrada do console do Windows para a página de código UTF-8 (65001)
    //SetConsoleOutputCP(65001);
    //SetConsoleCP(65001);

    int opcao = 0;
    int opcaoCat = 0;

    Categoria listaCategorias[CAPACIDADE_CATEGORIAS];
    int totalCategorias = 0;

    Produto listaProdutos[CAPACIDADE]; // Vetor com capacidade para 50 produtos
    int totalProdutos = 0;             // Contador de produtos cadastrados

    // Carregar dados salvos nos arquivos ao iniciar o programa (Requisito da Tarefa 4)
    totalCategorias = carregarCategoriasArquivo(listaCategorias);
    totalProdutos = carregarProdutosArquivo(listaProdutos);

    do {
        // Exibição do Menu Principal conforme exigido na Tarefa 4
        printf("\n====================================\n");
        printf("       SISTEMA DE ESTOQUE - MENU    \n");
        printf("====================================\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Categorias\n");
        printf("5 - Sair\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
               	totalProdutos = cadastrarProduto(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
    			salvarProdutosArquivo(listaProdutos, totalProdutos);
   				 break;

            case 2:
                listarProdutos(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                break;

            case 3:
                pesquisarProduto(listaProdutos, totalProdutos, listaCategorias, totalCategorias);
                break;

            case 4:
                // Submenu de Categorias (Requisito da Tarefa 4)
                do {
                    printf("\n------------------------------------\n");
                    printf("       SUBMENU - CATEGORIAS         \n");
                    printf("------------------------------------\n");
                    printf("1 - Cadastrar Categoria\n");
                    printf("2 - Listar Categoria\n");
                    printf("3 - Voltar\n");
                  	opcaoCat = lerInteiro("Escolha uma opcao: ");

                    switch (opcaoCat) {
                        case 1: // dentro do submenu
    						totalCategorias = cadastrarCategoria(listaCategorias, totalCategorias);
    						salvarCategoriasArquivo(listaCategorias, totalCategorias);
    						break;
                        case 2:
                            listarCategorias(listaCategorias, totalCategorias);
                            break;
                        case 3:
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        default:
                            printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 3.\n");
                            break;
                    }
                } while (opcaoCat != 3);
                break;

            case 5:
                salvarCategoriasArquivo(listaCategorias, totalCategorias);
                salvarProdutosArquivo(listaProdutos, totalProdutos);
                printf("\nDados salvos com sucesso. Saindo do sistema...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 5.\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}