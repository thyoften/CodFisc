#include "cf.h"

bool is_consonante(char c) {
	c = tolower(c);
	return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u';
}

int number_char(char c)
{
    if (c >= 48 && c <= 57)
        return c - 48; //'0'-'9' -> 0-9
    else if (c >= 65 && c <= 90)
        return c - 65; //'A'-'Z' -> 0-25
    else
        return -1;
}

char CodiceFiscale::car_controllo(std::string part_cf)
{
	int total = 0;
	for (int i = 0; i < part_cf.size(); i++)
	{
		char c = part_cf[i];
		int val = 0;
		if ((i + 1) % 2 == 0) //Se il carattere è in pos. pari
			val = number_char(c);
		else
			val = val_dispari[number_char(c)];

		total += val; //Aggiungi al totale
	}

	return (char)((total % 26) + 65); //ottieni una lettera tra A e Z
}

//Ottieni il carattere corr. al mese di nascita
//Usa il mese come indice
char CodiceFiscale::car_mese()
{
	std::string mesi = "ABCDEHLMPRST";
	return mesi[_dataNascita.Mese - 1];
}

//Rimuove spazi e inserisce tutti i caratteri restanti in maiuscolo
std::string prepara_txt(std::string txt)
{
	std::string final_str;
	
	for(char c : txt)
	{
		if(c != ' ' || c != '\'')
			final_str += toupper(c);
	}
	
	return final_str;
}

//Parte iniziale, usato poi per generare il nome e il cognome
std::string get_inizio_cf(std::string dato) {
	std::string consonanti, vocali;
	
	dato = prepara_txt(dato);
	
	if(dato.size() < 3) //Il dato (nome, cognome) non ha abb. caratteri?
						//Prendili e aggiungi X
	{
		return "" + dato[1] + dato[2] + std::string("X"); 
	} else {
		for(char c : dato)
		{
			if(is_consonante(c))
				consonanti += c;
			else
				vocali += c; 
		}	
		
		if(consonanti.size() < 3)
		{
			//std::cout << "we're here" << std::endl;
			int i = 0;
			//Se non ci sono abbastanza consonanti, occorre usare le vocali
			while(consonanti.size() != 3 && i < vocali.size())
			{
				//std::cout << "we're also here" << std::endl;
				consonanti += vocali[i];
				i++;
			}
				
			while(consonanti.size() < 3) //Se neanche le vocali bastano, aggiungi X
				consonanti += "X";
				
		}
	}
	
	return consonanti;
}

std::string CodiceFiscale::get_cognome()
{
	//Prendi le prime 3 lettere per il cognome
	return get_inizio_cf(this->_cognome).substr(0, 3); 
}

std::string CodiceFiscale::get_nome()
{
	
	std::string nm = get_inizio_cf(this->_nome);
	
	if(nm.size() > 3) { //Prendi la prima, la terza e la quarta per il nome
		std::string nome_fin;
		nome_fin += nm[0];
		nome_fin += nm[2];
		nome_fin += nm[3];
		
		return nome_fin;
	} else 
		return nm;
}

std::string CodiceFiscale::calcola() {
	std::string cf;
	
	cf += get_cognome() + get_nome() + std::to_string(_dataNascita.Anno % 100); //Ultime due cifre
	cf += car_mese();
	if(_sesso == 'M')
		if(_dataNascita.Giorno > 10)
			cf += std::to_string(_dataNascita.Giorno);
		else
			cf += '0' + std::to_string(_dataNascita.Giorno);
	else
		cf += std::to_string(_dataNascita.Giorno + 40);
	cf += _codCat;
	cf += car_controllo(cf);
	
	return cf;
}