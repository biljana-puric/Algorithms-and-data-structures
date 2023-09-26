#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Tree {
	string key;
	int grade = 0;
	vector<int>grades;
	Tree* parent = nullptr;
	
public:
	vector<Tree*>children;
	Tree() = default;
	Tree(string s) :key(s) {};
	string get_key() const { return key; }
	int get_grade() const { return grade; }
	Tree* get_parent() const { return parent; }
	Tree* add_answer(string s);
	Tree* search_answer (string s);
	void add_grade();
	void add_grades(int grade);
	void sort_answers();
	void print_answers();
	void delete_answer();
	int count_answers();
};

Tree* Tree::add_answer(string s) {
	Tree* newNode = new Tree();
	newNode->grade = 0;
	newNode->key = s;
	newNode->parent = this;
	return newNode;
}

Tree* Tree::search_answer(string s) {
	stack<Tree*> nodes;
	nodes.push(this);
	while (!nodes.empty()) {
		Tree* curr = nodes.top();
		nodes.pop();
		if (curr != NULL) {
			if (curr->get_key() == s) {
				return curr;
			}
			int n = curr->children.size();
			for (int i = n-1; i >= 0; i--) {
				nodes.push(curr->children[i]);
			}
		}
	}
	return nullptr;
}

void Tree::add_grade() {
	cout << "Unesite ocenu. " << endl;
	int ocena;
	cin >> ocena;
	grade += ocena;
}
void Tree::add_grades(int grade) {
	grades.push_back(grade);
}

void Tree::sort_answers() {
	stack<Tree*> nodes;
	nodes.push(this);
	while (!nodes.empty()) {
		Tree* curr = nodes.top();
		nodes.pop();
		if (curr != NULL) {
			int n = curr->children.size();
			for (int k = 0; k < n-1; k++) {
				for (int j = k+1; j < n; j++) {
					if (curr->children[k]->get_grade() < curr->children[j]->get_grade()) {
						Tree* tmp = curr->children[k];
						curr->children[k] = curr->children[j];
						curr->children[j] = tmp;
					}
				}
			}
			for (int i = n - 1; i >= 0; i--) {
				nodes.push(curr->children[i]);
			}
		}
	}
	sort(grades.begin(), grades.end(), greater<int>());
}

void Tree::print_answers() {
	stack<Tree*> nodes;
	stack<int>levels;
	int level = 0;
	nodes.push(this);
	levels.push(level);
	while (!nodes.empty()) {
		Tree* curr = nodes.top();
		int l = levels.top();
		nodes.pop();
		levels.pop();
		if (curr != NULL) {
			for (int k = 0; k < l; k++) {
				cout << "\t";
			}
			cout << curr->get_key() << endl;;
			int n = curr->children.size();
			level++;
			for (int i = n - 1; i >= 0; i--) {
				nodes.push(curr->children[i]);
				levels.push(level);
			}
		}
	}
}

void Tree::delete_answer() {
	stack<Tree*> nodes;
	nodes.push(this);
	while (!nodes.empty()) {
		Tree* curr = nodes.top();
		nodes.pop();
		if (curr != nullptr) {
			int n = curr->children.size();
			for (int i = n - 1; i >= 0; i--) {
				nodes.push(curr->children[i]);
			}
			Tree* parents = curr->get_parent();
			string s = curr->get_key();
			int m = parents->children.size();
			for (int i = 0; i < m ; i++) {
				if (parents->children[i]->get_key() == s) {
					delete parents->children[i];
					for (int j = i + 1; j < m; j++) {
						parents->children[i] = parents->children[j];
					}
					m--;
					parents->children.resize(m);
				}
			}
		}
	}

}

int Tree::count_answers() {
	int count = 0;
	stack<Tree*> nodes;
	nodes.push(this);
	while (!nodes.empty()) {
		Tree* curr = nodes.top();
		nodes.pop();
		if (curr != NULL) {
			count++;
			int n = curr->children.size();
			for (int i = n - 1; i >= 0; i--) {
				nodes.push(curr->children[i]);
			}
		}
	}
	return count;
}

string readLine() {
	string s;
	getline(cin, s);
	return s;
}

Tree* search_roots(vector<Tree> &roots, string q) {
	int n = roots.size();
	for (int i = 0; i < n; i++) {
		if (roots[i].get_key() == q) {
			return &roots[i];
		}
	}
	return nullptr;
}

void print_questions(vector<Tree> roots) {
	int n = roots.size();
	for (int i = 0; i < n; i++) {
		cout << roots[i].get_key() << endl;
	}
}

int main() {

	int zahtev;
	cout << " 1. Kreiraj stablo. " << endl;
	cout << " 2. Dodaj pitanje. " << endl;
	cout << " 3. Dodaj odgovor ili komentar. " << endl;
	cout << " 4. Pretrazi pitanje. " << endl;
	cout << " 5. Pretrazi odgovor. " << endl;
	cout << " 6. Povecaj ocenu. " << endl;
	cout << " 7. Uredi odgovore. " << endl;
	cout << " 8. Ispisi sva pitanja. " << endl;
	cout << " 9. Ispisi pitanje i njegove odgovore. " << endl;
	cout << " 10. Obrisi odgovor ili komentar. " << endl;
	cout << " 11. Obrisi pitanje. " << endl;
	cout << " 12. Pretrazi pitanje sa najvise odgovora. " << endl;
	vector<Tree>roots;
	while (true) {
		cin >> zahtev;
		switch (zahtev)
		{
		case 0: return 0;
		case 1: {
			vector<Tree>roots;
			break;
		}
		case 2: {
			cout << "Unesite pitanje. " << endl;
			cin.ignore();
			string s = readLine();
			Tree root(s);
			roots.push_back(root);
			break;
		}
		case 3: {
			cout << "Na koje pitanje ili odgovor dodajete odgovor? " << endl;
			cin.ignore();
			string s = readLine();
			int k = 0;
			Tree* question = search_roots(roots, s);
			if (question != nullptr) {
				cout << "Unesite odgovor. " << endl;
				string s = readLine();
				Tree* newNode = question->add_answer(s);
				question->children.push_back(newNode);
				k++;
			}
			else {
				int n = roots.size();
				for (int i = 0; i < n; i++) {
					Tree* answer = roots[i].search_answer(s);
					if (answer != nullptr) {
						cout << "Unesite odgovor. " << endl;
						string s = readLine();
						Tree* newNode = answer->add_answer(s);
						answer->children.push_back(newNode);
						k++;
						break;
					}
				}
			}
			if (k == 0) {
				cout << "Pitanje ili odgovor koji ste uneli ne postoji." << endl;
			}
			break;
		}
		case 4: {
			cout << "Unesite pitanje koje trazite. " << endl;
			string q = readLine();
			Tree* question = search_roots(roots, q);
			break;
		}
		case 5: {
			cout << "Unesite pitanje koje trazite. " << endl;
			string q = readLine();
			Tree* question = search_roots(roots, q);
			if (question != nullptr) {
				cout << "Unesite odgovor koje trazite. " << endl;
				string s = readLine();
				Tree* answer = question->search_answer(s);
				if (answer == nullptr) {
					cout << "Takav odgovor ne postoji. " << endl;
				}
				else {
					cout << "Odgovor pronadjen." << endl;
				}
			}
			else {
				cout << "Takvo pitanje ne postoji. " << endl;
			}
			break;
		}
		case 6: {
			cout << "Koji odgovor ocenjujete? " << endl;
			cin.ignore();
			string s = readLine();
			int n = roots.size();
			for (int i = 0; i < n; i++) {
				Tree* answer = roots[i].search_answer(s);
				if (answer != nullptr) {
					answer->add_grade();
					int g = answer->get_grade();
					roots[i].add_grades(g);
					break;
				}
				else {
					cout << "Odgovor ne postoji." << endl;
				}
			}
			break;
		}
		case 7: {
			int n = roots.size();
			for (int i = 0; i < n; i++) {
				roots[i].sort_answers();
			}
			break;
		}
		case 8: {
			print_questions(roots);
			break;
		}
		case 9: {
			int n = roots.size();
			for (int i = 0; i < n; i++) {
				roots[i].print_answers();
			}
			break;
		}
		case 10: {
			cout << "Koji odgovor zelite da obrisete? " << endl;
			cin.ignore();
			string s = readLine();
			int n = roots.size();
			for (int i = 0; i < n; i++) {
				Tree* answer = roots[i].search_answer(s);
				if (answer != nullptr) {
					answer->delete_answer();
				}
				else {
					cout << "Odgovor ne postoji." << endl;
				}
			}
			break;
		}
		case 11: {
			cout << "Koje pitanje zelite da obrisete? " << endl;
			cin.ignore();
			string s = readLine();
			Tree* question = search_roots(roots, s);
			if (question != nullptr) {
				for (int i = 0; i < question->children.size(); i++) {
					question->children[i]->delete_answer();
				}
				int m = roots.size();
				string q = question->get_key();
				for (int i = 0; i < m; i++) {
					if (roots[i].get_key() == q) {
						roots.erase(roots.begin() + (i));
						break;
					}
				}
			}
			else {
				cout << "Takvo pitanje ne postoji." << endl;
			}
			break;
		}
		case 12: {
			int n = roots.size();
			int max = 0;
			int index = 0;
			for (int i = 0; i < n; i++) {
				int counter = roots[i].count_answers();
				if (counter > max) {
					max = counter;
					index = i;
				}
			}
			Tree question = roots[index];
			cout << "Pitanje sa najvecim brojem odgovora je: " << question.get_key();
			break;
		}
		default: break;
		}
	}
	return 0;
}