

---

# Module BIP39 : Génération de Seed Phrases pour Portefeuilles de Cryptomonnaies



Le module BIP39 est une bibliothèque de cryptographie permettant de créer des phrases de récupération (seed phrases) pour les portefeuilles de cryptomonnaies. Elle s'appuie sur le standard BIP39 (Bitcoin Improvement Proposal 39), une norme de sécurité clé pour les cryptomonnaies.

## Aperçu

Ce module facilite la génération de phrases de récupération, également connues sous le nom de "mnemonic phrases". Ces phrases permettent de récupérer l'accès à un portefeuille de cryptomonnaie en mémorisant une liste de mots. Les phrases de récupération ont généralement une longueur de 12 à 24 mots, ce qui les rend faciles à retenir.

## Fonctionnalités Principales

Le module BIP39 propose les fonctionnalités suivantes :

- **Génération de Phrases de Récupération** : Vous pouvez créer une phrase de récupération en spécifiant le nombre de mots souhaités (12, 15, 18, 21 ou 24) ainsi que la langue (français ou anglais).

- **Validation de Phrases de Récupération** : Vous pouvez vérifier si une phrase de récupération est valide et correspond à un portefeuille.

## Cas d'Utilisation Courants

Ce module est utile dans les situations suivantes :

- **Création de Portefeuilles** : Il permet de générer une phrase de récupération lors de la création d'un nouveau portefeuille de cryptomonnaie.

- **Récupération de Portefeuilles** : Un utilisateur peut retrouver l'accès à son portefeuille en saisissant sa phrase mnémonique s'il perd son portefeuille ou les informations d'accès.

## Interface

L'interface du module BIP39 est conçue pour être simple et directe. Elle propose deux fonctions principales :

- `create_recovery_phrase(word_quantity, language)`: Cette fonction crée une phrase de récupération avec un nombre spécifique de mots dans la langue spécifiée.

- `validate_recovery_phrase(recovery_phrase, language)`: Cette fonction vérifie si une phrase de récupération est valide pour la langue spécifiée.

## Gestion des Erreurs

Le module BIP39 gère les erreurs comme suit :

- Lors de la création d'une phrase de récupération, une exception est déclenchée si le nombre de mots spécifié n'est pas dans l'intervalle autorisé (12, 15, 18, 21, 24) ou si la langue spécifiée n'est pas prise en charge.

- Lors de la validation d'une phrase de récupération, une exception est déclenchée si la phrase est vide ou si elle ne correspond pas à un portefeuille valide pour la langue spécifiée.

## Exécution des Tests

Pour exécuter les tests du module BIP39, utilisez la commande suivante :

```bash
python -m pytest test_bip39.py
```

Les tests vérifieront toutes les fonctions de l'interface du module et s'assureront qu'elles fonctionnent correctement en renvoyant les résultats attendus.

---

