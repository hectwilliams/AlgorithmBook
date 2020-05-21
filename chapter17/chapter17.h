#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <string_view>
#include <tuple>
#include <memory>
//#include <thread>
#include <mutex>
#include <future>

#ifndef CHAPTER17_H
#define CHAPTER17_H

namespace chapter17 {

	template <typename T>
	struct EL_Node {
		std::string src;
		std::string dest;
		T value;
	};

	template <class T, class E_v>
	class ELGraph {

	private:
		int n = 0;
		int size = 0; 
		std::map<std::string, T> vertex_map;
		std::vector<EL_Node<E_v>*> el_node_list;

		EL_Node<E_v>* el_node(std::string src, std::string dest, E_v val);
	public:
		ELGraph()
		{}
		~ELGraph()
		{
			while (el_node_list.size()) {
				delete el_node_list.front();
				el_node_list.erase(el_node_list.begin());
			}
		}
		std::string AddVertex(T value);
		bool RemoveVertex(std::string id);
		std::tuple<T, bool> GetVertexValue(std::string id);
		bool SetVertexValue(std::string id, int value);
		bool AddEdge(std::string id1, std::string id2, E_v value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E_v, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E_v value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
	};

	template <class T, class E>
	struct AM_Node_Vertex {
		std::string id;
		T value;
		std::map<std::string, E> neighbors;
	};

	template <class T, class E>
	class AMGraph {

	private:
		AM_Node_Vertex<T, E>* am_node(std::string id, T value) {
			return new AM_Node_Vertex<T, E>{ id, value };
		}

	protected:
		int n = 0;  
		int size = 0; 
		bool matrix_en; 
		std::map<std::string, AM_Node_Vertex<T, E>*> map;

	public:
		AMGraph(): matrix_en{true}
		{}
		
		~AMGraph() 
		{
			while (map.size()) {
				delete map.begin()->second;
				map.erase(map.begin());
			}
		}

		void Grid();
		std::string AddVertex(T value);
		bool RemoveVertex(std::string id);
		std::tuple<T, bool> GetVertexValue(std::string id);
		bool SetVertexValue(std::string id, T value);
		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);

	};

	template <class T, class E>
	class ALGraph: public AMGraph<T, E> {

	public:
		ALGraph() {
			this->matrix_en = false;
		}

		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
		std::vector <std::string> EasyToGetThere();
		bool IsDAG(void *ptr = nullptr);
		std::vector<std::string> DAGToArray();
	};

	template <class T, class E>
	class ALGraph_UnDir : public AMGraph<T, E> {

	public:
		ALGraph_UnDir() {
			this->matrix_en = false;
		}

		bool AddEdge(std::string id1, std::string id2, E value);
		void RemoveEdges(std::string id);
		bool RemoveEdge(std::string id1, std::string id2);
		std::tuple<E, bool> GetEdgeValue(std::string id1, std::string id2);
		bool SetEdgeValue(std::string id1, std::string id2, E value);
		bool Adjacent(std::string id1, std::string id2);
		std::vector<std::string> Neighbors(std::string id);
		bool SomeoneOntheInside(std::string my_id, std::vector<std::string> employees_ids);  // Stack [Depth First]
		std::string SomeoneOntheInside(std::vector<std::string> employees_ids);  
		std::vector<std::string> VertexIsReachable(const std::string& id1, const std::string& id2);  // recursion instead of Stack [Depth First]
		std::vector<std::vector<std::string>> AllPaths(const std::string& id1, const std::string& id2);  
		std::vector<std::string> ShortestPath(const std::string id1, const std::string id2);
		std::vector<std::string> GimmieNSteps(const std::string id1, const std::string id2, int n = 0);
	
	private:
		void  VertexIsReachable(std::string id1, std::string id2, std::vector<std::string> &path_list, std::map<std::string, bool> &visited, AM_Node_Vertex<T, E> *node = nullptr);
		void  AllPaths(const std::string& target, std::vector<std::vector<std::string>> &paths, std::vector<std::string> path, std::set<std::string> &visited, AM_Node_Vertex<T, E>* node = nullptr);

	};
	void SocialNetwork_ALGraph_UnDir_Test();
}

#endif