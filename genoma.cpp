#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

const int TAM = 3000;

struct Node {
    string seq;
    Node* next;
    bool printed;
    Node(string s) : seq(s), next(nullptr), printed(false) {}
};

class HashTable {

    vector<Node*> table;

    int hash(string seq) const {
        int valore = 0;
        int base;
        for (char c : seq) {
            
            if(c == 'A') base = 0;
            if(c == 'C') base = 1;
            if(c == 'G') base = 2;
            if(c == 'T') base = 3;

            valore = valore * 4 + base;
        }
        return valore % table.size();
    }

public:
    HashTable(int size = TAM) : table(size, nullptr) {}

    ~HashTable() {
        for (auto head : table) {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }


    void insert(string seq) {
        int index = hash(seq);
        Node* newNode = new Node(seq);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void resp() {

        ofstream arquivo("saida_meuexemplo.txt"); //mudar o nome do arquivo caso queira usar gerar outro arquivo

        for (auto head : table) {
            Node* current = head;
            while (current != nullptr) {
                if (!current->printed) {
                    int count = 0;

                    Node* atual = current;
                    while (atual != nullptr) {
                        if (atual->seq == current->seq) {
                            count++;
                            atual->printed = true; 
                        }
                        atual = atual->next;
                    }
                    arquivo << current->seq << ": " << count << " ocorrencias" << endl;
                }
                current = current->next;
            }
        }

        arquivo.close();
    }
};

int main() {
    HashTable tabela;

    ifstream arquivo("./genoma_diferente.txt"); //mudar aqui o caminho do arquivo caso queira usar outro

    if (!arquivo) {
        return -1;
    }

    vector<string> linhas;
    string linha;
    
    while (getline(arquivo, linha)) {
        if (!linha.empty())
            linhas.push_back(linha);
    }
    arquivo.close();

    for (const auto &l : linhas) {
        for (long long i = 0; i + 5 < l.length(); i += 6) {
            string bloco = l.substr(i, 6);
            tabela.insert(bloco);
        }
    }
    tabela.resp();

    system("Pause");
    return 0;
}
