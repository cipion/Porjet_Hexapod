Projet HEXAPOD

Acteur;
Thomas GACHE
Johan KARPINSKI

Langage de programmation : C++

Ce programme permet de contrôler un robot hexapode via une tablette (ou smartphone) ou une manette.

Programme :

Le projet est constitué de 5 parties (dossiers):
- Hexapod : c'est le code "main" du projet, il instancie un objet robot et un objet websocket

- jetty :   ce sont les classes qui gère l'arrivé des informations de positionnement de la manette ou tablette via le réseau WIFI. Objet géré dans un thread diffèrent de l'objet robot
        - robotwebsockethandler : classe de gestion des websockets entrants et erreur
        - websocketrobot : classe de gestion du thread et de la connexion au serveur

- robot :   ce sont des classes qui gère les mouvements du robot et qui envoi des instructions aux  objets servomoteurs
        - Patte : classe de gestion des informations à envoyer aux servomoteurs. Trois servomoteurs par patte
        - PeriodicUpdateTask : classe qui met à jour périodiquement la position du robot
        - Robot : classes qui gere les instructions à donner à chaque objet "Patte" (6 pattes)
        - StructPattes : classe qui gere les positionnements des objets "patte"

- Servomoteur : ces classes traduisent la demande de mouvement des classes robot pour les envoyer du le port série.
        - AX12 : classe qui gere la liaison série et qui prépare les paquets à envoyer
        - Servomoteur : classe qui contrôle est envoi les commandes à la classe "AX12"

- stdrpi : classe qui gère la communication avec les servomoteurs via le port série.


Commande :
La commande du robot se fait grâce à deux joysticks

Tout d'abord il faut se connecter au hotspot WIFI du robot
Nom : HEXAPOD
Mot de passe : hexapod_37

Pour charger la page de commande du robot on peut se connecter sur le serveur du robot via WIFI
Pour ça il faut utiliser un navigateur (Google chrome dans notre cas) et entrer l'adresse suivante dans la barre d'adresse.
Adresse IP Hexapod :	10.137.1.1
Masque : 		255.255.255.0

Ou installer dans la tablette/ordinateur le dossier "wwwRemote" fourni dans les livrables et ouvrir la page "index" dans un navigateur.


