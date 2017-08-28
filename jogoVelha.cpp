/*
	Representação de bola: 30
	Representação de X: 1
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;

struct Estado {
	string tab;
	int jogador;
	Estado() {}
	Estado(string tab, int jogador) :  tab(tab), jogador(jogador) {}
	bool operator < (const Estado &outro) const {
		return jogador <= outro.jogador;
	}
};

const int sizeTab = 3;
const int contGanhaBola = 30, contGanhaX = 3;
const int ganhaBola = 1, ganhaX = 2;
const int bola = 10, xis = 1;

map<Estado, Estado> utilidade;

int tab[sizeTab][sizeTab] = {{1, 1, 10},
														 {10, 1, 1},
														 {10, 10, 1}};

/*
	Verifica se nao existem mais casas para jogar
*/
bool impossivelJogar() {
	int cont;
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j]) cont++;
		}
	}
	return cont == sizeTab*sizeTab ? true : false;
}


/*
	Verifica se existe algum ganhador, caso nao exista retorna 0
*/
int verificaGanhador() {
	// verifica linhas e colunas
	for (int i = 0; i < sizeTab; i++) {
		int contLinha = 0, contColuna;
		for (int j = 0; j < sizeTab; j++) {
			contLinha += tab[i][j];
			contColuna += tab[j][i];
		}
		if (contLinha == contGanhaBola || contColuna == contGanhaBola) return ganhaBola;
		if (contLinha == contGanhaX || contColuna == contGanhaX) return ganhaX;
	}

	// verifica diagonais
	int contPrincipal = 0, contSecundaria = 0;
	for (int i = 0; i < sizeTab; i++) {
		contPrincipal += tab[i][i];
		contSecundaria += tab[i][sizeTab-i-1];
	}
	if (contPrincipal == contGanhaBola || contSecundaria == contGanhaBola) return ganhaBola;
	if (contPrincipal == contGanhaX || contSecundaria == contGanhaX) return ganhaX;

	return 0;
}

/*
	Muda o jogador da vez
*/
int trocaJogador(int jogador) {
	if (jogador == xis) return bola;
	return xis;
}


string criaEstado(int i = -1, int j = -1, int jogador) {
	// criar a string que representa o nosso tabuleiro
	
	// constroi a string atual
 
	if (i != -1) {

	}

	return "";
}

/*
	Imprime o tabuleiro atual
*/
void print() {
	puts("");
	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (tab[i][j] == bola) {
				printf("o ");
			} else if (tab[i][j] == xis){
				printf("x ");
			} else {
				printf(". ");
			}
		}puts("");
	}
}


/*
	Gera os estados com uma arvore de recursao
*/
int constroiTree(int jogador) {
	int resultado, iOtimo, jOtimo, estado;	
	print();
	
	estado = verificaGanhador();
	if (estado == ganhaBola) {
		cout << "O ganhou!!" << endl;
		return 1;
	}
	if (estado == ganhaX) {
		cout << "X ganhou!!" << endl;
		return -1;
	}
	if (impossivelJogar()) {
		return 0;
	}

	if (jogador == xis) {
		resultado = -1;
	} else {
		resultado = 1;
	}

	for (int i = 0; i < sizeTab; i++) {
		for (int j = 0; j < sizeTab; j++) {
			if (!tab[i][j]) {
				tab[i][j] = jogador;
				if (jogador == xis) {
					int val = constroiTree(trocaJogador(jogador));
					if (resultado == -1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					} else if (!resultado && val == 1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					}
				} else {
					int val = constroiTree(trocaJogador(jogador));
					if (resultado == 1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
				 	} else if (!resultado && val == -1) {
						iOtimo = i;
						jOtimo = j;
						resultado = val;
					}
				}
				constroiTree(trocaJogador(jogador));
				tab[i][j] = 0;
			}
		}
	}

	string estadoAtual = criaEstado();
	string novoEstado = criaEstado(iOtimo, jOtimo);
	utilidade.insert(make_pair(Estado(estadoAtual, jogador), Estado(novoEstado, trocaJogador(jogador))));
}

int main () {
	

	memset(tab, 0, sizeof tab);
	constroiTree(xis);

	return 0;
}
