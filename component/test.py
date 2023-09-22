import pytest
import bip39

def test_create_recovery_phrase():
    # Test avec un nombre de mots valide
    try:
        bip39.create_recovery_phrase(12, "en")
    except Exception:
        pytest.fail("Expected no exception for valid word count")

    # Test avec un nombre de mots en dehors de l'intervalle [12, 15, 18, 21, 24]
    with pytest.raises(ValueError):
        bip39.create_recovery_phrase(10, "en")

def test_validate_recovery_phrase():
    # Test avec une phrase mnémonique vide
    with pytest.raises(ValueError):
        bip39.validate_recovery_phrase("", "en")

    # Test avec une phrase mnémonique valide
    recovery_phrase = bip39.create_recovery_phrase(15, "en")
    assert bip39.validate_recovery_phrase(recovery_phrase, "en") == True

    # Test avec une phrase mnémonique invalide
    invalid_phrase = "invalid phrase here"
    assert bip39.validate_recovery_phrase(invalid_phrase, "en") == False

def test_extract_entropy():
    # Test de l'extraction de l'entropie d'une phrase de récupération
    recovery_phrase = bip39.create_recovery_phrase(18, "en")
    entropy = bip39.extract_entropy(recovery_phrase, "en")
    assert len(entropy) == 64  # 64 caractères hexadécimaux

if __name__ == "__main__":
    pytest.main()

