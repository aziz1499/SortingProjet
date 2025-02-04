#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// je commence par Générer une liste de 5 nombres aléatoires entre 1 et 50 en utilisant sfml dans mon dossier
std::vector<int> generateRandomNumbers() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 50);
    std::vector<int> numbers;
    for (int i = 0; i < 5; ++i) {
        numbers.push_back(distrib(gen));
    }
    return numbers;
}

// ici j'ai commencé à Dessiner les cercles avec SFML
void drawCircles(sf::RenderWindow& window, const std::vector<int>& numbers) {
    window.clear();
    float x = 100.0f; // j'ai declaré le x en tant que ma position de depart pour mon cercle 
    for (size_t i = 0; i < numbers.size(); ++i) {
        float radius = static_cast<float>(numbers[i]);
        sf::CircleShape circle(radius);
        circle.setPosition(x, 300.0f - radius); // Positionner le cercle
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineThickness(2.0f);
        circle.setOutlineColor(sf::Color::White);
        window.draw(circle);
        x += 2 * radius + 20.0f; // Espacement entre les cercles
    }
    window.display();
}

// maintenant je commence a faire mon Algorithmes de tri
// tri a bulle
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
// tri par insertion 
void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
// tri fusion 
void mergeSort(std::vector<int>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Fusionner les deux moitiés
        std::vector<int> temp(right - left + 1);
        size_t i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }
            else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (size_t p = 0; p < k; ++p) {
            arr[left + p] = temp[p];
        }
    }
}
// le tri rapide 
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
//finalement je finalise la creeation de ma fentere  
int main() {
    sf::RenderWindow window(sf::VideoMode(900, 500), "Sortingproject");
    std::vector<int> numbers = generateRandomNumbers();
  //ici je commence a faire des test grace a la methode sinon 'if' et la boucle 'while' pour faire lire a la console que chaque bouton touché en clavier contient un tri
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B) {
                    bubbleSort(numbers);
                }
                else if (event.key.code == sf::Keyboard::I) {
                    insertionSort(numbers);
                }
                else if (event.key.code == sf::Keyboard::M) {
                    mergeSort(numbers, 0, numbers.size() - 1);
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    quickSort(numbers, 0, numbers.size() - 1);
                }
                else if (event.key.code == sf::Keyboard::R) {
                    numbers = generateRandomNumbers();
                }
            }
        }
        drawCircles(window, numbers);
    }

    return 0;
}