#include "Die.h"
using namespace std;

//default ctor
Die::Die() {
	value = 0;
}

//one parameter ctor
Die::Die(int v) {
	value = v;
}

//getters
int Die::getValue(){
	return value;
}

//setters
void Die::setValue(int v) {
	value = v;
}