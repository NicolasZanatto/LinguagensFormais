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
#define TKGoto 46
#define TKContinue 47 
#define TKBreak 48

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
                  {"goto",TKGoto},
                  {"continue",TKContinue},
                  {"break",TKBreak},
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
				 tk=TKConsString;printf("Reconheceu token TKConsString\n");return;
			 }
			 
			 if(c>='0' && c<='9'){
			 	while(c>='0' && c<='9'){
			 		lex[posl++] = c;
			 		proxC();
				 }
				 lex[posl] = '\0';
				 tk=TKConsInteiro;printf("Reconheceu token TKConsInteiro\n");return;
			 }
			 
			 if (c=='=')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKRelacIGUAL;printf("Reconheceu token TKRelacIGUAL\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKAtrib;printf("Reconheceu token TKAtrib\n");return;
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
				   tk=TKDuploMais;printf("Reconheceu token TKDuploMais\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKSoma;printf("Reconheceu token TKSoma\n");return;
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
				   tk=TKDuploSub;printf("Reconheceu token TKDuploSub\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKSub;printf("Reconheceu token TKSub\n");return;
				   }
			 }
			 if (c=='|')
			 {
			    proxC();
				if (c=='|'){
				   lex[posl++]='|';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKLogicoOR;printf("Reconheceu token TKLogicoOR \n");return;
			    }
				else{
	               lex[posl]='\0';
				   tk=TKBitOR;printf("Reconheceu token TKBitOR\n");return;
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
				   tk=TKLogicoAND;printf("Reconheceu token TKLogicoAND\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKBitAND;printf("Reconheceu token TKBitAND\n");return;
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
				   tk=TKRelacDIFERENTE;printf("Reconheceu token TKRelacDIFERENTE\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKLogicoNot;printf("Reconheceu token TKLogicoNot\n");return;
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
				   tk=TKRelacMAIORouIGUAL;printf("Reconheceu token TKRelacMAIORouIGUAL\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKRelacMAIORQUE;printf("Reconheceu token TKRelacMAIORQUE\n");return;
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
				   tk=TKRelacMENORouIGUAL;printf("Reconheceu token TKRelacMENORouIGUAL\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKRelacMENORQUE;printf("Reconheceu token TKRelacMENORQUE\n");return;
				   }
			 }
             if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;printf("Reconheceu token TKProd\n");return;}
			 if (c=='/'){lex[posl]='\0';proxC();tk=TKDiv;printf("Reconheceu token TKDiv\n");return;}
			 if (c=='%'){lex[posl]='\0';proxC();tk=TKRestoDiv;printf("Reconheceu token TKRestoDiv\n");return;}
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbreParenteses;printf("Reconheceu token TKAbrePar\n");return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaParenteses;printf("Reconheceu token FechaPar\n");return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;printf("Reconheceu token TKAbreChaves\n");return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;printf("Reconheceu token TKFechaChaves\n");return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;printf("Reconheceu token TKVirgula\n");return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;printf("Reconheceu token TKPontoEVirgula\n");return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;printf("Reconheceu token TKDoisPontos\n");return;}
             if (c=='^'){lex[posl]='\0';proxC();tk=TKBitXOR;printf("Reconheceu token TKBitXOR\n");return;}
             if (c=='~'){lex[posl]='\0';proxC();tk=TKBitNOT;printf("Reconheceu token TKBitNOT\n");return;}
			 if (c=='!'){lex[posl]='\0';proxC();tk=TKLogicoNot;printf("Reconheceu token TKLogicoNot\n");return;}
			 if (c=='['){lex[posl]='\0';proxC();tk=TKAbreColchete;printf("Reconheceu token TKAbrePar\n");return;}
             if (c==']'){lex[posl]='\0';proxC();tk=TKFechaColchete;printf("Reconheceu token TKAbrePar\n");return;}
			 if (c==-1){lex[posl]='\0';proxC();tk=TKFimArquivo;printf("Reconheceu token TKFimArquivo\n");return;}
             if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
             if (c=='\0') {tk=-1;return;}
             printf("Erro léxico: encontrou o caracter %c (%d)",c,c);
             getch();
             break;
      case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {proxC();break;}
             lex[--posl]='\0';
             tk=palavra_reservada(lex);
             printf("reconheceu token %s\n",lex);
             return;
      } //switch
   }// while
   printf("Token:%d\n", tk);
}// função


// Protótipo das Funções do Analisador Sintático

int Initializer_list();

int Initializer_list1Linha();

int Initializer();

int Initializer1Linha();

int Initializer2Linha();

int Init_declarator();

int Init_declarator1Linha();

int Init_declarator_list();

int Init_declarator_list1Linha();

int Declaration();

int Declaration1Linha();

int Declaration_list();

int Declaration_list1Linha();

int Parameter_list();

int Parameter_list1Linha();

int Parameter_declaration();

int Declaration_specifiers();

int Declarator();

int Direct_declarator();

int Direct_declarator1Linha();

int Direct_declarator2Linha();

int Identifier_list();

int Identifier_list1Linha();

int Statement();

int Statement_list();

int Statement_list1Linha();

int Compound_statement();

int Compound_statement1Linha();

int Compound_statement2Linha();

int Expression_statement();

int Selection_statement();

int Selection_statement1Linha();

int Iteration_statement();

int Iteration_statement1Linha();

int Jump_statement();

int Jump_statement1Linha();

int Expression();

int Expression1Linha();

int ExpressionA();

int ExpressionA1Linha();

int ExpressionB();

int ExpressionB1Linha();

int ExpressionC();

int ExpressionC1Linha();

int ExpressionD();

int External_declaration();

int Translation_unit();

int Translation_unit1Linha();

int Function_definition();

int Function_definitionLinha();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>


//Initializer_list -> Initializer Initializer_list1Linha 
int Initializer_list(){
	if(Initializer()){
		if (Initializer_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Initializer_list1Linha -> , Initializer Initializer_list1Linha | ? 
int Initializer_list1Linha(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Initializer()){
			if (Initializer_list1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Initializer -> Expression | Initializer1Linha 
int Initializer(){
	if (Expression()){
		return 1;
	}
	else if (Initializer1Linha()){
		return 1;
	}
	else{return 0;}
}

//Initializer1Linha -> { initializer_list Initializer2Linha 
int Initializer1Linha(){
	if(tk == TKAbreChaves){// {
		getToken(); 
		if (Initializer_list()){
			if (Initializer2Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Initializer2Linha -> , } | } 
int Initializer2Linha(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if(tk == TKFechaChaves){// }
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKFechaChaves){// }
		getToken();
		return 1;
	}
	else{return 0;}
}

//Init_declarator -> Declarator Init_declarator1Linha 
int Init_declarator(){
	if(Declarator()){
		if (Init_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Init_declarator1Linha -> = Initializer | ? 
int Init_declarator1Linha(){
	if(tk == TKAtrib){// =
		getToken(); 
		if (Initializer()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Init_declarator_list -> Init_declarator Init_declarator_list1Linha 
int Init_declarator_list(){
	if(Init_declarator()){
		if (Init_declarator_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Init_declarator_list1Linha -> , Init_declarator Init_declarator_list1Linha | ? 
int Init_declarator_list1Linha(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Init_declarator()){
			if (Init_declarator_list1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Declaration -> Declaration_specifiers Declaration1Linha 
int Declaration(){
printf("Declaration\n");
	if(Declaration_specifiers()){
		printf("Declaration_specifiers\n");
		if (Declaration1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration1Linha -> ; | Declaration_specifiers Init_declarator_list ; 
int Declaration1Linha(){
	if(tk == TKVirgula){// ;
		getToken();
		return 1;
	}
	else if (Init_declarator_list()){
		if(tk == TKPontoEVirgula){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
	
}

//Declaration_list -> Declaration Declaration_list1Linha 
int Declaration_list(){
	if(Declaration()){
		if (Declaration_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration_list1Linha -> Declaration Declaration_list1Linha | ? 
int Declaration_list1Linha(){
	if(Declaration()){
		if (Declaration_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}




//Parameter_type_list -> Parameter_list 
int Parameter_type_list(){
	if (Parameter_list()){
		return 1;
	}
	else{return 0;}
}

//Parameter_list -> Parameter_declaration Parameter_list1Linha 
int Parameter_list(){
	if(Parameter_declaration()){
		if (Parameter_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Parameter_list1Linha -> , Parameter_declaration Parameter_list1Linha | ? 
int Parameter_list1Linha(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Parameter_declaration()){
			if (Parameter_list1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Parameter_declaration -> Declaration_specifiers Declarator 
int Parameter_declaration(){
	if(Declaration_specifiers()){
		if (Declarator()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration_specifiers -> int | float | char | void 
int Declaration_specifiers(){
	if(tk == TKInt){// int
		getToken();
		return 1;
	}
	else if(tk == TKFloat){// float
		getToken();
		return 1;
	}
	else if(tk == TKChar){// char
		getToken();
		return 1;
	}
	else if(tk == TKVoid){// void
		getToken();
		return 1;
	}
	else{return 0;}
}

//Declarator -> Direct_declarator 
int Declarator(){
	if (Direct_declarator()){
		return 1;
	}
	else{return 0;}
}

//Direct_declarator -> identifier Direct_declarator1Linha | ( Direct_declarator ) Direct_declarator1Linha 
int Direct_declarator(){
	if(tk == TKId){// identifier
		printf("Achou id\n");
		getToken(); 
		if (Direct_declarator1Linha()){
			printf("Direct_declarator1Linha\n");
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKAbreParenteses){// (
		printf("Achou ( \n");
		getToken(); 
		if (Direct_declarator()){
			if(tk == TKFechaParenteses){// )
				printf("Achou ) \n");
				getToken();
				if (Direct_declarator1Linha()){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Direct_declarator1Linha -> ( Direct_declarator2Linha | ? 
int Direct_declarator1Linha(){
	if(tk == TKAbreParenteses){// (
		printf("Achou (\n");
		getToken(); 
		if (Direct_declarator2Linha()){
			printf("Direct_declarator2Linha\n");
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Direct_declarator2Linha -> Parameter_type_list ) Direct_declarator2Linha | Identifier_list ) Direct_declarator2Linha | ) Direct_declarator2Linha 
int Direct_declarator2Linha(){
	if(Parameter_type_list()){
		printf("Achou Parameter_type_list\n");
		if(tk == TKFechaParenteses){// )
			printf("Achou )\n");
			return 1;
		}
		else{return 0;}
	}
	else if(Identifier_list()){
		printf("Achou Identifier_list\n");
		if(tk == TKFechaParenteses){// )
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKFechaParenteses){// )
		getToken();
		printf("Achou )\n");
		return 1;
	}
	else{printf("Erro Direct_declarator2Linha\n");return 0;}
}

//Identifier_list -> identifier Identifier_list1Linha 
int Identifier_list(){
	if(tk == TKId){// identifier
		printf("Achou id\n");
		getToken(); 
		if (Identifier_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Identifier_list1Linha -> , identifier Identifier_list1Linha | ? 
int Identifier_list1Linha(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if(tk == TKId){// identifier
			getToken();
			if (Identifier_list1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Statement -> Compound_statement | Expression_statement | Selection_statement | Iteration_statement | Jump_statement 
int Statement(){
	printf("TK:%d",tk);
	if (Compound_statement()){
		return 1;
	}
	else if (Expression_statement()){
		return 1;
	}
	else if (Selection_statement()){
		return 1;
	}
	else if (Iteration_statement()){
		return 1;
	}
	else if (Jump_statement()){
		return 1;
	}
	else{return 0;}
}

//Statement_list -> Statement Statement_list1Linha 
int Statement_list(){
	if(Statement()){
		if (Statement_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Statement_list1Linha -> Statement Statement_list1Linha | ? 
int Statement_list1Linha(){
	if(Statement()){
		if (Statement_list1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Compound_statement -> { Compound_statement1Linha 
int Compound_statement(){
	printf("Compound_statement - tk:%d\n",tk);
	if(tk == TKAbreChaves){// {
	printf("Achou {\n");
		getToken(); 
		if (Compound_statement1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Compound_statement1Linha -> } | Statement_list } | Declaration_list Compound_statement2Linha 
int Compound_statement1Linha(){
	if(tk == TKFechaChaves){// }
		getToken();
		return 1;
	}
	else if(Statement_list()){
		printf("Statement_list\n");
		if(tk == TKFechaChaves){// }
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else if(Declaration_list()){
		printf("Declaration_list\n");
		if (Compound_statement2Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Compound_statement2Linha -> } | Statement_list } 
int Compound_statement2Linha(){
	printf("ta aqui\n");
	if(tk == TKFechaChaves){// }
		getToken();
		return 1;
	}
	else if(Statement_list()){
		if(tk == TKFechaChaves){// }
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression_statement -> ; | Expression ; 
int Expression_statement(){
	if(tk == TKPontoEVirgula){// ;
		getToken();
		return 1;
	}
	else if(Expression()){
		if(tk == TKPontoEVirgula){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Selection_statement -> if ( Expression ) Statement Selection_statement1Linha 
int Selection_statement(){
	if(tk == TKIf){// if
		getToken(); 
		if(tk == TKAbreParenteses){// (
			getToken();
			if (Expression()){
				if(tk == TKFechaParenteses){// )
					getToken();
					if (Statement()){
						if (Selection_statement1Linha()){
							return 1;
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Selection_statement1Linha -> else Statement | ? 
int Selection_statement1Linha(){
	if(tk == TKElse){// else
		getToken(); 
		if (Statement()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Iteration_statement -> while ( Expression ) Statement | do Statement while ( Expression ) ; | for ( Expression_statement Expression_statement Iteration_statement1Linha 
int Iteration_statement(){
	if(tk == TKWhile){// while
		getToken(); 
		if(tk == TKAbreParenteses){// (
			getToken();
			if (Expression()){
				if(tk == TKFechaParenteses){// )
					getToken();
					if (Statement()){
						return 1;
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKDo){// do
		getToken(); 
		if (Statement()){
			if(tk == TKWhile){// while
				getToken();
				if(tk == TKAbreParenteses){// (
					getToken();
					if (Expression()){
						if(tk == TKFechaParenteses){// )
							getToken();
							if(tk == TKPontoEVirgula){// ;
								getToken();
								return 1;
							}
							else{return 0;}
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKFor){// for
		getToken(); 
		if(tk == TKAbreParenteses){// (
			getToken();
			if (Expression_statement()){
				if (Expression_statement()){
					if (Iteration_statement1Linha()){
						return 1;
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Iteration_statement1Linha -> ) Statement | Expression ) Statement 
int Iteration_statement1Linha(){
	if(tk == TKFechaParenteses){// )
		getToken(); 
		if (Statement()){
			return 1;
		}
		else{return 0;}
	}
	else if(Expression()){
		if(tk == TKFechaParenteses){// )
			getToken();
			if (Statement()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Jump_statement -> goto identifier ; | continue ; | break ; | return Jump_statement1Linha 
int Jump_statement(){
	if(tk == TKGoto){// goto
		getToken(); 
		if(tk == TKId){// identifier
			getToken();
			if(tk == TKPontoEVirgula){// ;
				getToken();
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKContinue){// continue
		getToken(); 
		if(tk == TKPontoEVirgula){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKBreak){// break
		getToken(); 
		if(tk == TKPontoEVirgula){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKReturn){// return
		getToken(); 
		if (Jump_statement1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Jump_statement1Linha -> ; | Expression ; 
int Jump_statement1Linha(){
	if(tk == TKPontoEVirgula){// ;
		getToken();
		return 1;
	}
	else if(Expression()){
		if(tk == TKPontoEVirgula){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression -> ExpressionA Expression1Linha 
int Expression(){
	if(ExpressionA()){
		if (Expression1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression1Linha -> + ExpressionA Expression1Linha | - ExpressionA Expression1Linha | * ExpressionA Expression1Linha | / ExpressionA Expression1Linha | % ExpressionA Expression1Linha | ? 
int Expression1Linha(){
	if(tk == TKSoma){// +
		getToken(); 
		if (ExpressionA()){
			if (Expression1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKSub){// -
		getToken(); 
		if (ExpressionA()){
			if (Expression1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKProd){// *
		getToken(); 
		if (ExpressionA()){
			if (Expression1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKDiv){// /
		getToken(); 
		if (ExpressionA()){
			if (Expression1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRestoDiv){// %
		getToken(); 
		if (ExpressionA()){
			if (Expression1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//ExpressionA -> ExpressionB ExpressionA1Linha 
int ExpressionA(){
	if(ExpressionB()){
		if (ExpressionA1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//ExpressionA1Linha -> & ExpressionB ExpressionA1Linha | bitor ExpressionB ExpressionA1Linha | ^ ExpressionB ExpressionA1Linha | ~ ExpressionB ExpressionA1Linha | ? 
int ExpressionA1Linha(){
	if(tk == TKBitAND){// &
		getToken(); 
		if (ExpressionB()){
			if (ExpressionA1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKBitOR){// bitor
		getToken(); 
		if (ExpressionB()){
			if (ExpressionA1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKBitXOR){// ^
		getToken(); 
		if (ExpressionB()){
			if (ExpressionA1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKBitNOT){// ~
		getToken(); 
		if (ExpressionB()){
			if (ExpressionA1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//ExpressionB -> ExpressionC ExpressionB1Linha 
int ExpressionB(){
	if(ExpressionC()){
		if (ExpressionB1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//ExpressionB1Linha -> == ExpressionC ExpressionB1Linha | != ExpressionC ExpressionB1Linha | > ExpressionC ExpressionB1Linha | < ExpressionC ExpressionB1Linha | >= ExpressionC ExpressionB1Linha | <= ExpressionC ExpressionB1Linha | ? 
int ExpressionB1Linha(){
	if(tk == TKRelacIGUAL){// ==
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacDIFERENTE){// !=
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMAIORQUE){// >
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMENORQUE){// <
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMAIORouIGUAL){// >=
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMENORouIGUAL){// <=
		getToken(); 
		if (ExpressionC()){
			if (ExpressionB1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//ExpressionC -> ExpressionD ExpressionC1Linha 
int ExpressionC(){
	if(ExpressionD()){
		if (ExpressionC1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//ExpressionC1Linha -> && ExpressionD ExpressionC1Linha | or ExpressionD ExpressionC1Linha | ! ExpressionD ExpressionC1Linha | ? 
int ExpressionC1Linha(){
	if(tk == TKLogicoAND){// &&
		getToken(); 
		if (ExpressionD()){
			if (ExpressionC1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKLogicoOR){// or
		getToken(); 
		if (ExpressionD()){
			if (ExpressionC1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKLogicoNot){// !
		getToken(); 
		if (ExpressionD()){
			if (ExpressionC1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//ExpressionD -> num | identifier | ( Expression ) 
int ExpressionD(){
	if(tk == TKConsInteiro){// num
		getToken();
		return 1;
	}
	else if(tk == TKId){// identifier
		getToken();
		return 1;
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Expression()){
			if(tk == TKFechaParenteses){// )
				getToken();
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//External_declaration -> Function_definition | Declaration 
int External_declaration(){
	if (Function_definition()){
		printf("Entrou Function_definition\n");
		return 1;
	}
	else if (Declaration()){
	printf("Entrou Declaration\n");

		return 1;
	}
	else{return 0;}
}

//Translation_unit -> External_declaration Translation_unit1Linha 
int Translation_unit(){
	if(External_declaration()){
		if (Translation_unit1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Translation_unit1Linha -> External_declaration Translation_unit1Linha | ? 
int Translation_unit1Linha(){
	if(External_declaration()){
		if (Translation_unit1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Function_definition -> Declaration_specifiers Declarator Function_definition’ | Declarator Function_definition’ 
int Function_definition(){
	if(Declaration_specifiers()){
		printf("Declaration_specifiers\n");
		if (Declarator()){
			printf("Declarator\n");
			if (Function_definitionLinha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Declarator()){
		if (Function_definitionLinha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Function_definition’ -> Declaration_list Compound_statement | Compound_statement 
int Function_definitionLinha(){
	printf("aqui");
	if(Declaration_list()){
		if (Compound_statement()){
			return 1;
		}
		else{return 0;}
	}
	else if (Compound_statement()){
		return 1;
	}
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>


void analisadorSintatico(){
	proxC(); // lê primeiro caracter do arquivo
	getToken(); // lê primeiro token
	
	if (Translation_unit()==0) printf("Erro no reconhecimento\n");
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
	
	/*arqin=fopen("fonte.c","rb");
	proxC(); // lê primeiro caracter do arquivo
	getToken(); // lê primeiro token
	while (tk!=TKFimArquivo)
	{
		printf("%d\n\n",tk);
		getToken();
	}*/
	
}
