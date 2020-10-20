typedef struct fila *Fila;

Fila cria_fila();
int fila_vazia(Fila fila);
int insere_fim(Fila fila, char *nome, int vol, float preco);
int remove_ini(Fila fila, char *nome, int *vol, float *preco);
int esvazia_fila(Fila fila);
int apaga_fila(Fila *fila);
