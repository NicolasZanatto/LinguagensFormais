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
#define TKAtribMul 49
#define TKAtribDiv 50
#define TKAtribRes 51
#define TKAtribSom 52
#define TKAtribSub 53
#define TKAtribShiftLeft 54
#define TKAtribShiftRight 55
#define TKAtribAnd 56
#define TKAtribXor 57
#define TKAtribOr 58
#define TKPonto 59
#define TKFlecha 60
#define TKShiftLeft 61
#define TKShiftRight 62
#define TKUnion 63
#define TKSizeof 64

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
                  {"union", TKUnion},
                  {"sizeof", TKUnion},
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
	printf("posglobal:%ld,tk:%d\n",posglobal,tk);
	posglobal=ftell(arqin);
	printf("posglobal:%ld,tk:%d\n",posglobal,tk);
	tkant=tk;
}

//Implemente aqui a sua função restauraPosToken()

void restauraPosToken() {
	fseek(arqin,posglobal-1,SEEK_SET);
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
printf("Leu caracter %c\n",c);
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
				else if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribSom;printf("Reconheceu token TKAtribSom\n");return;
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
				else if (c=='=')
			    {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribSub;printf("Reconheceu token TKAtribSub\n");return;
				}
				else if (c=='>')
			    {
				   lex[posl++]='>';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKFlecha;printf("Reconheceu token TKFlecha\n");return;
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
			    else if (c=='=')
			    {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribOr;printf("Reconheceu token TKAtribOr\n");return;
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
			    else if (c=='=')
		    	{
				   lex[posl++]='=';
	 			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribAnd;printf("Reconheceu token TKAtribAnd\n");return;
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
				else if(c == '>'){
					proxC();
					if (c=='=')
			        {
					   lex[posl++]='=';
	     			   lex[posl]='\0';
					   proxC();
					   tk=TKAtribShiftRight;printf("Reconheceu token TKAtribShiftRight\n");return;
				    }
				    else{
				    	lex[posl]='\0';
				   		tk=TKShiftRight;printf("Reconheceu token TKShiftRight\n");return;
					}
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
				else if(c == '<'){
					proxC();
					if (c=='=')
			        {
					   lex[posl++]='=';
	     			   lex[posl]='\0';
					   proxC();
					   tk=TKAtribShiftLeft;printf("Reconheceu token TKAtribShiftLeft\n");return;
				    }
				    else{
				    	lex[posl]='\0';
				   		tk=TKShiftLeft;printf("Reconheceu token TKShiftLeft\n");return;
					}
				}
				else
				   {
	               lex[posl]='\0';
				   tk=TKRelacMENORQUE;printf("Reconheceu token TKRelacMENORQUE\n");return;
				   }
			 }
			 if (c=='*')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribMul;printf("Reconheceu token TKAtribMul\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKProd;printf("Reconheceu token TKProd\n");return;
				   }
			 }
			 if (c=='/')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribDiv;printf("Reconheceu token TKAtribDiv\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKDiv;printf("Reconheceu token TKDiv\n");return;
				   }
			 }
			 if (c=='%')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribRes;printf("Reconheceu token TKAtribRes\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKRestoDiv;printf("Reconheceu token TKRestoDiv\n");return;
				   }
			 }
			 if (c=='^')
			 {
			    proxC();
				if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribXor;printf("Reconheceu token TKAtribXor\n");return;
				   }
				else
				   {
	               lex[posl]='\0';
				   tk=TKBitXOR;printf("Reconheceu token TKBitXOR\n");return;
				   }
			 }
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbreParenteses;printf("Reconheceu token TKAbrePar\n");return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaParenteses;printf("Reconheceu token FechaPar\n");return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;printf("Reconheceu token TKAbreChaves\n");return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;printf("Reconheceu token TKFechaChaves\n");return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;printf("Reconheceu token TKVirgula\n");return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;printf("Reconheceu token TKPontoEVirgula\n");return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;printf("Reconheceu token TKDoisPontos\n");return;}
             if (c=='.'){lex[posl]='\0';proxC();tk=TKPonto;printf("Reconheceu token TKPonto\n");return;}
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

int Parameter_declaration1Linha();

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

int External_declaration();

int Translation_unit();

int Translation_unit1Linha();

int Function_definition();

int Function_definitionLinha();

int Expression();

int Expression1Hash();

int Assignment_expression();

int Assignment_operator();

int Unary_expression();

int Unary_expression1Linha();

int Postfix_expression();

int Postfix_expression1Hash();

int Postfix_expressionHash1Linha();

int Primary_expression();

int Argument_expression_list();

int Argument_expression_list1Hash();

int Unary_operator();

int Cast_expression();

int Type_name();

int Type_name1Linha();

int Specifier_qualifier_list();

int Abstract_declarator();

int Direct_abstract_declarator();

int Direct_abstract_declarator1Linha();

int Direct_abstract_declarator1Hash();

int Direct_abstract_declaratorHash1Linha();

int Constant_expression();

int Conditional_expression();

int Logical_or_expression();

int Logical_or_expression1Hash();

int Logical_and_expression();

int Logical_and_expression1Hash();

int Inclusive_or_expression();

int Inclusive_or_expression1Hash();

int Exclusive_or_expression();

int Exclusive_or_expression1Hash();

int And_expression();

int And_expression1Hash();

int Equality_expression();

int Equality_expression1Hash();

int Relational_expression();

int Relational_expression1Hash();

int Shift_expression();

int Shift_expression1Hash();

int Additive_expression();

int Additive_expression1Hash();

int Multiplicative_expression();

int Multiplicative_expression1Hash();

int Struct_or_union_specifier();

int Struct_or_union_specifier1Linha();

int Struct_or_union();

int Struct_declaration_list();

int Struct_declaration_list1Hash();

int Struct_declaration();

int Struct_declarator_list();

int Struct_declarator_list1Hash();

int Struct_declarator();

int Struct_declarator1Linha();

int Type_specifier();

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
	if(Declaration_specifiers()){
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
	printf("kkk2\n");
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

//Parameter_declaration -> Declaration_specifiers Parameter_declaration1Linha 
int Parameter_declaration(){
	if(Declaration_specifiers()){
		if (Parameter_declaration1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Parameter_declaration1Linha -> Declarator | Abstract_declarator | ? 
int Parameter_declaration1Linha(){
	if (Declarator()){
		return 1;
	}
	else if (Abstract_declarator()){
		return 1;
	}
	else {return 1;}
}

//Declarator -> Type_specifier 
int Declaration_specifiers(){
	if (Type_specifier()){
		return 1;
	}
	else{return 0;}
}

//Type_specifier -> int | float | char | void  | Struct_or_union_specifier
int Type_specifier(){
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
	else if(Struct_or_union_specifier()){
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
		getToken(); 
		if (Direct_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Direct_declarator()){
			if(tk == TKFechaParenteses){// )
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
		getToken(); 
		if (Direct_declarator2Linha()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Direct_declarator2Linha -> Parameter_type_list ) Direct_declarator2Linha | Identifier_list ) Direct_declarator2Linha | ) Direct_declarator2Linha 
int Direct_declarator2Linha(){
	if(Parameter_type_list()){
		if(tk == TKFechaParenteses){// )
			return 1;
		}
		else{return 0;}
	}
	else if(Identifier_list()){
		if(tk == TKFechaParenteses){// )
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKFechaParenteses){// )
		getToken();
		return 1;
	}
	else{return 0;}
}

//Identifier_list -> identifier Identifier_list1Linha 
int Identifier_list(){
	if(tk == TKId){// identifier
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
	printf("kkk3\n");
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
	if(tk == TKAbreChaves){// {
		printf("cs\n");
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
	printf("kkk\n");
	if(tk == TKFechaChaves){// }
		getToken();
		return 1;
	}
	else if(Declaration_list()){
		if (Compound_statement2Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(Statement_list()){
		printf("Statement_list\n");
		if(tk == TKFechaChaves){// }
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Compound_statement2Linha -> } | Statement_list } 
int Compound_statement2Linha(){
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
		printf("kkk4 tk:%d\n",tk);
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
				printf("linha 1135\n");
				if(tk == TKFechaParenteses){// )
					printf("fechaParenteses\n");
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


//Expression -> Assignment_expression Expression1Hash 
int Expression(){
	if(Assignment_expression()){
		printf("dentro de Assignment_expression\n");
		if (Expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression1Hash -> , Assignment_expression Expression1Hash | ? 
int Expression1Hash(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Assignment_expression()){
			printf("dentro de Assignment_expression\n");
			if (Expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Assignment_expression -> Unary_expression Assignment_operator Assignment_expression | Conditional_expression 
int Assignment_expression(){
	marcaPosToken();
	if(Unary_expression()){
		printf("gg4\n");
		if (Assignment_operator()){
			if (Assignment_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{restauraPosToken();}
	}
	if (Conditional_expression()){
		printf("gg5\n");
		return 1;
	}
	else{return 0;}
}

//Assignment_operator -> = | *= | /= | %= | += | -= | <<= | >>= | &= | ^= | or_assign 
int Assignment_operator(){
	if(tk == TKAtrib){// =
		getToken();
		return 1;
	}
	else if(tk == TKAtribMul){// *=
		getToken();
		return 1;
	}
	else if(tk == TKAtribDiv){// /=
		getToken();
		return 1;
	}
	else if(tk == TKAtribRes){// %=
		getToken();
		return 1;
	}
	else if(tk == TKAtribSom){// +=
		getToken();
		return 1;
	}
	else if(tk == TKAtribSub){// -=
		getToken();
		return 1;
	}
	else if(tk == TKAtribShiftLeft){// <<=
		getToken();
		return 1;
	}
	else if(tk == TKAtribShiftRight){// >>=
		getToken();
		return 1;
	}
	else if(tk == TKAtribAnd){// &=
		getToken();
		return 1;
	}
	else if(tk == TKAtribXor){// ^=
		getToken();
		return 1;
	}
	else if(tk == TKAtribOr){// or_assign
		getToken();
		return 1;
	}
	else{return 0;}
}

//Unary_expression -> Postfix_expression | ++ Unary_expression | -- Unary_expression | Unary_operator Cast_expression | SIZEOF Unary_expression1Linha 
int Unary_expression(){
	if (Postfix_expression()){
		printf("gg2\n");
		return 1;
	}
	else if(tk == TKDuploMais){// ++
		getToken(); 
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKDuploSub){// --
		getToken(); 
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(Unary_operator()){
		if (Cast_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKSizeof){// sizeof
		getToken(); 
		if (Unary_expression1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Unary_expression1Linha -> Unary_expression | ( Type_name ) 
int Unary_expression1Linha(){
	if (Unary_expression()){
		return 1;
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Type_name()){
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

//Postfix_expression -> Primary_expression Postfix_expression1Hash 
int Postfix_expression(){
	if(Primary_expression()){
		if (Postfix_expression1Hash()){
			printf("gg tk: %d\n",tk);
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Postfix_expression1Hash -> [ Expression ] Postfix_expression1Hash | ( Postfix_expressionHash1Linha | . id Postfix_expression1Hash | -> id Postfix_expression1Hash | ++ Postfix_expression1Hash | -- Postfix_expression1Hash | ? 
int Postfix_expression1Hash(){
	if(tk == TKAbreColchete){// [
		getToken(); 
		if (Expression()){
			if(tk == TKFechaColchete){// ]
				getToken();
				if (Postfix_expression1Hash()){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Postfix_expressionHash1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKPonto){// .
		getToken(); 
		if(tk == TKId){// id
			getToken();
			if (Postfix_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKFlecha){// ->
		getToken(); 
		if(tk == TKId){// id
			getToken();
			if (Postfix_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKDuploMais){// ++
		getToken(); 
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKDuploSub){// --
		getToken(); 
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Postfix_expressionHash1Linha -> ) Postfix_expression1Hash | Argument_expression_list ) Postfix_expression1Hash 
int Postfix_expressionHash1Linha(){
	if(tk == TKFechaParenteses){// )
		getToken(); 
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(Argument_expression_list()){
		if(tk == TKFechaParenteses){// )
			getToken();
			if (Postfix_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Primary_expression -> id | number | string | ( Expression ) 
int Primary_expression(){
	printf("PE tk=%d\n",tk);
	if(tk == TKId){// id
		getToken();
		return 1;
	}
	else if(tk == TKConsInteiro){// number
		getToken();
		return 1;
	}
	else if(tk == TKConsString){// string
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

//Argument_expression_list -> Assignment_expression Argument_expression_list1Hash 
int Argument_expression_list(){
	if(Assignment_expression()){
		if (Argument_expression_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Argument_expression_list1Hash -> , Assignment_expression Argument_expression_list1Hash | ? 
int Argument_expression_list1Hash(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Assignment_expression()){
			if (Argument_expression_list1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Unary_operator -> & | * | + | - | ~ | ! 
int Unary_operator(){
	if(tk == TKBitAND){// &
		getToken();
		return 1;
	}
	else if(tk == TKProd){// *
		getToken();
		return 1;
	}
	else if(tk == TKSoma){// +
		getToken();
		return 1;
	}
	else if(tk == TKSub){// -
		getToken();
		return 1;
	}
	else if(tk == TKBitNOT){// ~
		getToken();
		return 1;
	}
	else if(tk == TKLogicoNot){// !
		getToken();
		return 1;
	}
	else{return 0;}
}

//Cast_expression -> Unary_expression | ( Type_name ) Cast_expression 
int Cast_expression(){
	if (Unary_expression()){
		return 1;
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Type_name()){
			if(tk == TKFechaParenteses){// )
				getToken();
				if (Cast_expression()){
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

//Type_name -> Specifier_qualifier_list Type_name1Linha 
int Type_name(){
	if(Specifier_qualifier_list()){
		if (Type_name1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Type_name1Linha -> ? | Abstract_declarator 
int Type_name1Linha(){
return 1;
if (Abstract_declarator()){
		return 1;
	}
	else{return 0;}
}

//Specifier_qualifier_list -> Type_specifier 
int Specifier_qualifier_list(){
	if (Type_specifier()){
		return 1;
	}
	else{return 0;}
}

//Abstract_declarator -> Direct_abstract_declarator 
int Abstract_declarator(){
	if (Direct_abstract_declarator()){
		return 1;
	}
	else{return 0;}
}

//Direct_abstract_declarator -> ( Direct_abstract_declarator1Linha | [ Direct_abstract_declarator1Linha 
int Direct_abstract_declarator(){
	if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Direct_abstract_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKAbreColchete){// [
		getToken(); 
		if (Direct_abstract_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Direct_abstract_declarator1Linha -> ] Direct_abstract_declarator1Hash | Constant_expression ] Direct_abstract_declarator1Hash | Abstract_declarator ) Direct_abstract_declarator1Hash | ) Direct_abstract_declarator1Hash | Parameter_type_list ) Direct_abstract_declarator1Hash 
int Direct_abstract_declarator1Linha(){
	if(tk == TKFechaColchete){// ]
		getToken(); 
		if (Direct_abstract_declarator1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(Constant_expression()){
		if(tk == TKFechaColchete){// ]
			getToken();
			if (Direct_abstract_declarator1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Abstract_declarator()){
		if(tk == TKFechaParenteses){// )
			getToken();
			if (Direct_abstract_declarator1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKFechaParenteses){// )
		getToken(); 
		if (Direct_abstract_declarator1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(Parameter_type_list()){
		if(tk == TKFechaParenteses){// )
			getToken();
			if (Direct_abstract_declarator1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Direct_abstract_declarator1Hash -> [ Direct_abstract_declaratorHash1Linha | ( Direct_abstract_declaratorHash1Linha | ? 
int Direct_abstract_declarator1Hash(){
	if(tk == TKAbreColchete){// [
		getToken(); 
		if (Direct_abstract_declaratorHash1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKAbreParenteses){// (
		getToken(); 
		if (Direct_abstract_declaratorHash1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Direct_abstract_declaratorHash1Linha -> ) Direct_abstract_declarator1Hash | Parameter_type_list ) Direct_abstract_declarator1Hash | ] Direct_abstract_declarator1Hash | Constant_expression ] Direct_abstract_declarator1Hash 
int Direct_abstract_declaratorHash1Linha(){
	if(tk == TKFechaParenteses){// )
		getToken(); 
		if (Direct_abstract_declarator1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(Parameter_type_list()){
		if(tk == TKFechaParenteses){// )
			getToken();
			if (Direct_abstract_declarator1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKFechaColchete){// ]
		getToken(); 
		if (Direct_abstract_declarator1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(Constant_expression()){
		if(tk == TKFechaColchete){// ]
			getToken();
			if (Direct_abstract_declarator1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Constant_expression -> Conditional_expression 
int Constant_expression(){
	if (Conditional_expression()){
		return 1;
	}
	else{return 0;}
}

//Conditional_expression -> Logical_or_expression 
int Conditional_expression(){
	if (Logical_or_expression()){
		return 1;
	}
	else{return 0;}
}

//Logical_or_expression -> Logical_and_expression Logical_or_expression1Hash 
int Logical_or_expression(){
	if(Logical_and_expression()){
		if (Logical_or_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Logical_or_expression1Hash -> or Logical_and_expression Logical_or_expression1Hash | ? 
int Logical_or_expression1Hash(){
	if(tk == TKLogicoOR){// or
		getToken(); 
		if (Logical_and_expression()){
			if (Logical_or_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Logical_and_expression -> Inclusive_or_expression Logical_and_expression1Hash 
int Logical_and_expression(){
	if(Inclusive_or_expression()){
		if (Logical_and_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Logical_and_expression1Hash -> && Inclusive_or_expression Logical_and_expression1Hash | ? 
int Logical_and_expression1Hash(){
	if(tk == TKLogicoAND){// &&
		getToken(); 
		if (Inclusive_or_expression()){
			if (Logical_and_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Inclusive_or_expression -> Exclusive_or_expression Inclusive_or_expression1Hash 
int Inclusive_or_expression(){
	if(Exclusive_or_expression()){
		if (Inclusive_or_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Inclusive_or_expression1Hash -> bitor Exclusive_or_expression Inclusive_or_expression1Hash | ? 
int Inclusive_or_expression1Hash(){
	if(tk == TKBitOR){// bitor
		getToken(); 
		if (Exclusive_or_expression()){
			if (Inclusive_or_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Exclusive_or_expression -> And_expression Exclusive_or_expression1Hash 
int Exclusive_or_expression(){
	if(And_expression()){
		if (Exclusive_or_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Exclusive_or_expression1Hash -> ^ And_expression Exclusive_or_expression1Hash | ? 
int Exclusive_or_expression1Hash(){
	if(tk == TKBitXOR){// ^
		getToken(); 
		if (And_expression()){
			if (Exclusive_or_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//And_expression -> Equality_expression And_expression1Hash 
int And_expression(){
	if(Equality_expression()){
		if (And_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//And_expression1Hash -> & Equality_expression And_expression1Hash | ? 
int And_expression1Hash(){
	if(tk == TKBitAND){// &
		getToken(); 
		if (Equality_expression()){
			if (And_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Equality_expression -> Relational_expression Equality_expression1Hash 
int Equality_expression(){
	if(Relational_expression()){
		if (Equality_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Equality_expression1Hash -> == Relational_expression Equality_expression1Hash | != Relational_expression Equality_expression1Hash | ? 
int Equality_expression1Hash(){
	if(tk == TKRelacIGUAL){// ==
		getToken(); 
		if (Relational_expression()){
			if (Equality_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacDIFERENTE){// !=
		getToken(); 
		if (Relational_expression()){
			if (Equality_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Relational_expression -> Shift_expression Relational_expression1Hash 
int Relational_expression(){
	if(Shift_expression()){
		if (Relational_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Relational_expression1Hash -> < Shift_expression Relational_expression1Hash | > Shift_expression Relational_expression1Hash | <= Shift_expression Relational_expression1Hash | >= Shift_expression Relational_expression1Hash | ? 
int Relational_expression1Hash(){
	if(tk == TKRelacMENORQUE){// <
		getToken(); 
		if (Shift_expression()){
			if (Relational_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMAIORQUE){// >
		getToken(); 
		if (Shift_expression()){
			if (Relational_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMENORouIGUAL){// <=
		getToken(); 
		if (Shift_expression()){
			if (Relational_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRelacMAIORouIGUAL){// >=
		getToken(); 
		if (Shift_expression()){
			if (Relational_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Shift_expression -> Additive_expression Shift_expression1Hash 
int Shift_expression(){
	if(Additive_expression()){
		if (Shift_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Shift_expression1Hash -> << Additive_expression Shift_expression1Hash | >> Additive_expression Shift_expression1Hash | ? 
int Shift_expression1Hash(){
	if(tk == TKShiftLeft){// <<
		getToken(); 
		if (Additive_expression()){
			if (Shift_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKShiftRight){// >>
		getToken(); 
		if (Additive_expression()){
			if (Shift_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Additive_expression -> Multiplicative_expression Additive_expression1Hash 
int Additive_expression(){
	if(Multiplicative_expression()){
		if (Additive_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Additive_expression1Hash -> + Multiplicative_expression Additive_expression1Hash | - Multiplicative_expression Additive_expression1Hash | ? 
int Additive_expression1Hash(){
	if(tk == TKSoma){// +
		getToken(); 
		if (Multiplicative_expression()){
			if (Additive_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKSub){// -
		getToken(); 
		if (Multiplicative_expression()){
			if (Additive_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Multiplicative_expression -> Cast_expression Multiplicative_expression1Hash 
int Multiplicative_expression(){
	if(Cast_expression()){
		if (Multiplicative_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Multiplicative_expression1Hash -> * Cast_expression Multiplicative_expression1Hash | / Cast_expression Multiplicative_expression1Hash | % Cast_expression Multiplicative_expression1Hash | ? 
int Multiplicative_expression1Hash(){
	if(tk == TKProd){// *
		getToken(); 
		if (Cast_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKDiv){// /
		getToken(); 
		if (Cast_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == TKRestoDiv){// %
		getToken(); 
		if (Cast_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Struct_or_union_specifier -> Struct_or_union id Struct_or_union_specifier1Linha 
int Struct_or_union_specifier(){
	if(Struct_or_union()){
		if(tk == TKId){// id
			getToken();
			if (Struct_or_union_specifier1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Struct_or_union_specifier1Linha -> { Struct_declaration_list } | ? 
int Struct_or_union_specifier1Linha(){
	if(tk == TKAbreChaves){// {
		getToken(); 
		if (Struct_declaration_list()){
			if(tk == TKFechaChaves){// }
				getToken();
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Struct_or_union -> struct | union 
int Struct_or_union(){
	if(tk == TKStruct){// struct
		getToken();
		return 1;
	}
	else if(tk == TKUnion){// union
		getToken();
		return 1;
	}
	else{return 0;}
}

//Struct_declaration_list -> Struct_declaration Struct_declaration_list1Hash 
int Struct_declaration_list(){
	if(Struct_declaration()){
		if (Struct_declaration_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Struct_declaration_list1Hash -> Struct_declaration Struct_declaration_list1Hash | ? 
int Struct_declaration_list1Hash(){
	if(Struct_declaration()){
		if (Struct_declaration_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Struct_declaration -> Specifier_qualifier_list Struct_declarator_list ; 
int Struct_declaration(){
	if(Specifier_qualifier_list()){
		if (Struct_declarator_list()){
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

//Struct_declarator_list -> Struct_declarator Struct_declarator_list1Hash 
int Struct_declarator_list(){
	if(Struct_declarator()){
		if (Struct_declarator_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Struct_declarator_list1Hash -> , Struct_declarator Struct_declarator_list1Hash | ? 
int Struct_declarator_list1Hash(){
	if(tk == TKVirgula){// ,
		getToken(); 
		if (Struct_declarator()){
			if (Struct_declarator_list1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Struct_declarator -> Declarator Struct_declarator1Linha | : Constant_expression 
int Struct_declarator(){
	if(Declarator()){
		if (Struct_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == TKDoisPontos){// :
		getToken(); 
		if (Constant_expression()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Struct_declarator1Linha -> ? | : Constant_expression 
int Struct_declarator1Linha(){
if(tk == TKDoisPontos){// :
		getToken(); 
		if (Constant_expression()){
			return 1;
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
		if (Declarator()){
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
