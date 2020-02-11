#include <vector>
#include <string>
#include <map>
#include <array>


#ifndef AALGO_H
#define ALGO_H

namespace chapter9
{
	int rgcf(int num1, int num2);
	void floodFill(int canvas2D[5][5], int startxy[2], const int& newColor, int target = -1);
	void floodFill_helper_printCanvas(const int canvas[5][5]);
	int rFib(int num, int a = 1, int b = 1, int counter = 0);
	bool rBinarySearch(std::vector<int> array, int target);
	int tarai(const int& x, const int& y, const int& z);
	void inOrderSubsets(std::string str);
	int GotAnyGrapes(std::vector<int> grapeBags, int& memo, int&& max = 0);
	int Collatz_apalooza(int num, int occurence = 1, int count = 0);
	void TelephoneWords(std::string telephoneNumber, std::string&& buffer = "", std::map <int, std::string> mapper = { {0, "O"},  {1, "I"}, {2, "ABC"}, {3, "DEF"}, {4, "GHI"}, {5, "JKL"}, {6,"MNO"}, {7,"PQRS"}, {8, "TUV"}, {9, "WXYZ"} });
	std::string RisingSquares(int num, int count = 1);
	void BinaryStringExpansion(std::string str, std::string buffer = "");
	void StringAnagrams(std::string&& str, std::string buffer = "");
	void climbingStairs(int footsteps, std::vector<std::vector<int>>& data, std::vector<int> buffer = {});
	void SumOfSquares(int num, std::vector<std::vector<int>>& combinations, std::vector<int> buffer = {}, double&& count = 1.0);
	void AllValidNPairsOfParens(int num, std::vector<std::string>& array, std::string buffer = "");
	void TowersofHanoi(int numOfDisks = -1, std::vector<std::vector<int>> poles = { {0,1,2}, {}, {}}, int value = 0, int &&depth = 0 );
	void IPAddresses(std::string digits, std::vector<int> buffer = {});
	void UnevenDigits(const int &num, std::string data = "", int index = 0);
	void GenerateAllPossibleCoinChange(int cents, std::vector< std::map<std::string, int>> &results, std::map<std::string, int> mapCents = { {"dimes", 0}, {"nickels", 0}, {"pennies", 0}, {"quarters", 0}});


	using array2_t = std::array<int, 2>;
	

	class Chess {

	private:

		int** board;
		int rowMax = 8;
		int colMax = 8;
		std::vector<array2_t> *freeblocks;

		void changeXY(int r, int c) {
			colMax = c;
			rowMax = r;
		}

		void initBoard() {
			if (board)
				boardRelease();

			board = new int* [rowMax];	// (row) of 8 int pointers 
			for (int i = 0; i < colMax; i++)
				board[i] = new int[colMax] {};	// (columns ) int pointer
		}

		void clearBoard() {
			freeblocks->clear();

			if (!board)
				return;

			for (int r{ 0 }; r < rowMax; r++) {
				for (int c{ 0 }; c < colMax; c++) {
					board[r][c] = 0;
					freeblocks->push_back({ r,c });
				}
			}
		}

		void boardRelease() {
			for (int i = rowMax; i--; ) {
				delete[] board[i];
			}
			delete[] board;
		}

		void insert(const array2_t& pos, const int& value) {
			this->board[pos[0]][pos[1]] = value; 
		}

		int& read(const array2_t& pos) {
			return this->board[pos[0]][pos[1]];
		}

		void boardFill(std::vector<array2_t> list) {
			clearBoard();
			for (auto pos : list)
				insert(pos, 1);
		}


		std::vector<array2_t> possiblePaths(std::vector<array2_t> list, int NQueens = 8, std::vector<array2_t> queens = {}, std::vector<array2_t> skip = {});

	public:
		Chess() : freeblocks{ new std::vector<array2_t>{} } {
			clearBoard();
		}

		~Chess() {
			boardRelease();
			delete freeblocks;
		}

		friend std::ostream& operator << (std::ostream& out, const Chess &chess) {
			out << '\n'<< '[' << "\t\n\t";
			for (int r{ 0 }; r < chess.rowMax; r++) {
				for (int c{ 0 }; c < chess.colMax; c++) {
					std::cout << '|' << chess.board[r][c];
				}
				std::cout << "|\n\t";
			}
			out << "\n]";
			return out;
		}

		std::vector<array2_t> getFreeBlocks( ) { 
			std::vector<array2_t> result; 
			for (int r = 0; r < rowMax; r++) {
				for (int c = 0; c < colMax; c++) {
					result.push_back({r, c});
				}
			}
			return result;
		};

		bool isChessMoveSafe(array2_t moveTo, array2_t queen);
		bool isChessMoveSafe(array2_t moveTo, std::vector<array2_t> queens);

		std::vector<array2_t> allSafeChessSquares(array2_t queen, std::vector<array2_t> list);
		std::vector<array2_t>  allSafeChessSquares(std::vector<array2_t> queens);
		std::vector<array2_t>  allSafeChessSquares(const int x, const int y);

		void Queens(std::vector<array2_t> list = {}, std::vector<array2_t> queens = {}, int n = 8);
		void NQueens(const int n, const int rLen, const int cLen);  // n = 13 rLen  = 13 cLen =13 largest N queens size to produce data

	};
}


namespace chapter10
{
	std::vector<std::string> StringToWordArray(std::string str);
}

#endif 
