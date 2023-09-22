
---

# Composant BIP39 - Transformateur de Clé Privée en Mnémonique

Le composant BIP39 permet de générer une suite de 24 mots mnémoniques conformément au standard BIP39 à partir d'une clé privée de 256 bits. Il offre également la possibilité de convertir une suite mnémonique en une clé privée.

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

### Génération d'une suite mnémonique depuis une clé privée

```python
import bip39

private_key = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
mnemonic_phrase = bip39.create_mnemonic_from_private_key(private_key, "en")
print(mnemonic_phrase)
```

Assurez-vous que `private_key` est une chaîne hexadécimale de 64 caractères correspondant à une clé privée de 256 bits. La fonction `create_mnemonic_from_private_key` génère la suite mnémonique correspondante.

### Conversion d'une suite mnémonique en clé privée

```python
import bip39

mnemonic_phrase = "legal winner thank year wave sausage worth useful legal winner thank yellow"
private_key = bip39.convert_to_private_key(mnemonic_phrase, "en")
print(private_key)
```

La fonction `convert_to_private_key` prend une suite mnémonique en entrée et renvoie la clé privée correspondante.

### Génération d'une suite mnémonique aléatoire

```python
import bip39

mnemonic_phrase = bip39.create_recovery_phrase(24, "en")
print(mnemonic_phrase)
```

Utilisez `create_recovery_phrase` pour générer une suite mnémonique aléatoire avec le nombre de mots souhaité (12, 15, 18, 21 ou 24) et la langue spécifiée ("en" pour l'anglais, "fr" pour le français).

---
