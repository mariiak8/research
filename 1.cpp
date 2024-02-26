#include <iostream>
#include <vector>

// Функция для проверки, можно ли поставить число в данную позицию
bool isValid(std::vector<std::vector<int>>& grid, int row, int col, int num) {
    int n = grid.size();
    
    // Проверяем строку и столбец на наличие повторяющихся чисел
    for (int i = 0; i < n; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Проверяем секцию sqrt(n) x sqrt(n) на наличие повторяющихся чисел
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Функция для решения судоку
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // Если клетка пустая, пробуем в нее поставить числа от 1 до n
            if (grid[row][col] == 0) {
                for (int num = 1; num <= n; num++) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;
                        
                        // Рекурсивный вызов функции solveSudoku для следующей клетки
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        
                        // Если решение не найдено, отмечаем клетку как пустую и продолжаем перебор
                        grid[row][col] = 0;
                    }
                }
                
                // Если не удалось найти подходящее число, возвращаем false
                return false;
            }
        }
    }
    
    // Если все клетки заполнены, решение найдено
    return true;
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> grid(n, std::vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> grid[i][j];
        }
    }
    
    if (!solveSudoku(grid)) {
        std::cout << "Invalid field" << std::endl;
        return 0;
    }
    
    // Выводим решение
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
