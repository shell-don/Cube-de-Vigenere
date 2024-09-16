// Code écrit par : Mathis

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>


void repeatKey(wchar_t *key, size_t taille_voulu, wchar_t *repeatedKey) {
   
    size_t keyLen = wcslen(key);
    size_t i, j;

    for (i = 0, j = 0; i < taille_voulu; i++, j++) {
        if (j == keyLen) {
            j = 0;
        }
        repeatedKey[i] = key[j];
    }
    repeatedKey[taille_voulu] = L'\0';  
}

// calcul a^b mod m
int log_discret(unsigned long long a, int b, int m) {

	int result = 1 ;
	a = a % m ;
	while (b > 0) {
		if (b % 2 == 1) {
			result = (result * a) % m ; 
		}
	b = b / 2 ; 
	a = (a * a) % m ;
	}
	return result ; 
}


void rectangle_proche(int n, int *lignes, int *Colonnes) {
    	int sqrt_n = (int)sqrt(n) ;
    	*lignes = sqrt_n ;
    	*Colonnes = sqrt_n ;

    	while ((*lignes) * (*Colonnes) < n) {
        	if ((*Colonnes) <= (*lignes)) {
            		(*Colonnes)++ ; 
        	} else {
            		(*lignes)++ ;
        	}
    	}
}


bool Temoin_de_Miller(int n, unsigned long long a) {
    	
	int d = n - 1 ;
    	while (d % 2 == 0) {
        	d /= 2 ;
    	}
    
    	int x = log_discret(a, d, n) ;
    	if (x == 1 || x == n - 1) {
        	return false ;
    	}
    
    	while (d != n - 1) {
        	x = log_discret(x, x, n) ;
        	d *= 2 ;
        
        	if (x == n - 1) {
            		return false ;
        	}
        	if (x == 1) {
            		return true ;
        	}
    	}
    	return true ;
}


bool Miller_Rabin(int n, int k) {
    
	if (n < 4) {
        	return n == 2 || n == 3 ;
    	}

    	for (int i = 0; i < k; i++) {
        	unsigned long long a = 2 + rand() % (n - 3) ;
        	if (Temoin_de_Miller(n, a)) {
            		return false ; 
        	}
    	}
    	return true ; 
}


int main() {
    
	setlocale(LC_ALL, "") ;

  size_t buffer_size = 1024 ; 
	char Choice[3] ; 
	int lignes, Colonnes ;

	printf("Voulez-vous chiffrer (1) ou déchiffrer (2) ?\n") ;
	fgets(Choice, 3, stdin) ;

	if (*(&Choice[0]) != '1' && *(&Choice[0]) != '2') {
        	printf("Choix invalide.\n") ;
        	return 1 ; 
  }
	
  // Allocation de la mémoire pour le message
  wchar_t* buffer = (wchar_t*)calloc(buffer_size, sizeof(wchar_t)) ;
	if (buffer == NULL) {
        	fwprintf(stderr, L"Erreur d'allocation de mémoire pour le tampon\n") ;
        	return 1 ;
  }

  // Lire le message
  fprintf(stdout, "Entrez le message : \n") ;
  if (fgetws(buffer, buffer_size, stdin) == NULL) {
        	fwprintf(stderr, L"Erreur de lecture de l'entrée\n") ;
        	free(buffer) ;
        	return 1 ;
  }
	size_t size_message = wcslen(buffer) ;

	// Supprimer le caractère de nouvelle ligne s'il est présent
  if (size_message > 0 && buffer[size_message - 1] == L'\n') {
        	buffer[size_message - 1] = L'\0' ;
        	size_message-- ;
  }

	if (Miller_Rabin(size_message, 10)) {
    		fprintf(stderr, "Erreur : la taille du message est un nombre premier\n") ;
		    free(buffer) ;
    		return 1 ;
  }
    	
	// Allocation pour le message
  wchar_t* message = (wchar_t*)calloc(size_message + 1, sizeof(wchar_t)) ;
    	if (message == NULL) {
        	fwprintf(stderr, L"Erreur d'allocation de mémoire pour le message\n") ;
        	free(buffer) ;
        	return 1 ;
    	}
  wcscpy(message, buffer) ;

  // Allocation pour le message chiffré
  wchar_t* cipher_message = (wchar_t*)calloc(size_message + 1, sizeof(wchar_t)) ;
  if (cipher_message == NULL) {
        	fwprintf(stderr, L"Erreur d'allocation de mémoire pour le message chiffré\n") ;
        	free(message) ;
        	free(buffer) ;
        	return 1 ;
  }

  // Allocation pour la clé répétée
  wchar_t* cle = (wchar_t*)calloc(size_message + 1, sizeof(wchar_t)) ;
  if (cle == NULL) {
        	fwprintf(stderr, L"Erreur d'allocation de mémoire pour la clé\n") ;
        	free(cipher_message) ;
        	free(message) ;
        	free(buffer) ;
        	return 1 ;
  }

  // Lire la clé
  fwprintf(stdout, L"Entrez la clé : \n") ;
  if (fgetws(buffer, buffer_size, stdin) == NULL) {
        	fwprintf(stderr, L"Erreur de lecture de l'entrée pour la clé\n") ;
        	free(cle) ;
        	free(cipher_message) ;
        	free(message) ; 
        	free(buffer) ;
        	return 1 ;
  }
	size_t size_key = wcslen(buffer) ;
    	
  // Supprimer le caractère de nouvelle ligne s'il est présent
  if (size_key > 0 && buffer[size_key - 1] == L'\n') {
        	buffer[size_key - 1] = L'\0' ;
        	size_key-- ;
  }
	repeatKey(buffer, size_message, cle) ;
	size_key = wcslen(cle) ;

	if (size_key != size_message) {
		fprintf(stderr, "Erreur : La clé répétée ne fait pas la même taille que le messgae.") ;
		free(cle) ;
        	free(cipher_message) ;
        	free(message) ; 
        	free(buffer) ;
		return 1 ;
	}

	// transposition cle
	rectangle_proche(size_message, &lignes, &Colonnes) ;
  wchar_t Tableau[lignes][Colonnes] ; 
  int k = 0 ;
  for (int i = 0 ; i < lignes ; i++) {
      for (int j = 0 ; j < Colonnes ; j++) {
        		Tableau[i][j] = cle[k] ; k++ ;
      } 
  } 
	int p = 0 ;
  for (int j = 0 ; j < Colonnes ; j++) {
      for (int i = 0 ; i < lignes ; i++) {
        		cle[p] = Tableau[i][j] ; p++ ;
      } 
  } 
	cle[size_message] = L'\0' ;

  free(buffer) ; // cipher_message, cle, message

	if (*(&Choice[0]) == '1') {

  // Chiffrement du message
	for (size_t i = 0 ; i < size_message ; i++) {
    		
	  int x = (int)message[i] ;
	  int key_val = (int)cle[i] ; 
		int y = log_discret(2, key_val, 1114083) ;
	  cipher_message[i] = (wchar_t)(((x + y) + 3) % 0x10FFFF) ;

	}
	cipher_message[size_message] = L'\0' ;

  // Affichage du message chiffré
  fwprintf(stdout, L"%ls", cipher_message) ;

  // Libération de la mémoire
  free(cle) ;
  free(cipher_message) ;
  free(message) ;
    	return 0 ;
	}

	if (*(&Choice[0]) == '2') {

	// Déhiffrement du message
  for (size_t i = 0 ; i < size_message ; i++) {
    		int x = (int)message[i] ;
   	   	int key_val = (int)cle[i] ;
		    int y = log_discret(2, key_val, 1114083) ;
		
		    cipher_message[i] = (wchar_t)(((x - y) - 3) % 0x10FFFF) ;
	}
  cipher_message[size_message] = L'\0' ; // Assurer la terminaison de la chaîne

  // Affichage du message chiffré
  fwprintf(stdout, L"%ls", cipher_message) ;

  // Libération de la mémoire
  free(cle) ;
  free(cipher_message) ;
  free(message) ;
  return 0 ;
	}

	return 1 ;

}
