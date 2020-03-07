#ifndef	_SENUS_
#define _SENUS_   						  "senus.h"

#define EOS												'\0'
#define NUMERO_ARGUMENTOS						2
#define TENTATIVAS									3
#define BANCO_DADOS									"BancoDeDados.txt"
typedef unsigned char byte;

typedef enum {
ok,
numeroInvalidoArgumentos,
usuarioNaoAchado,
erroFlagInvalida,
flagSemArgumento,
flagComArgumento,
senhaDiferente,
naoConsegueSairArquivo,
bancoDadosInacessivel,
usuarioNull,
temporarioInacessivel,
usuarioInvalido,
erroPegarNomeTeclado,
erroCopiaUsuarioNome
} tipoErros;

typedef enum {
zero,
um
} bit;

void
showH(void);

/*Principal*/
tipoErros	
EntrarSistema(char *usuario);			/*entra no sistema, aqui que será implementada as coisas do sistema*/
/*As funcoes basicas dentro do sistema sao as de editar a propria senha, o e-mail, o nome do usuario, apagar a propria conta, ver seus dados e sair*/
						

/*senha*/
tipoErros	
MudarSenha(char *usuario); 				/*muda a senha do usuario*/

tipoErros	
VerificaSenha(char *usuario);			/*pergunta senha ao usuario e verifica se bate com a do banco de dados*/

/*funcoes basicas*/
tipoErros	
VerificaExiste(char *usuario);		/*verifica se o usuario exite*/

tipoErros	
MudarUsuario(char *usuario);			/*muda o nome do usuario*/

tipoErros	
ApagarConta(char *usuario);				/*apaga a conta do usuario em questao*/

tipoErros	
MudarEmail(char *usuario);				/*muda o e-mail do usuario*/

tipoErros	
CadastroUsuario(char *usuario);		/*cadastra usuario*/


/*implementacoes necessarias*/
/*IMPLEMENTAR*/ /*manda e-mail aivsando que alguem tentou apagar a conta do usuario*/
/*IMPLEMENTAR*/ /*grande case para dizer qual foi o erro*/

#endif
