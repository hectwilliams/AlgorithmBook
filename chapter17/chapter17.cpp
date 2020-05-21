#include <iostream>
#include <math.h>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <numeric> // accumulate
#include <stdio.h> 
#include <stdlib.h>
#include <sstream>
#include <tuple>
#include <deque>
#include <exception>
#include <memory>
#include <chrono>
#include <mutex>
#include <future>
#include <iomanip>
#include <errno.h>
#include <string.h>
#include "chpater17.h"
extern int errno;

namespace chapter17 {

	/*Edge List Methods*/

	template <typename T, typename E_v>
	std::string ELGraph<T, E_v>::AddVertex( T value) {
		std::string key = std::to_string(n++);

		if (vertex_map.count(key) == 0)
			vertex_map.insert({key, value});
		return key;
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::RemoveVertex(std::string id) {
		EL_Node<E_v> *node = nullptr;
		int prev_index = -1;

		try {
			
			if (!vertex_map.count(id))
				throw "vertex not found";

			// remove vertex 
			vertex_map.erase(id);

			// remove links 
			for (int i = 0; i < el_node_list.size(); ) {
				node = el_node_list[i];
				
				//increment
				if (node->src != id && node->dest != id) {
					prev_index = i++;
				}

				//delete node 
				if (node->dest == id || node->src == id) {
					delete node;
					el_node_list.erase(el_node_list.begin() + i);
				} 

			}
			
			return prev_index != -1;
			
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E_v>
	std::tuple<T, bool> ELGraph<T, E_v>::GetVertexValue(std::string id) {
		try {
			return { vertex_map.at(id), true };
		} catch (...) {
			return { T(NULL), false };
		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::SetVertexValue(std::string id, int value) {
		try {
			vertex_map.at(id) = value;
			return true;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::AddEdge(std::string id1, std::string id2, E_v value) {
		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";
			
			for (auto node : el_node_list) {
				if ( node->src == id1 && node->dest == id2) {
					throw "edge found in graph";
				}
			}

			el_node_list.push_back(el_node(id1, id2, value));

			return true;

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E_v>
	EL_Node<E_v>* ELGraph<T, E_v>::el_node(std::string src, std::string dest, E_v val) {
		return new EL_Node<E_v>{src, dest, val};
	}

	template <typename T, typename E_v>
	void ELGraph<T, E_v>::RemoveEdges(std::string id) {
		EL_Node<E_v> *node;
		bool hasEdge;

		for (int i = 0; i < el_node_list.size(); ) {
			node = el_node_list[i];
			hasEdge = (node->src == id || node->dest == id);

			if (!hasEdge) {
				i++;
			} else {
				delete node; 
				el_node_list.erase(el_node_list.begin() + i);
			}

		}
	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::RemoveEdge(std::string id1, std::string id2) {
		EL_Node<E_v> *node;

		try {
			
			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];

				if (node->src == id1 && node->dest == id2) {
					delete node; 
					el_node_list.erase(el_node_list.begin() + i);
					return true;
				}

			}

			throw "edge not found";
		
		} catch (...) {

			return false;
		
		}
		
	}

	template <typename T, typename E_v>
	std::tuple<E_v, bool> ELGraph<T, E_v>::GetEdgeValue(std::string id1, std::string id2) {
		EL_Node<E_v>* node;

		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if ( node->src == id1 && node->dest == id2 ) {
					return {node->value, true};
				}
			}

			throw "edge not found";
		
		} catch (...) {

			return {E_v(NULL), false};
		
		}

	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::SetEdgeValue(std::string id1, std::string id2, E_v value) {
		EL_Node<E_v>* node = nullptr;
		bool state = false;

		try {

			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";

			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if (node->src == id1 && node->dest == id2) {
					node->value = value;
					return true;
				}
			}

			throw "edge not found";

		} catch (...) {

			return false;

		}

	}

	template <typename T, typename E_v>
	bool ELGraph<T, E_v>::Adjacent(std::string id1, std::string id2) {
		EL_Node<E_v>* node;

		try {
			if (vertex_map.count(id1) == 0 || vertex_map.count(id2) == 0)
				throw "vertex not found";
			
			for (int i = 0; i < el_node_list.size(); i++) {
				node = el_node_list[i];
				if (node->src == id1 && node->dest == id2) {
					return true;
				}
			}

			throw "edge not found";

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E_v>
	std::vector<std::string> ELGraph<T, E_v>::Neighbors(std::string id) {
		std::vector<std::string> result; 

		for (auto node : el_node_list) {
			if (node->src == id)
				result.push_back(node->dest);
		}
		return result;
	}

	template class ELGraph<int, int>;
	template class ELGraph<int, std::string>;
	template class ELGraph<std::string, std::string>;
	template class ELGraph<std::string, int>;


	/*Adjacency Map Methods*/
	template <typename T, typename E>
	void AMGraph<T, E>::Grid() {
		for (auto collection : map) {
			std::cout <<  "[  "  << "NAME - " << collection.second->value  << "\t ID  " << collection.second->id << "  ]"<< "\n";
			for (auto it = collection.second->neighbors.begin(); it != collection.second->neighbors.end(); it++) {
				std::cout << "\t dest " << it->first << "\t edge value: " << it->second << "\n";
			}
			printf("\n");
		}
	}

	template <typename T, typename E>
	std::string AMGraph<T, E>::AddVertex(T value) {
		std::string key = std::to_string(n++);
		map.insert({key, am_node(key, value)});	 // insert key/node pair

		if (matrix_en) {
			for (auto rev_it = map.rbegin(); rev_it != map.rend(); rev_it++) {
				for (auto obj : map) {
					if (obj.second->neighbors.count(rev_it->first) == 0) {
						obj.second->neighbors.insert({ rev_it->first, E{} });
					}
				}
			}
		}
		return key;
	}

	template <typename T, typename E>
	bool AMGraph<T, E>::RemoveVertex(std::string id) {

		try {
			
			if (map.count(id) == 0)
				throw "vertex not found";

			// remove links to vertex
			for (auto obj : map) {
				if (map.find(obj.first)->second->neighbors.count(id)) {
					map.find(obj.first)->second->neighbors.erase(id);
				}
			}

			// remove vertex
			delete map.find(id)->second;
			map.erase(id);

			return true;
		} catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	std::tuple<T, bool> AMGraph<T,E>::GetVertexValue(std::string id) {
		try {

			if (!map.count(id))
				throw "vertex not found";

			return { map.find(id)->second->value ,true };
		
		} catch (...) {

			return { T{}, false };

		}

	}


	template <typename T, typename E>
	bool AMGraph<T, E>::SetVertexValue(std::string id, T value) {
		try {

			if (map.count(id) == 0)
				throw "vertex does not exist";

			map.find(id)->second->value = value;
			
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	bool AMGraph<T,E>::AddEdge(std::string id1, std::string id2, E value) {
		try {

			if (id1 == id2)
				throw "vertex cannot move back to itself";

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = value; // valid route
		
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	void AMGraph<T,E>::RemoveEdges(std::string id) {
		if (map.count(id) == 0)
			return; 

		
		for (auto obj: map) {

			// clear direct routes to id
			if (obj.second->neighbors.count(id) ) {
				obj.second->neighbors.at(id) = E{};
			}
			
			//clear undirected routes to id
			if (obj.first == id) {
				for (auto it = map.find(obj.first)->second->neighbors.begin(); it != map.find(obj.first)->second->neighbors.end(); it++)
					it->second = E{};
			}
		}
	}


	template <typename T, typename E>
	bool AMGraph<T, E>::RemoveEdge(std::string id1, std::string id2) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = E{}; 
		} catch (...) {
			return false;
		}
	}


	template <typename T, typename E>
	std::tuple<E, bool> AMGraph<T, E>::GetEdgeValue(std::string id1, std::string id2) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			return { map.find(id1)->second->neighbors.at(id2), true };

		} catch (...) {

			return std::make_tuple(E{}, false);

		}

	}


	template <typename T, typename E>
	bool AMGraph<T, E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {

			if (!map.count(id1) || !map.count(id2))
				throw "vertex not found";

			map.find(id1)->second->neighbors.at(id2) = value;

			return true;

		} catch (...) {

			return false;

		}

	}

	template <typename T, typename E>
	bool AMGraph<T, E>::Adjacent(std::string id1, std::string id2) {
		try {

			if (map.count(id1) == 0 || map.count(id2) == 0)
				throw "vertex not found";

			if (map.find(id1)->second->neighbors.at(id2) == E{})
				throw "edge not found";
			
			return true;

		} catch (...) {

			return false;

		}
	}

	template <typename T, typename E>
	std::vector<std::string> AMGraph<T,E>::Neighbors(std::string id) {
		std::vector<std::string> result; 

		if (map.count(id) == 0)
			return result;

		for (auto it = map.find(id)->second->neighbors.begin(); it != map.find(id)->second->neighbors.end(); it++) {
			if (it->second != E{}) {
				result.push_back(it->first);
			}
		}
	}

	template class AMGraph<int, int>;
	template class AMGraph<int, std::string>;
	template class AMGraph<std::string, std::string>;
	template class AMGraph<std::string, int>;

	template <typename T, typename E>
	bool ALGraph<T, E>::AddEdge(std::string id1, std::string id2, E value) {
		
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				this->map.find(id1)->second->neighbors.insert({ id2, E{} }); // new directed edge  
			
				this->map.find(id1)->second->neighbors.at(id2) = value;
			return true;
		}
		catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	void ALGraph<T, E>::RemoveEdges(std::string id) {
		if (this->map.count(id)) {

			for (auto obj : this->map) {
				if (obj.second->neighbors.count(id))
					obj.second->neighbors.erase(id);
			}

		}
	}




	template<typename T, typename E>
	bool ALGraph<T, E>::RemoveEdge(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge does not exist";

			this->map.find(id1)->second->neighbors.erase(id2);
			
			return true;
		}
		catch (...) {
			return false;
		}
	}


	template<typename T, typename E>
	std::tuple<E, bool> ALGraph<T, E>::GetEdgeValue(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";

			return { this->map.find(id1)->second->neighbors.at(id2), true };
		}
		catch (...) {
			return { NULL, false };
		}
	}


	template<typename T, typename E>
	bool ALGraph<T,E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {
			
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			
			this->map.find(id1)->second->neighbors.at(id2) = value;
			return true;

		} catch (...) {
			
			return false;
		
		}
	}

	template<typename T, typename E>
	bool ALGraph<T, E>::Adjacent(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex does not exist";
			return this->map.find(id1)->second->neighbors.count(id2);
		} catch (...) {
			return false;
		}
	}

	template<typename T, typename E>
	std::vector<std::string> ALGraph<T,E>::Neighbors(std::string id) {
		std::vector<std::string> result;

		if (this->map.count(id) == 0)
			return result;

		for (auto it = this->map.find(id)->second->neighbors.begin(); it != this->map.find(id)->second->neighbors.end(); it++)
			result.push_back(it->first);

		return result;
	}

	template <typename T, typename E>
	std::vector <std::string> ALGraph<T, E>::EasyToGetThere() {
		int in_count, out_count; 
		std::string to_id, from_id;
		std::vector<std::string> IDs;
		std::vector<std::string > result;

		for (auto obj: this->map) {

			in_count = 0;
			out_count = 0;
			from_id = obj.first;

			for (auto obj_neighbor: obj.second->neighbors) {
				to_id = obj_neighbor.first;
				in_count++;
				out_count += this->map.find(from_id)->second->neighbors.count(to_id);

				if (in_count > out_count)
					result.push_back(from_id);
			}

		}

		return result;

	}

	template <typename T, typename E>
	bool ALGraph<T, E>::IsDAG(void *ptr) {
		std::map<std::string, std::string> visited;
		std::string curr_tail;

		try {
			for (auto from_obj : this->map) {
				if (from_obj.second->neighbors.size() > 1) {		// tx edge count > 1 
					throw "more than one edge from vertex";
				} else if (from_obj.second->neighbors.size() == 1) {		// tx edge count  == 1
					visited.insert({ from_obj.second->neighbors.begin()->first , from_obj.first}); 
				} else if (from_obj.second->neighbors.size() == 0) { // no tx edges 
					if (curr_tail.length() == 0) {
						visited.insert({ from_obj.first, "" });
						curr_tail = from_obj.first;
					} else {
						throw "multiple tail nodes";
					}
				}
			}

			//back propagation
			if (ptr) {
				while (curr_tail.length()) {
					((std::vector<std::string>*) ptr)->insert(((std::vector<std::string>*) ptr)->begin(), curr_tail);
					curr_tail = visited.at(curr_tail);
				}
			}
			
			return true;

		} catch (...) {

			return false;
		}
	
	}

	template <typename T, typename E>
	std::vector<std::string>  ALGraph<T,E>::DAGToArray() {
		std::vector<std::string> result;
		IsDAG(&result);
		return result;
	}

	template class ALGraph<int, int>;
	template class ALGraph<int, std::string>;
	template class ALGraph<std::string, std::string>;
	template class ALGraph<std::string, int>;

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::AddEdge(std::string id1, std::string id2, E value) {
		try {

			if (id1 == id2)
				throw "vertex cannot point to vertex";
			if ( this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			if (value == E{})
				throw "invalid edge value";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0) {
				this->map.find(id1)->second->neighbors.insert({ id2, E{} });	// 1 -> 2 
				this->map.find(id2)->second->neighbors.insert({ id1, E{} });	// 2 -> 1
			}

			this->map.find(id1)->second->neighbors.at(id2) = value;
			this->map.find(id2)->second->neighbors.at(id1) = value;

			return true;
		
			} catch (...) {
			
			return false;

		}

	}

	template <typename T, typename E>
	void ALGraph_UnDir<T, E> ::RemoveEdges (std::string id) {
		// remove edges to 
		for (auto obj : this->map) {
			if (obj.second->neighbors.count(id)) {
				obj.second->neighbors.erase(id);
			}
		}

		// remove edges from 
		this->map.find(id)->second->neighbors.clear();
	}


	template <typename T, typename E>
	bool ALGraph_UnDir<T, E> ::RemoveEdge(std::string id1, std::string id2) {
		try {
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			if (this->map.find(id1)->second->neighbors.count(id2)) {
				this->map.find(id1)->second->neighbors.erase(id2);
				this->map.find(id2)->second->neighbors.erase(id1);
			}
			return true;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	std::tuple<E, bool> ALGraph_UnDir<T,E>::GetEdgeValue(std::string id1, std::string id2) {
		try {
			
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			
			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			return  { this->map.find(id1)->second->neighbors.at(id2), true };

		} catch (...) {

			return  { E{}, false };

		}

	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::SetEdgeValue(std::string id1, std::string id2, E value) {
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			this->map.find(id1)->second->neighbors.at(id2) = value;

			return  true;

		} catch (...) {

			return  false;

		}

	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::Adjacent(std::string id1, std::string id2) {
		try {

			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";

			if (this->map.find(id1)->second->neighbors.count(id2) == 0)
				throw "edge not found";

			return true;

		} catch (...) {

			return  false;

		}
	}

	template <typename T, typename E>
	std::vector<std::string> ALGraph_UnDir<T, E>::Neighbors(std::string id) {
		std::vector<std::string> result;

		if (this->map.count(id) == 0)
			return result;
		
		for (auto it = this->map.find(id)->second->neighbors.begin(); it != this->map.find(id)->second->neighbors.end(); it++) {
			result.push_back(it->first);
		}
		return result;
	}

	template <typename T, typename E>
	bool ALGraph_UnDir<T, E>::SomeoneOntheInside (std::string my_id, std::vector<std::string> employees_ids) {
		std::map<std::string, bool> visited;
		std::vector< AM_Node_Vertex<T, E>*> stack;
		AM_Node_Vertex<T, E> *node = nullptr;
		std::string ERROR_MSG = "no friends at company";
		std::string curr_id, manager_id = "10";

		try {

			for (auto id: employees_ids) {
				//stack.clear();

				if (this->map.count(id) == 0) // employee not in my social network
					continue; 

				if (this->map.find(id)->second->neighbors.count(my_id) == 0)  // employee is not my friend 
					continue;

				if (visited.count(id) != 0) // already visited (id) vertex
					continue; 

				visited.insert({ id, true });		// mark visited employee-id


				// search for #10 aka Yoda part of innner circle
				stack.push_back(this->map.find(id)->second);	// add employee-id (i.e. node) to stack
				
				while (stack.size()) {

					node = stack.front();
					std::cout << node->id << " visited new " << "\n";
					stack.erase(stack.begin());

					if (node->id == manager_id) // found "employee"
						return true;


					for (auto obj : node->neighbors) {
						curr_id = obj.first;
						if (visited.count(curr_id) == 0) {	// if not visited add to front of stack
							visited.insert({ curr_id, true });		// mark visited employee-id
							stack.insert(stack.begin(), this->map.find(curr_id)->second);
						}
					}
				}
			}
			throw ERROR_MSG;
		} catch (...) {
			return false;
		}
	}

	template <typename T, typename E>
	std::string ALGraph_UnDir<T, E>::SomeoneOntheInside(std::vector<std::string> employees_ids) {
		
		// search manager id - using two points of reference  

		std::map <std::string, bool> visited;
		std::vector<AM_Node_Vertex<T,E>*> stack_A, stack_B;
		AM_Node_Vertex<T,E> *node_A = nullptr, *node_B = nullptr;
		std::string id_upper, id_lower, curr_id;

		std::string  manager_id = "10";
		std::string ERROR_MSG = "no friends at company";
		int  ptrA = 0, ptrB = employees_ids.size() - 1;

		try {
				
			while (ptrB >= ptrA) {
				id_upper = employees_ids[ptrA++];
				id_lower = employees_ids[ptrB--];

				if (this->map.count(id_upper) ) { // id in graph 
					stack_A.push_back(this->map.find(id_upper)->second);
					visited.insert({ id_upper, true });
				}

				if (this->map.count(id_lower)) {	// id in graph {
					stack_B.push_back(this->map.find(id_lower)->second);
					visited.insert({ id_lower, true });
				}

				while (stack_A.size() || stack_B.size()) {
					node_B = nullptr;
					node_A = nullptr;

					// insert vertex to stack 
					// ..upper
					if (stack_A.size()) {
						node_A = stack_A.front();
						stack_A.erase(stack_A.begin());
					}

					//.. lower
					if (stack_B.size()) {
						node_B = stack_B.front();
						stack_B.erase(stack_B.begin());
					}

					// insert 'non-visited' neighbors of vertcies 
					//..A
					if (node_A) {
						for (auto obj: node_A->neighbors) {
							curr_id = obj.first;
							if (visited.count(curr_id) == 0) {
								visited.insert({ curr_id, true });				// non- visited employee--vertex-id
								if (curr_id == manager_id) {
									throw  "employee " + node_A->id + "\ will recommend you to manager \t \t \n";
								}
								stack_A.insert(stack_A.begin(), this->map.find(curr_id)->second);
							}
						}
					}

					// insert 'non-visited' neighbors of vertcies 
					//..B
					if (node_B) {
						for (auto obj : node_B->neighbors) {
							curr_id = obj.first;
							if (visited.count(curr_id) == 0) {
								visited.insert({ curr_id, true });			// non- visited employee--vertex-id
								if (curr_id == manager_id) {
									throw  "employee " + node_B->id + "\ will recommend you to manager \t \t \n";
								}
								stack_B.insert(stack_B.begin(), this->map.find(curr_id)->second);
							}
						}
					}
					
				}

			}
	
			throw ERROR_MSG;

		} catch (const std::string &msg) {

			return msg;
		
		}

	}

	template <typename T, typename E>
	void  ALGraph_UnDir<T, E>::VertexIsReachable(std::string id1, std::string id2, std::vector<std::string> &path_list, std::map<std::string, bool>& visited, AM_Node_Vertex<T,E> * node ) {

		if (!node) {
			node = this->map.find(id1)->second;
			path_list.push_back(node->id);
		}

		if (visited.count(node->id) || node->id == id2)
			return; 

		visited.insert({ node->id , true });

		for (auto obj : node->neighbors) {
			if (visited.count(obj.first) == 0) {
				path_list.push_back(obj.first);
				VertexIsReachable(id1, id2, path_list, visited, this->map.find(obj.first)->second);

				if (path_list.back() != id2)
					path_list.pop_back();
			}
		}
	}

	template <typename T, typename E>
	std::vector<std::string>  ALGraph_UnDir<T, E>::VertexIsReachable(const std::string &id1, const std::string &id2) {
		std::vector<std::string> pathList; 
		std::map<std::string, bool> visited;
	
			if (this->map.count(id1) == 0 || this->map.count(id2) == 0)
				throw "vertex not found";
			
			 VertexIsReachable(id1, id2, pathList, visited);

			return pathList;
	}


	template <typename T, typename E>
	void ALGraph_UnDir<T, E>::AllPaths(const std::string& target, std::vector<std::vector<std::string>> &paths, std::vector<std::string> path, std::set<std::string>& visited, AM_Node_Vertex<T, E>* node) {
		
		if (node->id == target) { // found target
			printf(" \t how   %s \n", node->id.c_str());
			paths.push_back(path);
			return;
		}

		if (visited.count(node->id))
			return; 

		visited.insert(node->id);

		for (auto obj: node->neighbors) {
			if (visited.count(obj.first) == 0) {
				path.push_back(obj.first);
				AllPaths(target, paths, path, visited, this->map.find(obj.first)->second);
				path.pop_back();
			}
		}

	}


	template <typename T, typename E>
	std::vector<std::vector<std::string>> ALGraph_UnDir<T, E>::AllPaths(const std::string& id1, const std::string& id2) {
		std::vector<std::vector<std::string>> paths;
		std::vector<std::string> currPath;
		std::set<std::string> visited;

		if (this->map.count(id1) == 0)
			return paths;

		currPath.push_back(id1);

		AllPaths(id2, paths, currPath, visited, this->map.find(id1)->second);
		
		return paths;
	}

	template <typename T, typename E>
	std::vector<std::string> ALGraph_UnDir<T,E>::ShortestPath(const std::string id1, const std::string id2) {
		std::vector<std::string> path;
		AM_Node_Vertex<T, E>* node = nullptr; 
		std::vector< AM_Node_Vertex<T, E>*> queue;
		std::map < std::string, std::string> visited;
		std::string vertexID;


		if (this->map.count(id1) && this->map.count(id2)) {
			node = this->map.find(id1)->second;
			queue.push_back(node);
			visited.insert({ node->id, "" });

			while (queue.size()) {
				node = queue.front();
				queue.erase(queue.begin());

				if (node->id == id2) {
					vertexID = node->id;
					break;
				}

				for (auto obj : node->neighbors) {
					if (visited.count(obj.first) == 0) {
						visited.insert({ obj.first, node->id });
						queue.push_back(this->map.find(obj.first)->second);
					}
				}

			}

			while (vertexID.length()) {  // backtrace to vertex-id;
				path.push_back(vertexID);
				vertexID =  visited.at(vertexID);
			}

		}
	
		return path;
	}

	template <typename T, typename E> 
	std::vector<std::string> ALGraph_UnDir<T,E>::GimmieNSteps(const std::string id1, const std::string id2, int n ) {
		std::map<std::string, int> visited;
		AM_Node_Vertex<T, E>* node = nullptr;
		std::vector< AM_Node_Vertex<T, E>*> queue;
		std::vector<std::string> IDs;

		if (!(this->map.count(id1) && this->map.count(id2) )) 
			return IDs;

		node = this->map.find(id1)->second;
		visited.insert({ node->id, 0 });
		queue.push_back(node);

		while (queue.size()) {
			node = queue.front();
			queue.erase(queue.begin());

			if (visited.at(node->id) <= n)
				IDs.push_back(node->id);

			for (auto obj : node->neighbors) {
				if (visited.count(obj.first) == 0) {
					visited.insert({ obj.first, visited.at(node->id) + 1 });
					queue.push_back(this->map.find(obj.first)->second);
				}
			}
		}
		
			return IDs;
	}


	template class ALGraph_UnDir<int, int>;
	template class ALGraph_UnDir<int, std::string>;
	template class ALGraph_UnDir<std::string, std::string>;
	template class ALGraph_UnDir<std::string, int>;

	void SocialNetwork_ALGraph_UnDir_Test() {

		ALGraph_UnDir<std::string, int> graph;    

		{
			graph.AddVertex("Me");	// 0
			graph.AddVertex("A");		// 1
			graph.AddVertex("B");		// 2
			graph.AddVertex("C");		// 3
			graph.AddVertex("F");		// 4

			graph.AddVertex("R");		// 5
			graph.AddVertex("Q");		// 6
			graph.AddVertex("T");		// 7
			graph.AddVertex("Z");		// 8
			graph.AddVertex("O");		// 9

			graph.AddVertex("manager"); // 10  

			graph.AddEdge("0", "1", 1);

			graph.AddEdge("1", "2", 1);
			graph.AddEdge("1", "3", 1);
			graph.AddEdge("1", "4", 1);
			graph.AddEdge("1", "5", 1);

			graph.AddEdge("5", "6", 1);
			graph.AddEdge("5", "7", 1);
			graph.AddEdge("5", "8", 1);
			graph.AddEdge("5", "9", 1);

			graph.AddEdge("9", "10", 1);

			std::cout << graph.SomeoneOntheInside({"1","2","3","4","5","6"}) << '\n';  // found manager
			
			ALGraph<std::string, int> dir_graph;   

			dir_graph.AddVertex("Me");
			dir_graph.AddVertex("a");
			dir_graph.AddVertex("b");
			dir_graph.AddVertex("c");

			dir_graph.AddEdge("0", "1", 1);
			dir_graph.AddEdge("1", "2", 1);
			dir_graph.AddEdge("2", "3", 1);

			dir_graph.IsDAG();  // true
			for (auto x : dir_graph.DAGToArray()) { // print DAG
				std::cout << x << "\t";
			}
		}

	}

}