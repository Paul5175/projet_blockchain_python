---

# Composant BIP39 - Transformation de Clé Privée en Mnémonique

Le composant BIP39 permet de créer une séquence de 24 mots mnémoniques, conformément à la norme BIP39, à partir d'une clé privée de 256 bits. Il offre également la possibilité de convertir une séquence mnémonique en une clé privée.

## Installation

1. Assurez-vous d'avoir Python 3.7 ou une version ultérieure installée sur votre système.

2. Installez les dépendances requises, notamment pybind11, en utilisant pip :

   ```
   pip install pybind11
   ```

3. Compilez le composant en exécutant la commande "make" à partir du répertoire contenant les fichiers source :

   ```
   make
   ```

4. Vous pouvez maintenant utiliser le composant en important le module "bip39" dans Python.

## Utilisation

### Génération d'une Séquence Mnémonique à partir d'une Clé Privée

```python
import bip39

cle_privee = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
sequence_mnemonique = bip39.create_mnemonic_from_private_key(cle_privee, "en")
print(sequence_mnemonique)
```

Assurez-vous que la variable "cle_privee" est une chaîne hexadécimale de 64 caractères, correspondant à une clé privée de 256 bits. La fonction "create_mnemonic_from_private_key" génère la séquence mnémonique correspondante.

### Conversion d'une Séquence Mnémonique en Clé Privée

```python
import bip39

sequence_mnemonique = "legal winner thank year wave sausage worth useful legal winner thank yellow"
cle_privee = bip39.convert_to_private_key(sequence_mnemonique, "en")
print(cle_privee)
```

La fonction "convert_to_private_key" prend en entrée une séquence mnémonique et renvoie la clé privée correspondante.

### Génération d'une Séquence Mnémonique Aléatoire

```python
import bip39

sequence_mnemonique = bip39.create_recovery_phrase(24, "en")
print(sequence_mnemonique)
```

Utilisez la fonction "create_recovery_phrase" pour générer une séquence mnémonique aléatoire avec le nombre de mots souhaité (12, 15, 18, 21 ou 24) et la langue spécifiée ("en" pour l'anglais, "fr" pour le français).

---
