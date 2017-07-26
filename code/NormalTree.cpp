#include <iostream>
using namespace std;

typedef struct STreeNode* pSTreeNode;
typedef int TreeDataType;

struct STreeNode
{
	TreeDataType data;
	pSTreeNode pFirstChild;
	pSTreeNode pNextBrother;

	STreeNode( TreeDataType Value )
	{
		data = Value;
		pFirstChild = NULL;
		pNextBrother = NULL;
	}
}; 


class CTree
{
public:
	CTree();
	CTree( TreeDataType Value );
	~CTree();


public:
	void Insert( TreeDataType parentValue, TreeDataType Value );	//	parentValue：该节点的父结点；Value：该节点的值
	void InsertBrother( pSTreeNode pParentNode, TreeDataType Value );

	pSTreeNode Search( pSTreeNode pNode, TreeDataType Value );

	void Preorder( pSTreeNode pNode );		//	前序遍历
	void Inorder( pSTreeNode pNode );		//	中序遍历
	void postorder( pSTreeNode pNode );		//	后续遍历

	void PrintNode( pSTreeNode pNode );
	void FreeMemory( pSTreeNode pNode );	//	释放内存

	public:
	pSTreeNode pRoot;
};

CTree::CTree()
{
	pRoot = NULL;
}

CTree::CTree( TreeDataType Value )
{
	pRoot = new STreeNode( Value );
	if ( pRoot == NULL )
		return;
}

CTree::~CTree()
{
	if (pRoot == NULL )
		return;

	FreeMemory( pRoot );
}

void CTree::FreeMemory( pSTreeNode pNode )
{
	if ( pNode == NULL )
		return;

	if ( pNode->pFirstChild != NULL )
		FreeMemory( pNode->pFirstChild );

	if ( pNode->pNextBrother != NULL )
		FreeMemory( pNode->pNextBrother );
	
	delete pNode;
	pNode = NULL;
}

void CTree::Insert( TreeDataType parentValue, TreeDataType Value )
{
	if ( pRoot == NULL )
		return;

	pSTreeNode pFindNode = Search( pRoot, parentValue );
	if ( pFindNode == NULL )
		return;

	if ( pFindNode->pFirstChild == NULL )
	{
		pFindNode->pFirstChild = new STreeNode( Value );
		return;
	}
	else
	{
		InsertBrother( pFindNode->pFirstChild, Value );
		return;
	}
}

void CTree::InsertBrother( pSTreeNode pBrotherNode, TreeDataType Value )
{
	if ( pBrotherNode->pNextBrother != NULL )
		InsertBrother( pBrotherNode->pNextBrother, Value );
	else
	{
		pBrotherNode->pNextBrother = new STreeNode( Value );
		return;
	}

}

pSTreeNode CTree::Search( pSTreeNode pNode, TreeDataType Value )
{
	if ( pNode == NULL )
		return NULL;

	if ( pNode->data == Value )
		return pNode;

	if ( pNode->pFirstChild == NULL && pNode->pNextBrother == NULL )
		return NULL;
	else
	{
		if ( pNode->pFirstChild != NULL )
		{
			pSTreeNode pNodeTemp = Search( pNode->pFirstChild, Value );
			if ( pNodeTemp != NULL )
				return pNodeTemp;
			else
			{
				return Search( pNode->pNextBrother, Value );
			}
		}
		else
			return Search( pNode->pNextBrother, Value );
	}
}

void CTree::Preorder( pSTreeNode pNode )
{
	if (pNode == NULL)
		return;
	cout << " " << pNode->data << " ";
	
	Preorder( pNode->pFirstChild );
	Preorder( pNode->pNextBrother );
}

void CTree::Inorder( pSTreeNode pNode )
{
	if ( pNode == NULL )
		return;

	Inorder( pNode->pFirstChild );
	cout << " " << pNode->data << " ";
	Inorder( pNode->pNextBrother );
}

void CTree::postorder( pSTreeNode pNode )
{
	if ( pNode == NULL )
		return;

	postorder( pNode->pFirstChild );
	postorder( pNode->pNextBrother );
	cout << " " << pNode->data << " ";
}

int main()
{
	CTree* pTree = new CTree( 1 );
	if ( pTree == NULL )
		return 0;

	pTree->Insert( 1, 2 );
	pTree->Insert( 1, 3 );
	pTree->Insert( 1, 4 );
	pTree->Insert( 1, 5 );
	pTree->Insert( 1, 6 );
	pTree->Insert( 1, 7 );
	pTree->Insert( 4, 8 );
	pTree->Insert( 5, 9 );
	pTree->Insert( 5, 10 );
	pTree->Insert( 6, 11 );
	pTree->Insert( 6, 12 );
	pTree->Insert( 6, 13 );
	pTree->Insert( 10, 14 );
	pTree->Insert( 10, 15 );

	cout << "前序遍历：" << endl;
	pTree->Preorder( pTree->pRoot );
	cout << endl;

	cout << "中序遍历：" << endl;
	pTree->Inorder( pTree->pRoot );
	cout << endl;

	cout << "后序遍历：" << endl;
	pTree->postorder( pTree->pRoot );
	cout << endl;

	delete pTree;
	pTree = NULL;
	system("pause");
	return 1;
}