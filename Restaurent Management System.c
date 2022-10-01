// restaurent management (food menu for seller and customer) using linked_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char foodname[70];
	int quantity;
	float price;
	int data;
	struct node *prev;
	struct node *next;
} *heada = NULL, *heads, *headc = NULL, *taila = NULL, *tailc = NULL, *tails = NULL;

void adminmenu()
{
	printf("1. View total sales\n");
	printf("2. Add new item in order menu\n");
	printf("3. delete items from menu\n");
	printf("4. display order menu\n");
	printf("5. back to main menu\n\n\n");
	printf("Enter your choice:");
}
void customermenu()
{
	printf("1. Place your order\n");
	printf("2. View ordered items\n");
	printf("3. Delete item(s) from ordered menu\n");
	printf("4. Display final bill:\n");
	printf("5. Back to main menu\n\n");
	printf("Enter your choice: ");
}

struct node *createadmin(struct node *head, int data, char foodname[50], float price)
{
	struct node *x = (struct node *)malloc(sizeof(struct node));
	x->data = data;
	x->price = price;
	x->quantity = 0;
	strcpy(x->foodname, foodname);
	x->next = x->prev = NULL;

	struct node *temp = head;
	if (!temp)
		heada = taila = x;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = x;
		x->prev = taila;
		taila = x;
	}
	return heada;
}

struct node *createcustomer(struct node *head, int data, int quantity)
{
	struct node *x = (struct node *)malloc(sizeof(struct node));
	struct node *temp = heada;
	int flag = 0;
	while (temp)
	{
		if (temp->data == data)
		{
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	if (flag == 1)
	{
		x->data = data;
		x->price = quantity * temp->price;
		x->quantity = quantity;
		strcpy(x->foodname, temp->foodname);
		x->next = x->prev = NULL;

		struct node *temp1 = head;
		if (!temp1)
			headc = tailc = x;
		else
		{
			while (temp1->next)
				temp1 = temp1->next;
			temp1->next = x;
			x->prev = tailc;
			tailc = x;
		}
	}
	else
		printf("Item is absent in menu\n");
	return headc;
}
void display(struct node *head)
{
	struct node *temp = head;
	if (!temp)
		printf("List is Empty\n");
	else
	{
		while (temp)
		{
			if (temp->quantity == 0)
				printf("%d\t%s\t%0.2f\n", temp->data, temp->foodname, temp->price);
			else
				printf("%d\t%s\t%d\t\t%0.2f\n", temp->data, temp->foodname, temp->quantity, temp->price);
			temp = temp->next;
		}
		printf("\n");
	}
}
struct node *totalsales(int data, int quantity)
{
	struct node *x = (struct node *)malloc(sizeof(struct node));
	int flag = 0;

	struct node *temp1 = heada;
	while (temp1->data != data)
		temp1 = temp1->next;

	x->data = data;
	x->price = quantity * (temp1->price);
	x->quantity = quantity;
	strcpy(x->foodname, temp1->foodname);
	x->next = x->prev = NULL;

	struct node *temp = heads;

	if (temp == NULL)
		heads = x;
	else
	{
		while (temp->next)
		{
			if (temp->data == data)
			{
				flag = 1;
				break;
			}
			temp = temp->next;
		}

		if (flag == 1)
		{
			temp->quantity += x->quantity;
			temp->price += x->price;
		}
		else
			temp->next = x;
	}

	return heads;
}
void calculatesales()
{
	struct node *temp = headc;
	while (temp)
	{
		heads = totalsales(temp->data, temp->quantity);
		temp = temp->next;
	}
}
struct node *del(int data, struct node *head, struct node *tail)
{
	if (head == NULL)
		printf("List is empty\n");
	else
	{
		struct node *temp;
		if (data == head->data)
		{
			temp = head;
			head = head->next;
			if (head != NULL)
				head->prev = NULL;
			free(temp);
		}
		else if (data == tail->data)
		{
			temp = tail;
			tail = tail->prev;
			tail->next = NULL;
			free(temp);
		}
		else
		{
			temp = head;
			while (data != temp->data)
				temp = temp->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
		}
	}
	return head;
}
int deleteadmin()
{
	printf("enter sr no of food item to be deleted:\n");
	int sr;
	scanf("%d", &sr);

	struct node *temp = heada;
	while (temp)
	{
		if (temp->data == sr)
		{
			heada = del(sr, heada, taila);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
int deletecustomer()
{
	printf("Enter sr no of food item to be deleted:\n");
	int sr;
	scanf("%d", &sr);
	struct node *temp = headc;
	while (temp)
	{
		if (temp->data == sr)
		{
			headc = del(sr, headc, tailc);
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
void displaybill()
{
	display(headc);
	struct node *temp = headc;
	float totalprice = 0;
	while (temp)
	{
		totalprice += temp->price;
		temp = temp->next;
	}
	printf("TOTAL BILL: %0.2f\n", totalprice);
}
struct node *deletelist(struct node *head)
{
	if (head == NULL)
		return NULL;
	else
	{
		struct node *temp = head;
		while (temp->next)
		{
			temp = temp->next;
			free(temp->prev);
		}
		free(temp);
		head = NULL;
	}
	return head;
}

void admin()
{
	printf("-----------------------------------\n");
	printf("\t\tAdmin section\n");
	printf("-----------------------------------\n");
	while (1)
	{
		adminmenu();
		int opt;
		scanf("%d", &opt);
		if (opt == 5)
			break;
		switch (opt)
		{
		case 1:
			display(heads);
			break;
		case 2:
			printf("Enter sr no of the food item:\n");
			int sr, flag = 0;
			char name[50];
			float price;
			scanf("%d", &sr);
			struct node *temp = heada;
			while (temp)
			{
				if (temp->data = sr)
				{
					printf("food item with given sr number already exixts!\n\n");
					flag = 1;
					break;
				}
				temp = temp->next;
			}
			if (flag == 1)
				break;
			printf("enter food item name!\n\n");
			scanf("%s", &name);
			printf("enter price: \n");
			scanf("%f", &price);
			heada = createadmin(heada, sr, name, price);
			printf("new food item added to list!\n\n");
			break;
		case 3:
			if (deleteadmin())
			{
				printf("Updated list of food items!\n");
				display(heada);
			}
			else
				printf("food item of given sr no doesn't exists\n");
			break;
		case 4:
			printf("***Order Menu***\n\n");
			display(heada);
			break;
		default:
			printf("wrong input!! choose valid option\n");
			break;
		}
	}
}
void customer()
{
	int flag = 0;
	char c;
	printf("--------------------------------------------\n");
	printf("\t\tCUSTOMER SECTION\n");
	printf("--------------------------------------------\n");
	while (1)
	{
		customermenu();
		int opt;
		scanf("%d", &opt);
		if (opt == 5)
			break;

		switch (opt)
		{
		case 1:
			display(heada);
			printf("Enter no corresponding to item you want to order: ");
			int n;
			scanf("%d", &n);
			printf("Enter quantity: ");
			int qty;
			scanf("%d", &qty);
			printf("\n");
			headc = createcustomer(headc, n, qty);
			break;
		case 2:
			printf("List of ordered items: \n");
			display(headc);
			break;
		case 3:
			if (deletecustomer())
			{
				printf("Updated list of food items\n");
				display(headc);
			}
			else
			{
				printf("\t\t\t\tUpdated list of your ordered food items\n");
				break;
			}
		case 4:
			calculatesales();
			printf("Final bill\n");
			displaybill();
			headc = deletelist(headc);
			printf("Press back to return main menu:\n");
			//
			//
			flag = 1;
			break;
		default:
			printf("Choose valid option\n");
			break;
			if (flag == 1)
				break;
		}
	}
}
void mainmenu()
{
	printf("*********************************************\n");
	printf("\t\tWELCOME TO RESTAURENT\n");
	printf("*********************************************\n");
	printf("1. Admin section:\n");
	printf("2. Customer section:\n");
	printf("3. exit\n");
	printf("enter your choice: ");
}
int main()
{
	heada = createadmin(heada, 1, "Fresh Salad", 50);
	heada = createadmin(heada, 2, "Hot and Sour Soup", 100);
	heada = createadmin(heada, 3, "Manchow_Soup", 200);
	heada = createadmin(heada, 4, "Manchurian Noodles", 150);
	heada = createadmin(heada, 5, "Veg Fried Rice", 150);
	heada = createadmin(heada, 6, "Chicken Fried Rice", 180);
	heada = createadmin(heada, 7, "Hakka Noodles", 80);
	heada = createadmin(heada, 8, "Hot and Sour Soup", 100);

	while (1)
	{
		mainmenu();
		int choice;
		scanf("%d", &choice);

		if (choice == 3)
		{
			printf("********* THANK YOU! VISIT AGAIN ! ***********");
			break;
		}
		switch (choice)
		{
		case 1:
			admin();
			break;
		case 2:
			customer();
			break;
		case 3:
			break;
		default:
			printf("\t\t\tWrong input!! Please enter valid option\n");
			break;
		}
	}
	return 0;
}
