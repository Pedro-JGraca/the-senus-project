#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <errno.h>
#include <time.h>

#include "senus.h"

#define COMPRIMETO_SALT											3
#define COMPRIMENTO_MAXIMO_SENHA_CIFRADA	106
#define COMPRIMENTO_MAXIMO_SENHA					127
#define ALGORITMO_CRIPOGRAFIA							'6'

#define CONJUNTO_SALT 				"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./"

tipoErros
MudarSenha(char *usuario) 				/*muda a senha do usuario*/
{
	return ok;
}

tipoErros
VerificaSenha(char *usuario)			/*pergunta senha ao usuario e verifica se bate com a do banco de dados*/
{
	unsigned indice=0;
  char senhaCifradaTeste [COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1];
  char senhaCifradaOriginal [COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1];
	char algCript[(2*COMPRIMETO_SALT) +1];
	char auxiliar[COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1];
	char temporario[3];
	
	bit sair=zero;

	FILE *bancoDados;

	size_t tamanho;
	char *nome;
	
	/*senhaOriginal =  Senha do Arquivo*/
	bancoDados=fopen (BANCO_DADOS,"r");
	if (!bancoDados)
	{
		printf ("Nao foi possivel acessar ao banco de dados do programa. Chame alguem Especializado\n");
		printf ("Erro#%i: %s\n",errno, strerror (errno));
		return bancoDadosInacessivel; 
	}
	if (!usuario)
		return usuarioNull;
	
	tamanho = (strlen (usuario)+1);	
	nome= malloc (sizeof(tamanho)*tamanho);
	temporario[0]='a';
	temporario[1]=EOS;
	while (((fgets(nome,tamanho,bancoDados))!=NULL)&&(sair!=um))
	{
		if((strcmp(nome,usuario))==0)
		{
			fgets(auxiliar,2,bancoDados);
			for (indice=0;indice<92;indice++)
			{
				fgets(temporario,2,bancoDados);
				senhaCifradaOriginal[indice]=temporario[0];
			}
			sair=um;
		}
	}
	senhaCifradaOriginal[indice]=EOS;
	
	if (sair!=um)
	{
		free(nome);
		if(fclose(bancoDados)!=0)
		{
			printf ("Erro#%i: %s\n", errno, strerror (errno));
			printf ("Erro ao sair do arquivo.\n");
			return naoConsegueSairArquivo; 
		}
		return usuarioNaoAchado;
	}
	
	for (indice=0;indice<6;indice++)
		algCript[indice]=senhaCifradaOriginal[indice];
	algCript[indice]=EOS; /*pega o salt e o algoritmo da criptografia da senha guardada*/

	/*fim da pega da senha*/
	
	/*aqui o algCript e o senhaCrifadaOriginal já possuem a senha original do usuario, o seu salt e o algoritimo de criptografia desejado*/
/*	printf ("Senha Original: %s\n", senhaCifradaOriginal);
	printf ("Algcript:%s\n",algCript);
*/

	/*copiar em senhaTeste a senha criptogafada pedida agora ao usuario, usando o salt antirior*/

	memset (senhaCifradaTeste, 0x00, COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1);	
	strcpy (senhaCifradaTeste,strcpy (auxiliar,crypt(getpass ("Entre com a senha:"),algCript)));
  memset (auxiliar, 0x00, COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1);

	/*fim da copia*/
	
/*	printf ("senha testada: %s\n", senhaCifradaTeste);
	*//*comparar senhaOriginal com a senhaTeste e dar o retorno*/
	free(nome);

	if(fclose(bancoDados)!=0)
	{
		printf ("Erro#%i: %s\n", errno, strerror (errno));
		printf ("Erro ao sair do arquivo.\n");
		return naoConsegueSairArquivo; 
	}
		
	if (strcmp (senhaCifradaOriginal,senhaCifradaTeste)!=0)
	{
		return senhaDiferente;
	}
	
	return ok;
}


tipoErros
CadastroUsuario(char *usuario)		/*cadastra usuario*/
{
	FILE *bancoDados;
	bancoDados = fopen (BANCO_DADOS,"a+"); 
	char email [500];
	char senhaCifrada [ COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1];
	char auxiliar [ COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1];
	char algCript[(2*COMPRIMETO_SALT)+1];
	char salt [COMPRIMETO_SALT+1];

	if (!bancoDados)
	{
		printf ("Nao foi possivel acessar ao banco de dados do programa. Chame alguem Especializado\n");
		printf ("Erro#%i: %s\n",errno, strerror (errno));
		return bancoDadosInacessivel; 
	}
	if (!usuario)
		return usuarioNull;

	if (usuario[0]==('-'))
		return usuarioInvalido;
	srand(time(NULL));	

	fprintf (bancoDados,"%s",usuario);
	fprintf (bancoDados,"%c",1);
	
	salt[0]=CONJUNTO_SALT[rand()%64];
	salt[1]=CONJUNTO_SALT[rand()%64];
	salt[2]=EOS;

	algCript[0]='$';
	algCript[1]=ALGORITMO_CRIPOGRAFIA;
	algCript[2]='$';
	algCript[3]=salt[0];
	algCript[4]=salt[1];
	algCript[5]='$';
	algCript[6]=EOS;

	memset (senhaCifrada, 0x00, COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1);	
	strcpy (senhaCifrada,strcpy (auxiliar,crypt(getpass ("Entre com a senha:"),algCript)));
  memset (auxiliar, 0x00, COMPRIMENTO_MAXIMO_SENHA_CIFRADA + 1);
	
	fprintf (bancoDados,"%s",senhaCifrada);
	fprintf (bancoDados,"%c",1);

	printf ("Escreva seu e-mail:");
	scanf("%s",email);
	fprintf (bancoDados,"%s;\n",email);

  if (fclose(bancoDados)!=0)
	{
		printf ("Erro#%i: %s\n", errno, strerror (errno));
		printf ("Erro ao sair do arquivo.\n");
		return naoConsegueSairArquivo; 
	}
	return ok;
}
