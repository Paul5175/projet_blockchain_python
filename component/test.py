import pytest
import bip39

# Générer une clé privée aléatoire
private_key = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"

# Générer une suite mnémonique depuis la clé privée
mnemonic_phrase = bip39.create_mnemonic_from_private_key(private_key, "en")

# Convertir la suite mnémonique en clé privée
converted_private_key = bip39.convert_to_private_key(mnemonic_phrase, "en")

# Vérifier que la clé privée convertie est égale à l'originale
assert private_key == converted_private_key

