#ifndef CATEGORIA_H
#define CATEGORIA_H



#define CAPACIDADE_CATEGORIAS 20 // Capacidade mÃ¡xima de categorias

typedef struct {
    int codigo;
    char nome[30];
} Categoria;

// FunÃ§Ãµes de Categoria
void exibirCategoria(Categoria cat);
int buscarCategoriaPorCodigo(Categoria lista[], int total, int codigo);
int buscarCategoriaPorNome(Categoria lista[], int total, const char *nome);
int cadastrarCategoria(Categoria lista[], int total);
void listarCategorias(Categoria lista[], int total);
void salvarCategoriasArquivo(Categoria lista[], int total);
int carregarCategoriasArquivo(Categoria lista[]);

#endif