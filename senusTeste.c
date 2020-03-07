#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "senus.h"
 
/*
#define NUMERO_ARGUMENTOS           2
 numeroInvalidoArgumentos
 erroFlagInvalida
 */
int
main (int argc, char **argv)
{
	tipoErros validacao,validacao2,validacao3;
	/*validacao e para usuario, validacao 2 para senha e 3 para a flag em questao*/
	int opcao;
	unsigned indice,auxiliar;
	const char *opcoesCurtas = "h:e:v:c:p:s:n:l:";

	opterr = 0; /*para nao mostrar nenhuma mensagem de erro por parte da getopt*/
	if (argc<NUMERO_ARGUMENTOS)
	{
		printf ("ERRO#%u: Colocou Um Numero De Argumentos Invalido\n", numeroInvalidoArgumentos);
		printf ("Para ajuda use a flag -h\n");
		printf ("USO: %s [flag] <argumento-para-flag> [flag] <argumento-para-flag> ... [ultima-flag] <argumento-para-flag>\n\n", argv[0]);
		exit(numeroInvalidoArgumentos);
	}
 
	while ((opcao = getopt(argc,argv,opcoesCurtas)) != (-1)) /*opcao tera o valor do caracter da flag desejada, quando tudo termina retorna -1, dando tudo ok.*/
	{
		printf ("\n");
		if (optopt=='h')
			opcao='h'; /*faz com que os que nao precisam de argumentos (h em questao) sejam executados*/

		if (opcao=='?') /*quando encontrado algo diferente das opcoes Desejadas*/
		{ 
			for(indice=2;opcoesCurtas[indice]!=EOS;indice++) /*comeca do e em diante*/
			{
				if (optopt==opcoesCurtas[indice]) /*para quando encontramos um caracter das opcoesCurtas*/
				{
					printf ("Erro%u: \'%c\' precisa de argumento. Por favor coloque.\n", flagSemArgumento,optopt);
					printf ("Para ajuda use a flag -h\n");
					printf ("USO: %s [flag] <argumento-para-flag> [flag] <argumento-para-flag> ... [ultima-flag] <argumento-para-flag>\n\n", argv[0]);
					exit(flagSemArgumento);
				}
			}
			/*caso nenhum seja, e pq se pediu uma flag que nao e uma das possiveis*/
			printf ("ERRO#%u: \'%c\' nao e uma das opcoes possiveis\n",erroFlagInvalida, optopt);
			printf ("Para ajuda use a flag -h\n");
			printf ("USO: %s [flag] <argumento-para-flag> [flag] <argumento-para-flag> ... [ultima-flag] <argumento-para-flag>\n\n", argv[0]);
			exit(erroFlagInvalida);
		}	

		if (opcao=='h') /*Explica*/
		{
			if (argv[optind-1][1]=='h')
			{
				printf ("Uso:%s -[%s] <argumento-para-flag-desejada>\n", argv[0],opcoesCurtas);
				showH();
			}
			else
			{
				printf ("Uso:%s -[%s] <argumento-para-flag-desejada>\n", argv[0],opcoesCurtas);
				optind--;
				showH();
			}
		}	

		if (opcao=='c') /*cadastro*/
		{ 
			printf ("%s deseja ser cadastrado no sistema\n\n", optarg);
			validacao=VerificaExiste(optarg);
			if (validacao!=ok)
				if (validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
          /*IMPLEMENTAR*/ /*grande case para dizer qual foi o erro*/
          printf ("\tNao foi possivel verificar se %s existe\n",optarg);
          exit (validacao);
				}
			if (validacao==ok)
				printf ("\t%s ja existe. Tente outro nome\n",optarg);
		
			if (validacao==usuarioNaoAchado)
			{
				printf ("\tNome de Usuario \"%s\" Disponivel\n",optarg);
				validacao3=CadastroUsuario(optarg);
				if (validacao3!=ok)
				{
					printf ("\tErro#%i:\n",validacao2);
					/*IMPLEMENTAR*/ /*grande case para dizer qual foi o erro*/
					printf ("\tnao foi possivel cadastrar um novo usuario.\n");
					exit (validacao3);
				}
				printf ("%s foi cadastrado.\n",optarg);
			}
		}/*fim do cadastro*/
     
		if (opcao=='e') /*Entra*/
		{
			printf ("%s deseja entrar!\n\n",optarg);
			validacao=VerificaExiste(optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if (validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
          /*IMPLEMENTAR*/ /*grande case para dizer qual foi o erro*/
          printf ("\tNao foi possivel verificar se %s existe\n",optarg);
          exit (validacao);
				}
			if (validacao==ok)
			{
				printf ("\t%s foi encontrado\n", optarg);
				auxiliar=0;
				for (indice=0;indice<TENTATIVAS;indice++)
				{
					validacao2=VerificaSenha(optarg);
	  			if (validacao2==ok)
						{
							printf ("\tSenha de %s correta\n", optarg);
							validacao3=EntrarSistema(optarg);
							/*fale que pode editar a senha, o e-mail, o nome do usuario, apagar a propria conta, ver seus dados e sair*/
							if (validacao3!=ok)
							{
								printf ("ERRO#%i:",validacao3);
								/*grande case para dizer qual foi o erro*/
								printf ("\t\tnao foi possivel entrar no sistema\n");
								exit (validacao3);
							}
							printf ("\tusuario %s entrou com sucesso\n",optarg);
							indice=TENTATIVAS;
						}
					if (validacao2==senhaDiferente)
					{
						printf ("\tsenha errada. Voce tem mais %u tentativas\n", (TENTATIVAS-1)-indice);
						auxiliar++;
					}
					if (validacao2!=ok)
						if (validacao2!=senhaDiferente)
						{
							printf ("\tErro#%i:\n",validacao2);
							/*grande case para dizer qual foi o erro*/
							printf ("\tNao foi possivel verificar senha de %s\n",optarg);
							exit (validacao2);
						}
				}
				if (auxiliar==TENTATIVAS)
				{
					printf ("voce passou do limite de tentativas.\n");
					/*IMPLEMENTAR*//*DISPARAR E-MAIL*/
				}		
			}  	
		}/*fim do entramento*/

		if (opcao=='v') /*verifica*/
		{
			validacao=VerificaExiste(optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if (validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
          /*grande case para dizer qual foi o erro*/
          printf ("\tNao foi possivel verificar se %s existe\n",optarg);
          exit (validacao);
				}
			if (validacao==ok)
				printf ("%s existe!\n",optarg);
		}/*fim da verificacao*/
 
		if (opcao=='p') /*apaga a conta*/
		{
			printf ("%s deseja apagar a sua conta\n", optarg);
		
	/*comeca verificacao da existencia da conta*/
			validacao = VerificaExiste (optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if(validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
					/*grande case para dizer qual foi o erro*/
					printf ("\tNao foi possivel verificar se %s existe\n",optarg);
					exit (validacao);
				}
			/*termina verificacao da existencia da conta*/
			auxiliar=0;
			
			if (validacao==ok) /*conta existe*/
			{
				printf ("\t%s Existe!\n", optarg);
				/*comeca verificacao da senha da conta*/
				auxiliar=TENTATIVAS;
				for(indice=TENTATIVAS ;indice !=0;indice--)
				{
					validacao2=VerificaSenha(optarg);
					if (validacao2!=ok)
					{
						if (validacao2!=senhaDiferente)
						{
							printf ("\tErro#%i:\n",validacao2);
							/*grande case para dizer qual foi o erro*/
							printf ("\tNao foi possivel verificar senha de %s\n",optarg);;
							exit(validacao2);
						}
						else
						{
							auxiliar--;
							printf ("\tsenha errada. Voce tem mais %u tentativas\n", auxiliar);
						}
					}
				}
			}/*termina verificacao da senha da conta*/
	
			if (auxiliar!=0) /*conta existe e acertou a senha*/
			{
				printf ("\tSenha de %s coreta\n", optarg);
        	 /*IMPLEMENTAR*/ /*PERGUNTA SE QUER MESMO APAGAR A CONTA*/
				validacao3=ApagarConta(optarg);
				if (validacao3!=ok)
				{
					printf ("ERRO#%i:",validacao3);
					/*grande case para dizer qual foi o erro*/
					printf ("\t\tnao foi possivel Apagar %s\n",optarg);
					exit (validacao3);
				}
				printf ("A conta \"%s\" foi apagada.\n", optarg);
			/*acaba Apagar conta*/
			}
			else
			{
				if (validacao!=usuarioNaoAchado)
				{
					printf ("\tMandar Emaili\n");
					/*IMPLEMENTAR*/ /*manda e-mail aivsando que alguem tentou apagar a conta do usuario*/
				}
			}	 /*termina o apagador de conta*/
		}/*fim do P*/
		
		if (opcao=='s') /*mudar senha*/
		{
			printf ("%s deseja mudar sua senha\n", optarg);
			validacao= VerificaExiste(optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if(validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
					/*grande case para dizer qual foi o erro*/
					printf ("\tNao foi possivel verificar se %s existe\n",optarg);
					exit (validacao);
				}
			if (validacao==ok) /*usario achado*/
			{
				printf ("\t%s foi encontrado\n",optarg);
				auxiliar=0;
				for (indice=0;indice<TENTATIVAS;indice++)
				{
					validacao2= VerificaSenha(optarg);
	  			if (validacao2==ok)
						{
							printf ("\t\tSenha de %s correta\n", optarg);
							validacao3= MudarSenha(optarg);
							if (validacao3!=ok)
							{
								printf ("ERRO#%i:",validacao3);
								/*grande case para dizer qual foi o erro*/
								printf ("\t\tnao foi possivel mudar senha de %s",optarg);
								exit (validacao3);
							}
							printf ("senha alterada com sucesso\n");
							indice=TENTATIVAS;
						}
					if (validacao2==senhaDiferente)
					{
						printf ("\tsenha errada. Voce tem mais %u tentativas\n", (TENTATIVAS-1)-indice);
						auxiliar++;
					}
					if (validacao2!=ok)
						if (validacao2!=senhaDiferente)
						{
							printf ("\tErro#%i:\n",validacao2);
							/*grande case para dizer qual foi o erro*/
							printf ("\tNao foi possivel verificar senha de %s\n",optarg);
							exit (validacao2);
						}
				}
				if (auxiliar==TENTATIVAS)
				{
					printf ("voce passou do limite de tentativas.\n");
					printf ("MANDAR E-MAIL\n");
					/*IMPLEMENTAR*//*DISPARAR E-MAIL*/
				}		
			}
		}/*fim do mudar senha*/
		
		if (opcao=='n') /*mudar usuario*/
		{ 
			printf ("%s deseja mudar nome de usuario\n", optarg);
			validacao=VerificaExiste(optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if(validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
					/*grande case para dizer qual foi o erro*/
					printf ("\tNao foi possivel verificar se %s existe\n",optarg);
					exit (validacao);
				}
			if (validacao==ok) /*usario achado*/
			{
				printf ("\t%s foi encontrado\n",optarg);
				auxiliar=0;
				for (indice=0;indice<TENTATIVAS;indice++)
				{
					validacao2=VerificaSenha(optarg);
	  			if (validacao2==ok)
						{
							printf ("\t\tSenha de %s correta\n", optarg);
							validacao3=MudarUsuario(optarg);
							if (validacao3!=ok)
							{
								printf ("ERRO#%i:",validacao3);
								/*grande case para dizer qual foi o erro*/
								printf ("\t\tnao foi possivel mudar o nome \"%s\"\n",optarg);
								exit (validacao3);
							}
							printf ("O nume de Usuario foi alterado com sucesso.\n");
							indice=TENTATIVAS;
						}
					if (validacao2==senhaDiferente)
					{
						printf ("\tsenha errada. Voce tem mais %u tentativas\n", (TENTATIVAS-1)-indice);
						auxiliar++;
					}
					if (validacao2!=ok)
						if (validacao2!=senhaDiferente)
						{
							printf ("\tErro#%i:\n",validacao2);
							/*grande case para dizer qual foi o erro*/
							printf ("\tNao foi possivel verificar senha de %s\n",optarg);
							exit (validacao2);
						}
				}
				if (auxiliar==TENTATIVAS)
				{
					printf ("voce passou do limite de tentativas.\n");
					printf ("MANDAR E-MAIL\n");
					/*IMPLEMENTAR*//*DISPARAR E-MAIL*/
				}		
			}	
		}		/*fim do mudar usuario*/

		if (opcao=='l') /*mudar e-mail*/
		{
			printf ("%s deseja mudar seu e-mail cadastrado\n",optarg);
			validacao=VerificaExiste(optarg);
			if (validacao==usuarioNaoAchado)
				printf ("\t%s nao foi encontrado!\n", optarg);
			if (validacao!=ok)
				if(validacao!=usuarioNaoAchado)
				{
					printf ("\tErro#%i:\n",validacao);
					/*grande case para dizer qual foi o erro*/
					printf ("\tNao foi possivel verificar se %s existe\n",optarg);
					exit (validacao);
				}
			if (validacao==ok) /*usario achado*/
			{
				printf ("\t%s foi encontrado\n",optarg);
				auxiliar=0;
				for (indice=0;indice<TENTATIVAS;indice++)
				{
					validacao2=VerificaSenha(optarg);
	  			if (validacao2==ok)
						{
							printf ("\t\tSenha de %s correta\n", optarg);
							validacao3=MudarEmail(optarg);
							if (validacao3!=ok)
							{
								printf ("ERRO#%i:",validacao3);
								/*grande case para dizer qual foi o erro*/
								printf ("\t\tnao foi possivel mudar o e-mail \"%s\"\n",optarg);
								exit (validacao3);
							}
							printf ("E-mail foi alterado com sucesso\n");
							indice=TENTATIVAS;
						}
					if (validacao2==senhaDiferente)
					{
						printf ("\tsenha errada. Voce tem mais %u tentativas\n", (TENTATIVAS-1)-indice);
						auxiliar++;
					}
					if (validacao2!=ok)
						if (validacao2!=senhaDiferente)
						{
							printf ("\tErro#%i:\n",validacao2);
							/*grande case para dizer qual foi o erro*/
							printf ("\tNao foi possivel verificar senha de %s\n",optarg);
							exit (validacao2);
						}
				}
				if (auxiliar==TENTATIVAS)
				{
					printf ("voce passou do limite de tentativas.\n");
					printf ("MANDAR E-MAIL\n");
					/*IMPLEMENTAR*//*DISPARAR E-MAIL*/
				}
			}
		}/*fim do mudar e-mail*/
		

		printf ("-------------------------------------------------------------------------------------------------------------------------\n");
	}/*fim do while*/

	printf ("\nsaiu do while\n\n");
	return ok;
}

void
showH()
{
	printf ("h\t-->\tExplica como usa o aplicativo\n");
	printf ("e\t-->\tTenta entrar no sistema\n");
	printf ("v\t-->\tVerifica se o usuario existe\n");
	printf ("c\t-->\tTenta cadastrar o usuario\n");
	printf ("p\t-->\tTenta apagar o usuario do sistema\n");
	printf ("s\t-->\tTenta mudar a senha\n");
	printf ("n\t-->\tTenta mudar o nome do usuario\n");
	printf ("l\t-->\tTenta mudar o e-mail do usuario\n");
}


/*IMPLEMENTAR*/ /*grande case para dizer qual foi o erro*/
