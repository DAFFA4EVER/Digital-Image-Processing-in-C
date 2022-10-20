SHELL		= /bin/sh
CC     		= gcc
CFLAGS 		= -g -Wall
LDFLAGS		= -g -Wall -lm

#--------------- You must write all linked file name ----------------
SRCS	= main.c ppm.c pgm.c pbm.c niblack.c
#--------------------------------------------------------------------
OBJS    = ${SRCS:.c=.o} 

#-------- Please write executive file name and directory ------------
DIR     = ./
BINS    = a03-02
#--------------------------------------------------------------------

all: ${BINS}

${BINS}: ${OBJS}
	${CC} -o ${DIR}$@ ${OBJS} ${LDFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${OBJS} core
