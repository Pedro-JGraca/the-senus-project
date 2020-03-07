#macros
CC=gcc
LD=gcc

CFLAGS = -std=c99 -Wall -lcrypt
LFLAGS = -std=c99 -Wall -lcrypt

#SFLAG = -lcrypy

SENUS_TESTE_OBJS= senusPrincipal.o senusSenha.o senusEmail.o senusFuncoesBasicas.o senusTeste.o
#SENUS_SENHA_OBJS= senusSenha.o

SENUS= 	senus0.01.0
#				senusSenha

EXECS = $(SENUS)

ALL= $(EXECS)

#fim das macros

#regra implicita
.c.o:
	$(CC) $(CFLAGS) -c $<
#fim da regra implicita

#objetivos

all: $(ALL)

senus: $(SENUS)

senus0.01.0: $(SENUS_TESTE_OBJS)
	$(LD) $(LFLAGS) -o $@ $(SENUS_TESTE_OBJS)

#senusSenha: $(SENUS_SENHA_OBJS)
#	$(LD) $(LFLAGS) $(SFLAG) -o $@ $(SENUS_SENHA_OBJS)


clean:
	rm -rf *.o $(EXECS)

#fim dos objetivo
