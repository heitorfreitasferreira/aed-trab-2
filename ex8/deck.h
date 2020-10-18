typedef struct deque *Deque;
//Metodos das estruturas
Deque cria_Deque();
int deque_vazio(Deque);
int push(Deque, float);    //insert end
int pop(Deque, float *);   //remove end
int shift(Deque, float *); //remove beg
int unshift(Deque, float); //insert beg
int libera_deque(Deque *); //apaga tudo
