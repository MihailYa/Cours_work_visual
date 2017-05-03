#include "stdafx.hpp"
//#include "functions.h"
#include "input.hpp"
#include "Ford.hpp"
#include "Humori.hpp"

#define OUTPUT_DIR "output"

int main()
{
	CreateDirectory(L"" OUTPUT_DIR, NULL);

	graph *graph1 = NULL;
	input("gr3.txt", graph1);

	chdir(OUTPUT_DIR);
	graphviz("Input.png", graph1);

	//TO DO: const char*/./. values
	//TO DO: Add comments
	//TO DO: Chech for bugs
	//TO DO: Create new project without Develop
	//TO DO: Add visual part

	//------Main TO DO------
	//------Main TO DO------


	//Ford("Test.txt", graph1, 0, 1);
	Humori("Humori_result.txt", graph1);

	// Free memory
	delete_graph(graph1);

	getch();
}