#include<GL/glut.h>
#include <stdlib.h>
#include<string.h>
#include <MMSystem.h>
#include<math.h>
#include <iostream>
#include <stdio.h>
#include<time.h>

// Constantes
#define JOGAR 1
#define CONTROLES 2
#define CREDITOS 3
#define SAIR 4
#define MENU 5

using namespace std;
// Variáveis
char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, primitiva, cor, ClickON = 0;
int maxPoint = 5000;
int fase = 1;
int inc = 1;
GLint xi = 100;
GLint yi = 50;
int x = 50;
int yt = 60;
int yb = 300;
int pontos = 0;
int xt;
int direita = 1;
int esquerda = 0;
int teste = 0;
//flag do tiro da nave
int flagt = 0;
//flag do tiro dos bixos
int flagB = 0;
//flag dos bixo
int flagw3[10] = { 3,3,3,3,3,3,3,3,3,3 };
int flagw2[10] = { 2,2,2,2,2,2,2,2,2,2 };
int flagw[10] = { 1,1,1,1,1,1,1,1,1,1 };
int flagq[10] = { 1,1,1,1,1,1,1,1,1,1 };
int flag[10] = { 1,1,1,1,1,1,1,1,1,1 };
int flagVida = 2;
//reedesenha
void redesenha()
{
	xi = 100;
	yi = 50;
	x = 50;
	yt = 60;
	yb = 300;
	xt;
	direita = 1;
	esquerda = 0;
	//flag do tiro
	flagt = 0;
	//flag dos bixo
	for (int i = 0; i < 10; i++)
	{
		flagw3[i] = 3;
		flagw2[i] = 2;
		flagw[i] = 1;
		flagq[i] = 1;
		flag[i] = 1;
	}
}
//escreve na tela
//Desenha um texto na janela GLUT
void DesenhaTexto(char *string, float x, float y)
{
	glPushMatrix();
	// Posição no universo onde o texto será colocado          
	glRasterPos2f(x, y);
	// Exibe caracter a caracter
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
	glPopMatrix();
}
void init(void)
{

	glClearColor(0.0, 0.0, 0.0, 0.0);
	//set projection paramaters
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}
void setPixel(GLint xCoordinate, GLint yCoordinate)
{
	glBegin(GL_POINTS);
	glVertex2i(xCoordinate, yCoordinate);
	glEnd();
	//glFlush(); //executes all OpenGL functions as quickly as possible
}



void lineBres(GLint x0, GLint y0, GLint x1, GLint y1) {
	if (x0 > x1 && y0 > y1) {
		int x0Aux = x0;
		int y0Aux = y0;
		x0 = x1;
		x1 = x0Aux;
		y0 = y1;
		y1 = y0Aux;

	}

	int pass;
	// delta x e delta y
	int dx = x1 - x0;
	int dy = y1 - y0;


	if (dx > dy)
		pass = abs(dx);
	else
		pass = abs(dy);

	float incrementoX = dx / pass;
	float incrementoY = dy / pass;

	float x = x0;
	float y = y0;
	//mostra os pixels
	for (int i = 0; i < pass; i++)
	{
		x = x + incrementoX;
		y = y + incrementoY;
		setPixel(x, y);
	}

}
void desenhaEstrela(int x, int yb)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x, yb);
	glVertex2i(x + 1, yb + 4);
	glVertex2i(x + 2, yb);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x, yb);
	glVertex2i(x + 1, yb - 4);
	glVertex2i(x + 2, yb);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x + 1, yb + 1);
	glVertex2i(x - 3, yb);
	glVertex2i(x + 1, yb - 1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i(x + 1, yb + 1);
	glVertex2i(x + 5, yb);
	glVertex2i(x + 1, yb - 1);
	glEnd();
}
void desenhaBixo5(int x, int yb, int flaga[10], int pos)
{

	if (flagw3[pos] >= 1)
	{
		glBegin(GL_TRIANGLES);
		// Especifica que a cor corrente e verde
		glColor3f(0.0f, 1.0f, 0.4f);
		glVertex2i(x, yb);
		glVertex2i(x + 10, yb - 10);
		glVertex2i(x + 20, yb);
		glEnd();

		if ((xt>x) && (xt<x + 20) && (yb >= yt) && (yb < yt + 10) && flagt == 1)
		{
			flagw3[pos] = flagw3[pos] - 1;
			flagt = 0;
			if (flagw3[pos] == 0)
			{
				pontos = pontos + 400;
			}
			PlaySound(TEXT("destroy.wav"), NULL, SND_ASYNC);
		}
		if ((yb - 10) <= 60)
		{
			flagVida = flagVida - 1;
			PlaySound(TEXT("Super_Mario_World_Death_on_piano.wav"), NULL, SND_ASYNC);
			Sleep(500);
			redesenha();
		}
	}

}
void desenhaBixo4(int x, int yb, int flaga[10], int pos)
{
	if (flagw2[pos] >= 1)
	{
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.3f, 1.0f);
		glVertex2i(x, yb);
		glVertex2i(x + 20, yb);
		glVertex2i(x + 10, yb + 5);
		glVertex2i(x + 20, yb + 5);
		glEnd();

		if ((xt>x) && (xt<x + 20) && (yb >= yt) && (yb < yt + 10) && flagt == 1)
		{
			flagw2[pos] = flagw2[pos] - 1;
			flagt = 0;
			if (flagw2[pos] == 0)
			{
				pontos = pontos + 300;
			}
			PlaySound(TEXT("destroy.wav"), NULL, SND_ASYNC);
		}
		if (yb <= 60)
		{
			flagVida = flagVida - 1;
			PlaySound(TEXT("Super_Mario_World_Death_on_piano.wav"), NULL, SND_ASYNC);
			Sleep(500);
			redesenha();
		}
	}
}
void desenhaBixo3(int x, int yb, int flaga[10], int pos)
{
	if (flagw[pos] >= 1)
	{
		glBegin(GL_QUADS);
		glColor3f(1.0f, 2.0f, 1.0f);
		glVertex2i(x, yb);
		glVertex2i(x + 20, yb);
		glVertex2i(x + 10, yb + 5);
		glVertex2i(x, yb + 5);
		glEnd();

		if ((xt>x) && (xt<x + 20) && (yb >= yt) && (yb < yt + 10) && flagt == 1)
		{
			flagw[pos] = flagw[pos] - 1;
			flagt = 0;
			if (flagw[pos] == 0)
			{
				pontos = pontos + 150;
			}
			PlaySound(TEXT("destroy.wav"), NULL, SND_ASYNC);
		}
		if (yb <= 60)
		{
			flagVida = flagVida - 1;
			PlaySound(TEXT("Super_Mario_World_Death_on_piano.wav"), NULL, SND_ASYNC);
			Sleep(500);
			redesenha();
		}
	}
}
void desenhaBixo2(int x, int yb, int flaga[10], int pos)
{

	if (flag[pos] >= 1)
	{
		glBegin(GL_TRIANGLES);
		// Especifica que a cor corrente e verde
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(x, yb);
		glVertex2i(x + 10, yb + 10);
		glVertex2i(x + 20, yb);
		glEnd();

		if ((xt>x) && (xt<x + 20) && (yb >= yt) && (yb < yt + 10) && flagt == 1)
		{
			flag[pos] = flag[pos] - 1;
			flagt = 0;
			if (flag[pos] == 0)
			{
				pontos = pontos + 100;
			}
			PlaySound(TEXT("destroy.wav"), NULL, SND_ASYNC);
		}
		if (yb <= 60)
		{
			flagVida = flagVida - 1;
			PlaySound(TEXT("Super_Mario_World_Death_on_piano.wav"), NULL, SND_ASYNC);
			Sleep(500);
			redesenha();
		}
	}

}

void desenhaBixo(int x, int yb, int flaga[10], int pos)
{

	if (flaga[pos] >= 1)
	{

		glBegin(GL_QUADS);
		// Especifica que a cor corrente é azul
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(x, yb + 20);
		glVertex2i(x, yb);
		glVertex2i(x + 20, yb);
		glVertex2i(x + 20, yb + 20);
		glEnd();
		if ((xt>x) && (xt<x + 20) && (yb >= yt) && (yb < yt + 10) && flagt == 1)
		{
			flagq[pos] = flagq[pos] - 1;
			flagt = 0;
			pontos = pontos + 50;
			PlaySound(TEXT("destroy.wav"), NULL, SND_ASYNC);

		}
		if (yb <= 60)
		{
			flagVida = flagVida - 1;
			PlaySound(TEXT("Super_Mario_World_Death_on_piano.wav"), NULL, SND_ASYNC);
			Sleep(500);
			redesenha();
		}
	}


}
void desenhaTiro()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	if (yt <= 60)
	{
		xt = xi;
	}
	if (flagt == 1)
	{
		lineBres(xt + 5, yt, xt + 5, yt + 5);
	}
}

void movimentaTiro()
{
	if (yt < 240)
	{
		yt = yt + 3;
	}
	else
	{
		flagt = 0;
		yt = 60;
	}
}

void movimentaBixo()
{
	if (direita == 1 && x < 280)
	{
		x = x + inc;
	}
	if (esquerda == 1 && x > 0)
	{
		x = x - inc;
	}
	if (x >= 280)
	{
		direita = 0;
		esquerda = 1;
		yb = yb - 2;
	}
	if (x <= 120)
	{
		direita = 1;
		esquerda = 0;
		yb = yb - 2;
	}
}
void desenhaNave()
{
	glColor3f(1.0, 0.0, 0.0);
	lineBres(xi, yi, xi, yi + 5);
	lineBres(xi, yi, xi + 10, yi);
	lineBres(xi, yi + 5, xi + 10, yi + 5);
	lineBres(xi + 10, yi, xi + 10, yi + 5);
	lineBres(xi, yi + 5, xi + 5, yi + 10);
	lineBres(xi + 5, yi + 10, xi + 10, yi + 5);
	lineBres(xi - 5, yi, xi, yi);
	lineBres(xi - 5, yi, xi, yi + 5);
	lineBres(xi + 10, yi + 5, xi + 15, yi);
	lineBres(xi + 10, yi, xi + 15, yi);
}
void desenhaCeu()
{
	desenhaEstrela(260, 80);
	desenhaEstrela(260, 160);
	desenhaEstrela(260, 240);

	desenhaEstrela(240, 120);
	desenhaEstrela(240, 200);

	desenhaEstrela(220, 80);
	desenhaEstrela(220, 160);
	desenhaEstrela(220, 240);

	desenhaEstrela(200, 120);
	desenhaEstrela(200, 200);

	desenhaEstrela(180, 80);
	desenhaEstrela(180, 160);
	desenhaEstrela(180, 240);

	desenhaEstrela(160, 120);
	desenhaEstrela(160, 200);

	desenhaEstrela(140, 80);
	desenhaEstrela(140, 160);
	desenhaEstrela(140, 240);

	desenhaEstrela(120, 120);
	desenhaEstrela(120, 200);

	desenhaEstrela(100, 80);
	desenhaEstrela(100, 160);
	desenhaEstrela(100, 240);

	desenhaEstrela(80, 120);
	desenhaEstrela(80, 200);

	desenhaEstrela(60, 80);
	desenhaEstrela(60, 160);
	desenhaEstrela(60, 240);
}
void desenhaBixos1()
{
	desenhaBixo(x - 30, yb, flagq, 1);
	desenhaBixo(x - 60, yb, flagq, 2);
	desenhaBixo(x - 90, yb, flagq, 3);
	desenhaBixo(x - 120, yb, flagq, 4);
	desenhaBixo(x, yb, flagq, 5);
}
void desenhaBixos2()
{
	desenhaBixo2(x, yb + 35, flag, 1);
	desenhaBixo2(x - 30, yb + 35, flag, 2);
	desenhaBixo2(x - 60, yb + 35, flag, 3);
	desenhaBixo2(x - 90, yb + 35, flag, 4);
	desenhaBixo2(x - 120, yb + 35, flag, 5);
}
void desenhaBixos4()
{
	desenhaBixo4(x, yb + 105, flag, 1);
	desenhaBixo4(x - 30, yb + 105, flag, 2);
	desenhaBixo4(x - 60, yb + 105, flag, 3);
	desenhaBixo4(x - 90, yb + 105, flag, 4);
	desenhaBixo4(x - 120, yb + 105, flag, 5);
}
void desenhaBixos3()
{
	desenhaBixo3(x, yb + 70, flag, 1);
	desenhaBixo3(x - 30, yb + 70, flag, 2);
	desenhaBixo3(x - 60, yb + 70, flag, 3);
	desenhaBixo3(x - 90, yb + 70, flag, 4);
	desenhaBixo3(x - 120, yb + 70, flag, 5);
}
void desenhaBixos5()
{
	desenhaBixo5(x, yb + 140, flag, 1);
	desenhaBixo5(x - 30, yb + 140, flag, 2);
	desenhaBixo5(x - 60, yb + 140, flag, 3);
	desenhaBixo5(x - 90, yb + 140, flag, 4);
	desenhaBixo5(x - 120, yb + 140, flag, 5);
}

void desenhaJogo(void)
{

	//
	if (flagVida < 0)
	{

		DesenhaTexto("Game Over", 170, 180);
		glFlush();
		Sleep(4000);
		maxPoint = 5000;
		fase = 1;
		inc = 1;
		xi = 100;
		yi = 50;
		x = 50;
		yt = 60;
		yb = 300;
		pontos = 0;
		direita = 1;
		esquerda = 0;
		teste = 0;
		//flag do tiro
		flagt = 0;
		//flag dos bixo
		redesenha();
		flagVida = 2;


	}
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);
	//desenha estrela
	desenhaCeu();
	//Desenha bixo e nave
	desenhaNave();
	desenhaBixos1();
	desenhaBixos2();
	desenhaBixos3();
	desenhaBixos4();
	desenhaBixos5();
	movimentaBixo();
	desenhaTiro();
	movimentaTiro();
	//Mostra Pontos e vida
	DesenhaTexto("Pontos:", 50, 20);
	char ponts[7];
	_itoa_s(pontos, ponts, 10);
	DesenhaTexto(ponts, 90, 20);
	DesenhaTexto("vida", 130, 20);
	char ponts2[7];
	_itoa_s(flagVida, ponts2, 10);
	DesenhaTexto(ponts2, 150, 20);
	DesenhaTexto("Fase", 170, 20);
	char ponts3[7];
	_itoa_s(fase, ponts3, 10);
	DesenhaTexto(ponts3, 190, 20);
	//glFlush();
	if (pontos == maxPoint)
	{
		maxPoint = maxPoint + 5000;
		inc = inc + 1;
		fase = fase + 1;
		PlaySound(TEXT("Fase.wav"), NULL, SND_ASYNC);
		redesenha();

	}
	Sleep(10);
	glFlush();
}
void keyboardDown(unsigned char key, int x, int y) {
	cout << "Xi: " << xi << " Tecla regular pressionada: " << char(key) << endl;

	switch (key) {
	case 32: if (flagt == 0)
	{
		yt = 60; flagt = 1;
		PlaySound(TEXT("Fire.wav"), NULL, SND_ASYNC);
	}break;
	case  27:   // ESC
		exit(0);
	case 'a':
		if (xi > 4)
		{
			xi = xi - 1; break;
		}
		break;
	case 'A':
		if (xi > 4)
		{
			xi = xi - 1; break;
		}
		break;
	case 'd':
		if (xi < 277)
		{
			xi = xi + 1; break;
		}break;
	case 'D':
		if (xi < 277)
		{
			xi = xi + 1; break;
		}break;


	}
}


void DesenhaBotao(int x0, int x1, int y0, int y1) { // Desenha um botao usando 2 valores de x e 2 valores de y
	glBegin(GL_QUADS);
	glVertex2i(x0, y0);
	glVertex2i(x0, y1);
	glVertex2i(x1, y1);
	glVertex2i(x1, y0);
	glEnd();
}

// Gerenciamento do menu com as opções de cores           
void EscolheCor(int cor)
{
	if (cor == 1) {  // VERMELHO
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else if (cor == 2) { // VERDE
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if (cor == 3) { // AZUL
		glColor3f(0.0f, 0.0f, 1.0f);
	}
	else if (cor == 4) { // BRANCO
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (cor == 5) { // PRETO
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	//glutPostRedisplay();
}

// Função callback chamada para fazer o desenho
void DesenhaBotoes(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	EscolheCor(5);
	DesenhaBotao(0, 300, 230, 250);
	EscolheCor(2);       // Desenha o nome do jogo no alto do menu
	strcpy_s(texto, "Space   Invaders");
	DesenhaTexto(texto, 120, 235);

	EscolheCor(2);
	DesenhaBotao(100, 180, 190, 210);
	EscolheCor(5);       // Desenha botao Iniciar
	strcpy_s(texto, "Iniciar");
	DesenhaTexto(texto, 130, 195);

	EscolheCor(2);
	DesenhaBotao(100, 180, 160, 180);
	EscolheCor(5);       // Desenha botao Opções
	strcpy_s(texto, "Opcoes");
	DesenhaTexto(texto, 125, 165);

	EscolheCor(2);
	DesenhaBotao(100, 180, 130, 150);
	EscolheCor(5);       // Desenha botao Créditos
	strcpy_s(texto, "Credi[t]os");
	DesenhaTexto(texto, 125, 135);

	EscolheCor(2);
	DesenhaBotao(100, 180, 100, 120);
	EscolheCor(5);       // Desenha botao Sair
	strcpy_s(texto, "Sair");
	DesenhaTexto(texto, 130, 105);

	EscolheCor(cor);

	glutSwapBuffers();
	// Executa os comandos OpenGL
	glFlush();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	cor = 3;
	primitiva = MENU;
}

void DesenhaTelaControles(void) { // Desenha a tela dos controles e instruções do jogo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	EscolheCor(5);
	DesenhaBotao(100, 180, 190, 210);
	EscolheCor(2);
	strcpy_s(texto, "Controles");
	DesenhaTexto(texto, 125, 195);

	EscolheCor(2);
	DesenhaBotao(100, 120, 140, 160);
	EscolheCor(5);
	strcpy_s(texto, "[A]");
	DesenhaTexto(texto, 105, 145);

	EscolheCor(2);
	DesenhaBotao(100, 120, 110, 130);
	EscolheCor(5);
	strcpy_s(texto, "[D]");
	DesenhaTexto(texto, 105, 115);

	/*EscolheCor(2);
	DesenhaBotao(100, 120, 80, 100);
	EscolheCor(5);
	strcpy_s(texto, "[S]");
	DesenhaTexto(texto, 105, 85);
	*/
	EscolheCor(2);
	DesenhaBotao(100, 150, 80, 100);
	EscolheCor(5);
	strcpy_s(texto, "[ESPACO]");
	DesenhaTexto(texto, 105, 85);

	EscolheCor(5);
	DesenhaBotao(130, 210, 140, 160);
	EscolheCor(2);
	strcpy_s(texto, "Move p/ esquerda");
	DesenhaTexto(texto, 137, 145);

	EscolheCor(5);
	DesenhaBotao(130, 210, 110, 130);
	EscolheCor(2);
	strcpy_s(texto, "Move p/ direita");
	DesenhaTexto(texto, 137, 115);
	EscolheCor(5);
	DesenhaBotao(130, 210, 50, 70);
	EscolheCor(2);
	strcpy_s(texto, "Atira");
	DesenhaTexto(texto, 160, 85);

	EscolheCor(2);
	strcpy_s(texto, "Objetivo: Destruir o ");
	DesenhaTexto(texto, 30, 40);
	strcpy_s(texto, "maximo de aliens!");
	DesenhaTexto(texto, 88, 40);

	EscolheCor(2);
	DesenhaBotao(0, 50, 230, 250);
	EscolheCor(5);
	strcpy_s(texto, "[<--] Voltar");
	DesenhaTexto(texto, 3, 235);
}

void DesenhaTelaCreditos(void) { // Desenha tela de créditos (autores do trabalho)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	EscolheCor(2);
	DesenhaBotao(80, 200, 190, 210);
	EscolheCor(5);
	strcpy_s(texto, "ALUNOS CEFET-MG");
	DesenhaTexto(texto, 105, 195);

	EscolheCor(2);
	DesenhaBotao(50, 130, 160, 180);
	EscolheCor(5);
	strcpy_s(texto, "Davidson Estole");
	DesenhaTexto(texto, 60, 170);

	EscolheCor(2);
	DesenhaBotao(150, 230, 160, 180);
	EscolheCor(5);
	strcpy_s(texto, "Eduardo Rangel");
	DesenhaTexto(texto, 160, 170);

	EscolheCor(2);
	DesenhaBotao(50, 130, 130, 150);
	EscolheCor(5);
	strcpy_s(texto, "Leandro Martins");
	DesenhaTexto(texto, 60, 140);

	EscolheCor(2);
	DesenhaBotao(150, 230, 130, 150);
	EscolheCor(5);
	strcpy_s(texto, "Marlon Felix");
	DesenhaTexto(texto, 160, 140);


	EscolheCor(2);
	DesenhaBotao(100, 180, 100, 120);
	EscolheCor(5);
	strcpy_s(texto, "Rodrigo Silva");
	DesenhaTexto(texto, 115, 110);

	EscolheCor(2);
	DesenhaBotao(0, 50, 230, 250);
	EscolheCor(5);
	strcpy_s(texto, "[<--] Voltar");
	DesenhaTexto(texto, 3, 235);

}

void DesenhaTelaSair(void) { // Desenha tela sair (somente para teste)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	EscolheCor(5);
	DesenhaBotao(100, 180, 190, 210);
	EscolheCor(2);
	strcpy_s(texto, "Sair");
	DesenhaTexto(texto, 130, 195);

	EscolheCor(5);
	DesenhaBotao(80, 200, 160, 180);
	EscolheCor(2);
	strcpy_s(texto, "Deseja realmente sair ?");
	DesenhaTexto(texto, 100, 165);

	EscolheCor(2);
	DesenhaBotao(80, 100, 130, 150);
	EscolheCor(5);
	strcpy_s(texto, "Sim");
	DesenhaTexto(texto, 83, 135);

	EscolheCor(1);
	DesenhaBotao(180, 200, 130, 150);
	EscolheCor(5);
	strcpy_s(texto, "Nao");
	DesenhaTexto(texto, 183, 135);

}

void DesenhaTelaJogar() {   // Desenha Tela do Jogo (somente para teste)
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	EscolheCor(2);
	DesenhaBotao(100, 200, 190, 210);
	EscolheCor(5);
	strcpy_s(texto, "Babaca Invaders");
	DesenhaTexto(texto, 125, 195);

	EscolheCor(2);
	DesenhaBotao(0, 50, 230, 250);
	EscolheCor(5);
	strcpy_s(texto, "[<--] Voltar");
	DesenhaTexto(texto, 3, 235);
}

// Tratamento de Teclas comuns no menu
void keyboardDown2(unsigned char key, int x, int y)
{
	switch (key) {

	case 13:
		if (primitiva == MENU) {
			primitiva = JOGAR;
			PlaySound(TEXT("Fase.wav"), NULL, SND_ASYNC);
			break;
		}
		break;

	case 'm':
		if (primitiva != MENU) {
			primitiva = MENU;
			break;
		}
		break;

	case 27:
		if (primitiva == MENU) {
			exit(0);
		}
		break;

		break;

	case 8:
		if (primitiva != MENU) {
			primitiva = MENU;
		}
		break;

		break;

	case 'o':
		if (primitiva == MENU) {
			primitiva = CONTROLES;
			break;
		}
		break;

	case 'O':
		if (primitiva == MENU) {
			primitiva = CONTROLES;
			break;
		}
		break;

	case 't':
		if (primitiva == MENU) {
			primitiva = CREDITOS;
			break;
		}
		else if (primitiva == CREDITOS) {
			primitiva = MENU;
			break;
		}
		break;

	case 'T':
		if (primitiva == MENU) {
			primitiva = CREDITOS;
			break;
		}
		break;

	}
	glutPostRedisplay();
}

// Função callback chamada para fazer o desenho
void DesenhaTudo(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha uma primitiva     
	switch (primitiva) {

	case MENU: DesenhaBotoes();
		break;
	case JOGAR:
		desenhaJogo();
		glutIdleFunc(desenhaJogo);
		glutKeyboardFunc(keyboardDown);
		break;
	case CONTROLES: DesenhaTelaControles();
		break;
	case CREDITOS: DesenhaTelaCreditos();
		break;
	case SAIR: DesenhaTelaSair();
		break;
	}
	glutSwapBuffers();
}

void TrataMouse(int button, int state, int x, int y)
{

			//pTransInfo[0].vTranslate  = Vector3( 0.5f, 0.5f, 0.5f ); // center of scene
			GLint viewport[4]; //var to hold the viewport info
			GLdouble modelview[16]; //var to hold the modelview info
			GLdouble projection[16]; //var to hold the projection matrix info
			GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
			GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

			glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
			glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
			glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

			winX = (float)x;
			winY = (float)viewport[3] - (float)y;
			winZ = 0;

			//get the world coordinates from the screen coordinates
			gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

			cout << "coordinates: worldX = " << worldX << " worldY = " << worldY << " worldZ = " << worldZ << endl; //THIS IS WHAT YOU WANT, STORE IT IN AN ARRAY OR OTHER STRUCTURE

			if (button == GLUT_LEFT_BUTTON)  // quando botao esquerdo do mouse é pressionado ClickON se torna igual a 1 
			{
				if (state == GLUT_DOWN) { 
					ClickON = 1;
				}
			}
			if (button == GLUT_LEFT_BUTTON) // quando botao esquerdo do mouse não é pressionado ClickON se torna igual a 0
			{
				if (state == GLUT_UP) { 
					ClickON = 0;
				}
			}

			if (primitiva == MENU)
			{
				if (button == GLUT_LEFT_BUTTON)
				{
					if (state == GLUT_DOWN)
					{
						if (worldX > 100 && worldX < 180) {

							if (worldY > 190 && worldY < 210)
							{
								primitiva = JOGAR;
								PlaySound(TEXT("Fase.wav"), NULL, SND_ASYNC);
							}
							if (worldY > 160 && worldY < 180)
							{
								primitiva = CONTROLES;
							}
							if (worldY > 130 && worldY < 150)
							{
								primitiva = CREDITOS;
							}
							if (worldY > 100 && worldY < 120)
							{
								exit(0);
							}
						}
					}
				}

			}

			if (primitiva == CONTROLES)
			{
				if (button == GLUT_LEFT_BUTTON)
				{
					if (state == GLUT_DOWN)
					{
						if (worldX > 0 && worldX < 50) {

							if (worldY > 230 && worldY < 250)
							{
								primitiva = MENU;
							}
						}
					}
				}
			}

			if (primitiva == CREDITOS)
			{
				if (button == GLUT_LEFT_BUTTON)
				{
					if (state == GLUT_DOWN)
					{
						if (worldX > 0 && worldX < 50) {

							if (worldY > 230 && worldY < 250)
							{
								primitiva = MENU;
							}
						}
					}
				}
			}
}
	

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if (h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h / w);
	else
		gluOrtho2D(0.0f, 250.0f*w / h, 0.0f, 250.0f);
}

// Programa Principal 
void main(int argc, char**argv)
{
	//initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Space Invaders");
	glutDisplayFunc(DesenhaTudo);
	PlaySound(TEXT("Black_RX_8bit.wav"), NULL, SND_ASYNC);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc(keyboardDown2);
	glutMouseFunc(TrataMouse);
	Inicializa();
	glutMainLoop();
}

