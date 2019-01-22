/// <summary>
/// 1. Each node is either red or black, this can be saved in memory as a single bit (e.g. 'red' = 1, 'black' = 0).
/// 2. The root of the tree is always black.
/// 3. All leaves are null and they are black.
/// 4. If a node is red, then its parent is black.
/// 5. Any path from a given node to any of its descendant leaves contains the same amount of black nodes.This is sometimes known as the black - depth.
/// 6. The height of the red - black tree is at most 2log(n+1); this property will be proven later.
/// </summary>