#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <bitset>
#include <fstream>
#include <cstring>
#include <pybind11/pybind11.h>

namespace py = pybind11;

using random_bytes_engine = std::independent_bits_engine<
    std::default_random_engine, CHAR_BIT, unsigned char>;

std::string generate_random_bytes(int length) {
    random_bytes_engine rbe;
    rbe.seed(time(nullptr));
    std::vector<unsigned char> data(length);
    std::generate(begin(data), end(data), std::ref(rbe));
    std::string result{};
    std::for_each(begin(data), end(data), [&](unsigned char c) {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2) << std::hex << int(c);
        result.append(stream.str());
    });

    return result;
}

const char* hex_char_to_bin(char c) {
    switch (std::toupper(c)) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default: throw std::invalid_argument("");
    }
}

std::string hex_str_to_bin_str(const std::string& hex) {
    std::string bin;
    for (unsigned i = 0; i != hex.length(); ++i) {
        bin += hex_char_to_bin(hex[i]);
    }
    return bin;
}

std::string bin_str_to_hex_str(const std::string& bin) {
    const char *end = bin.c_str() + bin.length();
    const char *cur = bin.c_str();
    size_t x = 0;
    while (cur != end && (*cur == '0' || *cur == '1')) {
        x <<= 1;
        x |= *cur == '1';
        cur++;
    }
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << x;
    return stream.str();
}

std::vector<std::string> get_words(std::string langage) {
    std::string file_name = "wordlists/";
    if (langage == "fr") {
        file_name += "french.txt";
    } else {
        file_name += "english.txt";
    }
    std::vector<std::string> words;

    std::ifstream input_stream(file_name);
    if (input_stream.is_open()) {
        std::string word;

        while (std::getline(input_stream, word)) {
            words.push_back(word);
        }
        input_stream.close();
    } else {
        // Gérer l'erreur si le fichier n'est pas ouvert correctement
    }

    return words;
}

std::string create_checksum(const std::string& entropy_sequence, int checksum_bits) {
    std::string entropy_sha256 = sha256(hex_str_to_bin_str(entropy_sequence));
    std::string sha256_bin = hex_str_to_bin_str(entropy_sha256);
    return sha256_bin.substr(0, checksum_bits);
}

std::string convert_to_recovery_phrase(const std::string& checksum_sequence, const std::vector<std::string>& words_dict) {
    std::vector<std::string> v;

    for (size_t i = 0; i < checksum_sequence.length(); i += 11) {
        auto sub = checksum_sequence.substr(i, 11);
        auto word = words_dict[std::stoi(sub, nullptr, 2)];
        v.push_back(word);
    }

    std::string result = std::accumulate(std::next(v.begin()), v.end(), v[0], [](std::string a, std::string b) {
        return std::move(a) + " " + b;
    });

    return result;
}

std::string create_random_entropy(int entropy_bits) {
    std::string random_bytes_hex = generate_random_bytes(entropy_bits / 8);
    return random_bytes_hex;
}

std::string create_recovery_phrase(int word_quantity, const std::string& language) {
    std::vector<int> POSSIBLE_WORD_COUNT = {12, 15, 18, 21, 24};

    if (std::find(POSSIBLE_WORD_COUNT.begin(), POSSIBLE_WORD_COUNT.end(), word_quantity) == POSSIBLE_WORD_COUNT.end()) {
        throw std::invalid_argument("The number of words wanted must be in [12, 15, 18, 21, 24] interval");
    }

    int checksum_bits = (word_quantity * 11) % 32;
    int entropy_bits = (word_quantity * 11) - checksum_bits;

    auto entropy_sequence = create_random_entropy(entropy_bits);
    entropy_sequence = hex_str_to_bin_str(entropy_sequence);
    auto checksum_sequence = create_checksum(entropy_sequence, checksum_bits);

    std::vector<std::string> words_dict = get_words(language);

    return convert_to_recovery_phrase(entropy_sequence + checksum_sequence, words_dict);
}

std::string extract_entropy(const std::string& recovery_phrase, const std::string& language) {
    std::vector<std::string> words_dict = get_words(language);

    std::stringstream ss(recovery_phrase);
    std::string buf;
    std::vector<std::string> words;

    while (ss >> buf) {
        words.push_back(buf);
    }

    std::string words_string_binary;
    int word_count = words.size();

    for (const std::string& w : words) {
        auto it = std::find(words_dict.begin(), words_dict.end(), w);

        if (it == words_dict.end()) {
            throw std::invalid_argument("The word: " + w + " is not in the wordlist!");
        }

        words_string_binary += std::bitset<11>(std::distance(words_dict.begin(), it)).to_string();
    }

    std::string words_without_checksum = words_string_binary.substr(0, words_string_binary.length() - word_count);
    std::string result;

    for (size_t i = 0; i < words_without_checksum.length(); i += 8) {
        result += bin_str_to_hex_str(words_without_checksum.substr(i, 8));
    }

    return result;
}

bool validate_recovery_phrase(const std::string& recovery_phrase, const std::string& language) {
    if (recovery_phrase.empty()) {
        throw std::invalid_argument("Empty phrase");
    } else {
        std::string extracted_entropy = extract_entropy(recovery_phrase, language);
        std::string recreated_phrase = create_recovery_phrase(extracted_entropy.length() / 2 / 4, language);

        return recovery_phrase == recreated_phrase;
    }
}

PYBIND11_MODULE(bip39, m) {
    m.def("create_recovery_phrase", &create_recovery_phrase, "Creates a new mnemonic phrase");
    m.def("validate_recovery_phrase", &validate_recovery_phrase, "Validates if a mnemonic phrase exists");
}
