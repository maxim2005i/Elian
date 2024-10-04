#include <stdio.h>
#include <string.h>

struct Medicine {
	int id;
	char name[50];
	char country[50];
	char firm[50];
};

int main() {
	struct Medicine paracetomol = {100, "paracetomol", "Russia", "Farmstandart"};

	printf(paracetomol.name, paracetomol.country);

	return 0;
}

