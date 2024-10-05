class TreeNode:
    def __init__(self, id, parent=None, children=None):
        self.id = id                    # ID of the node
        self.parent = parent            # Parent node (None if it's the root)
        self.children = children or []  # List of children nodes

def getTreeNode(id, parent, children):
    return TreeNode(id, parent, children)

def rootTree(graph, rootId=0):
    # Create the root node with no parent and an empty list of children
    root = getTreeNode(rootId, None, [])
    # Build the tree by traversing the graph and assigning child-parent relationships
    return buildTree(graph, root, None)

def buildTree(graph, node, parent):
    for childId in graph[node.id]:
        if parent and childId == parent.id:  # Avoid traversing back to the parent(avoid cycles)
            continue
        # Create a new tree node for the child, setting the current node as the parent
        child = getTreeNode(childId, node, [])
        # Add this child node to the current node's children
        node.children.append(child)
        # Recursively build the subtree rooted at this child
        buildTree(graph, child, node)
    return node

# finding tree center
def getTreeNode():
    print("hi")

def getTreeCenters():
    print("hi")

#
def getTreeHigh():
    print("hi")
    
    
def isTreeIsomorphic():
    print("hi")