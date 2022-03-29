//
// Created by Mouaad Labhairi on 3/20/22.
//

#ifndef CONTAINERS_NODE_HPP
#define CONTAINERS_NODE_HPP

namespace ft
{
	struct pairs
	{
		int key;
		int value;
	};

	class Node
	{
	public:
		pairs	*pair;
		Node	*right;
		Node	*left;
		int 	height;
	};
}


#endif //CONTAINERS_NODE_HPP
