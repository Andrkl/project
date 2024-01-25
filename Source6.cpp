#include <iostream>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* getNode() {
    TrieNode* newNode = new TrieNode;
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}

void insertWord(TrieNode* root, const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = getNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

void autoComplete(TrieNode* root, const string& prefix) {
    TrieNode* node = root;
    for (char ch : prefix) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            cout << "Нет подходящих слов\n";
            return;
        }
        node = node->children[index];
    }
    vector<string> suggestions;
    findWords(node, prefix, suggestions);
    if (suggestions.empty()) {
        cout << "Нет подходящих слов\n";
    }
    else {
        cout << "Подходящие варианты:\n";
        for (const string& word : suggestions) {
            cout << word << "\n";
        }
    }
}

void findWords(TrieNode* node, const string& prefix, vector<string>& suggestions) {
    if (node->isEndOfWord) {
        suggestions.push_back(prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            char ch = 'a' + i;
            findWords(node->children[i], prefix + ch, suggestions);
        }
    }
}

int main() {
    vector<string> dictionary = { "apple", "banana", "ball", "cat", "dog", "duck", "elephant" };

    TrieNode* root = getNode();

    for (const string& word : dictionary) {
        insertWord(root, word);
    }

    string prefix;
    while (true) {
        cout << "Введите часть слова (или 'x' для выхода): ";
        cin >> prefix;
        if (prefix == "x") {
            break;
        }
        autoComplete(root, prefix);
    }

    return 0;
}