# **HomeNet Control - A Web-Based IoT System for Smart Device Management**

> à partir de 20/01/2024 jusqu'à 20/2/2024


## Description du Projet
HomeNet Control est une application web innovante conçue pour combler le fossé entre les utilisateurs quotidiens et la technologie de la maison intelligente. Exploitant HTML, CSS, PHP et JavaScript, cette plateforme offre une interface conviviale pour la gestion et la surveillance à distance d'une large gamme d'appareils IoT dans les maisons ou les cafés. Au cœur de HomeNet Control, l'interaction avec les microcontrôleurs ESP32 permet de contrôler les lumières, les moteurs servo et autres gadgets intelligents via une connexion réseau sécurisée. L'application utilise une API PHP pour le traitement en backend, interfaçant avec une base de données MySQL pour la gestion des données. En choisissant le protocole HTTP pour sa simplicité et une compatibilité plus large, le système assure une communication transparente entre l'interface utilisateur et les appareils IoT. HomeNet Control vise à rendre la technologie de la maison intelligente plus accessible et gérable pour un large public.

## Plan de Développement sur 4 Semaines pour "HomeNet Control" - Un Système IoT Web pour la Gestion des Appareils Intelligents

### Semaine 1 : Configuration du Projet et Analyse des Besoins

#### Jour 1-2
- Configurer l'environnement de développement.
- Installer le serveur PHP (ex. : XAMPP), MySQL, IDEs/éditeurs de code.

#### Jour 3-4
- Définir les exigences détaillées du projet (fonctionnalités, types de widgets, interactions utilisateurs).

#### Jour 5-7
- Concevoir le schéma de la base de données MySQL.
- Planifier la communication du microcontrôleur ESP32 avec l'API PHP.

### Semaine 2 : Développement Backend et Intégration Microcontrôleur

#### Jour 8-10
- Développer le backend PHP et les points de terminaison de l'API.

#### Jour 11-12
- Développer le code pour l'ESP32 pour envoyer/recevoir des requêtes HTTP.
- Assurer l'interaction de l'ESP32 avec la base de données MySQL.

#### Jour 13-14
- Tester l'intégration entre l'ESP32, l'API PHP et MySQL.
- Résoudre les problèmes de connectivité et d'échange de données.

### Semaine 3 : Développement Frontend

#### Jour 15-17
- Créer les modèles HTML et CSS (mise en page principale, page d'accueil, inscription/connexion utilisateur, tableau de bord).

#### Jour 18-20
- Implémenter JavaScript pour l'interactivité et les appels AJAX au backend PHP.

#### Jour 21
- Intégrer le frontend avec le backend.
- Assurer que les actions des utilisateurs sur le site déclenchent les réponses correctes du backend à l'ESP32.

### Semaine 4 : Tests, Débogage et Déploiement

#### Jour 22-24
- Réaliser des tests approfondis du système (frontend, backend, base de données, microcontrôleur).

#### Jour 25-26
- Corriger les bugs découverts lors des tests.
- Optimiser les performances.

#### Jour 27-28
- Préparer le déploiement (configurer le serveur de production, assurer la sécurité, finaliser la documentation).

#### Jour 29-30
- Déployer l'application web.
- Surveiller le système pour les problèmes immédiats et apporter des corrections rapides.

