//	1. Удаление недостижимых состояний
//	2. Минимизация ДКА, не содержащего недостижимых состояний
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>

using namespace std;
// Определение ДКА
string X = "ijnmk/$"; // Входной алфавит
map<int, vector<int> > M // Функция-словарь переходов
{
	{0, {9, 9, 1, 3, 9, 9, 9, 9}},
	{1, {3, 5, 9, 9, 9, 9, 9, 9}},
	{2, {9, 9, 1, 5, 9, 9, 9, 9}},
	{3, {9, 4, 6, 9, 9, 9, 9, 9}},
	{4, {9, 9, 9, 1, 7, 9, 9, 9}},
	{5, {9, 4, 8, 9, 9, 9, 9, 9}},
	{6, {9, 9, 9, 4, 9, 6, 7, 9}},
	{7, {9, 9, 9, 9, 9, 9, 9, 9}},
	{8, {9, 9, 9, 4, 9, 8, 7, 9}},
	{9, {9, 9, 9, 9, 9, 9, 9, 9}}
};
int N = M.size() - 1;
int i_state = 1; // Начальное состояние
set<int> F{ 7 }; // Заключительные состояния

set<pair<int, int>> same_states;		// Хранит одинаковые состояния
set<pair<int, int>> eliminated_states;  // Хранения исключенные состояния

void print_fm(string title) // Вывод на ДКА экран
{
	cout << title << endl;
	cout << "X = \"" << X << "\"" << endl;
	cout << "M =\n{" << endl;
	for (auto& [i, set] : M) {
		cout << "\t" << i << ": ";
		for (int el : set) cout << el << " ";
		cout << endl;
	}
	cout << "}" << endl;
	cout << "i_state = " << i_state << endl;
	cout << "F = ";
	for (int el : F) cout << el << " ";
	cout << endl;
}

void remove_unreachable_states()
{
	set<int> reachable_states;
	queue<int> q;
	q.push(i_state);
	reachable_states.insert(i_state);
	while (!q.empty()) {
		int current_state = q.front();
		q.pop();						// Удаляет передний эл. из очереди q
		for (int next_state : M[current_state])
			if (reachable_states.find(next_state) == reachable_states.end()) {
				reachable_states.insert(next_state);
				q.push(next_state);		// Добавляет next_state в очередь q
			}
	}
	map<int, vector<int>> new_M;
	for (auto const& [state, transitions] : M)
		if (reachable_states.count(state)) new_M[state] = transitions;	// Проверка, является ли state достижимым состоянием
	M = new_M;
}

void create_pairs_state()
{
	set<pair<int, int>> final_state;		// Структура данных, но в этом случае каждый элемент является парой целых чисел.
	//  Сохряняем пары, где одно состояние конечное
	for (const auto& [f1, _] : M) for (const auto& [f2, _] : M)
		if ((F.count(f1) && !F.count(f2)) || (F.count(f2) && !F.count(f1)))
			final_state.insert(make_pair(f1, f2));
	eliminated_states.insert(final_state.begin(), final_state.end());	// Объеденяем пары в одну структуру данных


	// Сохраняем отличимые пары
	set<pair<int, int>> different_states;	// Пары целых чисел, представляющих состояния, которые различны друг от друга.
	for (int i = 0; i < X.size(); ++i)
		for (const auto& [f1, _] : M) for (const auto& [f2, _] : M)
			if (M[f1][i] != N && M[f2][i] == N)
				different_states.insert(make_pair(f1, f2));
	eliminated_states.insert(different_states.begin(), different_states.end());


	// Удаляем зеркальные пары
	set<pair<int, int>> unique_pairs;
	for (const auto& [second, first] : eliminated_states)
		if (unique_pairs.find(make_pair(first, second)) == unique_pairs.end()) // Проверяем, есть ли зеркальная пара в множестве
			unique_pairs.insert(pair<int, int>(second, first));
	eliminated_states = unique_pairs;		// Оставляем только уникальные пары без зеркальных


	// Находим неотличимые пары
	for (const auto& [f1, _] : M) for (const auto& [f2, _] : M) {
		if (f1 == f2 || f1 > f2) continue;			// Исключаем пары с одинаковыми числами и пары, где f1 > f2
		same_states.insert(make_pair(f1, f2));
	}
	for (const auto& pair : eliminated_states) same_states.erase(pair);  // Удаляем из всех возможных пар отличимымые и с заключительными состояниями
}

void minimization_fm()	// Минимизируем ДКА
{
	map<int, vector<int>> min_M;
	for (const auto& pair : same_states) min_M[pair.first] = M[pair.first];
	for (const auto& pair : eliminated_states) {
		bool is_first = true;        // Для отслеживания, содержится ли первый элемент во всех парах из структуры данных eliminated_states
		for (int i = 0; i <= M.size() - 1; i++) {
			if (i >= pair.first) continue;
			if (eliminated_states.find(make_pair(pair.first, i)) == eliminated_states.end()) {
				is_first = false;
				break;
			}
		}
		// Если первое число стоит в паре с каждым из чисел, копируем его блок новый M
		if (is_first) min_M[pair.first] = M[pair.first];
	}
	for (auto& [state, transitions] : min_M)
		for (size_t i = 0; i < transitions.size(); ++i)		// Проходим по каждому состоянию в transitions используя индексы
			for (const auto& pair : same_states)
				if (transitions[i] == pair.second) transitions[i] = pair.first;     // Заменяем его на первое число в паре
	M = min_M;
}

int main()
{
	print_fm(" Initial DKA");

	remove_unreachable_states();
	print_fm(" DKA without unattainable states");

	create_pairs_state();
	minimization_fm();
	print_fm(" Min DKA");
}