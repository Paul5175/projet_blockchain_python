import pytest
import bip39

# Test de validation
def test_validate_recovery_phrase():
    # Phrase mnémonique valide
    mnemonic_phrase = "legal winner thank year wave sausage worth useful legal winner thank yellow"
    assert bip39.validate_recovery_phrase(mnemonic_phrase, "en") is True

    # Phrase mnémonique invalide
    invalid_phrase = "invalid phrase here"
    assert bip39.validate_recovery_phrase(invalid_phrase, "en") is False

    # Phrase mnémonique vide
    with pytest.raises(ValueError):
        bip39.validate_recovery_phrase("", "en")

# Test fonctionnel
def test_functional_create_and_convert():
    # Générer une clé privée aléatoire
    private_key = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"

    # Générer une suite mnémonique depuis la clé privée
    mnemonic_phrase = bip39.create_mnemonic_from_private_key(private_key, "en")

    # Convertir la suite mnémonique en clé privée
    converted_private_key = bip39.convert_to_private_key(mnemonic_phrase, "en")

    # Vérifier que la clé privée convertie est égale à l'originale
    assert private_key == converted_private_key

if __name__ == "__main__":
    pytest.main()
