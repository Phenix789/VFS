/**
 * File:   protocol.h
 * Author: phenix
 *
 * Created on 10 novembre 2013, 19:53
 */

#ifndef __PROTOCOL_H__
#define	__PROTOCOL_H__

#define MAGIC_NUMBER 0x56465300 // "VFS\0"

#define FILENAME_SIZE_MAX 256

/**
 * List des commandes
 */
#define COMMAND_LIST 0x1
#define COMMAND_INFO 0x2
#define COMMAND_SEND 0x4
#define COMMAND_RECEIVE 0x8

/* Bit de requete */
#define REQUEST_BIT (0x1 << 30)
/* Bit de reponse */
#define RESPONSE_BIT (0x1 << 31)
/* Bit d'erreur */
#define ERROR_BIT (0x1 << 23)

/**
 * Liste des requetes
 */
#define REQUEST_LIST (REQUEST_BIT | COMMAND_LIST)
#define REQUEST_INFO (REQUEST_BIT | COMMAND_INFO)
#define REQUEST_SEND (REQUEST_BIT | COMMAND_SEND)
#define REQUEST_RECEIVE (REQUEST_BIT | COMMAND_RECEIVE)

/**
 * Liste des reponses
 */
#define RESPONSE_LIST (RESPONSE_BIT | COMMAND_LIST)
#define RESPONSE_INFO (RESPONSE_BIT | COMMAND_INFO)
#define RESPONSE_SEND (RESPONSE_BIT | COMMAND_SEND)
#define RESPONSE_RECEIVE (RESPONSE_BIT | COMMAND_RECEIVE)

#define CHECK_MAGIC(command) (((struct command)(command)).magic == MAGIC_NUMBER)

#define IS_REQUEST(code) ((code) & REQUEST_BIT)
#define IS_RESPONSE(code) ((code) & RESPONSE_BIT)
#define IS_ERROR(code) ((code) & ERROR_BIT)

#define IS_COMMAND_REQUEST(command) IS_REQUEST(((struct command)(command)).code)
#define IS_COMMAND_RESPONSE(command) IS_RESPONSE(((struct command)(command)).code)
#define IS_COMMAND_ERROR(command) IS_ERROR(((struct command)(command)).code)

/* Unknown type */
typedef int date;
typedef int right;

/**
 *
 */
struct command
{
	uint32_t magic;
	uint32_t code;
};

struct filename
{
	char filename[FILENAME_SIZE_MAX];
};

struct info
{
	date atime;
	date mtime;
	date ctime;
	right user;
	right group;
	right all;
	uint64_t size;
	struct filename filename;
};

/**
 * List
 */
struct request_list
{
	struct command command;
	struct filename dir;
};

struct response_list
{
	struct command command;
	uint32_t count;
};

struct request_info
{
	struct command command;
	struct filename file;
};

struct response_info
{
	struct command command;
	struct info info;
};

struct request_send
{
	struct command command;
	struct info info;
};

struct response_send
{
	struct command command;
	uint32_t status;
};

struct request_receive
{
	struct command command;
	struct filename filename;
};

struct response_receive
{
	struct command command;
	struct info info;
};


int main()
{
}

/*
 * Exemple:
 *
 * Pour demander des info sur un fichier
 *
 * struct request_info request;
 * request.command.magic = MAGIC_NUMBER;
 * request.command.code = REQUEST_INFO;
 * strcpy(&request.file.filename, "/dir/my_file");
 * struct response_info * response = server_send(&request);
 * = >response contient toutes les infos du fichier, si celui ci existe (sinon tout a null)
 *
 */

#endif	/* __PROTOCOL_H__ */
