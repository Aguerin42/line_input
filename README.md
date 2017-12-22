# line_edit

Le programme permet l'édition d'une ligne de commande. L'utilisateur peut se déplacer dans celle-ci et l'éditer à l'endroit voulu.

La fonction `line_input` est prototypée de la manière suivante :

	char *line_input(char *prompt, t_list *history)

- La variable `prompt` est la chaîne représentant l'invite de commande du Shell. La fonction se sert de cette variable pour que l'affichage soit correct et pour le réafficher en cas d'effacement de l'écran.
- La variable `history` contient l'historique des précédentes commandes.

Ces deux variables peuvent être `NULL`.

Lorsque l'utilisateur appuie sur `entrée`, la fonction renvoie la commande tapée.

## Fonctionnalités

- [x] Édition de la ligne à l'emplacement du curseur
- [x] Déplacement du curseur vers la gauche et la droite sur plusieurs lignes
- [x] Navigation dans l'historique
	+ `Ctrl-p` ou `flèche haute` pour voir les commandes précédentes
	+ `Ctrl-n` ou `flèche basse` pour voir les commandes suivantes
- [ ] Couper, copier, coller une partie de la ligne
- [x] Déplacement rapide de mot en mot
	+ `Ctrl-flèche gauche` pour aller au mot précédent
	+ `Ctrl-flèche droite` pour aller au mot suivant
- [x] Déplacement rapide en début ou fin de ligne
	+ `Ctrl-a`, `home` ou `fn`+`flèche de gauche` pour aller en début de ligne
	+ `Ctrl-e`, `end` ou `fn`+`flèche de droite` pour aller en début de ligne
- [x] Gestion de `Ctrl-d`
- [x] Invertion du caractère sous le curseur et du précédent avec `Ctrl-t`
- [x] Effacement de l'écran avec `Ctrl-l`

## **Sources**

- [Opengroup.org - The Open Group Base Specifications Issue 7](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
- [marionpatrick.free.fr - Manuel des manuels](http://marionpatrick.free.fr/man_html/html/index.html)