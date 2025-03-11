Le projet minishell de l'école 42 consiste à créer un interpréteur de commandes (shell) minimaliste en C, avec certaines fonctionnalités de base d'un shell UNIX. Ce projet aide les étudiants à comprendre en profondeur les systèmes d'exploitation, la gestion des processus et la gestion des entrées-sorties. Voici un aperçu des étapes nécessaires pour coder ce projet :

1. Initialisation du projet
Création du dossier du projet : Commence par créer un dossier pour ton projet (minishell), et initialise un dépôt Git pour gérer ton code source.
Préparer le Makefile : Crée un Makefile qui compile ton programme avec les bonnes options et dépendances (comme les bibliothèques standard C, etc.).
2. Analyse des fonctionnalités
Le but de minishell est de créer un programme qui :

Attend une entrée de la part de l'utilisateur.
Analyse cette entrée (parsing).
Exécute des commandes en appelant des programmes externes ou des builtins (comme cd, echo, exit, etc.).
Gère les redirections (>, <, >>, <<) et les tubes (|).
3. Développement des fonctionnalités de base
a. Boucle principale
Affichage d’un prompt : Crée un prompt pour indiquer à l'utilisateur qu'il peut entrer une commande.
Lecture de l'entrée utilisateur : Utilise des fonctions comme read() ou getline() pour récupérer l'entrée de l'utilisateur.
Exécution de la commande : Lorsque l'utilisateur entre une commande, il faut que le programme puisse exécuter cette commande. Cela implique de gérer la création de processus (via fork()) et d'exécuter des commandes (avec execve()).
Gérer la fin de commande : La boucle doit continuer tant que l'utilisateur ne tape pas exit.
b. Gestion des commandes internes (builtins)
Implémenter les commandes internes du shell, telles que :
echo : Afficher une ligne de texte.
cd : Changer le répertoire courant.
exit : Quitter le programme.
env : Afficher les variables d'environnement.
Ces commandes ne nécessitent pas de créer de nouveaux processus, il suffit de les gérer directement dans le shell.
c. Gestion des processus et fork
Fork : Lorsque l'utilisateur exécute une commande, ton shell doit créer un processus fils avec fork() et exécuter la commande dans ce processus avec execve().
Attente de fin du processus : Le parent doit attendre la fin du processus fils avec waitpid() ou wait().
d. Gestion des redirections
Implémenter les redirections comme >, <, >> :
Pour >, redirige la sortie standard vers un fichier.
Pour <, redirige l'entrée standard depuis un fichier.
Pour >>, ajoute à la fin du fichier au lieu de le remplacer.
Utilise des fonctions comme dup2() pour manipuler les descripteurs de fichiers.
e. Gestion des pipes
Implémenter les pipes (|), qui permettent de connecter la sortie d'une commande à l'entrée de la suivante.
Utilise pipe() pour créer un pipe, et dup2() pour rediriger les sorties et entrées des commandes.
4. Analyse de la commande (Parsing)
Tokenisation : La première étape est de diviser l'entrée de l'utilisateur en tokens. Par exemple, la commande ls -l | grep foo > result.txt doit être analysée en plusieurs parties : ls, -l, |, grep, foo, >, result.txt.
Gestion des espaces et des séparateurs : Il faut gérer les espaces entre les tokens et aussi les redirections et les pipes.
Gestion des guillemets et des échappements : Prendre en compte les chaînes entre guillemets et les caractères spéciaux échappés (\).
5. Gestion des erreurs
Vérification des erreurs : Ton programme doit être capable de détecter les erreurs lors de la création des processus, de l'ouverture des fichiers pour les redirections, et d'autres opérations système.
Gestion de l'entrée invalide : Si l'utilisateur entre une commande invalide ou des arguments erronés, le shell doit renvoyer un message d'erreur approprié.
6. Gestion des variables d’environnement
Le shell doit être capable de gérer les variables d'environnement (comme PATH, HOME, etc.). Pour cela, tu peux utiliser getenv() pour obtenir des variables d'environnement et setenv() ou unsetenv() pour les modifier.
7. Nettoyage et gestion de la mémoire
Il est essentiel de libérer la mémoire allouée dynamiquement à chaque étape, en particulier pour les chaînes de caractères et les structures de données utilisées pour stocker les tokens et les arguments des commandes.
8. Tests
Teste régulièrement ton code pour t'assurer que chaque fonctionnalité fonctionne correctement. Crée des tests unitaires et des tests d'intégration pour valider le comportement du shell.
Pense à tester :
Les commandes simples.
Les redirections.
Les pipes.
Les commandes internes.
Les erreurs comme des arguments manquants ou incorrects.
9. Améliorations et fonctionnalités avancées (facultatives)
Implémenter des fonctionnalités avancées comme les job control (gestion des processus en arrière-plan, &, fg, bg).
Supporter les signaux UNIX (par exemple, gérer les signaux SIGINT, SIGQUIT).
10. Rendu du projet
Une fois que ton shell fonctionne correctement, tu peux soumettre ton projet. Veille à respecter les règles de formatage et à fournir une documentation si nécessaire.
En résumé, le projet minishell implique de développer un interpréteur de commandes minimal, capable de lire les entrées des utilisateurs, d'analyser les commandes, d'exécuter les processus, et de gérer des fonctionnalités comme les redirections, les pipes, et les commandes internes. C’est un projet qui te permet de comprendre le fonctionnement interne des systèmes Unix et des shells.
