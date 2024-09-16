# Cube-de-Vigenere
Chiffrement de Vigenère multidimensionnel universel.  Ce chiffre ajoute une dimension (généralisable) au chiffrement de Vigenère (Tableau) pour former un "Cube".
Amélioration par rapport au chiffre de Vigenère classique, la clé est transposé (transposition rectangulaire) donc le test de Kasiski est moins efficace, puis une fonction de hashage (logarithme discret) est appliqué avant le chiffrement. 

## Installation

```zsh
gcc -o Cube_Vigenère Cube_Vigenère.c
```
## Usage
Lors de l'ouverture de l'exécutable ce message s'affiche :
```bash
Voulez-vous Chiffrer (1) ou Déchiffrer (2) ?
```
Quelques exemples de chiffrement (haut) et de déchiffrement (bas) :
```bash
1
Entrez le message : 
A æ💀‹ࢢญጩ ឦᮗᰜ∑⨕𐁍
Entrez la clé : 
Github
񕐈疲򋮢񴡇񐓫򍢾򯫮񏊿򌷥񕏧贸򍙓򰹨񐛃򀧔򿊙
```
```bash
2
Entrez le message :
񕐈疲򋮢񴡇񐓫򍢾򯫮񏊿򌷥񕏧贸򍙓򰹨񐛃򀧔򿊙
Entrez la clé : 
Github
A æ💀‹ࢢญጩ ឦᮗᰜ∑⨕𐁍
```
Remarque : La troisième dimension (z) est fixe (Version 1).

Contact au début du code source.
