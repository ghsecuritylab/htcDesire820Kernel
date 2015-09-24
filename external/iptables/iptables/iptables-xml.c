/* Code to convert iptables-save format to xml format,
 * (C) 2006 Ufo Mechanic <azez@ufomechanic.net>
 * based on iptables-restore (C) 2000-2002 by Harald Welte <laforge@gnumonks.org>
 * based on previous code from Rusty Russell <rusty@linuxcare.com.au>
 *
 * This code is distributed under the terms of GNU GPL v2
 */

#include <getopt.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "iptables.h"
#include "libiptc/libiptc.h"
#include "xtables-multi.h"
#include <xtables.h>

#ifdef DEBUG
#define DEBUGP(x, args...) fprintf(stderr, x, ## args)
#else
#define DEBUGP(x, args...)
#endif

#ifndef IPTABLES_MULTI
int line = 0;
#endif

struct xtables_globals iptables_xml_globals = {
	.option_offset = 0,
	.program_version = IPTABLES_VERSION,
	.program_name = "iptables-xml",
};
#define prog_name iptables_xml_globals.program_name
#define prog_vers iptables_xml_globals.program_version

static void print_usage(const char *name, const char *version)
	    __attribute__ ((noreturn));

static int verbose = 0;
static int combine = 0;
static struct option options[] = {
	{"verbose", 0, NULL, 'v'},
	{"combine", 0, NULL, 'c'},
	{"help", 0, NULL, 'h'},
	{ .name = NULL }
};

static void
print_usage(const char *name, const char *version)
{
	fprintf(stderr, "Usage: %s [-c] [-v] [-h]\n"
		"          [--combine ]\n"
		"	   [ --verbose ]\n" "	   [ --help ]\n", name);

	exit(1);
}

static int
parse_counters(char *string, struct ipt_counters *ctr)
{
	__u64 *pcnt, *bcnt;

	if (string != NULL) {
		pcnt = &ctr->pcnt;
		bcnt = &ctr->bcnt;
		return (sscanf
			(string, "[%llu:%llu]",
			 (unsigned long long *)pcnt,
			 (unsigned long long *)bcnt) == 2);
	} else
		return (0 == 2);
}

static char *newargv[255];
static unsigned int newargc = 0;

static char *oldargv[255];
static unsigned int oldargc = 0;

static int newargvattr[255];

#define IPT_CHAIN_MAXNAMELEN IPT_TABLE_MAXNAMELEN
static char closeActionTag[IPT_TABLE_MAXNAMELEN + 1];
static char closeRuleTag[IPT_TABLE_MAXNAMELEN + 1];
static char curTable[IPT_TABLE_MAXNAMELEN + 1];
static char curChain[IPT_CHAIN_MAXNAMELEN + 1];

struct chain {
	char *chain;
	char *policy;
	struct ipt_counters count;
	int created;
};

#define maxChains 10240		
static struct chain chains[maxChains];
static int nextChain = 0;

static int
add_argv(char *what, int quoted)
{
	DEBUGP("add_argv: %d %s\n", newargc, what);
	if (what && newargc + 1 < ARRAY_SIZE(newargv)) {
		newargv[newargc] = strdup(what);
		newargvattr[newargc] = quoted;
		newargc++;
		return 1;
	} else
		return 0;
}

static void
free_argv(void)
{
	unsigned int i;

	for (i = 0; i < newargc; i++) {
		free(newargv[i]);
		newargv[i] = NULL;
	}
	newargc = 0;

	for (i = 0; i < oldargc; i++) {
		free(oldargv[i]);
		oldargv[i] = NULL;
	}
	oldargc = 0;
}

static void
save_argv(void)
{
	unsigned int i;

	for (i = 0; i < oldargc; i++)
		free(oldargv[i]);
	oldargc = newargc;
	newargc = 0;
	for (i = 0; i < oldargc; i++) {
		oldargv[i] = newargv[i];
		newargv[i] = NULL;
	}
}

static void
xmlEncode(char *text)
{
	while (text && *text) {
		if ((unsigned char) (*text) >= 127)
			printf("&#%d;", (unsigned char) (*text));
		else if (*text == '&')
			printf("&amp;");
		else if (*text == '<')
			printf("&lt;");
		else if (*text == '>')
			printf("&gt;");
		else if (*text == '"')
			printf("&quot;");
		else
			putchar(*text);
		text++;
	}
}

static void
xmlCommentEscape(char *comment)
{
	int h_count = 0;

	while (comment && *comment) {
		if (*comment == '-') {
			h_count++;
			if (h_count >= 2) {
				h_count = 0;
				putchar(' ');
			}
			putchar('*');
		}
		
		if (*comment == '\n' && *(comment + 1) == 0);
		else
			putchar(*comment);
		comment++;
	}
}

static void
xmlComment(char *comment)
{
	printf("<!-- ");
	xmlCommentEscape(comment);
	printf(" -->\n");
}

static void
xmlAttrS(char *name, char *value)
{
	printf("%s=\"", name);
	xmlEncode(value);
	printf("\" ");
}

static void
xmlAttrI(char *name, long long int num)
{
	printf("%s=\"%lld\" ", name, num);
}

static void
closeChain(void)
{
	if (curChain[0] == 0)
		return;

	if (closeActionTag[0])
		printf("%s\n", closeActionTag);
	closeActionTag[0] = 0;
	if (closeRuleTag[0])
		printf("%s\n", closeRuleTag);
	closeRuleTag[0] = 0;
	if (curChain[0])
		printf("    </chain>\n");
	curChain[0] = 0;
	
}

static void
openChain(char *chain, char *policy, struct ipt_counters *ctr, char close)
{
	closeChain();

	strncpy(curChain, chain, IPT_CHAIN_MAXNAMELEN);
	curChain[IPT_CHAIN_MAXNAMELEN] = '\0';

	printf("    <chain ");
	xmlAttrS("name", curChain);
	if (strcmp(policy, "-") != 0)
		xmlAttrS("policy", policy);
	xmlAttrI("packet-count", (unsigned long long) ctr->pcnt);
	xmlAttrI("byte-count", (unsigned long long) ctr->bcnt);
	if (close) {
		printf("%c", close);
		curChain[0] = 0;
	}
	printf(">\n");
}

static int
existsChain(char *chain)
{
	
	int c = 0;

	if (0 == strcmp(curChain, chain))
		return 1;
	for (c = 0; c < nextChain; c++)
		if (chains[c].chain && strcmp(chains[c].chain, chain) == 0)
			return 1;
	return 0;
}

static void
needChain(char *chain)
{
	
	int c = 0;

	if (0 == strcmp(curChain, chain))
		return;

	for (c = 0; c < nextChain; c++)
		if (chains[c].chain && strcmp(chains[c].chain, chain) == 0) {
			openChain(chains[c].chain, chains[c].policy,
				  &(chains[c].count), '\0');
			chains[c].created = 1;
		}
}

static void
saveChain(char *chain, char *policy, struct ipt_counters *ctr)
{
	if (nextChain >= maxChains) {
		xtables_error(PARAMETER_PROBLEM,
			   "%s: line %u chain name invalid\n",
			   prog_name, line);
		exit(1);
	};
	chains[nextChain].chain = strdup(chain);
	chains[nextChain].policy = strdup(policy);
	chains[nextChain].count = *ctr;
	chains[nextChain].created = 0;
	nextChain++;
}

static void
finishChains(void)
{
	int c;

	for (c = 0; c < nextChain; c++)
		if (!chains[c].created) {
			openChain(chains[c].chain, chains[c].policy,
				  &(chains[c].count), '/');
			free(chains[c].chain);
			free(chains[c].policy);
		}
	nextChain = 0;
}

static void
closeTable(void)
{
	closeChain();
	finishChains();
	if (curTable[0])
		printf("  </table>\n");
	curTable[0] = 0;
}

static void
openTable(char *table)
{
	closeTable();

	strncpy(curTable, table, IPT_TABLE_MAXNAMELEN);
	curTable[IPT_TABLE_MAXNAMELEN] = '\0';

	printf("  <table ");
	xmlAttrS("name", curTable);
	printf(">\n");
}

static int
isTarget(char *arg)
{
	return ((arg)
		&& (strcmp((arg), "-j") == 0 || strcmp((arg), "--jump") == 0
		    || strcmp((arg), "-g") == 0
		    || strcmp((arg), "--goto") == 0));
}

static int
isTerminatingTarget(char *arg)
{
	return ((arg)
		&& (strcmp((arg), "ACCEPT") == 0
		    || strcmp((arg), "DROP") == 0
		    || strcmp((arg), "QUEUE") == 0
		    || strcmp((arg), "RETURN") == 0));
}

static void
do_rule_part(char *leveltag1, char *leveltag2, int part, int argc,
	     char *argv[], int argvattr[])
{
	int arg = 1;		
	char invert_next = 0;
	char *spacer = "";	
	char *level1 = NULL;
	char *level2 = NULL;
	char *leveli1 = "        ";
	char *leveli2 = "          ";

#define CLOSE_LEVEL(LEVEL) \
	do { \
		if (level ## LEVEL) printf("</%s>\n", \
		(leveltag ## LEVEL)?(leveltag ## LEVEL):(level ## LEVEL)); \
		level ## LEVEL=NULL;\
	} while(0)

#define OPEN_LEVEL(LEVEL,TAG) \
	do {\
		level ## LEVEL=TAG;\
		if (leveltag ## LEVEL) {\
			printf("%s<%s ", (leveli ## LEVEL), \
				(leveltag ## LEVEL));\
			xmlAttrS("type", (TAG)); \
		} else printf("%s<%s ", (leveli ## LEVEL), (level ## LEVEL)); \
	} while(0)

	if (part == 1) {	
		while (arg < argc && (argvattr[arg] || !isTarget(argv[arg])))
			arg++;
	}

	if (arg < argc && argv[arg][0] == '-' && !isTarget(argv[arg])
	    && strcmp(argv[arg], "-m") != 0) {
		OPEN_LEVEL(1, "match");
		printf(">\n");
	}
	while (arg < argc) {
		
		
		if (part == -1 && !argvattr[arg] && (isTarget(argv[arg]))) {
			break;
		} else if (!argvattr[arg] && strcmp(argv[arg], "!") == 0) {
			if ((arg + 1) < argc && argv[arg + 1][0] == '-')
				invert_next = '!';
			else
				printf("%s%s", spacer, argv[arg]);
			spacer = " ";
		} else if (!argvattr[arg] && isTarget(argv[arg])
			   && existsChain(argv[arg + 1])
			   && (2 + arg >= argc)) {
			if (!((1 + arg) < argc))
				
				break;
			CLOSE_LEVEL(2);
			if (level1)
				printf("%s", leveli1);
			CLOSE_LEVEL(1);
			spacer = "";
			invert_next = 0;
			if (strcmp(argv[arg], "-g") == 0
			    || strcmp(argv[arg], "--goto") == 0) {
				
				OPEN_LEVEL(1, "goto");
				printf(">\n");
				arg++;
				OPEN_LEVEL(2, argv[arg]);
				printf("/>\n");
				level2 = NULL;
			} else {
				
				OPEN_LEVEL(1, "call");
				printf(">\n");
				arg++;
				OPEN_LEVEL(2, argv[arg]);
				printf("/>\n");
				level2 = NULL;
			}
		} else if (!argvattr[arg]
			   && (isTarget(argv[arg])
			       || strcmp(argv[arg], "-m") == 0
			       || strcmp(argv[arg], "--module") == 0)) {
			if (!((1 + arg) < argc))
				
				break;
			CLOSE_LEVEL(2);
			if (level1)
				printf("%s", leveli1);
			CLOSE_LEVEL(1);
			spacer = "";
			invert_next = 0;
			arg++;
			OPEN_LEVEL(1, (argv[arg]));
			
			if ((arg + 1) >= argc || (!argvattr[arg + 1]
						  && (isTarget(argv[arg + 1])
						      || strcmp(argv[arg + 1],
								"-m") == 0
						      || strcmp(argv[arg + 1],
								"--module") ==
						      0))) {
				printf(" />\n");
				level1 = NULL;
			} else {
				printf(">\n");
			}
		} else if (!argvattr[arg] && argv[arg][0] == '-') {
			char *tag;
			CLOSE_LEVEL(2);
			
			tag = argv[arg];
			while (*tag == '-' && *tag)
				tag++;

			spacer = "";
			OPEN_LEVEL(2, tag);
			if (invert_next)
				printf(" invert=\"1\"");
			invert_next = 0;

			
			if (!((arg + 1) < argc)
			    || (argv[arg + 1][0] == '-'  )) {
				printf(" />\n");
				level2 = NULL;
			} else {
				printf(">");
			}
		} else {	
			char *spaces = strchr(argv[arg], ' ');
			printf("%s", spacer);
			if (spaces || argvattr[arg])
				printf("&quot;");
			
			xmlEncode(argv[arg]);
			if (spaces || argvattr[arg])
				printf("&quot;");
			spacer = " ";
		}
		arg++;
	}
	CLOSE_LEVEL(2);
	if (level1)
		printf("%s", leveli1);
	CLOSE_LEVEL(1);
}

static int
compareRules(void)
{

	unsigned int old = 0;
	unsigned int new = 0;

	int compare = 0;

	while (new < newargc && old < oldargc) {
		if (isTarget(oldargv[old]) && isTarget(newargv[new])) {
			if (((strcmp((oldargv[old]), "-j") == 0 
					|| strcmp((oldargv[old]), "--jump") == 0) 
				&& old+1 < oldargc
				&& isTerminatingTarget(oldargv[old+1]) )
			    || strcmp((oldargv[old]), "-g") == 0 
			    || strcmp((oldargv[old]), "--goto") == 0 ) {
					
				compare = 0;
			} else {
				compare = 1;
			}
			break;
		}
		
		if (strcmp(oldargv[old], newargv[new]) != 0) {
			compare = 0;
			break;
		}

		old++;
		new++;
	}
	
	

	return compare == 1;
}

static void
do_rule(char *pcnt, char *bcnt, int argc, char *argv[], int argvattr[])
{
	if (combine && argc > 2 && !isTarget(argv[2]) && compareRules()) {
		xmlComment("Combine action from next rule");
	} else {

		if (closeActionTag[0]) {
			printf("%s\n", closeActionTag);
			closeActionTag[0] = 0;
		}
		if (closeRuleTag[0]) {
			printf("%s\n", closeRuleTag);
			closeRuleTag[0] = 0;
		}

		printf("      <rule ");
		
		
		if (pcnt)
			xmlAttrS("packet-count", pcnt);
		if (bcnt)
			xmlAttrS("byte-count", bcnt);
		printf(">\n");

		strncpy(closeRuleTag, "      </rule>\n", IPT_TABLE_MAXNAMELEN);
		closeRuleTag[IPT_TABLE_MAXNAMELEN] = '\0';

		
		if (argc >= 3 && !isTarget(argv[2])) {
			printf("       <conditions>\n");
			do_rule_part(NULL, NULL, -1, argc, argv, argvattr);
			printf("       </conditions>\n");
		}
	}
	
	
	if (!closeActionTag[0]) {
		printf("       <actions>\n");
		strncpy(closeActionTag, "       </actions>\n",
			IPT_TABLE_MAXNAMELEN);
		closeActionTag[IPT_TABLE_MAXNAMELEN] = '\0';
	}
	do_rule_part(NULL, NULL, 1, argc, argv, argvattr);
}

#ifdef IPTABLES_MULTI
int
iptables_xml_main(int argc, char *argv[])
#else
int
main(int argc, char *argv[])
#endif
{
	char buffer[10240];
	int c;
	FILE *in;

	line = 0;

	xtables_set_params(&iptables_xml_globals);
	while ((c = getopt_long(argc, argv, "cvh", options, NULL)) != -1) {
		switch (c) {
		case 'c':
			combine = 1;
			break;
		case 'v':
			printf("xptables-xml\n");
			verbose = 1;
			break;
		case 'h':
			print_usage("iptables-xml", IPTABLES_VERSION);
			break;
		}
	}

	if (optind == argc - 1) {
		in = fopen(argv[optind], "re");
		if (!in) {
			fprintf(stderr, "Can't open %s: %s", argv[optind],
				strerror(errno));
			exit(1);
		}
	} else if (optind < argc) {
		fprintf(stderr, "Unknown arguments found on commandline");
		exit(1);
	} else
		in = stdin;

	printf("<iptables-rules version=\"1.0\">\n");

	
	while (fgets(buffer, sizeof(buffer), in)) {
		int ret = 0;

		line++;

		if (buffer[0] == '\n')
			continue;
		else if (buffer[0] == '#') {
			xmlComment(buffer);
			continue;
		}

		if (verbose) {
			printf("<!-- line %d ", line);
			xmlCommentEscape(buffer);
			printf(" -->\n");
		}

		if ((strcmp(buffer, "COMMIT\n") == 0) && (curTable[0])) {
			DEBUGP("Calling commit\n");
			closeTable();
			ret = 1;
		} else if ((buffer[0] == '*')) {
			
			char *table;

			table = strtok(buffer + 1, " \t\n");
			DEBUGP("line %u, table '%s'\n", line, table);
			if (!table) {
				xtables_error(PARAMETER_PROBLEM,
					   "%s: line %u table name invalid\n",
					   prog_name, line);
				exit(1);
			}
			openTable(table);

			ret = 1;
		} else if ((buffer[0] == ':') && (curTable[0])) {
			
			char *policy, *chain;
			struct ipt_counters count;
			char *ctrs;

			chain = strtok(buffer + 1, " \t\n");
			DEBUGP("line %u, chain '%s'\n", line, chain);
			if (!chain) {
				xtables_error(PARAMETER_PROBLEM,
					   "%s: line %u chain name invalid\n",
					   prog_name, line);
				exit(1);
			}

			DEBUGP("Creating new chain '%s'\n", chain);

			policy = strtok(NULL, " \t\n");
			DEBUGP("line %u, policy '%s'\n", line, policy);
			if (!policy) {
				xtables_error(PARAMETER_PROBLEM,
					   "%s: line %u policy invalid\n",
					   prog_name, line);
				exit(1);
			}

			ctrs = strtok(NULL, " \t\n");
			parse_counters(ctrs, &count);
			saveChain(chain, policy, &count);

			ret = 1;
		} else if (curTable[0]) {
			unsigned int a;
			char *ptr = buffer;
			char *pcnt = NULL;
			char *bcnt = NULL;
			char *parsestart;
			char *chain = NULL;

			
			char *param_start, *curchar;
			int quote_open, quoted;

			
			newargc = 0;

			if (buffer[0] == '[') {
				
				ptr = strchr(buffer, ']');
				if (!ptr)
					xtables_error(PARAMETER_PROBLEM,
						   "Bad line %u: need ]\n",
						   line);

				pcnt = strtok(buffer + 1, ":");
				if (!pcnt)
					xtables_error(PARAMETER_PROBLEM,
						   "Bad line %u: need :\n",
						   line);

				bcnt = strtok(NULL, "]");
				if (!bcnt)
					xtables_error(PARAMETER_PROBLEM,
						   "Bad line %u: need ]\n",
						   line);

				
				parsestart = ptr + 1;
			} else {
				
				parsestart = buffer;
			}



			quote_open = 0;
			quoted = 0;
			param_start = parsestart;

			for (curchar = parsestart; *curchar; curchar++) {
				if (*curchar == '"') {
					if (quote_open &&
					    *(curchar - 1) != '\\') {
						quote_open = 0;
						*curchar = ' ';
					} else {
						quote_open = 1;
						quoted = 1;
						param_start++;
					}
				}
				if (*curchar == ' '
				    || *curchar == '\t' || *curchar == '\n') {
					char param_buffer[1024];
					int param_len = curchar - param_start;

					if (quote_open)
						continue;

					if (!param_len) {
						
						param_start++;
						continue;
					}

					
					strncpy(param_buffer, param_start,
						param_len);
					*(param_buffer + param_len) = '\0';

					
					if (!strncmp(param_buffer, "-t", 3)
					    || !strncmp(param_buffer,
							"--table", 8)) {
						xtables_error(PARAMETER_PROBLEM,
							   "Line %u seems to have a "
							   "-t table option.\n",
							   line);
						exit(1);
					}

					add_argv(param_buffer, quoted);
					if (newargc >= 2
					    && 0 ==
					    strcmp(newargv[newargc - 2], "-A"))
						chain = newargv[newargc - 1];
					quoted = 0;
					param_start += param_len + 1;
				} else {
					
				}
			}

			DEBUGP("calling do_command4(%u, argv, &%s, handle):\n",
			       newargc, curTable);

			for (a = 0; a < newargc; a++)
				DEBUGP("argv[%u]: %s\n", a, newargv[a]);

			needChain(chain);
			do_rule(pcnt, bcnt, newargc, newargv, newargvattr);

			save_argv();
			ret = 1;
		}
		if (!ret) {
			fprintf(stderr, "%s: line %u failed\n",
				prog_name, line);
			exit(1);
		}
	}
	if (curTable[0]) {
		fprintf(stderr, "%s: COMMIT expected at line %u\n",
			prog_name, line + 1);
		exit(1);
	}

	if (in != NULL)
		fclose(in);
	printf("</iptables-rules>\n");
	free_argv();

	return 0;
}
