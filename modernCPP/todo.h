/// <summary>
/// https://herbsutter.com/2013/05/29/gotw-89-solution-smart-pointers/
/// 
/// 
/// https://herbsutter.com/welcome-to-the-jungle/
/// a. Unified : Every pointer (or object reference) can address every byte, and every byte is equally “far away” from the core.
///					-- locality
///					-- how well “hot” data fits into cache
///       NUMA : retains a single chunk of RAM, but adds multiple caches
///					-- two cores that share an L2 cache vs. two cores that share only L3 or RAM
///					-- layout matters,  on the same cache line because we have to keep data physically close together if it’s used together
///					--  to avoid the ping-pong game of false sharing
/// b. Morre law
/// 
/// </summary>