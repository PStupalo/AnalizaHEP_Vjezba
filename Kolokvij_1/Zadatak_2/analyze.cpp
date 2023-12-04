#include "Analyzer.h"

int main (void){
	Analyzer *analyze;
	analyze = new Analyzer ();
	analyze -> Plot ();
	analyze -> ~Analyzer ();

	return 0;
}
