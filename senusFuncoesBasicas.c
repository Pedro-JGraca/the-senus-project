
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "senus.h"

tipoErros
VerificaExiste(char *usuario)	/*verifica se o usuario exite*/
{
	size_t tamanho;
	
	char auxiliar[2];
	char *nomeTeste;
	char temporario[2];
	char nomeOriginal[500];
	
	FILE *bancoDados;
	
	if (!usuario)
		return usuarioNull;

/*	printf ("Usuario: %s\n", usuario);
*/	bancoDados= fopen (BANCO_DADOS, "r");
	
	if (!bancoDados)
		return bancoDadosInacessivel;

	tamanho=strlen (usuario);
	tamanho++;
	nomeTeste= malloc (sizeof(tamanho)*tamanho);
	strcpy (nomeTeste,usuario);
	
	nomeOriginal[0]=EOS;
	
	while (fgets(temporario,2,bancoDados))
	{
		temporario[1]=EOS; /*letra em letra*/
		while (temporario[0]!=0x01) /*vai ate o fim do nome de cada usuario*/
		{
			strcat (nomeOriginal,temporario); /*carrega nome em questao*/
			fgets(temporario,2,bancoDados);
		}
/*		printf ("Nome da Memoria: \"%s\"\nNome de Testado: \"%s\"\n",nomeOriginal, nomeTeste);
*/		if (strcmp(nomeOriginal,nomeTeste)==0)
			return ok;
		nomeOriginal[0]=EOS; /*apaga o nome em questao*/
		
		auxiliar[0]=EOS; /*pular nova linha*/
		while (auxiliar[0]!='\n')
		{
			fgets(auxiliar,2,bancoDados);
			auxiliar[1]=EOS;
		}	
	}

	free (nomeTeste);
	if (fclose(bancoDados)!=0)
		return  naoConsegueSairArquivo;
	
	return usuarioNaoAchado;

}/*termina verificacao*/

tipoErros
MudarUsuario(char *usuario)			/*muda o nome do usuario*/
{
	FILE *bancoDados, *temporario;
	bancoDados= fopen (BANCO_DADOS, "a+");
	size_t tamanho;
	char *nome, *novoNome;
	if (!bancoDados)
		return bancoDadosInacessivel;
	temporario = fopen (".temp", "w");
	if (!temporario)
		return temporarioInacessivel;
	
	if (!usuario)
		return usuarioNull;
	
	tamanho = strlen (usuario);
	tamanho++;
	nome = malloc ((sizeof (tamanho))*tamanho);
	novoNome = malloc ((sizeof (tamanho))*(tamanho+50));
	
	while (fgets(nome, tamanho, bancoDados)!=NULL)
	{
		if (strcmp (nome,usuario)==0)
		{
			if ((scanf("%s",novoNome))==0)
			{
				/*procurar usuario no banco de dados, apagar e escrever o novoNome*/
			}
			else
			{
				free(nome);
				free(novoNome);
				return erroPegarNomeTeclado;
			}
		}
		else
		{
			free (nome);
			free (novoNome);
			return erroCopiaUsuarioNome;
		}
	}
			
	free (nome);
	free (novoNome);
	
	return ok;
}


tipoErros
ApagarConta(char *usuario)				/*apaga a conta do usuario em questao*/
{
	return ok;
}


tipoErros
MudarEmail(char *usuario)				/*muda o e-mail do usuario*/
{
	return ok;
}



