// SPDX-License-Identifier: GPL-2.0+
#ifndef __RZG_UPDATE_FDT__
#define __RZG_UPDATE_FDT__

#include <common.h>
#include <malloc.h>
#include <fdt_support.h>
#include <linux/ctype.h>
#include "common.h"

int add_new_node(void *fdt, char *node);

int add_new_node(void *fdt, char *node)
{
	char *parent, *name;
	int len, nodeoffset;

	name = strrchr(node, '/');
	if (!strcmp(node, "/") || !name)
		return 0;

	len = strlen(node) - strlen(name) + 1;
	parent = malloc(sizeof(char) * len);
	strncpy(parent, node, len);
	parent[len] = '\0';
	nodeoffset = fdt_path_offset(fdt, parent);
	if (nodeoffset < 0) {
		/* Remove the last '/' in the path*/
		parent[len - 1] = '\0';
		nodeoffset = add_new_node(fdt, parent);
		if (nodeoffset == 0)
			nodeoffset = fdt_path_offset(fdt, "/");
	}
	nodeoffset = fdt_add_subnode(fdt, nodeoffset, name + 1);
	free(parent);
	return nodeoffset;
}

int fdt_parse_prop(void *fdt, char **newval, char *data, int *len)
{
	char *cp;               /* temporary char pointer */
	char *newp;             /* temporary newval char pointer */
	unsigned long tmp;      /* holds converted values */

	*len = 0;
	newp = newval[0];

	/* An array of cells */
	if (*newp == '<') {
		newp++;
		while ((*newp != '>')) {
			/*
			 * Keep searching until we find that last ">"
			 * That way users don't have to escape the spaces
			 */
			if (*newp == '\0')
				break;

			cp = newp;

			if (strchr(cp, '&')) {
				char *handler, *next;
				int size, nodeoffset;
				u32 phandle;

				cp = strchr(cp, '&');
				next = strchr(cp + 1, '&');
				if (!next)
					size = strlen(cp) - 1;
				else
					size = next - cp - 1;

				/* Trim the space or tab*/
				while (cp[size] == ' ' || cp[size] == '\t')
					size--;

				handler = malloc(sizeof(char) * size);
				/* We increase data pointer and decrease size
				 * to 1 value to remove '&' character
				 */
				strncpy(handler, cp + 1, size - 1);
				handler[size - 1] = '\0';
				nodeoffset = fdt_path_offset(fdt, handler);
				if (nodeoffset > 0) {
					phandle = fdt_get_phandle(fdt,
								  nodeoffset);
					if (phandle == 0) {
						phandle =
							fdt_alloc_phandle(fdt);
						fdt_set_phandle(fdt, nodeoffset,
								phandle);
					}
					*(fdt32_t *)data =
							cpu_to_fdt32(phandle);
				}
				free(handler);
				/* Move to the next */
				newp = cp + size;
			} else  {
				tmp = simple_strtoul(cp, &newp, 0);
				if (*cp != '?')
					*(fdt32_t *)data = cpu_to_fdt32(tmp);
				else
					newp++;
			}
			data  += 4;
			*len += 4;

			/* If the ptr didn't advance,
			 * something went wrong
			 */
			if ((newp - cp) <= 0) {
				printf("Sorry, I could not convert ");
				printf("\"%s\"\n", cp);
				return 1;
			}
			while (*newp == ' ')
				newp++;
		}

		if (*newp != '>') {
			printf("Unexpected character '%c'\n", *newp);
			return 1;
		}
	} else if (*newp == '[') {
		/*
		 * Byte stream.  Convert the values.
		 */
		newp++;
		while (*newp != ']') {
			while (*newp == ' ')
				newp++;
			if (*newp == '\0')
				break;
			if (!isxdigit(*newp))
				break;
			tmp = simple_strtoul(newp, &newp, 16);
			*data++ = tmp & 0xFF;
			*len    = *len + 1;
		}
		if (*newp != ']') {
			printf("Unexpected character '%c'\n", *newp);
			return 1;
		}
	} else {
		/*
		 * Assume it is one or more strings.  Copy it into our
		 * data area for convenience (including the
		 * terminating '\0's).
		 */
		size_t length = strlen(newp) + 1;

		strcpy(data, newp);
		data += length;
		*len += length;
	}
	return 0;
}

int process_node_data(void *fdt, char *node, char *prop, char *val)
{
	static char data[1024] __aligned(4);
	const void *ptmp;
	int len, ret, nodeoffset;

	nodeoffset = fdt_path_offset(fdt, node);
	if (!val) {
		len = 0;
	} else {
		ptmp = fdt_getprop(working_fdt, nodeoffset, prop, &len);
		if (len > 1024) {
			printf("prop (%d) doesn't fit in scratchpad!\n", len);
			return 1;
		}
		if (ptmp)
			memcpy(data, ptmp, len);

		ret = fdt_parse_prop(fdt, &val, data, &len);
		if (ret != 0)
			return ret;
	}

	/* After parsing value for property, nodeoffset may be changed*/
	nodeoffset = fdt_path_offset(fdt, node);

	return fdt_setprop(fdt, nodeoffset, prop, data, len);
}

int update_fdt(void *fdt, const char **list_dt_change, int size)
{
	int i, ret;

	if (!list_dt_change)
		return 1;

	if ((size > 0) && ((size % 3) == 0)) {
		printf("Changing the current FDT in %lx.\n", (uintptr_t)fdt);
	} else {
		pr_debug("Wrong define FDT change structure. No change FDT.\n");
		return 1;
	}

	for (i = 0 ; i < size; i += 3) {
		int nodeoffset;
		char *node, *prop, *val;

		node = (char *)list_dt_change[i];
		prop = (char *)list_dt_change[i + 1];
		val = (char *)list_dt_change[i + 2];
		nodeoffset = fdt_path_offset(fdt, node);

		if (!node)
			continue;

		if (!prop) {
			if (nodeoffset < 0) {
				pr_debug("\tUnavailable node %s\n", node);
				continue;
			}
			printf("   Remove Node %s\n", node);
			ret = fdt_del_node(fdt, nodeoffset);
			if (ret < 0) {
				printf("\tCan't remove. ERR %d\n", ret);
			} else {
				printf("\tRemoved.\n");
			}
		} else {
			printf("   Config Node %s\n", node);
			if (nodeoffset < 0) {
				pr_debug("\tUnavailable node\n");
				printf("\tCreate node.\n");
				nodeoffset = add_new_node(fdt, node);
			}
			printf("\tSet property %s : %s\n", prop, val);
			ret = process_node_data(fdt, node, prop, val);
			if (ret < 0) {
				printf("\t\tCan't set property. ERR %d\n", ret);
			}
		}
	}
	/* We fit the FDT size in order not to consume the memory*/
	fdt_shrink_to_minimum(fdt, 0x0);
	return 1;
}
#endif // __RZG_UPDATE_FDT__
