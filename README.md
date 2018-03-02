# line_input - Gestion d'une ligne de commande

La fonction permet l'édition d'une ligne de commande. L'utilisateur peut se déplacer dans celle-ci et l'éditer à l'endroit voulu.

La fonction `line_input` est prototypée de la manière suivante :

	char *line_input(char *prompt, t_list *history)

- La variable `prompt` est la chaîne représentant l'invite de commande du Shell.
- La variable `history` contient l'historique des précédentes commandes.

Ces deux variables peuvent être `NULL`.

Lorsque l'utilisateur appuie sur `entrée`, la fonction renvoie la commande tapée.

## Fonctionnalités

- [x] Édition de la ligne à l'emplacement du curseur
- [x] Déplacement du curseur
	- vers la gauche et la droite sur plusieurs lignes
- [x] Déplacement rapide
	+ [x] de haut en bas
		- `Ctrl`-`haut/bas` 
	+ [x] de mot en mot
		- `Ctrl`-`gauche/droite`
	+ [x] en début ou fin de ligne
		- `Ctrl-a`, `home` ou `fn`+`gauche` pour aller en début de ligne
		- `Ctrl-e`, `end` ou `fn`+`droite` pour aller en début de ligne
- [x] Sélection de tout ou partie de la ligne
	+ [x] sélection lettre par lettre avec `Shift`-`gauche/droite`
	+ [x] sélection plus complète avec `Shift`-_`combinaison de touches de déplacement rapide`_
- [x] Modification de la sélection
	+ [x] suppression de la sélection
	+ [x] remplacement de la sélection par un caractère
	+ [x] copie de la sélection avec `alt`-`c`
	+ [x] coupage la sélection avec `alt`-`x`
	+ [x] collage de la précédente sélection avec `alt`-`v`
- [x] Navigation dans l'historique
	+ `Ctrl-p` ou `haut` pour voir les commandes précédentes
	+ `Ctrl-n` ou `bas` pour voir les commandes suivantes
- [x] Gestion de `Ctrl-d` : efface le caractère sous le curseur, quitte s'il n'y a plus de caractère et renvoie `exit`
- [x] Gestion de `Ctrl-c`
- [x] Invertion du caractère sous le curseur et du précédent avec `Ctrl-t`
- [x] Effacement de l'écran avec `Ctrl-l`
- [ ] Completion de commande avec `tab`

## Utilisation et compilation

*line_input* utilise des fonctions de la [libft][], de la [libag][], de [environment][] et de [completion][] et a besoin de leurs headers pour pouvoir être compilé. Il faut fournir au _Makefile_ le chemin vers les dossiers les contenant à l'aide des variables *LIBFT_INC*, *LIBAG_INC* et *ENV_INC* et *CMP_INC*.

	$> make LIBFT_INC=../libft/includes LIBAG_INC=../libag/includes ENV_INC=../environment/includes CMP_INC=../completion/includes all

Le programme devra être compilé avec la bibliothèque `termcap`.

La documentation peut être créée avec la commande suivante :

	$> make doxygen

La documentation est générée grâce à [Doxygen][]. Le _Makefile_ utilise l'alias `doxygen` pour faire appel à l'exécutable, mais si celui-ci n'est pas défini il faut utiliser la commande :

	$> make doxygen DOXYGEN=/CHEMIN/VERS/EXECUTABLE/DE/DOXYGEN

## Sources

- [Opengroup.org - The Open Group Base Specifications Issue 7](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html)
- [marionpatrick.free.fr - Tutoriel Shell](http://marionpatrick.free.fr/man_html/html/tuto_shell.html)

[libft]: https://github.com/aguerin42/libft.git
[libag]: https://github.com/aguerin42/libag.git
[environment]: https://github.com/aguerin42/environment.git
[completion]: https://github.com/aguerin42/completion.git
[Doxygen]: https://github.com/doxygen/doxygen
