

---

# Composant BIP39 - Transformateur de Clé Privée en Mnémonique

Le composant BIP39 est un outil polyvalent permettant de générer des suites mnémoniques conformes au standard BIP39 à partir de clés privées cryptographiques. De plus, il offre la possibilité de convertir ces suites mnémoniques en clés privées d'origine. Ce composant est conçu pour être utilisé avec Python grâce à l'intégration pybind11.

## Installation

1. Assurez-vous d'avoir Python 3.7 ou une version ultérieure installée sur votre système.

2. Installez les dépendances requises, notamment pybind11. Vous pouvez l'installer via pip :

   ```
   pip install pybind11
   ```

3. Compilez le composant en utilisant le Makefile fourni :

   ```
   make
   ```

4. Vous pouvez maintenant utiliser le composant depuis Python en important le module `bip39`.

## Utilisation

### Génération d'une Suite Mnémonique depuis une Clé Privée

```python
import bip39

private_key = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
mnemonic_phrase = bip39.create_mnemonic_from_private_key(private_key, "en")
print(mnemonic_phrase)
```

Assurez-vous que `private_key` est une chaîne hexadécimale de 64 caractères correspondant à une clé privée de 256 bits. La fonction `create_mnemonic_from_private_key` génère la suite mnémonique correspondante.

### Conversion d'une Suite Mnémonique en Clé Privée

```python
import bip39

mnemonic_phrase = "legal winner thank year wave sausage worth useful legal winner thank yellow"
private_key = bip39.convert_to_private_key(mnemonic_phrase, "en")
print(private_key)
```

La fonction `convert_to_private_key` prend une suite mnémonique en entrée et renvoie la clé privée correspondante.

### Génération d'une Suite Mnémonique Aléatoire

```python
import bip39

mnemonic_phrase = bip39.create_recovery_phrase(24, "en")
print(mnemonic_phrase)
```

Utilisez `create_recovery_phrase` pour générer une suite mnémonique aléatoire avec le nombre de mots souhaité (12, 15, 18, 21 ou 24) et la langue spécifiée ("en" pour l'anglais, "fr" pour le français).

## Fonctions du Composant BIP39

Le composant BIP39 propose plusieurs fonctions pour faciliter la gestion des clés privées cryptographiques et des séquences mnémoniques. Voici un aperçu de ces fonctions :

### `create_mnemonic_from_private_key(private_key: str, language: str) -> str`

Cette fonction prend une clé privée de 256 bits (sous forme de chaîne hexadécimale de 64 caractères) en entrée et génère une suite mnémonique de 24 mots conformément au standard BIP39. Elle renvoie la séquence mnémonique générée.

### `convert_to_private_key(mnemonic_phrase: str, language: str) -> str`

La fonction `convert_to_private_key` effectue l'opération inverse. Elle prend une séquence mnémonique valide en entrée et retrouve la clé privée d'origine. La clé privée est renvoyée sous forme de chaîne hexadécimale.

### `create_recovery_phrase(word_quantity: int, language: str) -> str`

Cette fonction génère une suite mnémonique aléatoire avec le nombre de mots spécifié (12, 15, 18, 21 ou 24) et dans la langue spécifiée ("en" pour l'anglais, "fr" pour le français). Elle est utile pour la création de nouvelles clés privées ou de sauvegardes sécurisées.

---
