#include <iostream>
#include "cf.h"

/*
	Calcolo codice fiscale
	
	(Non supporta casi di omonimia, yet)
*/

int main()
{
	std::string nome, cognome, cod_catastale;
	int giornoN, meseN, annoN;
	char sesso;
	
	std::cout << "Ins. nome: ";
	std::cin >> nome;
	
	std::cout << "Ins. cognome: ";
	std::cin >> cognome;
	
	std::cout << "Ins. cod. catastale: ";
	std::cin >> cod_catastale;
	
	std::cout << "Ins. giorno nascita: ";
	std::cin >> giornoN;
	
	std::cout << "Ins. mese nascita: ";
	std::cin >> meseN;
	
	std::cout << "Ins. anno nascita: ";
	std::cin >> annoN;
	
	Data dataNascita(giornoN, meseN, annoN);
	
	std::cout << "Ins. sesso (M/F): ";
	std::cin >> sesso;
	
	CodiceFiscale cf(nome, cognome, dataNascita, cod_catastale, sesso);
	std::cout << "CF = " << cf.calcola() << std::endl;
	
    return 0;
}