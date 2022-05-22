#include <iostream>
#include <cctype>
#include <string>

struct Data {
    int Giorno;
    int Mese;
    int Anno;

    Data() { }

    inline Data(int g, int m, int a)
    {
        Giorno = g;
        Mese = m;
        Anno = a;
    }

    inline Data(Data& dt)
    {
        Giorno = dt.Giorno;
        Mese = dt.Mese;
        Anno = dt.Anno;
    }
};

class CodiceFiscale {
    private:
        std::string _nome, _cognome, _codCat;
        Data _dataNascita;
        char _sesso;
		
		//Usato per la generazione del carattere di controllo,
		//nel caso di caratteri in posizione dispari.
        int val_dispari[26] = { 1, 0, 5, 7, 9, 13, 15, 17, 19, 21,
                                2, 4, 18, 20, 11, 3, 6, 8, 12, 14,
                                16, 10, 22, 25, 24, 23 };
								
		char car_controllo(std::string);
		char car_mese();
		std::string get_nome();
		std::string get_cognome();
    public:
        inline CodiceFiscale(std::string nome, std::string cognome, Data dataNascita, std::string codCat, char sesso)
        {
            _nome = nome;
            _cognome = cognome;
            _dataNascita = dataNascita;
			_sesso = toupper(sesso);
			_codCat = codCat;
        }

        std::string calcola();
};
