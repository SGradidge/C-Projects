/*
 * Description:
 * This program takes a file name/location, opens the file and processed the commands into a linked list. The program
 * is command sensitive and will only accept the commands: Push, Remove, Head, Tail and PrintList. These commands are 
 * case sensitive and any other input will result in an error being generated. The Push and Remove commands require a
 * a parameter e.g. Push x where x can be any character from A - Z only.
 *
 * Inputs:
 * argc - the number of inputted arguments
 * argv:
 * argv[0] - program name
 * argv[1] - the input file name
 *
 * Outputs:
 * If valid inputs are received:
 * - Printlist: Prints all the node values in the list in order
 * - Head: Prints the value of the head node
 * - Tail: Prints the value of the tail node
 * - Length: Prints the size of the linked list
 * If invalid inputs are received
 * - prints "Input not valid"
 * - prints "Out of memory" if it runs out of memory
 *
 * Caveats
 * This program only runs with the specified commands above. This program only accepts A - Z as parameters for Push and Remove commands.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Description:
 * Create a node structure that can be used to create the linked list. Each node contains a data part of type character and also a pointer 
 * to the next node in the linked list.
 */
struct node 
{
	char data; /*Data part of the node*/
	struct node *next; /*A pointer to the next node in the linked list*/
};

int length = 0; /*Keep track of the length of the linked list*/
struct node *head = NULL; /*Create a head node for the linked list and set it to NULL*/

/*
 * The printError routine takes a error number and outputs the correspoding error message
 *
 * Algorithm
 * Recevie an error number as an input parameter and output a orrespoding error message
 * 
 *
 * Inputs
 * Error number as input parameter
 *
 * Outputs
 * Input paramter: 0 - Print "Input not valid"
 *						 1 - Print "Out of memory" and exit the program with an exit failure parameter
 * Caveats
 * The routine can only accept input parameters of either '1' or '0'
 *  
 */
void printError(int errorNo)
{
	if(errorNo == 0) /*Check if input parameter '0' was received*/
	{
		fprintf(stderr, "Input not valid\n"); /*Print input not valid*/
	}
	else if(errorNo == 1) /*Check if input parameter '1' was received*/
	{
		fprintf(stderr, "Out of memory\n"); /*Print Out of memory*/
		exit(EXIT_FAILURE); /*Exit the program*/
	}	
}

/*
 * The pushNode routine creates a new node with the given character parameter, and adds the node to the linked list.
 *
 * Algorithm
 * Receive a character and create a node with the data part set to the received character
 * 
 * Inputs
 * The data of the new node in the form of a character
 *
 * Outputs
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z
 *  
 */
void pushNode(char c)
{
	if(length != 0) /*Check if the linked list has a head*/
	{
		struct node *tempNode = NULL; /*Create a new temporary node*/
		if((tempNode = malloc(sizeof(struct node))) == NULL) /*Allocate memory to the temp Node and check for any memory error*/
		{
			printError(1);  /*Print the memory error*/
		}
		tempNode->data = c; /*Assign the recevied parameter to the temp node's data field*/
		tempNode->next = head; /*Make the temp node point to the head node*/
		head = tempNode; /*Update the head node to be the temp node*/
		length++; /*Increase the size of length*/
		
	}
	else /*Create the head of the linked list*/
	{
		if((head = malloc(sizeof(struct node))) == NULL) /*Check if the linked list size is bigger than zero*/
		{
			printError(1);/*Print the memory error*/
		}
		head->data = c; /*Assign the recevied parameter to the head node's data field*/
		head->next = NULL; /*Update the head node to point to NULL*/
		length++; /*Increase the size of length*/
	}
}

/*
 * The RemoveNode routine removes a node with the given character parameter from the linked list.
 *
 * Algorithm
 * Receive a character and remove a node with the data part set to the received character
 * 
 * Inputs
 * The data of the node to remove in the form of a character
 *
 * Outputs
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void removeNode(char c) /*Increase the size of length*/
{
	int found = 0; /*Keep track of if the node has been found*/
	if(length == 0) /*Check if a link list exists*/
	{
		printError(0);
		return;
	}
	else if(head->data == c) /*Check if the head is the node to be removed*/
	{
		struct node *tempNode = head;
		head = head->next;
		free(tempNode);
		found = 1;
		length--;
	}
	else /*Run through the list until the node to be removed is found*/
	{
		struct node *tempNodeBack = head;
		struct node *tempNodeFront = head->next;
		while(tempNodeFront != NULL)
		{
			if(tempNodeFront->data == c) /*Remove the node from the list if found*/
			{
				tempNodeBack->next = tempNodeFront->next;
				tempNodeFront = NULL;
				free(tempNodeFront);
				found = 1;
				length--;
			}
			else /*If not found, check the next node*/
			{
				tempNodeFront = tempNodeFront->next;
				tempNodeBack = tempNodeBack->next;
			}
		}	
	}
	if(found == 0) /*If the node is not found, output an errors*/
	{
		printError(0);
		return;
	}
}

/*
 * The headNode routine prints the head node's data of the linked list 
 *
 * Algorithm
 * Prints the head node's data of the linked list 
 * 
 * Inputs
 * None
 *
 * Outputs
 * Prints the data part of the head node
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void headNode()
{
	if(length != 0)
	{
		printf("%c\n", head->data); /*Print the head's data part*/
	}
	else
	{
		printError(0);
	}
}

/*
 * The lengthNode routine prints the size of the linked list 
 *
 * Algorithm
 * Prints the size of the linked list 
 * 
 * Inputs
 * None
 *
 * Outputs
 * Prints the size of the linked list
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void lengthNodes()
{
	printf("%d\n",length);
}

/*
 * The tailNode routine prints the tail node's data of the linked list 
 *
 * Algorithm
 * Prints the tail node's data of the linked list 
 * 
 * Inputs
 * None
 *
 * Outputs
 * Prints the data part of the tail node
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void tailNode()
{
	if(length != 0)
	{
		struct node *tempNode = head;
		while(tempNode->next != NULL) /*Loop through to the last node*/
		{
			tempNode = tempNode->next;
		}
		printf("%c\n",tempNode->data); /*Print its data part*/
	}
	else
	{
		printError(0);
	}
}

/*
 * The printNode routine prints the data part of all the nodes in the linked list
 *
 * Algorithm
 * Prints the data part of all the nodes in the linked listt 
 * 
 * Inputs
 * None
 *
 * Outputs
 * Prints the data part of all the nodes in the linked list
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void printNodes()
{
	if(length == 0)
	{
		printf("-\n");
	}
	else
	{
		struct node *tempNode = head;
		while(tempNode != NULL) /*Loop through all the nodes*/
		{
			printf("%c",tempNode->data); /*Print the nodes data part*/
			tempNode = tempNode->next;
			if(tempNode != NULL)
			{	
				printf("-");
			}
		}
		printf("\n");
	}
}

/*
 * The processCommand routine processess all of the commands read in from the text file
 *
 * Algorithm
 * Receive the commands in the form of an array, check if the commands are valid and then 
 * process the commands
 * 
 * Inputs
 * commands - 2d character array containing the read-in commands e.g. Push A
 * count - the number of commands received
 *
 * Outputs
 * If an error is encountered, it will output the corresponding error message.
 *	
 * Caveats
 * The routine will only accept data characters between A - Z  
 */
void processCommands(char commands[100][150],int count)
{
	int i;
	for(i = 0; i < count; i++)
	{
		char *pieces = strtok (commands[i]," "); /*Split the commands at the space*/
		char *command;
		char value;

      command = pieces; /*Store the first piece into commands*/
      pieces = strtok(NULL, " "); /*Store the second piece into pieces*/
		if(pieces != NULL) /*Check if the second piece is not NULL*/
		{
			if(pieces[1] == '\n' && ((int)(pieces[0]) > 64) && ((int)(pieces[0]) < 91)) /*Check that the second pieces
			is between A-Z*/
			{
				value = pieces[0];
			}
			else
			{
				command = "useless"; /*If an incorrect command is received*/
			}
		}
		
		if(strcmp("Push",command) == 0) /*Push command received*/
		{
			pushNode(value);
		}
		else if(strcmp("Remove",command) == 0) /*Remove command received*/
		{
			removeNode(value);
		}
		else if(strcmp("Head\n",command) == 0 || strcmp("Head",command) == 0) /*Head command received*/
		{
			headNode();
		}
		else if(strcmp("Length\n",command) == 0 || strcmp("Length",command) == 0) /*Length command received*/
		{
			lengthNodes();
		}
		else if(strcmp("Tail\n",command) == 0 || strcmp("Tail",command) == 0) /*Tail command received*/
		{
			tailNode();
		}
		else if(strcmp("PrintList\n",command) == 0 || strcmp("PrintList",command) == 0) /*PrintList command received*/
		{
			printNodes();
		}
		else /*Incorrect command received*/
		{
			printError(0);
		}
	}
}

/*
 * The main routine controls the execution of the overall program.
 *
 * Algorithm
 * Get input from command line and pass it to prac2
 *
 Inputs:
 * argc - the number of inputted arguments
 * argv:
 * argv[0] - program name
 * argv[1] - the input file name
 *
 * Outputs
 * "Input not valid" if the number of arguments is not 4
 *
 * Caveats
 * This program only accepts A - Z as parameters for Push and Remove commands. 
 */
int main(int argc, char* argv[]) /*The main method*/
{
	FILE *fptr;
    char ch;
	char storeCommands[100][150],buffer[150];
	int count = 0;

	if(argc != 2) /*Check if the input parameters have 3 arguments*/
	{
		printError(0);
	}
	else
	{
		fptr = fopen(argv[1], "r"); /*Open the file*/
		if (fptr == NULL)
		{
		    printError(0);
		}
		while(fgets(buffer,150,fptr)) /*Read the file*/
		{
		    strcpy(storeCommands[count],buffer);
		    count++;
		}
		fclose(fptr);
		processCommands(storeCommands,count); /*Give the commands to processCommands routine*/
	}

	return 0; /*Return at the end of the main method*/
}
