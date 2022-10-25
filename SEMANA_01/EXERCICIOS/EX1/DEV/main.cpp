#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
using namespace std;

// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente 
// entre dois valores mínimo e máximo e retorna esse valor

void ajuste() {
	int min{ 1 };
	int max{ 10 };
	int value{ 0 };
	
	cout << "Digite um valor pertecente ao intervalo de 1 a 10:" << endl;
	cin >> value;
	cout << fixed << setprecision(1);
	cout << "O valor digitado ajustado ao intervalo de 1 a 10 resulta em "
		<< float(value - min) / float(max - min) * 100 <<  "%" << endl;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o 
// valor do teclado ao final a função retorna este valor
void scan() {

	cout << "Aperte alguma tecla para scanear:" << endl;

	while (true) {
		if (_kbhit()) {
			cout << "A tecla digitada foi: " << char(_getch()) << endl;
			break;
		}
	}
}

// 3 - Faça uma função que armazena uma medida inteira qualquer 
// em um vetor fornecido. Note que como C não possui vetores 
// nativos da linguagem, lembre-se que você precisa passar o 
// valor máximo do vetor assim como a última posição preenchida
// Evite também que, por acidente, um valor seja escrito em 
// uma área de memória fora do vetor
int* vetor(int* vector, int size, int last, int data) {
	if (last < size) {
		cout << "Digite o numero que será adicionado ao vetor: " << endl;
		vector[last + 1] = data;
		last += 1;
	}
	else {
		return vector;
	}
}

// 4 - Faça uma função que recebe um vetor com 4 posições que contém 
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção 
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a 
// segunda é esta maior distância.
int direcao(int* v) {
	int bigger{ v[0] };
	int	direction{ 0 };

	for (int i = 0; i < 4; i++) {
		if (v[i] > bigger) {
			bigger = v[i];
			direction = i;
			i = 0;
		}
	}

	switch (direction)
	{
	default:
		cout << "Direita" << endl;
		break;
	case 1:
		cout << "Esquerda" << endl;
		break;
	case 2:
		cout << "Frente" << endl;
		break;
	case 3:
		cout << "Tras" << endl;
		break;
	}

	return direction;

	//cout << " tem a maior distancia com o valor " << bigger << endl;
}

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e 
// retorna verdadeiro ou falso
bool decisao() {
	cout << "Digite 1 para continuar ou 0 para parar:" << endl;

	while (true) {
		if (_kbhit()) {
			char key = char(_getch());

			if (key == '1') {
				cout << "Voce digitou 1, entao iremos prosseguir" << endl;
				return 1;
			}
			else if (key == '0') {
				cout << "Voce digitou 0, entao iremos parar" << endl;
				return 0;
			}
			else {
				cout << "Valor informado e invalido, digite 1 para continuar ou 0 para parar" << endl;
			}
		}
	}


}


// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô 
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", 
// "Frente", "Tras"). 
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno 
// para uma movimentação futura. 
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro 
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado 
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas 
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja 
// enviado pelo usuário. 
//
//      Complete a função com a chamada das funções já criadas
void dirige(int* v, int maxv) {
	int maxVetor = maxv;
	int* vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;
	int direction = 0;

	while (dirigindo) {
		direction = direcao(vetorMov);

		if (vetorMov[direction] > 0) {
			vetorMov[direction] -= 1;
			cout << "direita: " << vetorMov[0] << ", esquerda: " << vetorMov[1] << ", frente: "
				<< vetorMov[2] << ", tras: " << vetorMov[3] << endl;
			dirigindo = decisao();
		}

		if (vetorMov[0] == 0 && vetorMov[1] == 0 && vetorMov[2] == 0 && vetorMov[3] == 0) {
			dirigindo = 0;
			cout << "Voce chegou ate o objeto";
		}
	}
}

int main() {
	const int maxVetor = 100;
	int movVetor[4] = {1, 4, 6, 8};

	//ajuste();
	//scan();
	//vetor();
	//decisao();
	dirige(movVetor, maxVetor);

	return 0;
}