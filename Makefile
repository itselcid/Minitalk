CC = cc
CFLAGS = -Wall -Wextra -Werror

CSRC = client.c
CSRC_OBJ = ${CSRC:.c=.o}

SSRC = server.c
SSRC_OBJ = ${SSRC:.c=.o}

CNAME = client

BNSSERVER = server_bonus.c
BNSCLIENT = client_bonus.c ft_itoa.c

SNAME = server

all: $(CNAME) $(SNAME)

$(CNAME): $(CSRC_OBJ)
	$(CC) $(CFLAGS) $(CSRC_OBJ) -o $(CNAME)

$(SNAME): $(SSRC_OBJ)
	$(CC) $(CFLAGS) $(SSRC_OBJ) -o $(SNAME)

clean:
	@rm -rf $(SSRC_OBJ) $(CSRC_OBJ)

fclean: clean
	@rm -rf $(CNAME) $(SNAME)

bonus: $(BNSCLIENT) $(BNSSERVER)
	$(CC) $(CFLAGS) $(BNSCLIENT) -o $(CNAME)
	$(CC) $(CFLAGS) $(BNSSERVER) -o $(SNAME)

re: fclean all