#include "stdafx.h"
#include "Node.h"
//#include "Transformation.h"

Node::Node()
{
}


Node::~Node()
{
}




//////////////////////////////////////////////////////////////////////////
void Node::Translate(Vec3f offsetVector, int flag){
	if (flag==TRANS_GROUP_CENTRE)
	{
	}
	else if (flag==TRANS_INDIVIDUAL)
		if (hasNodes)
		{
			for (unsigned int i = 0; i < Spatials.size();i++)
			{
				//Nodes[i]->Translate(offsetVector, TRANS_GROUP_PIVOT);
			}
		}
		if (hasModels)
		{
		}
	{
	}
}

void Node::Rotate(Vec3f angles, Vec3f axis, int flag){
}

void Node::Scale(Vec3f scaleVector, int flag){
}

//////////////////////////////////////////////////////////////////////////
//L-system

void Node::replace(Node &pNode){
	Spatials.clear();
	///*Spatials*/.push_back(pNode.Spatials);
}

//void Node::setPivot2Root(){
//	setPivot(root);
//}