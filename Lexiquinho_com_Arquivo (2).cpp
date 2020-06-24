#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbreParenteses 7
#define TKFechaParenteses 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKFimArquivo 18
#define TKDuploSub 19
#define TKDiv 20
#define TKRestoDiv 21
#define TKBitAND 22
#define TKBitOR 23
#define TKBitXOR 24
#define TKBitNOT 25
#define TKLogicoAND 26
#define TKLogicoOR 27
#define TKLogicoNot 28
#define TKRelacIGUAL 29
#define TKRelacDIFERENTE 30
#define TKRelacMAIORQUE 31
#define TKRelacMENORQUE 32
#define TKRelacMAIORouIGUAL 33
#define TKRelacMENORouIGUAL 34
#define TKFor 35
#define TKWhile 36 
#define TKDo 37
#define TKIf 38
#define TKElse 39
#define TKReturn 40
#define TKAbreColchete 41
#define TKFechaColchete 42
#define TKConsInteiro 43
#define TKConsString 44
#define TKStruct 45 

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int pos = 0;

int tk;
char lex[20];
FILE *arqin;
char c; // último caracter lido do arquivo

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"char",TKChar},
                  {"for", TKFor},
                  {"while",TKWhile},
                  {"do", TKDo},
                  {"if", TKIf},
                  {"else", TKElse},
                  {"return", TKReturn},
                  {"struct", TKStruct},
                  {"fimtabela",TKId}};

int palavra_reservada(char lex[])
{
	int postab=0;
	while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
	   {
	   if (strcmp(lex,lista_pal[postab].palavra)==0)
	      return lista_pal[postab].tk;
	   postab++;
	   }
	return TKId;
}


void getToken(); // protótipos
void proxC();

// variáveis globais para retrocesso

long int posglobal;
int tkant;

void marcaPosToken() {
	posglobal=ftell(arqin);
	tkant=tk;
}

//Implemente aqui a sua função restauraPosToken()

void restauraPosToken() {
	fseek(arqin,posglobal,SEEK_SET);
	proxC();
	tk=tkant;
}

void proxC()
{
if (feof(arqin)) {
   c=-1;
//   printf("Chegou no fim de arquivo\n");
   return;
   }
fread(&c,1,1,arqin);
//printf("Leu caracter %c\n",c);
}

void getToken()
{
int estado=0,
    fim=0,
    posl=0;
while (!fim)
   {
   lex[posl++]=c;
   
   switch(estado){
      case 0:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_')
                {proxC();estado=1;break;}
             
			 if(c == '"'){
             	proxC();
             	while(c !='"'){
             		lex[posl++] = c;
             		proxC();
				 }
				 lex[posl] = '\0';
				 tk=TKConsString;/*printf("Reconheceu token TKSoma\n");*/return;
			 }
			 
			 if(c>='0' && c<='9'){
			 	while(c>='0' && c<='9'){
			 		lex[posl++] = c;
			 		proxC();
				 }
				 lex[posl] = '\0';
				 tk=TKConsInteiro;/*printf("Reconheceu token TKSoma\n");*/return;
			 }
			 
			 if (c=='=')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKRelacIGUAL;/*printf("Reconheceu token TKRelacIGUAL\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKAtrib;/*printf("Reconheceu token TKAtrib\n");*/return;
				   }
			 }
             if (c=='+')
			    {
			    proxC();
				if (c=='+')
			       {
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKSoma;/*printf("Reconheceu token TKSoma\n");*/return;
				   }
			    }
			    
			 if (c=='-')
			 {
			    proxC();
				if (c=='-')
			       {
				   lex[posl++]='-';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploSub;/*printf("Reconheceu token TKDuploSub\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKSub;/*printf("Reconheceu token TKSub\n");*/return;
				   }
			 }
			 if (c=='|')
			 {
			    proxC();
				if (c=='|'){
				   lex[posl++]='|';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKLogicoOR;/*printf("Reconheceu token TKLogicoOR \n");*/return;
			    }
				else{
	               lex[posl]='\0';
				   tk=TKBitOR;/*printf("Reconheceu token TKBitOR\n");*/return;
			    }
			 }
			 if (c=='&')
			 {
			    proxC();
				if (c=='&')
			       {
				   lex[posl++]='&';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKLogicoAND;/*printf("Reconheceu token TKLogicoAND\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKBitAND;/*printf("Reconheceu token TKBitAND\n");*/return;
				   }
			 }
			 if (c=='!')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKRelacDIFERENTE;/*printf("Reconheceu token TKRelacDIFERENTE\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKLogicoNot;/*printf("Reconheceu token TKLogicoNot\n");*/return;
				   }
			 }
			 if (c=='>')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKRelacMAIORouIGUAL;/*printf("Reconheceu token TKRelacMAIORouIGUAL\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKRelacMAIORQUE;/*printf("Reconheceu token TKRelacMAIORQUE\n");*/return;
				   }
			 }
			 if (c=='<')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKRelacMENORouIGUAL;/*printf("Reconheceu token TKRelacMAIORouIGUAL\n");*/return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKRelacMENORQUE;/*printf("Reconheceu token TKRelacMAIORQUE\n");*/return;
				   }
			 }
             if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;/*printf("Reconheceu token TKProd\n");*/return;}
			 if (c=='/'){lex[posl]='\0';proxC();tk=TKDiv;/*printf("Reconheceu token TKDiv\n");*/return;}
			 if (c=='%'){lex[posl]='\0';proxC();tk=TKRestoDiv;/*printf("Reconheceu token TKRestoDiv\n");*/return;}
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbreParenteses;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaParenteses;/*printf("Reconheceu token FechaPar\n");*/return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;/*printf("Reconheceu token TKAbreChaves\n");*/return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;/*printf("Reconheceu token TKFechaChaves\n");*/return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;/*printf("Reconheceu token TKVirgula\n");*/return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;/*printf("Reconheceu token TKPontoEVirgula\n");*/return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;/*printf("Reconheceu token TKDoisPontos\n");*/return;}
             if (c=='^'){lex[posl]='\0';proxC();tk=TKBitXOR;/*printf("Reconheceu token TKBitXOR\n");*/return;}
             if (c=='~'){lex[posl]='\0';proxC();tk=TKBitNOT;/*printf("Reconheceu token TKBitNOT\n");*/return;}
			 if (c=='!'){lex[posl]='\0';proxC();tk=TKLogicoNot;/*printf("Reconheceu token TKLogicoNot\n");*/return;}
			 if (c=='['){lex[posl]='\0';proxC();tk=TKAbreColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==']'){lex[posl]='\0';proxC();tk=TKFechaColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
			 if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;/*printf("Reconheceu token TKFimArquivo\n");*/return;}
             if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
             if (c=='\0') {tk=-1;return;}
             printf("Erro léxico: encontrou o caracter %c (%d)",c,c);
             getch();
             break;
      case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {proxC();break;}
             lex[--posl]='\0';
             tk=palavra_reservada(lex);
             //printf("reconheceu token %s\n",lex);
             return;
      } //switch
   }// while
}// função



void analisadorSintatico(){
	proxC(); // lê primeiro caracter do arquivo
	getToken(); // lê primeiro token
	
	if (Declarator()==0) printf("Erro no reconhecimento\n");
	else printf("Reconheceu OK!\n");
}


int main()
{
	int a; int b;
	arqin=fopen("fonte.c","rb");
	if (!arqin) {
		printf("Erro na abertura do fonte.\n");
		return 0;
	}
	
	analisadorSintatico();
	
	arqin=fopen("fonte.c","rb");
	proxC(); // lê primeiro caracter do arquivo
	getToken(); // lê primeiro token
	while (tk!=TKFimArquivo)
	{
		printf("%d\n\n",tk);
		getToken();
	}
	
}
