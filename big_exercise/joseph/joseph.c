#include <stdio.h>
#include <stdlib.h>
#define NEW (struct node*)malloc(sizeof(struct node))

static struct node *init(int n);

struct node {
	int nr;
	int flag;
	struct node *next;
};

/* n是玩游戏的人数,m是报的数 */
void joseph(int m, int n)
{
	int cnt = 0, out = 0;
	struct node *head, *this;

	head = init(n);
	while (out < n) {
		this = head;
		while (this != NULL) {
			if (1 == this->flag) {
				cnt++;
				if (m == cnt) {
					cnt = 0;
					this->flag = 0;
					out++;
					printf("%3d:%3d out.", out,
					       this->nr);
					if (0 == out % 5)
						printf("\n");
				}
			}
			this = this->next;
		}
	}
	printf("\n");
}

/* 链表初始化 */
static struct node *init(int n)
{
	int i;
	struct node *head, *new, *this = NULL;

	for (i = 1; i <= n; i++) {
		new = NEW;
		if (new == NULL) {
			printf("Allocation failure\n");
			exit(1);
		}
		new->nr = i;
		new->flag = 1;
		new->next = NULL;
		if (this == NULL) {
			this = new;
			head = this;
		} else {
			this->next = new;
			this = new;
		}
	}

	return head;
}
