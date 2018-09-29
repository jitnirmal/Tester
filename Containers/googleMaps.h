#pragma once
#include <unordered_map>
#include <random>
#include <map>
#include <iostream>

/// <summary>
/// https://tessil.github.io/2016/08/29/benchmark-hopscotch-map.html
/// When memory usage must be low and allocation smooth, sparse_hash_map is the clear choice. 
/// uses quadratic probing built on top of a dynamic array. 
/// At sparse_hash_map‘s default load factor of 0.8,
/// a conventional array-backed quadratic probing scheme ‘wastes’ 20% of allocated memory
/// Rehashes are the only allocation hiccup in this scheme.
/// 
/// 
/// In the opposite case where throughput is of paramount importance, dense_hash_map shines. 
/// It maintains a 0.5 load factor and stores entries in a regular C array
///  which means it has to pay for all the buckets it addresses (not just the ones it uses) and also leaves half of them empty. 
/// 
/// unless you properly allocate the initial table size, you will be forced to suffer catastrophically slow resizes
/// 
/// Performance
/// In general, the performance of a hash table is affected a number of factors :
/// 1. Choice of hash function
/// 2. Distribution of key values
/// 3. Load factor thresholds
/// 4. Resize factor
/// 
/// </summary>
